# OpenAA-Inspection

Inspection OpenSource system in main OpenAA.

This document outlines the complete installation, dependency resolution, and build process for the OpenAA-Inspection system on Linux (x64) and Raspberry Pi (arm64/aarch64) environments.

---

## 1. Prerequisites & System Packages

Before building from source, ensure your system is up to date and has the necessary tools installed.

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake git wget tar nasm pkg-config \
    libtommath1 libtommath-dev libncurses5 libncurses6 \
    libpng-dev libfontconfig1-dev libpugixml-dev \
    libglfw3-dev libglew-dev libleptonica-dev \
    libpango1.0-dev libcairo2-dev libtiff-dev libarchive-dev libcurl4-openssl-dev \
    libavformat-dev libavcodec-dev libswscale-dev libavutil-dev
```

---

## 2. Database Setup: Firebird 5.0.4

Remove any existing Firebird installations and set up the new environment.

```bash
# 1. Clean old installations
sudo apt-get purge "^firebird.*" "^libfbclient.*"
sudo apt-get autoremove
sudo apt-get update

# 2. Download and Extract (Choose based on your OS)
# For Linux x64:
tar -zxvf Firebird-5.0.4.1812-0-linux-x64.tar.gz
cd Firebird-5.0.4.1812-0-linux-x64/

# For Raspberry Pi (arm64):
tar -zxvf Firebird-5.0.4.1812-0-linux-arm64.tar.gz
cd Firebird-5.0.4.1812-0-linux-arm64/

# 3. Install
sudo ./install.sh
# Prompt: "Please enter new password for SYSDBA user:" -> enter: masterkey

# 4. Configure Libraries
sudo sh -c "echo '/opt/firebird/lib' > /etc/ld.so.conf.d/firebird.conf"
sudo ldconfig
sudo ln -s /opt/firebird/lib/libfbclient.so /usr/lib/libfbclient.so.2

# 5. Setup Database File
sudo mkdir -p /var/lib/firebird/data
# Note: Manually copy your OpenAA.FDB file into /var/lib/firebird/data (requires admin privileges)
sudo chown -R firebird:firebird /var/lib/firebird/data
```

---

## 3. Third-Party Library Compilation

Create a workspace directory for downloading and building dependencies.

### 3.1 Core Libraries (ZLib, Eigen, LibPNG, JPEG, FFTW)
```bash
# ZLib (1.3.2)
mkdir zlib && cd zlib
wget https://zlib.net/zlib-1.3.2.tar.gz && tar -zxvf zlib-1.3.2.tar.gz
cd zlib-1.3.2 && ./configure && make && sudo make install && cd ../..

# Eigen (5.0.0)
mkdir eigen && cd eigen
wget https://gitlab.com/libeigen/eigen/-/archive/5.0.0/eigen-5.0.0.tar.gz
tar -zxvf eigen-5.0.0.tar.gz && cd ..

# LibPNG (1.6.53)
mkdir LibPNG && cd LibPNG
wget https://download.sourceforge.net/libpng/libpng-1.6.53.tar.gz
tar -zxvf libpng-1.6.53.tar.gz
cd libpng-1.6.53 && ./configure && make && sudo make install && cd ../..

# JPEG (9d)
mkdir JPEG && cd JPEG
wget http://www.ijg.org/files/jpegsrc.v9d.tar.gz
tar -zxvf jpegsrc.v9d.tar.gz
cd jpeg-9d && ./configure && make && sudo make install && cd ../..

