//
//  fr_standardization_common.cpp
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#include "fr_standardization_common.hpp"
#include <string.h>
#include <cstdlib>

using namespace DJIFR::standardization;

//MARK: - LocationCoordinate2DImp

LocationCoordinate2DImp::LocationCoordinate2DImp(double latitude, double longitude) :
latitude_(latitude),
longitude_(longitude) {
    
}

LocationCoordinate2DImp::~LocationCoordinate2DImp() {
    
}

double LocationCoordinate2DImp::latitude() const {
    return latitude_;
}

double LocationCoordinate2DImp::longitude() const {
    return longitude_;
}

//MARK: - VelocityImp

VelocityImp::VelocityImp(float velocityX, float velocityY, float velocityZ) :
velocityX_(velocityX),
velocityY_(velocityY),
velocityZ_(velocityZ)
{
    
}

VelocityImp::~VelocityImp() {
    
}

float VelocityImp::velocityX() const {
    return velocityX_;
}

float VelocityImp::velocityY() const {
    return velocityY_;
}

float VelocityImp::velocityZ() const {
    return velocityZ_;
}

//MARK: - AttitudeImp

AttitudeImp::AttitudeImp(double pitch, double roll, double yaw) :
pitch_(pitch),
roll_(roll),
yaw_(yaw) {
    
}

AttitudeImp::~AttitudeImp() {
    
}

double AttitudeImp::pitch() const {
    return pitch_;
}

double AttitudeImp::roll() const {
    return roll_;
}

double AttitudeImp::yaw() const {
    return yaw_;
}

//MARK: - Buffer

Buffer::Buffer(void *pointer, size_t length) {
    length_ = length;
    void *temp = malloc(length);
    memcpy(temp, pointer, length);
    data_ = std::shared_ptr<void>(temp, [](void *ptr) {
        free(ptr);
    });
}

Buffer::Buffer(size_t length) {
    length_ = length;
    void *temp = calloc(length, 1);
    data_ = std::shared_ptr<void>(temp, [](void *ptr) {
        free(ptr);
    });
}

Buffer::~Buffer() {
    data_ = nullptr;
}

//MARK: - DecryptKeychain

DecryptKeychain::DecryptKeychain(const Buffer& private_key, const Buffer& lparam):
private_key_(private_key),
lparam_(lparam) {
    
}

DecryptKeychain::~DecryptKeychain() {
    
}
