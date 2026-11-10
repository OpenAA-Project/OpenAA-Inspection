#include "XOnnx.h"
#include <QImage>
#include <QElapsedTimer>
#include <QDebug>
#include <QDir>
#include <omp.h> // Required for OpenMP
#include "XDataInLayer.h"
#include <windows.h>

BarcodeEnhancer::BarcodeEnhancer(LayersBase *base,const QString& modelPath,const QString& ONNXSystemPath, bool useCUDA)
    : ServiceForLayers(base),
      m_env(ORT_LOGGING_LEVEL_WARNING, "BarcodeSuperResolution"),
      m_memoryInfo(Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault))
{
	DllPath = GetLayersBase()->GetSystemPath() +QDir::separator()+ ONNXSystemPath;
	wchar_t	dllPathName[1024];
	memset(dllPathName,0,sizeof(dllPathName));
	DllPath.toWCharArray(dllPathName);
	SetDllDirectoryW(dllPathName);


    // Suppress unnecessary CPU thread creation
    m_sessionOptions.SetIntraOpNumThreads(1);

    // Configure Execution Providers based on the useCUDA flag
    if (useCUDA) {
        // ==========================================
        // Enable TensorRT & CUDA for GPU Optimization
        // ==========================================
		QString cachePath = GetLayersBase()->GetUserPath() + QString(/**/"/trt_cache");
        std::string cachePathStd = cachePath.toStdString();

        QDir().mkpath(QString::fromStdString(cachePathStd));

        try {
            OrtTensorRTProviderOptions trt_options{};
            trt_options.device_id = 0;
            trt_options.trt_fp16_enable = 1;
            trt_options.trt_engine_cache_enable = 1; 
            
            // The variable cachePathStd survives until the constructor exits, making it safe
            trt_options.trt_engine_cache_path = cachePathStd.c_str();

            m_sessionOptions.AppendExecutionProvider_TensorRT(trt_options);
            
            OrtCUDAProviderOptions cuda_options;
            cuda_options.device_id = 0;
            m_sessionOptions.AppendExecutionProvider_CUDA(cuda_options);
            
            qDebug() << "TensorRT & CUDA Execution Providers enabled.";
        } catch (const Ort::Exception& e) {
            qDebug() << "Failed to enable TensorRT/CUDA, falling back to CPU:" << e.what();
        }
    } else {
        qDebug() << "CPU Execution Provider enabled (CUDA disabled by configuration).";
    }

    // Safely convert model path via std::wstring
#ifdef _WIN32
    const wchar_t* final_model_path = reinterpret_cast<const wchar_t*>(modelPath.utf16());
#else
    const char* final_model_path = modelPath.toStdString().c_str();
#endif

    try {
        m_session = Ort::Session(m_env, final_model_path, m_sessionOptions);
    } catch (const Ort::Exception& e) {
        qDebug() << "Session Initialization Error:" << e.what();
        return;
    }

    // Retrieve and cache input/output node names once in the constructor to avoid runtime overhead
    Ort::AllocatorWithDefaultOptions allocator;
    m_inputName = m_session.GetInputNameAllocated(0, allocator).get();
    m_inputNames.push_back(m_inputName.c_str());

    m_outputName = m_session.GetOutputNameAllocated(0, allocator).get();
    m_outputNames.push_back(m_outputName.c_str());

    SetDllDirectoryW(NULL);
}

BarcodeEnhancer::~BarcodeEnhancer()
{
}

std::vector<QImage> BarcodeEnhancer::enhanceBatch(const std::vector<QImage>& inputImages)
{
    std::vector<QImage> outputImages(inputImages.size());

    // Execute enhancement in parallel.
    // Ort::Session::Run is inherently thread-safe for inference tasks.
    
	wchar_t	dllPathName[1024];
	memset(dllPathName,0,sizeof(dllPathName));
	DllPath.toWCharArray(dllPathName);
	SetDllDirectoryW(dllPathName);

    int Len=inputImages.size();
    if(Len==1){
        outputImages[0] = enhance(inputImages[0]);
    }
    else if(Len>=2){
        #pragma omp parallel for
        for (int i = 0; i < Len; ++i) {
            outputImages[i] = enhance(inputImages[i]);
        }
    }
    SetDllDirectoryW(NULL);
    return outputImages;
}

QImage BarcodeEnhancer::enhance(const QImage& inputImage)
{
    if (!m_session) {
        qDebug() << "Error: Model session is not initialized.";
        return inputImage;
    }

    //QElapsedTimer timer;
    //timer.start();

    // 1. Prepare QImage
    QImage image = inputImage.convertToFormat(QImage::Format_RGB888);
    int width = image.width();
    int height = image.height();
    
    // Ensure dimensions are multiples of 4
    if (width % 4 != 0 || height % 4 != 0) {
        width = width - (width % 4);
        height = height - (height % 4);
        image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    int channels = 3;

    // Local buffer allocation guarantees thread-safety when running OpenMP
    std::vector<float> inputTensorValues(channels * width * height);

    // 2. Pre-processing: Copy to C++ tensor array and normalize
    for (int h = 0; h < height; ++h) {
        const uchar* scanline = image.constScanLine(h);
        for (int w = 0; w < width; ++w) {
            for (int c = 0; c < channels; ++c) {
                inputTensorValues[c * (width * height) + h * width + w] = scanline[w * channels + c] / 255.0f;
            }
        }
    }

    // 3. Create Input Tensor
    std::vector<int64_t> inputShape = {1, channels, height, width};
    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        m_memoryInfo, inputTensorValues.data(), inputTensorValues.size(),
        inputShape.data(), inputShape.size());

    // 4. Execute Inference (Pure inference time)
    std::vector<Ort::Value> outputTensors;
    try {
        outputTensors = m_session.Run(
            Ort::RunOptions{nullptr}, 
            m_inputNames.data(), &inputTensor, 1, 
            m_outputNames.data(), 1
        );
    } catch (const Ort::Exception& e) {
        qDebug() << "ONNX Runtime Exception:" << e.what();
        return inputImage;
    }

    // 5. Post-processing: Convert output tensor to QImage
    float* outputTensorValues = outputTensors.front().GetTensorMutableData<float>();
    auto typeInfo = outputTensors.front().GetTensorTypeAndShapeInfo();
    std::vector<int64_t> outputShape = typeInfo.GetShape();
    
    int out_channels = outputShape[1];
    int out_height = outputShape[2];
    int out_width = outputShape[3];

    QImage outputImage(out_width, out_height, QImage::Format_RGB888);

    for (int h = 0; h < out_height; ++h) {
        uchar* scanline = outputImage.scanLine(h);
        for (int w = 0; w < out_width; ++w) {
            for (int c = 0; c < out_channels; ++c) {
                float val = outputTensorValues[c * (out_width * out_height) + h * out_width + w] * 255.0f;
                if (val < 0.0f) val = 0.0f;
                if (val > 255.0f) val = 255.0f;
                scanline[w * out_channels + c] = static_cast<uchar>(val);
            }
        }
    }

    //qDebug() << "Inference Cycle Time for image of size" << width << "x" << height << ":" << timer.elapsed() << "ms";
    return outputImage;
}