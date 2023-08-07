# DJIFlightRecord

### <p>[中文版](https://github.com/dji-sdk/FlightRecordParsingLib/blob/master/README_cn.md)</p>

## What is DJIFlightRecord?

Flight record parsing library can parse version 13 flight log files. Convert DJI protocol data into time frame objects for presentation and analysis. An App Key is required to run the flight record parsing library.

## How to apply for my App Key?
1. Log in to the [DJI Developer Technologies](https://developer.dji.com/user), click "CREATE APP", select "Open API" for App Type, fill in the "App Name", "Category" and "Description" by yourself, and click "CREATE".

2. Activate the App through your personal email. After activation, click on the corresponding App information on your developer user page. The App Key is the SDK key parameter you need for the next steps.

## Where does the app create the version 13 flight log?

* App using Mobile SDK version 4.12

## Architectural relationship

![](images/architectural.png)

* FRSample: Used to introduce how to call interfaces and parse data
* FlightRecordStandardizationCpp: Used to convert C++ structure objects into Protobuf objects for cross-platform data transfer
* FlightRecordStandardization: Used to record the raw data in 10 HZ, and present a view model of aircraft status
* FlightRecordEngine: Used to parse cryptographic data to plaintext data
* libtomcrypt/libtommath: Used to decrypt original documents
* curl/openssl: Used to communicate with DJIService to get the decryption key

### Folder structure

Here is an introduction to the role of file directories：

* FR-V1.0.0/third-party/source: Source files storage location of the dependent third-party platform libraries. The specific compilation method needs to be solved by yourself.
* FR-V1.0.0/third-party/header: Header files storage location of the dependent third-party platform libraries
* FR-V1.0.0/third-party/cmake: For CMake to compile custom functions
* FR-V1.0.0/third-party/build: Storage location of compiled products of third-party libraries, and it can only run on certain platforms
* FR-V1.0.0/dji-flightrecord-engine/build: Compilation products for each platform used to house the dji-flightrecordengine library
* FR-V1.0.0/dji-flightrecord-engine/source: Source code for the dji-flightrecordengine library
* FR-V1.0.0/dji-flightrecord-kit/build: Compilation products for each platform used to house the dji-flightrecord-kit library
* FR-V1.0.0/dji-flightrecord-kit/protoc: Protobuf files that house standardized data structures and can be used for cross-platform data transfer
* FR-V1.0.0/dji-flightrecord-kit/source: Source code for the dji-flightrecord-kit library
* FR-V1.0.0/images：Photo resources cited in README


## How to run the sample?

### Running the sample in Docker
**Get docker** 

https://docs.docker.com/get-docker

**Build docker image**
```shell
docker build --build-arg SDK_KEY=your_app_key -t pf .
```

**Docker run**
```shell
docker run -v host_dir:container_dir pf "container_flight_record_dir"
```
Sample code：
docker run -v $(pwd):/tmp pf "/tmp/V132_DJIFlightRecord_2020-06-18_[19-01-24].txt" > json_result.json

"> json_result.json" Redirecting the running result to a specified file

### Running the Sample in Mac

Here is the Mac version of the Sample run creation process.

```shell
cd dji-flightrecord-kit/build/Mac/FRSample
sh generate.sh

// Which do you want to build? Please Input the number:
// 0: Executable 1: Project        input:
// input 1 can create a xcode project.
```

1. Open dji-flightrecord-kit/build/Mac/FRSample/FRSample.xcodeproj
2. Go to the main.cc file and configure the path of the file you want to parse to the variable file_path
3. Configure the SDK key parameter of the "startRequestParser" interface and you are able to parse the file for the version of Flight Record 13

### Running the sample in Ubuntu

```shell
cd dji-flightrecord-kit/build/Ubuntu/FRSample
sh generate.sh
./FRSample
```

1. Go to the main.cc file and configure the path of the file you want to parse to the variable file_path
2. Configure the SDK key parameter of the "startRequestParser" interface and you will be able to parse the file for the version of Flight Record 13
3. Run the above script

## How to compile the library?

### Mac

```shell
cd dji-flightrecord-kit/build/Mac/FlightRecordStandardizationCpp
sh generate.sh
./FRSample
```

1. Run the above script
2. Get the library you want, the header files are stored in the dji-flightrecord-kit/source/FlightRecordStandardizationCpp/parser/DJIFRProtoParser.hpp

### Ubuntu

```shell
cd dji-flightrecord-kit/build/Ubuntu/FlightRecordStandardizationCpp
sh generate.sh
./FRSample
```

1. Run the above script
2. Get the library you want, the header files are stored in the dji-flightrecord-kit/source/FlightRecordStandardizationCpp/parser/DJIFRProtoParser.hpp

## Error Codes

If an error occurs during the flight record files parsing, you can solve the problem according to the returned value. The table below shows returned values and error descriptions. Returned value 0 indicates successful parsing.

<table align="center">
  <thead>
    <tr>
      <th>Error Code</th>
      <th>Error Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
        <td>1</td>
        <td>Illegal input parameter</td>
    </tr>
    <tr>
        <td>2</td>
        <td>Illegal flight record file content</td>
    </tr>
    <tr>
        <td>3</td>
        <td>Unsupported flight record file version</td>
    </tr>
    <tr>
        <td>4</td>
        <td>The flight record parser does not exist</td>
    </tr>
    <tr>
        <td>5</td>
        <td>The flight record file includes unsupported functions</td>
    </tr>
    <tr>
        <td>6</td>
        <td>Parsing failed due to message loss</td>
    </tr>
    <tr>
        <td>7</td>
        <td>File operation failed</td>
    </tr>
    <tr>
        <td>8</td>
        <td>Invalid data. The file might be modified </td>
    </tr>
    <tr>
        <td>9</td>
        <td>Data filling failed. Unsupported data filling types</td>
    </tr>
    <tr>
        <td>255</td>
        <td>Unknown error</td>
    </tr>
   </tbody>
</table>

## Credits

FlightRecord is owned and maintained by [DJI SDK](https://developer.dji.com).

## Support

Expect more customized data, please let us know your data needs and application scenarios.
You can get support from DJI with the following methods:

* dev@dji.com

## License

DJIFlightRecord is available under the MIT license. See the LICENSE.txt file for more info.
