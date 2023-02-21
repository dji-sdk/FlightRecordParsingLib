//
//  FlightRecordFileHandleUtils.hpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordFileHandleUtils_hpp
#define FlightRecordFileHandleUtils_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <Parser/FlightRecordParserDataTypePublic.h>

namespace DJI {
    namespace FlightRecord {
        enum class FileHandleType {
            FileHandlerReader = 0,
            // if the file exist, it will append to write. If not, it will create one.
            FileHandlerReaderAndWriterWithExistContent,
            // if the file exist, it will empty the file, and write it as a new file
            FileHandlerReaderAndWriterByNewFile,
        };
        
        /**
         *  Using to control the file stream
         *  All the interface is not safe in thread.
         */
        class FileHandlerUtils : public std::enable_shared_from_this<FileHandlerUtils> {
        public:
            /**
             * read the data in file
             
             @param filePath the file path
             @param handleType operation permissions
             */
            FileHandlerUtils(std::string filePath, FileHandleType handleType);
            ~FileHandlerUtils();
            
            /**
             * know the handler can read or not.

             @return ParserResult
             */
            ParserResult canRead();
            
            /**
             * know the handler can write or not.
             
             @return ParserResult
             */
            ParserResult canWrite();
            
            /**
             * read the data in file

             @param inputStream the memory to store the data
             @param size need to read size
             @return if success when the return value is same to size. if -1, it's failure.
             */
            size_t read(void *inputStream, size_t size);
            
            /**
             * write the data in file
             
             @param outputStream the memory data to storage
             @param size need to write size
             @return if success when the return value is same to size. if -1, it's failure.
             */
            size_t write(void *outputStream, size_t size);
            
            /**
             * write the data in the storage
             
             @return if success the result is 0. if failure, it will result eof error code.
             */
            int flush();
            
            /**
             * Sets the position indicator associated with the stream to a new position.

             @param offset the offset from begin position
             @return if success the return value will be zero. if non-zero, it's failure.
             */
            size_t seekFromStart(long offset);
            
        public:
            //////////////////////////////// Public Property ////////////////////////////////
            FileHandleType m_HandleType;
            long m_FileSize;
            long m_FileLocation;
            
        private:
            std::shared_ptr<std::string> m_FilePath;
            FILE *file_handle_;
            
        };
    
        using FileHandlerUtilsPtr = std::shared_ptr<FileHandlerUtils>;
    }
}

#endif /* FlightRecordFileHandleUtils_hpp */
