platform="Ubuntu"
sourceFolder="../../../source/FlightRecordStandardization"

echo "Which do you want to build? Please Input the number: "

cmake -D platform=${platform} -DENABLE_SHARED_LIB=false ${sourceFolder}
make