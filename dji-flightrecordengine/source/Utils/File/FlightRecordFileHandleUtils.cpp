//
//  FlightRecordFileHandleUtils.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Utils/File/FlightRecordFileHandleUtils.h>
#include <stdio.h>

#include <iostream>
#include <Parser/FlightRecordParserDataTypePublic.h>
#ifdef WIN32
#include "winunistd.h"
#else
#include <unistd.h>
#endif // WIN32
#include <algorithm>


using namespace DJI::FlightRecord;

FileHandlerUtils::FileHandlerUtils(std::string filePath, FileHandleType handleType) {
    m_FilePath   = std::make_shared<std::string>(filePath);
    m_HandleType = handleType;
    
    switch (handleType) {
        case FileHandleType::FileHandlerReader:
        {
            file_handle_ = fopen(filePath.c_str(), "rb");
        }
            break;
        case FileHandleType::FileHandlerReaderAndWriterWithExistContent:
        {
            if (access(filePath.c_str(), F_OK) != 0) {
                file_handle_ = fopen(filePath.c_str(), "w+");
            } else {
                file_handle_ = fopen(filePath.c_str(), "rb+");
            }
        }
            break;
        case FileHandleType::FileHandlerReaderAndWriterByNewFile: {
            file_handle_ = fopen(filePath.c_str(), "w+");
        }
            
        default:
            break;
    }
    
    do {
        if (!file_handle_) {
            break;
        }
        
        switch (handleType) {
            case FileHandleType::FileHandlerReader:
            case FileHandleType::FileHandlerReaderAndWriterWithExistContent:
            {
                fseek(file_handle_, 0, SEEK_END);
                m_FileSize = ftell(file_handle_);
                rewind(file_handle_);
                m_FileLocation = ftell(file_handle_);
            }
                break;
                
            default:
                break;
        }
    } while (0);
}

FileHandlerUtils::~FileHandlerUtils() {
    if (canWrite() == ParserResult::Success) {
        fflush(file_handle_);
    }
    
    if (file_handle_) {
        fclose(file_handle_);
    }
}

ParserResult FileHandlerUtils::canRead() {
    do {
        if (!file_handle_) {
            break;
        }
        
        switch (m_HandleType) {
            case FileHandleType::FileHandlerReaderAndWriterWithExistContent:
            case FileHandleType::FileHandlerReader:
            case FileHandleType::FileHandlerReaderAndWriterByNewFile:
            {
                return ParserResult::Success;
            }
                break;
                
            default:
                break;
        }
    } while (0);
    
    return ParserResult::NoFileHandle;
}

ParserResult FileHandlerUtils::canWrite() {
    do {
        if (!file_handle_) {
            break;
        }
        
        switch (m_HandleType) {
            case FileHandleType::FileHandlerReaderAndWriterWithExistContent:
            case FileHandleType::FileHandlerReaderAndWriterByNewFile:
            {
                return ParserResult::Success;
            }
                break;
                
            default:
                break;
        }
    } while (0);
    
    return ParserResult::NoFileHandle;
}

size_t FileHandlerUtils::read(void *inputStream, size_t size) {
    if (size == 0) {
        return 0;
    }
    
    if (canRead() != ParserResult::Success) {
        return -1;
    }
    
    long leftFileSize = m_FileSize - m_FileLocation;
    long realReadSize = std::min<size_t>(size, (size_t)leftFileSize);
    size_t ret = fread(inputStream, 1, realReadSize, file_handle_);
    
    if (ret <= 0) {
        rewind(file_handle_);
        m_FileLocation = ftell(file_handle_);
        
        return ret;
    } else {
        m_FileLocation = ftell(file_handle_);
        
        return ret;
    }
}

size_t FileHandlerUtils::write(void *outputStream, size_t size) {
    if (size == 0) {
        return 0;
    }
    
    if (canWrite() != ParserResult::Success) {
        return -1;
    }
    
    size_t ret = fwrite(outputStream, 1, size, file_handle_);
    
    if (ret <= 0) {
        rewind(file_handle_);
        m_FileLocation = ftell(file_handle_);
        
        return ret;
    } else {
        m_FileLocation = ftell(file_handle_);
        
        if (m_FileLocation >= m_FileSize) {
            m_FileSize = m_FileLocation;
        }
        
        return ret;
    }
}

int FileHandlerUtils::flush() {
    if (canWrite() != ParserResult::Success) {
        return -1;
    }
    
    return fflush(file_handle_);
}

size_t FileHandlerUtils::seekFromStart(long offset) {
    if (!file_handle_) {
        return -1;
    }
    
    if (offset > m_FileSize) {
        return -1;
    }
    
    int ret = fseek(file_handle_, offset, SEEK_SET);
    
    if (ret != 0) {
        rewind(file_handle_);
    }
    
    m_FileLocation = ftell(file_handle_);
    
    return ret;
}
