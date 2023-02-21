//
//  flight_record_buffer_manage.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Utils/buffer/flight_record_buffer.h>
#include <functional>
#include <string.h>
#include <stdlib.h>

using namespace DJI::FlightRecord;

Buffer::Buffer(void *pointer, size_t length):
buffer_length_(length),
buffer_pointer_(nullptr) {
    if (pointer == nullptr || length <= 0) {
        return;
    }
    
    buffer_pointer_ = (uint8_t *)malloc(buffer_length_);
    memcpy(buffer_pointer_, pointer, length);
}

Buffer::Buffer(size_t length) :
buffer_length_(length),
buffer_pointer_(nullptr) {
    if (length <= 0) {
        return;
    }
    
    buffer_pointer_ = (uint8_t *)malloc(length);
}

Buffer::~Buffer() {
    if (buffer_pointer_) {
        free(buffer_pointer_);
        buffer_pointer_ = nullptr;
    }
}

WriterBuffer::WriterBuffer(FlightRecordDataType dataType, void *bytes, size_t len) :
Buffer::Buffer(bytes, len),
data_type_(dataType) {
    
}

WriterBuffer::WriterBuffer(FlightRecordDataType data_type, size_t len) :
Buffer::Buffer(len),
data_type_(data_type) {
    
}

WriterBuffer::~WriterBuffer() {
    
}

void WriterBuffer::setWriteOperation(WriteOperation operation) {
    write_operation_ = operation;
}

WriteOperation WriterBuffer::writeOperation() const {
    return write_operation_;
}
