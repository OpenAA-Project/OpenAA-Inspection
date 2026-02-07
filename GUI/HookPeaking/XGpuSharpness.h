#ifndef GPU_SHARPNESS_H
#define GPU_SHARPNESS_H

bool	 InitialGPUForShader(bool &isGLES);
//void computeSharpness(unsigned char* inputData, unsigned char* outputData, int w, int h, float sensitivityVal,int Radius, bool isGLES);

class GpuSharpnessContextBase
{
public:
    GpuSharpnessContextBase(){}
    virtual ~GpuSharpnessContextBase(){}

    // 初期化 (サイズ変更時にも呼ぶ)
    // 戻り値: 成功したら true
    virtual bool init(int w, int h, int radius, bool isGLES)=0;

    // 実行 (画像データだけ渡す)
    virtual void process(const unsigned char* inputData, unsigned char* outputData, float sensitivity)=0;

    // リソース解放
    virtual void cleanup()=0;
};

GpuSharpnessContextBase *GetGpuSharpnessContextInstance();



#endif