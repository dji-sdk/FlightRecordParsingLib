//
//  flight_record_buffer.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef flight_record_buffer_manage_hpp
#define flight_record_buffer_manage_hpp

#include <stdio.h>
#include <FlightRecordProtocolEnum.h>
#include <memory>

namespace DJI {
    namespace FlightRecord {
        class Buffer {
        public:
            Buffer(void *pointer, size_t length);
            Buffer(size_t length);
            virtual ~Buffer();
            
        public:
            void *buffer_pointer_;
            size_t buffer_length_;
        };
    
        enum class WriteOperation {
            Detail = 0,
            Snapshot,
            Thumbnail,
            Info,
            RewriteInfo,
            CheckSum,
            VersionCategory,
            /// Just need to update the detail data and without write buffer.
            RefreshDetailDataFromHead,
        };
        
        class WriterBuffer : public Buffer {
        public:
            WriterBuffer(FlightRecordDataType dataType, void *bytes, size_t len);
            WriterBuffer(FlightRecordDataType data_type, size_t len);
            ~WriterBuffer();
            
            FlightRecordDataType data_type_;
            
            void setWriteOperation(WriteOperation operation);
            WriteOperation writeOperation() const;
            
        private:
            WriteOperation write_operation_;
        };
        
        using BufferPtr = std::shared_ptr<Buffer>;
        using WriterBufferPtr = std::shared_ptr<WriterBuffer>;
    }
}

#endif /* flight_record_buffer_manage_hpp */
