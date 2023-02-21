//
//  flight_record_utf8.cpp
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include <Utils/string/flight_record_utf8.hpp>
#include <memory>
#include <string.h>

using namespace DJI::FlightRecord;

bool DJI::FlightRecord::isValidUTF8(const char* str, size_t strLen) {
    bool bAllAscii = false;
    unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
    unsigned char chr;
    
    for (unsigned int i = 0; i < strLen; ++i){
        chr = *(str + i);
        //判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
        if (nBytes == 0 && (chr & 0x80) != 0){
            bAllAscii = false;
        }
        if (nBytes == 0) {
            //如果不是ASCII码,应该是多字节符,计算字节数
            if (chr >= 0x80) {
                if (chr >= 0xFC && chr <= 0xFD){
                    nBytes = 6;
                }
                else if (chr >= 0xF8){
                    nBytes = 5;
                }
                else if (chr >= 0xF0){
                    nBytes = 4;
                }
                else if (chr >= 0xE0){
                    nBytes = 3;
                }
                else if (chr >= 0xC0){
                    nBytes = 2;
                }
                else{
                    return false;
                }
                nBytes--;
            }
        }
        else{
            //多字节符的非首字节,应为 10xxxxxx
            if ((chr & 0xC0) != 0x80){
                return false;
            }
            //减到为零为止
            nBytes--;
        }
    }
    
    //违返UTF8编码规则
    if (nBytes != 0) {
        return false;
    }
    if (bAllAscii){ //如果全部都是ASCII, 也是UTF8
        return true;
    }
    return true;
}

bool DJI::FlightRecord::isValidContent(const char* str, size_t strlen) {
    if (isValidUTF8(str, strlen) == false) {
        return false;
    }
    
    char empty = 0;
    for (int i = 0; i < strlen; i ++) {
        if (memcmp(&empty, (str + i), 1) != 0) {
            return true;
        }
    }
    
    return false;
}
