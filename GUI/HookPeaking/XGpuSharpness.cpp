//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include "XGpuSharpness.h"

class GpuSharpnessContext : public GpuSharpnessContextBase
{
public:
    GpuSharpnessContext();
    ~GpuSharpnessContext();

    // 初期化 (サイズ変更時にも呼ぶ)
    // 戻り値: 成功したら true
    bool init(int w, int h, int radius, bool isGLES)    override;

    // 実行 (画像データだけ渡す)
    void process(const unsigned char* inputData, unsigned char* outputData, float sensitivity)  override;

    // リソース解放
    void cleanup()  override;

private:
    GLuint m_program = 0;
    GLuint m_inputTex = 0;
    GLuint m_outputTex = 0;
    GLuint m_fbo = 0;

    int m_width = 0;
    int m_height = 0;
    bool m_isInitialized = false;

    // Uniform変数の場所キャッシュ
    GLint m_locSensitivity = -1;

    GLuint createComputeShaderProgram(const std::string& source);
};

GpuSharpnessContextBase *GetGpuSharpnessContextInstance()
{
    return new GpuSharpnessContext();
}

void printErrorLog(const std::string& msg) {
    // Qtを使っているなら qDebug() << msg.c_str(); に変えてください
    // Windows APIなら OutputDebugStringA(msg.c_str()); でもOK
    std::cerr << msg << std::endl; 
    
    // もしコンソールが見えないなら、例外を投げて止めるのが一番早いです
    // throw std::runtime_error(msg); 
}

// -----------------------------------------------------------------------------
// シェーダーの共通部分 (バージョン宣言以外の本体)
// -----------------------------------------------------------------------------
const std::string computeShaderBody7 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 7; // 半径7 (15x15ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";

const std::string computeShaderBody6 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 6; // 半径6 (13x13ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";
const std::string computeShaderBody5 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 5; // 半径5 (11x11ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";
const std::string computeShaderBody4 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 4; // 半径4 (9x9ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";

const std::string computeShaderBody3 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 3; // 半径3 (7x7ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";

const std::string computeShaderBody2 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 2; // 半径2 (5x5ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";

const std::string computeShaderBody1 = R"(
layout(local_size_x = 16, local_size_y = 16) in;

// binding指定はDesktop GL 4.2+ / GLES 3.1+ で共通して使える
layout(binding = 0, r8ui) readonly highp uniform uimage2D inputImage;
layout(binding = 1, r8ui) writeonly highp uniform uimage2D outputImage;

uniform float sensitivity;

void main() {
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(inputImage);

    if (pos.x >= size.x || pos.y >= size.y) return;

    const int R = 1; // 半径1 (3x3ウィンドウ)
    float sumLaplacianSq = 0.0;
    
    // スライディングウィンドウ処理
    for (int dy = -R; dy <= R; ++dy) {
        for (int dx = -R; dx <= R; ++dx) {
            ivec2 p = pos + ivec2(dx, dy);

            // 簡易境界チェック
            if (p.x <= 0 || p.y <= 0 || p.x >= size.x - 1 || p.y >= size.y - 1) continue;

            // ラプラシアン (4近傍)
            uint center = imageLoad(inputImage, p).r;
            uint up     = imageLoad(inputImage, p + ivec2(0, -1)).r;
            uint down   = imageLoad(inputImage, p + ivec2(0,  1)).r;
            uint left   = imageLoad(inputImage, p + ivec2(-1, 0)).r;
            uint right  = imageLoad(inputImage, p + ivec2( 1, 0)).r;

            float lap = float(up + down + left + right) - 4.0 * float(center);
            sumLaplacianSq += (lap * lap);
        }
    }

    float windowArea = float((2 * R + 1) * (2 * R + 1));
    float score = sqrt(sumLaplacianSq / windowArea) * sensitivity;

    uint outVal = uint(clamp(score, 0.0, 255.0));
    imageStore(outputImage, pos, uvec4(outVal, 0, 0, 0));
}
)";


GpuSharpnessContext::GpuSharpnessContext() {}

GpuSharpnessContext::~GpuSharpnessContext() {
    cleanup();
}

void GpuSharpnessContext::cleanup() {
    if (m_inputTex) glDeleteTextures(1, &m_inputTex);
    if (m_outputTex) glDeleteTextures(1, &m_outputTex);
    if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
    if (m_program) glDeleteProgram(m_program);

    m_inputTex = 0;
    m_outputTex = 0;
    m_fbo = 0;
    m_program = 0;
    m_isInitialized = false;
}

