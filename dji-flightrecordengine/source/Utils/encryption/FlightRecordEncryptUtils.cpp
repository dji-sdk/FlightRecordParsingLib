//
//  FlightRecordEncryptUtils.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <Utils/encryption/FlightRecordEncryptUtils.h>
#include <Utils/encryption/FlightRecordCRC64.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

using namespace DJI::FlightRecord;

static const uint64_t sample_tab[1] = {
    UINT64_C(0x123456789ABCDEF0),
};
static const uint64_t sample_tab_count = 1;

////////////////////////////////////////////////////////////////////////////////
//                      Copy From iOS DJI GO Begin                            //
////////////////////////////////////////////////////////////////////////////////

static void doXor(uint8_t *destBuffer, uint8_t* originbuffer, uint8_t* key ,uint64_t bufferLen,uint8_t lastChar) {
    int i=0;
    //xor
    for(i=0;i <bufferLen;i++)
        destBuffer[i] = originbuffer[i]^key[i];
    destBuffer[i] = lastChar^key[i];
}

static uint8_t getNumber() {
    //generate a random uint8
    //srand(time(NULL));
    return (uint8_t) rand()%256;
}

static void getKey(uint8_t* key, uint16_t keyLen, uint8_t crc, uint64_t magicStr) {
    uint64_t crcRes = crc64(crc,(unsigned char*)&magicStr,sizeof(uint64_t));
    
    
    int times = keyLen / sizeof(uint64_t);
    
    //uint8_t* newKey = (uint8_t*)malloc((times+1)*sizeof(uint64_t));
    int i=0;
    while (i<=times) {
        //uint64_t tmpCRC = crcRes << i;
        if((i+1)*sizeof(uint64_t)<=keyLen ){
            memcpy(key+i*sizeof(uint64_t), &crcRes, sizeof(uint64_t));
        }
        else if(keyLen >= (i)*sizeof(uint64_t)){
            memcpy(key+i*sizeof(uint64_t), &crcRes,  keyLen - (i)*sizeof(uint64_t));
        }
        i++;
    }
    
    return;
}

uint64_t DJI::FlightRecord::deEncryptData(uint8_t* destBuffer, uint8_t* originBuffer, uint16_t originBufferLen, int paraType, uint64_t encryptVersion){
    if(originBufferLen<=2){
        return 0;
    }
    
    uint64_t magicStr;
    if(encryptVersion<sample_tab_count){
        magicStr = sample_tab[encryptVersion];
    }else{
        return 0;
    }
    
    uint64_t result= 0;
    uint8_t firstChar = originBuffer[0];
    
    uint8_t lastChar = originBuffer[originBufferLen-1];
    
    
    
    
    uint8_t*key  = (uint8_t*)malloc(originBufferLen-1);
    
    uint8_t *destBufferCopy = (uint8_t*)malloc(originBufferLen-1);
    
    getKey(key, originBufferLen-1, (firstChar+encryptVersion+paraType ), magicStr*firstChar);
    
    doXor(destBufferCopy, originBuffer+1, key, originBufferLen-2 ,lastChar);
    
    memcpy(destBuffer, destBufferCopy, originBufferLen-2);
    
    if(destBufferCopy[originBufferLen-2] == (firstChar + paraType + (uint8_t)encryptVersion) % 256)
        result = originBufferLen-2;//success
    if(key)
        free(key);
    if(destBufferCopy)
        free(destBufferCopy);
    return result;
}

//MARK: - PKCS7 Padding

BufferPtr DJI::FlightRecord::RemovePKCS7Padding(void *buffer, unsigned long length, int block_size) {
    unsigned char lastBuffer = *((unsigned char *)buffer + length - 1);
    if ((unsigned long)lastBuffer > block_size) {
        return std::make_shared<Buffer>(buffer, length);
    }
    
    auto buff_len = length - lastBuffer;
    if (buff_len <= 0) {
        assert(false && "Invalid PKCS7 Padding");
        return nullptr;
    }
    
    return std::make_shared<Buffer>(buffer, buff_len);
}
