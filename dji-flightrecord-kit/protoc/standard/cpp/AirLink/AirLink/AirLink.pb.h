// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AirLink/AirLink.proto

#ifndef PROTOBUF_AirLink_2fAirLink_2eproto__INCLUDED
#define PROTOBUF_AirLink_2fAirLink_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_AirLink_2fAirLink_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsAirLinkStateImpl();
void InitDefaultsAirLinkState();
inline void InitDefaults() {
  InitDefaultsAirLinkState();
}
}  // namespace protobuf_AirLink_2fAirLink_2eproto
namespace DJIFRProto {
namespace Standard {
class AirLinkState;
class AirLinkStateDefaultTypeInternal;
extern AirLinkStateDefaultTypeInternal _AirLinkState_default_instance_;
}  // namespace Standard
}  // namespace DJIFRProto
namespace DJIFRProto {
namespace Standard {

// ===================================================================

class AirLinkState : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:DJIFRProto.Standard.AirLinkState) */ {
 public:
  AirLinkState();
  virtual ~AirLinkState();

  AirLinkState(const AirLinkState& from);

  inline AirLinkState& operator=(const AirLinkState& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AirLinkState(AirLinkState&& from) noexcept
    : AirLinkState() {
    *this = ::std::move(from);
  }

  inline AirLinkState& operator=(AirLinkState&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const AirLinkState& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AirLinkState* internal_default_instance() {
    return reinterpret_cast<const AirLinkState*>(
               &_AirLinkState_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(AirLinkState* other);
  friend void swap(AirLinkState& a, AirLinkState& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AirLinkState* New() const PROTOBUF_FINAL { return New(NULL); }

  AirLinkState* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const AirLinkState& from);
  void MergeFrom(const AirLinkState& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(AirLinkState* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 downlinkSignalQuality = 1;
  void clear_downlinksignalquality();
  static const int kDownlinkSignalQualityFieldNumber = 1;
  ::google::protobuf::int32 downlinksignalquality() const;
  void set_downlinksignalquality(::google::protobuf::int32 value);

  // int32 uplinkSignalQuality = 3;
  void clear_uplinksignalquality();
  static const int kUplinkSignalQualityFieldNumber = 3;
  ::google::protobuf::int32 uplinksignalquality() const;
  void set_uplinksignalquality(::google::protobuf::int32 value);

  // bool hasDownlinkSignalQuality = 2;
  void clear_hasdownlinksignalquality();
  static const int kHasDownlinkSignalQualityFieldNumber = 2;
  bool hasdownlinksignalquality() const;
  void set_hasdownlinksignalquality(bool value);

  // bool hasUplinkSignalQuality = 4;
  void clear_hasuplinksignalquality();
  static const int kHasUplinkSignalQualityFieldNumber = 4;
  bool hasuplinksignalquality() const;
  void set_hasuplinksignalquality(bool value);

  // @@protoc_insertion_point(class_scope:DJIFRProto.Standard.AirLinkState)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 downlinksignalquality_;
  ::google::protobuf::int32 uplinksignalquality_;
  bool hasdownlinksignalquality_;
  bool hasuplinksignalquality_;
  mutable int _cached_size_;
  friend struct ::protobuf_AirLink_2fAirLink_2eproto::TableStruct;
  friend void ::protobuf_AirLink_2fAirLink_2eproto::InitDefaultsAirLinkStateImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// AirLinkState

// int32 downlinkSignalQuality = 1;
inline void AirLinkState::clear_downlinksignalquality() {
  downlinksignalquality_ = 0;
}
inline ::google::protobuf::int32 AirLinkState::downlinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.downlinkSignalQuality)
  return downlinksignalquality_;
}
inline void AirLinkState::set_downlinksignalquality(::google::protobuf::int32 value) {
  
  downlinksignalquality_ = value;
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.downlinkSignalQuality)
}

// bool hasDownlinkSignalQuality = 2;
inline void AirLinkState::clear_hasdownlinksignalquality() {
  hasdownlinksignalquality_ = false;
}
inline bool AirLinkState::hasdownlinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.hasDownlinkSignalQuality)
  return hasdownlinksignalquality_;
}
inline void AirLinkState::set_hasdownlinksignalquality(bool value) {
  
  hasdownlinksignalquality_ = value;
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.hasDownlinkSignalQuality)
}

// int32 uplinkSignalQuality = 3;
inline void AirLinkState::clear_uplinksignalquality() {
  uplinksignalquality_ = 0;
}
inline ::google::protobuf::int32 AirLinkState::uplinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.uplinkSignalQuality)
  return uplinksignalquality_;
}
inline void AirLinkState::set_uplinksignalquality(::google::protobuf::int32 value) {
  
  uplinksignalquality_ = value;
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.uplinkSignalQuality)
}

// bool hasUplinkSignalQuality = 4;
inline void AirLinkState::clear_hasuplinksignalquality() {
  hasuplinksignalquality_ = false;
}
inline bool AirLinkState::hasuplinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.hasUplinkSignalQuality)
  return hasuplinksignalquality_;
}
inline void AirLinkState::set_hasuplinksignalquality(bool value) {
  
  hasuplinksignalquality_ = value;
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.hasUplinkSignalQuality)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Standard
}  // namespace DJIFRProto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AirLink_2fAirLink_2eproto__INCLUDED