bool GpuSharpnessContext::init(int w, int h, int radius, bool isGLES) {
    // すでに同じサイズで初期化済みなら何もしない (ここが高速化の肝)
    if (m_isInitialized && m_width == w && m_height == h) {
        return true; 
    }

    // サイズが変わった、または初回の場合はリセット
    cleanup();

    m_width = w;
    m_height = h;

    // 1. シェーダーコンパイル
    std::string versionHeader = isGLES ? "#version 310 es\n" : "#version 430 core\n#define highp\n";
    switch(radius){
        case 7:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody7);
            break;
        case 6:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody6);
            break;
        case 5:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody5);
            break;
        case 4:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody4);
            break;
        case 3:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody3);
            break;
        case 2:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody2);
            break;
        case 1:
            m_program = createComputeShaderProgram(versionHeader + computeShaderBody1);
            break;
        default:
            printErrorLog("Error: Unsupported Radius value. Supported values are 2 to 7.");
            return false;
	}

    if (m_program == 0){
        return false;
    }

    // Uniformキャッシュ
    m_locSensitivity = glGetUniformLocation(m_program, "sensitivity");

    // 2. テクスチャ作成 (Immutable Storage)
    glGenTextures(1, &m_inputTex);
    glBindTexture(GL_TEXTURE_2D, m_inputTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8UI, w, h); // メモリ確保のみ

    glGenTextures(1, &m_outputTex);
    glBindTexture(GL_TEXTURE_2D, m_outputTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8UI, w, h);

    // 3. FBO作成 (読み出し用)
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_outputTex, 0);
    
    // FBO完全性チェック
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "FBO Error" << std::endl;
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // バインド解除

    m_isInitialized = true;
    return true;
}

