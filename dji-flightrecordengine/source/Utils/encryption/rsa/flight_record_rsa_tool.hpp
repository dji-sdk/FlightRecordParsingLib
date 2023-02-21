//
//  flight_record_rsa_tool.hpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef flight_record_rsa_tool_hpp
#define flight_record_rsa_tool_hpp

#include <stdio.h>
#include <Utils/buffer/flight_record_buffer.h>
#include <tomcrypt.h>

#define FR_SHA256_Length 32

namespace DJI {
    namespace FlightRecord {
    
        /// Decrypted the ciphertext by using the RSA decrypted method.
        /// @param ciphertext the ciphertext
        /// @param lparam the RSA lparam.
        /// @param rsa_custom_key the RSA key.
        BufferPtr RSADecryptData(const BufferPtr& ciphertext,
                                 const BufferPtr& lparam,
                                 rsa_key& rsa_custom_key);
    }
}

#endif /* flight_record_rsa_tool_hpp */
