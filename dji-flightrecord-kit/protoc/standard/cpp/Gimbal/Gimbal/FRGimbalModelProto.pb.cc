// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Gimbal/FRGimbalModelProto.proto

#include "Gimbal/FRGimbalModelProto.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace DJIFRProto {
namespace Standard {
PROTOBUF_CONSTEXPR GimbalState::GimbalState(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.atitude_)*/nullptr
  , /*decltype(_impl_.finetunedroll_)*/0
  , /*decltype(_impl_.finetunedpitch_)*/0
  , /*decltype(_impl_.finetunedyaw_)*/0
  , /*decltype(_impl_.isrollatstop_)*/false
  , /*decltype(_impl_.isyawatstop_)*/false
  , /*decltype(_impl_.ispitchatstop_)*/false
  , /*decltype(_impl_.yawrelativetoaircraftheading_)*/0
  , /*decltype(_impl_.mode_)*/0
  , /*decltype(_impl_.index_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct GimbalStateDefaultTypeInternal {
  PROTOBUF_CONSTEXPR GimbalStateDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~GimbalStateDefaultTypeInternal() {}
  union {
    GimbalState _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 GimbalStateDefaultTypeInternal _GimbalState_default_instance_;
}  // namespace Standard
}  // namespace DJIFRProto
static ::_pb::Metadata file_level_metadata_Gimbal_2fFRGimbalModelProto_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Gimbal_2fFRGimbalModelProto_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Gimbal_2fFRGimbalModelProto_2eproto = nullptr;

const uint32_t TableStruct_Gimbal_2fFRGimbalModelProto_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.atitude_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.finetunedroll_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.finetunedpitch_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.finetunedyaw_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.isrollatstop_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.isyawatstop_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.ispitchatstop_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.yawrelativetoaircraftheading_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.mode_),
  PROTOBUF_FIELD_OFFSET(::DJIFRProto::Standard::GimbalState, _impl_.index_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::DJIFRProto::Standard::GimbalState)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::DJIFRProto::Standard::_GimbalState_default_instance_._instance,
};

const char descriptor_table_protodef_Gimbal_2fFRGimbalModelProto_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\037Gimbal/FRGimbalModelProto.proto\022\023DJIFR"
  "Proto.Standard\032\037Common/FRCommonModelProt"
  "o.proto\"\250\002\n\013GimbalState\022.\n\007atitude\030\001 \001(\013"
  "2\035.DJIFRProto.Standard.Attitude\022\025\n\rfineT"
  "unedRoll\030\002 \001(\002\022\026\n\016fineTunedPitch\030\003 \001(\002\022\024"
  "\n\014fineTunedYaw\030\004 \001(\002\022\024\n\014isRollAtStop\030\005 \001"
  "(\010\022\023\n\013isYawAtStop\030\006 \001(\010\022\025\n\risPitchAtStop"
  "\030\007 \001(\010\022$\n\034yawRelativeToAircraftHeading\030\010"
  " \001(\001\022-\n\004mode\030\t \001(\0162\037.DJIFRProto.Standard"
  ".GimbalMode\022\r\n\005index\030\n \001(\005*.\n\nGimbalMode"
  "\022\010\n\004Free\020\000\022\007\n\003FPV\020\001\022\r\n\tYawFollow\020\002B\r\242\002\nD"
  "JIFRProtob\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_deps[1] = {
  &::descriptor_table_Common_2fFRCommonModelProto_2eproto,
};
static ::_pbi::once_flag descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto = {
    false, false, 457, descriptor_table_protodef_Gimbal_2fFRGimbalModelProto_2eproto,
    "Gimbal/FRGimbalModelProto.proto",
    &descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_once, descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_deps, 1, 1,
    schemas, file_default_instances, TableStruct_Gimbal_2fFRGimbalModelProto_2eproto::offsets,
    file_level_metadata_Gimbal_2fFRGimbalModelProto_2eproto, file_level_enum_descriptors_Gimbal_2fFRGimbalModelProto_2eproto,
    file_level_service_descriptors_Gimbal_2fFRGimbalModelProto_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_getter() {
  return &descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Gimbal_2fFRGimbalModelProto_2eproto(&descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto);
namespace DJIFRProto {
namespace Standard {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* GimbalMode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto);
  return file_level_enum_descriptors_Gimbal_2fFRGimbalModelProto_2eproto[0];
}
bool GimbalMode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class GimbalState::_Internal {
 public:
  static const ::DJIFRProto::Standard::Attitude& atitude(const GimbalState* msg);
};

const ::DJIFRProto::Standard::Attitude&
GimbalState::_Internal::atitude(const GimbalState* msg) {
  return *msg->_impl_.atitude_;
}
void GimbalState::clear_atitude() {
  if (GetArenaForAllocation() == nullptr && _impl_.atitude_ != nullptr) {
    delete _impl_.atitude_;
  }
  _impl_.atitude_ = nullptr;
}
GimbalState::GimbalState(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:DJIFRProto.Standard.GimbalState)
}
GimbalState::GimbalState(const GimbalState& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  GimbalState* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.atitude_){nullptr}
    , decltype(_impl_.finetunedroll_){}
    , decltype(_impl_.finetunedpitch_){}
    , decltype(_impl_.finetunedyaw_){}
    , decltype(_impl_.isrollatstop_){}
    , decltype(_impl_.isyawatstop_){}
    , decltype(_impl_.ispitchatstop_){}
    , decltype(_impl_.yawrelativetoaircraftheading_){}
    , decltype(_impl_.mode_){}
    , decltype(_impl_.index_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_atitude()) {
    _this->_impl_.atitude_ = new ::DJIFRProto::Standard::Attitude(*from._impl_.atitude_);
  }
  ::memcpy(&_impl_.finetunedroll_, &from._impl_.finetunedroll_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.index_) -
    reinterpret_cast<char*>(&_impl_.finetunedroll_)) + sizeof(_impl_.index_));
  // @@protoc_insertion_point(copy_constructor:DJIFRProto.Standard.GimbalState)
}

inline void GimbalState::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.atitude_){nullptr}
    , decltype(_impl_.finetunedroll_){0}
    , decltype(_impl_.finetunedpitch_){0}
    , decltype(_impl_.finetunedyaw_){0}
    , decltype(_impl_.isrollatstop_){false}
    , decltype(_impl_.isyawatstop_){false}
    , decltype(_impl_.ispitchatstop_){false}
    , decltype(_impl_.yawrelativetoaircraftheading_){0}
    , decltype(_impl_.mode_){0}
    , decltype(_impl_.index_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

GimbalState::~GimbalState() {
  // @@protoc_insertion_point(destructor:DJIFRProto.Standard.GimbalState)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void GimbalState::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete _impl_.atitude_;
}

void GimbalState::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void GimbalState::Clear() {
// @@protoc_insertion_point(message_clear_start:DJIFRProto.Standard.GimbalState)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaForAllocation() == nullptr && _impl_.atitude_ != nullptr) {
    delete _impl_.atitude_;
  }
  _impl_.atitude_ = nullptr;
  ::memset(&_impl_.finetunedroll_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.index_) -
      reinterpret_cast<char*>(&_impl_.finetunedroll_)) + sizeof(_impl_.index_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GimbalState::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .DJIFRProto.Standard.Attitude atitude = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_atitude(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // float fineTunedRoll = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 21)) {
          _impl_.finetunedroll_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float fineTunedPitch = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.finetunedpitch_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float fineTunedYaw = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.finetunedyaw_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // bool isRollAtStop = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.isrollatstop_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool isYawAtStop = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.isyawatstop_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool isPitchAtStop = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          _impl_.ispitchatstop_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // double yawRelativeToAircraftHeading = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 65)) {
          _impl_.yawrelativetoaircraftheading_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // .DJIFRProto.Standard.GimbalMode mode = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 72)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_mode(static_cast<::DJIFRProto::Standard::GimbalMode>(val));
        } else
          goto handle_unusual;
        continue;
      // int32 index = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 80)) {
          _impl_.index_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* GimbalState::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:DJIFRProto.Standard.GimbalState)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .DJIFRProto.Standard.Attitude atitude = 1;
  if (this->_internal_has_atitude()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::atitude(this),
        _Internal::atitude(this).GetCachedSize(), target, stream);
  }

  // float fineTunedRoll = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedroll = this->_internal_finetunedroll();
  uint32_t raw_finetunedroll;
  memcpy(&raw_finetunedroll, &tmp_finetunedroll, sizeof(tmp_finetunedroll));
  if (raw_finetunedroll != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(2, this->_internal_finetunedroll(), target);
  }

  // float fineTunedPitch = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedpitch = this->_internal_finetunedpitch();
  uint32_t raw_finetunedpitch;
  memcpy(&raw_finetunedpitch, &tmp_finetunedpitch, sizeof(tmp_finetunedpitch));
  if (raw_finetunedpitch != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_finetunedpitch(), target);
  }

  // float fineTunedYaw = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedyaw = this->_internal_finetunedyaw();
  uint32_t raw_finetunedyaw;
  memcpy(&raw_finetunedyaw, &tmp_finetunedyaw, sizeof(tmp_finetunedyaw));
  if (raw_finetunedyaw != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_finetunedyaw(), target);
  }

  // bool isRollAtStop = 5;
  if (this->_internal_isrollatstop() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(5, this->_internal_isrollatstop(), target);
  }

  // bool isYawAtStop = 6;
  if (this->_internal_isyawatstop() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(6, this->_internal_isyawatstop(), target);
  }

  // bool isPitchAtStop = 7;
  if (this->_internal_ispitchatstop() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(7, this->_internal_ispitchatstop(), target);
  }

  // double yawRelativeToAircraftHeading = 8;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_yawrelativetoaircraftheading = this->_internal_yawrelativetoaircraftheading();
  uint64_t raw_yawrelativetoaircraftheading;
  memcpy(&raw_yawrelativetoaircraftheading, &tmp_yawrelativetoaircraftheading, sizeof(tmp_yawrelativetoaircraftheading));
  if (raw_yawrelativetoaircraftheading != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(8, this->_internal_yawrelativetoaircraftheading(), target);
  }

  // .DJIFRProto.Standard.GimbalMode mode = 9;
  if (this->_internal_mode() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      9, this->_internal_mode(), target);
  }

  // int32 index = 10;
  if (this->_internal_index() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(10, this->_internal_index(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DJIFRProto.Standard.GimbalState)
  return target;
}

size_t GimbalState::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:DJIFRProto.Standard.GimbalState)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .DJIFRProto.Standard.Attitude atitude = 1;
  if (this->_internal_has_atitude()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.atitude_);
  }

  // float fineTunedRoll = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedroll = this->_internal_finetunedroll();
  uint32_t raw_finetunedroll;
  memcpy(&raw_finetunedroll, &tmp_finetunedroll, sizeof(tmp_finetunedroll));
  if (raw_finetunedroll != 0) {
    total_size += 1 + 4;
  }

  // float fineTunedPitch = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedpitch = this->_internal_finetunedpitch();
  uint32_t raw_finetunedpitch;
  memcpy(&raw_finetunedpitch, &tmp_finetunedpitch, sizeof(tmp_finetunedpitch));
  if (raw_finetunedpitch != 0) {
    total_size += 1 + 4;
  }

  // float fineTunedYaw = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedyaw = this->_internal_finetunedyaw();
  uint32_t raw_finetunedyaw;
  memcpy(&raw_finetunedyaw, &tmp_finetunedyaw, sizeof(tmp_finetunedyaw));
  if (raw_finetunedyaw != 0) {
    total_size += 1 + 4;
  }

  // bool isRollAtStop = 5;
  if (this->_internal_isrollatstop() != 0) {
    total_size += 1 + 1;
  }

  // bool isYawAtStop = 6;
  if (this->_internal_isyawatstop() != 0) {
    total_size += 1 + 1;
  }

  // bool isPitchAtStop = 7;
  if (this->_internal_ispitchatstop() != 0) {
    total_size += 1 + 1;
  }

  // double yawRelativeToAircraftHeading = 8;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_yawrelativetoaircraftheading = this->_internal_yawrelativetoaircraftheading();
  uint64_t raw_yawrelativetoaircraftheading;
  memcpy(&raw_yawrelativetoaircraftheading, &tmp_yawrelativetoaircraftheading, sizeof(tmp_yawrelativetoaircraftheading));
  if (raw_yawrelativetoaircraftheading != 0) {
    total_size += 1 + 8;
  }

  // .DJIFRProto.Standard.GimbalMode mode = 9;
  if (this->_internal_mode() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_mode());
  }

  // int32 index = 10;
  if (this->_internal_index() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_index());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData GimbalState::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    GimbalState::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GimbalState::GetClassData() const { return &_class_data_; }


void GimbalState::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<GimbalState*>(&to_msg);
  auto& from = static_cast<const GimbalState&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:DJIFRProto.Standard.GimbalState)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_atitude()) {
    _this->_internal_mutable_atitude()->::DJIFRProto::Standard::Attitude::MergeFrom(
        from._internal_atitude());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedroll = from._internal_finetunedroll();
  uint32_t raw_finetunedroll;
  memcpy(&raw_finetunedroll, &tmp_finetunedroll, sizeof(tmp_finetunedroll));
  if (raw_finetunedroll != 0) {
    _this->_internal_set_finetunedroll(from._internal_finetunedroll());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedpitch = from._internal_finetunedpitch();
  uint32_t raw_finetunedpitch;
  memcpy(&raw_finetunedpitch, &tmp_finetunedpitch, sizeof(tmp_finetunedpitch));
  if (raw_finetunedpitch != 0) {
    _this->_internal_set_finetunedpitch(from._internal_finetunedpitch());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_finetunedyaw = from._internal_finetunedyaw();
  uint32_t raw_finetunedyaw;
  memcpy(&raw_finetunedyaw, &tmp_finetunedyaw, sizeof(tmp_finetunedyaw));
  if (raw_finetunedyaw != 0) {
    _this->_internal_set_finetunedyaw(from._internal_finetunedyaw());
  }
  if (from._internal_isrollatstop() != 0) {
    _this->_internal_set_isrollatstop(from._internal_isrollatstop());
  }
  if (from._internal_isyawatstop() != 0) {
    _this->_internal_set_isyawatstop(from._internal_isyawatstop());
  }
  if (from._internal_ispitchatstop() != 0) {
    _this->_internal_set_ispitchatstop(from._internal_ispitchatstop());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_yawrelativetoaircraftheading = from._internal_yawrelativetoaircraftheading();
  uint64_t raw_yawrelativetoaircraftheading;
  memcpy(&raw_yawrelativetoaircraftheading, &tmp_yawrelativetoaircraftheading, sizeof(tmp_yawrelativetoaircraftheading));
  if (raw_yawrelativetoaircraftheading != 0) {
    _this->_internal_set_yawrelativetoaircraftheading(from._internal_yawrelativetoaircraftheading());
  }
  if (from._internal_mode() != 0) {
    _this->_internal_set_mode(from._internal_mode());
  }
  if (from._internal_index() != 0) {
    _this->_internal_set_index(from._internal_index());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void GimbalState::CopyFrom(const GimbalState& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:DJIFRProto.Standard.GimbalState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GimbalState::IsInitialized() const {
  return true;
}

void GimbalState::InternalSwap(GimbalState* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(GimbalState, _impl_.index_)
      + sizeof(GimbalState::_impl_.index_)
      - PROTOBUF_FIELD_OFFSET(GimbalState, _impl_.atitude_)>(
          reinterpret_cast<char*>(&_impl_.atitude_),
          reinterpret_cast<char*>(&other->_impl_.atitude_));
}

::PROTOBUF_NAMESPACE_ID::Metadata GimbalState::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_getter, &descriptor_table_Gimbal_2fFRGimbalModelProto_2eproto_once,
      file_level_metadata_Gimbal_2fFRGimbalModelProto_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Standard
}  // namespace DJIFRProto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::DJIFRProto::Standard::GimbalState*
Arena::CreateMaybeMessage< ::DJIFRProto::Standard::GimbalState >(Arena* arena) {
  return Arena::CreateMessageInternal< ::DJIFRProto::Standard::GimbalState >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