# FFTW (3.3.10)
mkdir FFTW && cd FFTW
wget https://www.fftw.org/fftw-3.3.10.tar.gz
tar -zxvf fftw-3.3.10.tar.gz && cd fftw-3.3.10
# For Linux (x64): ./configure --enable-shared --enable-avx2
# For Raspberry Pi: ./configure --enable-shared --enable-neon
make -j4 && sudo make install && cd ../..
```

### 3.2 Documents & Fonts (OpenXLSX, LibXLSXWriter, FreeType)
```bash
# OpenXLSX
mkdir OpenXLSX && cd OpenXLSX
git clone https://github.com/troldal/OpenXLSX.git && cd OpenXLSX
mkdir build && cd build && cmake .. && make && sudo make install
mkdir ../lib && cp output/*.a ../lib && cd ../../..

# LibXLSXWriter
mkdir LibXLSXWriter && cd LibXLSXWriter
git clone https://github.com/jmcnamara/libxlsxwriter.git && cd libxlsxwriter
mkdir build && cd build && cmake .. && make && sudo make install && sudo ldconfig
cp libxlsxwriter.a ../lib && cd ../../..

# FreeType (2.14.3)
mkdir FreeType && cd FreeType
wget https://download.savannah.gnu.org/releases/freetype/freetype-2.14.3.tar.gz
tar -zxvf freetype-2.14.3.tar.gz
cd freetype-2.14.3 && ./configure && make && sudo make install && cd ../..
```

### 3.3 Cryptography, Imaging & OCR (Crypto++, Turbo-JPEG, Haru PDF, FFmpeg, ZXing, Tesseract)
```bash
# Crypto++
mkdir CryptoPP && cd CryptoPP
git clone https://github.com/weidai11/cryptopp.git && cd cryptopp
make && sudo make install && sudo ldconfig && cd ../..

# Turbo-JPEG
mkdir libjpeg-turbo && cd libjpeg-turbo
git clone https://github.com/libjpeg-turbo/libjpeg-turbo.git && cd libjpeg-turbo
mkdir build && cd build && cmake .. && make && sudo make install && sudo ldconfig && cd ../../..

# Haru PDF
mkdir PDF && cd PDF
git clone https://github.com/libharu/libharu.git && cd libharu
mkdir build && cd build && cmake .. && make && sudo make install && sudo ldconfig && cd ../../..

# FFmpeg
mkdir ffmpeg && cd ffmpeg
git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg && cd ffmpeg
./configure --enable-shared && make && sudo make install && sudo ldconfig && cd ../..

# ZXing (Barcode)
mkdir Barcode && cd Barcode
git clone https://github.com/zxing-cpp/zxing-cpp.git && cd zxing-cpp
git submodule update --init --recursive
mkdir build && cd build
cmake .. -DBUILD_PYTHON_MODULE=OFF -DBUILD_EXAMPLES=OFF
make && sudo make install && sudo ldconfig && cd ../../..

# Tesseract (OCR)
mkdir OCR && cd OCR
# Note: Ensure initramfs updates are configured correctly per environment before building
git clone https://github.com/tesseract-ocr/tesseract.git && cd tesseract
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..
make -j4 && sudo make install && sudo ldconfig && cp *.a .. && cd ../../..
```

---

## 4. Specific Patches and Configurations

### 4.1 Xpdf (4.06) Build & Patching
```bash
mkdir PDF && cd PDF
wget https://dl.xpdfreader.com/xpdf-4.06.tar.gz
tar -zxvf xpdf-4.06.tar.gz && cd xpdf-4.06
```

**Patch A: Edit `xpdf/CMakeLists.txt`**
Add the following lines immediately after the `add_library(xpdf_objs OBJECT ...)` block:
```cmake
add_library(xpdf_objs_static STATIC $<TARGET_OBJECTS:xpdf_objs>)
set_target_properties(xpdf_objs_static PROPERTIES OUTPUT_NAME "xpdf_objs")
```

**Patch B: Edit `xpdf-qt/CMakeLists.txt`**
Add the following lines before `add_executable(xpdf ...)`:
```cmake
add_library(PDFWidget STATIC
  ${XPDFWIDGET_PRINT_MODULES}
  QtPDFCore.cc
  XpdfWidget.cc
  ${XPDFWIDGET_MOC}
)
target_link_libraries(PDFWidget 
  ${QT_LIBRARIES} ${EXTRA_QT_LIBRARIES}
  ${PAPER_LIBRARY}
  ${FREETYPE_LIBRARY} ${FREETYPE_OTHER_LIBS}
  ${DTYPE_LIBRARY}
  ${LCMS_LIBRARY}
  ${FONTCONFIG_LIBRARY}
  ${CMAKE_THREAD_LIBS_INIT}
)
```

**Build Xpdf:**
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..
make && sudo make install

# Copy static libraries to root
cp xpdf/libxpdf_objs.a ..
cp xpdf-qt/libPDFWidget.a ..
cp fofi/libfofi.a ..
cp goo/libgoo.a ..
cp splash/libsplash.a ..
cd ..
mv libfofi.a libfofi_objs.a
mv libgoo.a libgoo_objs.a
mv libsplash.a libsplash_objs.a
mv libPDFWidget.a libPDFWidget_.a
cd ../..
```

### 4.2 ONNX Runtime (1.31.1)
Choose the correct setup for your environment:

*   **Windows:** `vcpkg install onnxruntime:x64-windows`
*   **Linux (x64):**
    ```bash
    mkdir ONNX && cd ONNX
    wget https://github.com/microsoft/onnxruntime/releases/download/v1.31.1/onnxruntime-linux-x64-1.31.1.tgz
    tar -zxvf onnxruntime-linux-x64-1.31.1.tgz && cd onnxruntime-linux-x64-1.31.1
    sudo cp -r include/* /usr/local/include/ && sudo cp -r lib/* /usr/local/lib/
    sudo ldconfig
    ```
*   **Raspberry Pi (64-bit):** Download `onnxruntime-linux-aarch64-1.31.1.tgz` and apply the same steps as Linux x64.
*   **Raspberry Pi (32-bit):** Must compile from source (`./build.sh --config Release --build_shared_lib --arm`). *Ensure swap memory is expanded before building.*

### 4.3 Hardware Drivers (HIKRobot-MVS & CONTEC DIO)
```bash
# HIKRobot-MVS
mkdir HIKRobot && cd HIKRobot
# Extract corresponding MVS tarball for your architecture (x86_64 or aarch64)
tar -zxvf MVS.tar.gz && sudo ./setup.sh
cd .. && mkdir MVS
# Ensure you copy MvCamera.h and MvCamera.cpp to your project's MVS folder.

# CONTEC DIO
# Download cdio_990F.tgz manually
cd contec/cdio && make && sudo make install
# Copy contec/cdio/samples/inc/cdio.h to your project's "Open" folder.
```

---

## 5. Project Installation and Build Guide

### 5.0 Clone the Repository
```bash
git clone https://github.com/OpenAA-Project/OpenAA-Inspection.git
```

### 5.1 System Parameters & Debug Configuration
```bash
# 1. (Raspberry Pi Only) Install sse2neon.h
cd /home/raspberrypi/OpenAA-Inspection/Open/
wget https://raw.githubusercontent.com/DLTcollab/sse2neon/master/sse2neon.h

# 2. Maximize stack size to prevent overflow during build
ulimit -s unlimited

# 3. Allow debugging via QtCreator attachment (ptrace scope)
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
```

### 5.2 Build Steps
Build the modules in the exact order below:

**1. OpenSource Module**
```bash
cd OpenAA-Inspection/OpenSource
mkdir build && cd build
rm -rf CMakeCache.txt CMakeFiles/
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)
```

**2. ServiceLib Module**
```bash
cd ../../OpenAA-Inspection/ServiceLib
mkdir build && cd build
rm -rf CMakeCache.txt CMakeFiles/
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)
```

**3. Main OpenAA-Inspection Application**
```bash
cd ../../OpenAA-Inspection
mkdir build && cd build
rm -rf CMakeCache.txt CMakeFiles/
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)

# If you need to output build logs: 
# cmake --build . -- -j$(nproc) -k > build_log.txt 2>&1
```

### 5.3 Cleaning the Build
To quickly clean all build directories and start fresh, run the following from the root directory:
```bash
cd OpenAA-Inspection
find . -type d -name "build" -prune -exec find {} -mindepth 1 -delete \;
```
