platform="Mac"
sourceFolder="../../../source/FlightRecordStandardizationCpp"

echo "Which do you want to build? Please Input the number: "

read -p "0: Libray 1: Project        input: " operation
generate.sh
if [ $operation == '0' ]
then
    echo "Which library do you want? Static or Dynamic"
    read -p "0: Static Library 1: Dynamic Library      input: " libraryType
    if [ $libraryType == "0" ]
    then
        cmake -D platform=${platform} -DENABLE_SHARED_LIB=false ${sourceFolder}
    else
        cmake -D platform=${platform} -DENABLE_SHARED_LIB=true ${sourceFolder}
    fi

    make
elif [ $operation == '1' ]
then
    echo "Start generate the project"
    cmake -D platform=${platform} -G "Xcode" ${sourceFolder}
else
    echo "without any operation"
fi