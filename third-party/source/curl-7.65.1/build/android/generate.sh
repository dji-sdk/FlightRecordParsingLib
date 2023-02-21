#!/bin/sh

if [[ ! $1 ]]; then
echo "Need Input Arch: The Supported Arch is armeabi-v7a or arm64-v8a"
exit 1
fi

ARCH=$1

if [[ $ARCH == "armeabi-v7a" ]]; then
    TOOLCHAIN_NAME=arm-linux-androideabi-4.9
elif [[ $ARCH == "arm64-v8a" ]]; then
    TOOLCHAIN_NAME=aarch64-linux-android-4.9
else
    echo "Error: Not Supported Arch $1"
    exit 2
fi

rm -rf CMakeCache.txt
rm -rf CMakeFiles
rm -rf cmake_install.cmake
rm -rf Makefile

OPENSSL_INCLUDE="../../../../libs/libopenssl/include"
OPENSSL_CRYPTO="../../../../libs/libopenssl/lib/android/${ARCH}/libcrypto.a"
OPENSSL_SSL="../../../../libs/libopenssl/lib/android/${ARCH}/libssl.a"

NDK_ROOT="/Users/ares.li/Android/ndk"
CMAKE_NDK_TOOLCHAIN="${NDK_ROOT}/build/cmake/android.toolchain.cmake"

cmake -DCMAKE_TOOLCHAIN_FILE=$CMAKE_NDK_TOOLCHAIN \
      -DCMAKE_BUILD_TYPE=Release \
      -DANDROID_NDK=${NDK_ROOT} \
      -DOPENSSL_INCLUDE_DIR=${OPENSSL_INCLUDE} \
      -DOPENSSL_CRYPTO_LIBRARY=${OPENSSL_CRYPTO} \
      -DOPENSSL_SSL_LIBRARY=${OPENSSL_SSL} \
      -DBUILD_SHARED_LIBS=OFF \
      -DENABLE_DEBUG=OFF \
      -DANDROID_ABI=${ARCH} \
      -DANDROID_NATIVE_API_LEVEL=21 \
      -DANDROID_TOOLCHAIN_NAME=${TOOLCHAIN_NAME} \
      "../.."


if [[ $? == 0 ]]; then
make clean
make
fi



