//
//  FlightRecordEncryptUtils.hpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordEncryptUtils_hpp
#define FlightRecordEncryptUtils_hpp

#include <stdio.h>
#include <iostream>
#include <Utils/buffer/flight_record_buffer.h>

namespace DJI {
    namespace FlightRecord {
        
        uint64_t deEncryptData(uint8_t* destBuffer, uint8_t* originBuffer, uint16_t originBufferLen, int paraType, uint64_t encryptVersion);
    
        //MARK: - PKCS7 Padding
    
        /// Remove the PKCS7 Padding data.
        /// @param buffer  the padding data.
        /// @param length  the length of the padding data.
        /// @param block_size  the block size. Should be multiple of 8 bytes. The maximum number is 255.
        /// @return the data without padding.
        BufferPtr RemovePKCS7Padding(void *buffer,
                                     unsigned long length,
                                     int block_size);
    }
}

#endif /* FlightRecordEncryptUtils_hpp */
