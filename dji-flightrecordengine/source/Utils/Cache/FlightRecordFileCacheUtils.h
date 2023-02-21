//
//  FlightRecordFileCacheUtils.hpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordFileCacheUtils_hpp
#define FlightRecordFileCacheUtils_hpp

#include <stdio.h>
#include <functional>
#include <iostream>
#include <memory>

namespace DJI {
    namespace FlightRecord {
        class FileHandlerUtils;
        
        /**
         *  It will read the file, and store the data in memory
         *  All the interface is not safe in thread.
         */
        class FileCacheUtils {
        public:
            FileCacheUtils(std::shared_ptr<FileHandlerUtils> fileHandler, long location, long length);
            
            ~FileCacheUtils();
            
            /**
             * read the data in file
             
             @param inputStream the memory to store the data
             @param size need to read size
             @return if success when the return value is same to size. if -1, it's failure.
             */
            size_t read(void *inputStream, size_t size);
            
            /**
             * Sets the position indicator associated with the stream to a new position.
             
             @param offset the offset from begin position
             @return if success the return value will be zero. if non-zero, it's failure.
             */
            size_t seekFromStart(long offset);
            
        public:
            long m_location;
            long m_cacheSize;
            
        private:
            uint8_t *m_cache;
        };
    
        using FileCacheUtilsPtr = std::shared_ptr<FileCacheUtils>;
    }
}

#endif /* FlightRecordFileCacheUtils_hpp */
