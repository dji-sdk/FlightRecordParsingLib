platform="Ubuntu"
executableSourceFolder="../../../source/FRSample"

echo "Which do you want to build? Please Input the number: "

cmake -D platform=${platform} -DENABLE_SHARED_LIB=false ${executableSourceFolder}
make

