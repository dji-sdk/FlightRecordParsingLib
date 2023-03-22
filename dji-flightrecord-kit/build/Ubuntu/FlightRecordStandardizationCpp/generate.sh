platform="Ubuntu"
sourceFolder="../../../source/FlightRecordStandardizationCpp"

echo "Which do you want to build? Please Input the number: "

cmake -D platform=${platform} -DENABLE_SHARED_LIB=false -DCMAKE_BUILD_TYPE=Release ${sourceFolder}
make -j$(nproc)