void GpuSharpnessContext::process(const unsigned char* inputData, unsigned char* outputData, float sensitivity) {
    if (!m_isInitialized) return;

    glUseProgram(m_program);

    // 1. 画像データの転送 (再確保ではなく、部分更新を使う)
    // glTexStorage2Dで確保した領域にデータを流し込むだけなので高速
    glBindTexture(GL_TEXTURE_2D, m_inputTex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RED_INTEGER, GL_UNSIGNED_BYTE, inputData);

    // 2. イメージユニットへのバインド
    glBindImageTexture(0, m_inputTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R8UI);
    glBindImageTexture(1, m_outputTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8UI);

    // 3. Uniformセット
    if (m_locSensitivity != -1) glUniform1f(m_locSensitivity, sensitivity);

    // 4. 計算実行
    glDispatchCompute((m_width + 15) / 16, (m_height + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // 5. 読み出し (FBO経由)
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glReadPixels(0, 0, m_width, m_height, GL_RED_INTEGER, GL_UNSIGNED_BYTE, outputData);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

// (ヘルパー関数: 前回のコードと同じものを使用)
GLuint GpuSharpnessContext::createComputeShaderProgram(const std::string& source) {
    // ... 前回の createComputeShaderProgram の実装をここにコピー ...
    // または外部関数としてリンクしてもOKです
    const char* srcPtr = source.c_str();
    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &srcPtr, NULL);
    glCompileShader(shader);
    // ... エラーチェックとリンク処理 ...
    GLuint prog = glCreateProgram();
    glAttachShader(prog, shader);
    glLinkProgram(prog);
    glDeleteShader(shader);
    return prog;
}





















//// -----------------------------------------------------------------------------
//// ヘルパー: シェーダーコンパイル
//// -----------------------------------------------------------------------------
//GLuint createComputeShaderProgram(const std::string& fullSource)
//{
//    // 1. シェーダー作成
//    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
//    if (shader == 0) {
//        printErrorLog("Error: glCreateShader failed. (OpenGL context might be missing?)");
//        return 0;
//    }
//
//    const char* srcPtr = fullSource.c_str();
//    glShaderSource(shader, 1, &srcPtr, NULL);
//    glCompileShader(shader);
//
//    // 2. コンパイルエラー確認
//    GLint success;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        GLint logLength;
//        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
//        std::vector<char> log(logLength);
//        glGetShaderInfoLog(shader, logLength, NULL, log.data());
//        
//        std::string errorMsg = "[Shader Compile Error]\n" + std::string(log.data());
//        printErrorLog(errorMsg);
//        
//        glDeleteShader(shader);
//        return 0;
//    }
//
//    // 3. プログラム作成とリンク
//    GLuint program = glCreateProgram();
//    glAttachShader(program, shader);
//    glLinkProgram(program);
//    glDeleteShader(shader); // リンク後はアタッチ済みシェーダーを削除してOK
//
//    // 4. リンクエラー確認
//    glGetProgramiv(program, GL_LINK_STATUS, &success);
//    if (!success) {
//        GLint logLength;
//        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
//        std::vector<char> log(logLength);
//        glGetProgramInfoLog(program, logLength, NULL, log.data());
//        
//        std::string errorMsg = "[Program Link Error]\n" + std::string(log.data());
//        printErrorLog(errorMsg);
//        
//        glDeleteProgram(program);
//        return 0;
//    }
//
//    return program;
//}
//
bool  InitialGPUForShader(bool &isGLES)
{
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return false;
    }

    // ウィンドウは表示しない
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* window = nullptr;
    isGLES = false;

    // --- トライアル 1: Desktop OpenGL 4.3 (Windows/Linux PC向け) ---
    std::cout << "Attempting to create OpenGL 4.3 context..." << std::endl;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(100, 100, "Compute", NULL, NULL);

    if (!window) {
        // --- トライアル 2: OpenGL ES 3.1 (Raspberry Pi向け) ---
        std::cout << "Desktop GL failed. Attempting to create OpenGL ES 3.1 context..." << std::endl;
        // ヒントをリセット
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        
        window = glfwCreateWindow(100, 100, "Compute", NULL, NULL);
        if (window) {
            isGLES = true;
        }
    }

    if (!window) {
        std::cerr << "Failed to create both OpenGL 4.3 and ES 3.1 contexts." << std::endl;
        std::cerr << "Ensure your GPU drivers support Compute Shaders." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    // GLEW初期化 (GLEWは実験的機能を有効にしないとCoreProfile等で失敗することがある)
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW" << std::endl;
        return false;
    }

    // 実際のバージョン確認
    std::cout << "Context Created: " << (isGLES ? "OpenGL ES" : "Desktop OpenGL") << std::endl;
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    return true;
}
//
//
//// -----------------------------------------------------------------------------
//// シャープネス計算 (FBO使用で互換性確保)
//// -----------------------------------------------------------------------------
//void computeSharpness(unsigned char* inputData, unsigned char* outputData, int w, int h ,float sensitivityVal, int Radius,bool isGLES)
//{
//    // 1. シェーダーソースの動的構築
//    std::string versionHeader;
//    if (isGLES) {
//        // Raspberry Pi / Mobile
//        versionHeader = "#version 310 es\n"; 
//    } else {
//        // Windows / Linux Desktop (highpマクロで互換性維持)
//        versionHeader = "#version 430 core\n#define highp\n";
//    }
//    GLuint program;
//    switch(Radius){
//        case 7:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody7);
//            break;
//        case 6:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody6);
//            break;
//        case 5:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody5);
//            break;
//        case 4:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody4);
//            break;
//        case 3:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody3);
//            break;
//        case 2:
//            program = createComputeShaderProgram(versionHeader + computeShaderBody2);
//            break;
//        default:
//            printErrorLog("Error: Unsupported Radius value. Supported values are 2 to 7.");
//            return;
//	}
//    if (program == 0){
//        return;
//    }
//    glUseProgram(program);
//
//    // 2. テクスチャ設定
//    GLuint inputTex, outputTex;
//    glGenTextures(1, &inputTex);
//    glBindTexture(GL_TEXTURE_2D, inputTex);
//    // Desktop/ES共通の設定
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8UI, w, h); // Immutable storage (推奨)
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_RED_INTEGER, GL_UNSIGNED_BYTE, inputData);
//
//    glGenTextures(1, &outputTex);
//    glBindTexture(GL_TEXTURE_2D, outputTex);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8UI, w, h);
//
//    // イメージユニットへのバインド
//    glBindImageTexture(0, inputTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_R8UI);
//    glBindImageTexture(1, outputTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8UI);
//
//    //glUniform1f(glGetUniformLocation(program, "sensitivity"), 2.0f);
//
//    // 2. 変数の場所(Location)を取得する
//    // "sensitivity" はシェーダーコード内の uniform float sensitivity; と名前を一致させる
//    GLint loc = glGetUniformLocation(program, "sensitivity");
//
//    // 3. 値をセットする (場所が見つかった場合のみ)
//    if (loc != -1) {
//        glUniform1f(loc, sensitivityVal);
//    } else {
//        // シェーダー内でその変数が使われていない場合(最適化で消された場合)、-1が返ります
//        std::cerr << "Warning: uniform 'sensitivity' not found in shader." << std::endl;
//    }
//
//    // 3. 実行
//    glDispatchCompute((w + 15) / 16, (h + 15) / 16, 1);
//    
//    // バリア (書き込み完了待ち)
//    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
//
//    // 4. 読み戻し
//    // glGetTexImageはESで使えない場合があるため、FBO経由でglReadPixelsを使う (最も互換性が高い)
//    GLuint fbo;
//    glGenFramebuffers(1, &fbo);
//    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTex, 0);
//
//    // 整数フォーマットとして読み取る
//    glReadPixels(0, 0, w, h, GL_RED_INTEGER, GL_UNSIGNED_BYTE, outputData);
//
//    // クリーンアップ
//    glDeleteFramebuffers(1, &fbo);
//    glDeleteTextures(1, &inputTex);
//    glDeleteTextures(1, &outputTex);
//    glDeleteProgram(program);
//}

