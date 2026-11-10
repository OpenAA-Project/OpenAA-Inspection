#pragma once


#include <QImage>
#include <QString>
#include <vector>
#include <memory>
#include <string>
#define ORT_API_MANUAL_INIT
#include <onnxruntime_cxx_api.h>
#include "XServiceForLayers.h"

class BarcodeEnhancer :public ServiceForLayers
{
public:
    // Constructor handles ONNX Runtime initialization and optional GPU transfer
    // Added a boolean flag to switch between CUDA and CPU execution
    explicit BarcodeEnhancer(LayersBase *base,const QString& modelPath, const QString& ONNXSystemPath,bool useCUDA = true);
    ~BarcodeEnhancer();

    // Receives an input image and performs purely inference
    QImage enhance(const QImage& inputImage);

    // Processes multiple images in parallel using OpenMP
    // Each image can be a different size
    std::vector<QImage> enhanceBatch(const std::vector<QImage>& inputImages);

private:
    QString DllPath;
    Ort::Env m_env;
    Ort::SessionOptions m_sessionOptions;
    Ort::Session m_session{nullptr};
    Ort::MemoryInfo m_memoryInfo;

    // Cache node names to prevent string allocation overhead during inference
    std::string m_inputName;
    std::string m_outputName;
    std::vector<const char*> m_inputNames;
    std::vector<const char*> m_outputNames;
};
