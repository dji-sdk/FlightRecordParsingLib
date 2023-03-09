# ubuntu下编译包含SSL的curl库
WORK_DIR=$(pwd)
CURL_SOURCE_DIR=$WORK_DIR/../../source/curl-7.65.1
THIRD_PARTY_DIR=$WORK_DIR/../..
echo $WORK_DIR

echo "[configure]"
cd $CURL_SOURCE_DIR
CPPFLAGS="-I$WORK_DIR/../../header/libopenssl/include" \
LDFLAGS="-L$WORK_DIR/../../build/libopenssl/lib/ubuntu" \
./configure --disable-shared --enable-static --with-ssl --prefix=$WORK_DIR/../../source/curl-install

cmake
make install

cp $CURL_SOURCE_DIR/../curl-install/lib/libcurl.a $WORK_DIR/lib/ubuntu/
