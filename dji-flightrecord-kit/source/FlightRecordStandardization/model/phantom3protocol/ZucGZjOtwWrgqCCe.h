//
//  ZucGZjOtwWrgqCCe.h
//  FlightRecordKit
//
//  Copyright © 2017 dji. All rights reserved.
//

#ifndef ZucGZjOtwWrgqCCe_h
#define ZucGZjOtwWrgqCCe_h

#pragma pack(1)
/**
 *  @brief joystick
 */
typedef struct
{
    uint8_t mFlag;
    float mRoll;          //Aircraft Roll. left and right panning [-30, 30] degrees
    float mPitch;         //Aircraft Pitch. forward or reverse [-30, 30] degrees.
    float mYaw;           //Aircraft Yaw. left and right rotation [-180, 180] degrees
    float mThrottle;      //Aircraft throttle.    Up or down [-5, 5]m/s
}GSJoystickData;

typedef struct {
    uint8_t ctdEkCtOjwPqMlcc;
} ytvyrhTCbgeMPBrj;

typedef struct {
    uint8_t OFnneYcvdNWWRwLH;
}awqIdgRJuPbLbnPs;

typedef struct
{
    uint8_t lApQZpUwFGvLQFZJ;
    uint8_t reserved;
}GPVBVDuWHHrNElzC;

typedef struct
{
    uint8_t oirzBEhcuqwBojPi;
    //
    uint8_t reserved;
}UErvlbTKNTNfbBID;

typedef struct
{
    GPVBVDuWHHrNElzC cuupIGlCfGIWyPdr;
    UErvlbTKNTNfbBID ugKjDbOFWYqwGzGK;
} fkWtLnwZUkkqeIdS;

typedef struct
{
    //4byte
    uint8_t UMVZnTkvPKuBTmSa;
    
    //5byte
    awqIdgRJuPbLbnPs tracking_avoid;
    
    //6byte
    uint8_t vIWHnMquREzEUdJB;
    
    //以上7字节
    uint8_t cBjOCByZbxwIZkmt;
} mKkrpblklcjEoiGp;

typedef struct {
    
    uint8_t fRdFifFFqRNRpogo;
    
    //1 byte
    uint8_t MheZdVfzyXELGWJH;
    
    //2 byte
    uint8_t seNDbGGhqbYXYPeJ;
    
    //3byte
    ytvyrhTCbgeMPBrj wjkNnYCzYvUOdfTU;
    
    union
    {
        mKkrpblklcjEoiGp yYhEmrNNBoTTMkAC;
        fkWtLnwZUkkqeIdS smartGoHomeStatus;
    } WLAxTbkGyLNJneyI;
    
    // 8 bytes
    uint32_t uIotsVUvlFIYomDJ;
    
    //12 byte 以上
    uint8_t FKaKCemXevmvpwNc;
    
} pjEvVPrhPuHWwlgx;

///////////////////////////// come from DJITomatoVisionCmdPack.h ///////////////////////////

#pragma pack()

#endif
