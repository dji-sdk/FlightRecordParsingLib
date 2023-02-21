# DJIFlightRecord

## What is this?

Flight logs can parse version 13 flight log files. Convert DJI protocol data into time frame objects for presentation and analysis

## Where does the app create the version 13 flight log?

* App using Mobile SDK version 4.12

## architectural relationship

![](images/architectural.png)

* FRSample: Introducing how to call interfaces and parse data
* FlightRecordStandardizationCpp: Convert C++ structure objects into Protobuf objects for cross-platform data transfer
* FlightRecordStandardization: Aggregate raw data into a view model of aircraft status in 0.1 seconds
* FlightRecordEngine: For parsing cryptographic to plaintext data
* libtomcrypt/libtommath: Used to decrypt original documents
* curl/openssl: Used to communicate with DJIService to get the decryption key

### Folder Structure

Here is an introduction to the role of file directories：

* FR-V1.0.0/third-party/source: Rely on third-party source libraries to compile the platform you want to run. The specific compilation method needs to be solved by itself.
* FR-V1.0.0/third-party/header: Relying on third-party platform libraries for header files
* FR-V1.0.0/third-party/cmake: For cmake to compile custom functions
* FR-V1.0.0/third-party/build: Third-party repositories have compiled the product. Only partial platforms supported
* FR-V1.0.0/dji-flightrecord-engine/build: Compilation products for each platform used to house the dji-flightrecordengine library
* FR-V1.0.0/dji-flightrecord-engine/source：Source code for the dji-flightrecordengine library
* FR-V1.0.0/dji-flightrecord-kit/build: Compilation products for each platform used to house the dji-flightrecord-kit library
* FR-V1.0.0/dji-flightrecord-kit/protoc: Protobuf files that house standardized data structures and can be used for cross-platform data transfer
* FR-V1.0.0/dji-flightrecord-kit/source: Source code for the dji-flightrecord-kit library
* FR-V1.0.0/images：Photo resources cited in README

## How to run sample?

### Runing the sample in Mac

Here is the MAC version of the SAMPLE run creation process.

```shell
cd dji-flightrecord-kit/build/Mac/FRSample
sh generate.sh

// Which do you want to build? Please Input the number:
// 0: Executable 1: Project        input:
// input 1 can create a xcode project.
```

1. Open dji-flightrecord-kit/build/Mac/FRSample/FRSample.xcodeproj
2. Go to the main.cc file and configure the path of the file you want to parse to the variable file_path.
3. Configure the sdk key parameter of the 'startRequestParser' interface and you will be able to parse the file for the version of Flight Record 13

### Runing the sample in Ubuntu

```shell
cd dji-flightrecord-kit/build/Ubuntu/FRSample
sh generate.sh
./FRSample
```

1. Go to the main.cc file and configure the path of the file you want to parse to the variable file_path.
2. Configure the sdk key parameter of the 'startRequestParser' interface and you will be able to parse the file for the version of Flight Record 13
3. Runing the above script

## How to compile the library?

### Mac

```shell
cd dji-flightrecord-kit/build/Mac/FlightRecordStandardizationCpp
sh generate.sh
./FRSample
```

1. Execute the above script
2. Get the library you want, the header files are stored in the dji-flightrecord-kit/source/FlightRecordStandardizationCpp/parser/DJIFRProtoParser.hpp

### Ubuntu

```shell
cd dji-flightrecord-kit/build/Ubuntu/FlightRecordStandardizationCpp
sh generate.sh
./FRSample
```

1. Execute the above script
2. Get the library you want, the header files are stored in the dji-flightrecord-kit/source/FlightRecordStandardizationCpp/parser/DJIFRProtoParser.hpp

## Credits

FlightRecord is owned and maintained by [DJI SDK](https://developer.dji.com).

## Support

Expect more customized data, please let us know your data needs and application scenarios.
You can get support from DJI with the following methods:

* dev@dji.com

## License

DJIFlightRecord is available under the MIT license. See the LICENSE file for more info.
