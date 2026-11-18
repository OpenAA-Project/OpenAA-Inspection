#!/bin/bash
# エラーが発生した時点で処理を中断する（安全のため）
set -e

# スクリプト実行時のルートディレクトリを記憶
BASE_DIR=$(pwd)

echo "=== Building OpenSource ==="
cd "$BASE_DIR/OpenSource"
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)

echo "=== Building ServiceLib ==="
cd "$BASE_DIR/ServiceLib"
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)

echo "=== Building Main Project ==="
cd "$BASE_DIR"
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -- -j$(nproc)

echo "=== All builds completed successfully! ==="
