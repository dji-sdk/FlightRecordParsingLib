//
//  FlightRecordFileCacheUtils.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Utils/Cache/FlightRecordFileCacheUtils.h>
#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace DJI::FlightRecord;

FileCacheUtils::FileCacheUtils(std::shared_ptr<FileHandlerUtils> fileHandler, long location, long length) :
m_cache(nullptr) {
    if (length <= 0) {
        return;
    }
    
    if (location >= fileHandler->m_FileSize) {
        return;
    }
    
    long readLength = std::min(length, fileHandler->m_FileSize - location);
    m_cache = (uint8_t *)malloc(readLength);
    m_location = 0;
    
    fileHandler->seekFromStart(location);
    m_cacheSize = fileHandler->read(m_cache, readLength);
}

FileCacheUtils::~FileCacheUtils() {
    if (m_cache) {
        free(m_cache);
    }
}

size_t FileCacheUtils::read(void *inputStream, size_t size) {
    if (size <= 0 || !m_cache) {
        return 0;
    }
    
    if (size + m_location <= m_cacheSize) {
        memcpy(inputStream, m_cache + m_location, size);
        m_location += size;
        
        return size;
    }
    
    return 0;
}

size_t FileCacheUtils::seekFromStart(long offset) {
    if (!m_cache) {
        return -1;
    }
    
    if (offset <= m_cacheSize) {
        m_location = offset;
        
        return 0;
    }
    
    return -1;
}
