platform="Mac"
executableSourceFolder="../../../source/FRSample"

echo "Which do you want to build? Please Input the number: "

read -p "0: Executable 1: Project        input: " operation

if [ $operation == '0' ]
then
    cmake -D platform=${platform} -DENABLE_SHARED_LIB=false -DCMAKE_BUILD_TYPE=Release ${executableSourceFolder}
    make
elif [ $operation == '1' ]
then
    echo "Start generate the project"
    cmake -D platform=${platform} -G "Xcode" -DENABLE_SHARED_LIB=false ${executableSourceFolder}
else
    echo "without any operation"
fi

