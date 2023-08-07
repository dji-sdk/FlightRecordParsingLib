// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AirLink/AirLink.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_AirLink_2fAirLink_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_AirLink_2fAirLink_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_AirLink_2fAirLink_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_AirLink_2fAirLink_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_AirLink_2fAirLink_2eproto;
namespace DJIFRProto {
namespace Standard {
class AirLinkState;
struct AirLinkStateDefaultTypeInternal;
extern AirLinkStateDefaultTypeInternal _AirLinkState_default_instance_;
}  // namespace Standard
}  // namespace DJIFRProto
PROTOBUF_NAMESPACE_OPEN
template<> ::DJIFRProto::Standard::AirLinkState* Arena::CreateMaybeMessage<::DJIFRProto::Standard::AirLinkState>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace DJIFRProto {
namespace Standard {

// ===================================================================

class AirLinkState final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:DJIFRProto.Standard.AirLinkState) */ {
 public:
  inline AirLinkState() : AirLinkState(nullptr) {}
  ~AirLinkState() override;
  explicit PROTOBUF_CONSTEXPR AirLinkState(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  AirLinkState(const AirLinkState& from);
  AirLinkState(AirLinkState&& from) noexcept
    : AirLinkState() {
    *this = ::std::move(from);
  }

  inline AirLinkState& operator=(const AirLinkState& from) {
    CopyFrom(from);
    return *this;
  }
  inline AirLinkState& operator=(AirLinkState&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const AirLinkState& default_instance() {
    return *internal_default_instance();
  }
  static inline const AirLinkState* internal_default_instance() {
    return reinterpret_cast<const AirLinkState*>(
               &_AirLinkState_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(AirLinkState& a, AirLinkState& b) {
    a.Swap(&b);
  }
  inline void Swap(AirLinkState* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AirLinkState* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AirLinkState* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AirLinkState>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const AirLinkState& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const AirLinkState& from) {
    AirLinkState::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AirLinkState* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "DJIFRProto.Standard.AirLinkState";
  }
  protected:
  explicit AirLinkState(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDownlinkSignalQualityFieldNumber = 1,
    kUplinkSignalQualityFieldNumber = 3,
    kHasDownlinkSignalQualityFieldNumber = 2,
    kHasUplinkSignalQualityFieldNumber = 4,
  };
  // int32 downlinkSignalQuality = 1;
  void clear_downlinksignalquality();
  int32_t downlinksignalquality() const;
  void set_downlinksignalquality(int32_t value);
  private:
  int32_t _internal_downlinksignalquality() const;
  void _internal_set_downlinksignalquality(int32_t value);
  public:

  // int32 uplinkSignalQuality = 3;
  void clear_uplinksignalquality();
  int32_t uplinksignalquality() const;
  void set_uplinksignalquality(int32_t value);
  private:
  int32_t _internal_uplinksignalquality() const;
  void _internal_set_uplinksignalquality(int32_t value);
  public:

  // bool hasDownlinkSignalQuality = 2;
  void clear_hasdownlinksignalquality();
  bool hasdownlinksignalquality() const;
  void set_hasdownlinksignalquality(bool value);
  private:
  bool _internal_hasdownlinksignalquality() const;
  void _internal_set_hasdownlinksignalquality(bool value);
  public:

  // bool hasUplinkSignalQuality = 4;
  void clear_hasuplinksignalquality();
  bool hasuplinksignalquality() const;
  void set_hasuplinksignalquality(bool value);
  private:
  bool _internal_hasuplinksignalquality() const;
  void _internal_set_hasuplinksignalquality(bool value);
  public:

  // @@protoc_insertion_point(class_scope:DJIFRProto.Standard.AirLinkState)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t downlinksignalquality_;
    int32_t uplinksignalquality_;
    bool hasdownlinksignalquality_;
    bool hasuplinksignalquality_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_AirLink_2fAirLink_2eproto;
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
  _impl_.downlinksignalquality_ = 0;
}
inline int32_t AirLinkState::_internal_downlinksignalquality() const {
  return _impl_.downlinksignalquality_;
}
inline int32_t AirLinkState::downlinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.downlinkSignalQuality)
  return _internal_downlinksignalquality();
}
inline void AirLinkState::_internal_set_downlinksignalquality(int32_t value) {
  
  _impl_.downlinksignalquality_ = value;
}
inline void AirLinkState::set_downlinksignalquality(int32_t value) {
  _internal_set_downlinksignalquality(value);
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.downlinkSignalQuality)
}

// bool hasDownlinkSignalQuality = 2;
inline void AirLinkState::clear_hasdownlinksignalquality() {
  _impl_.hasdownlinksignalquality_ = false;
}
inline bool AirLinkState::_internal_hasdownlinksignalquality() const {
  return _impl_.hasdownlinksignalquality_;
}
inline bool AirLinkState::hasdownlinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.hasDownlinkSignalQuality)
  return _internal_hasdownlinksignalquality();
}
inline void AirLinkState::_internal_set_hasdownlinksignalquality(bool value) {
  
  _impl_.hasdownlinksignalquality_ = value;
}
inline void AirLinkState::set_hasdownlinksignalquality(bool value) {
  _internal_set_hasdownlinksignalquality(value);
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.hasDownlinkSignalQuality)
}

// int32 uplinkSignalQuality = 3;
inline void AirLinkState::clear_uplinksignalquality() {
  _impl_.uplinksignalquality_ = 0;
}
inline int32_t AirLinkState::_internal_uplinksignalquality() const {
  return _impl_.uplinksignalquality_;
}
inline int32_t AirLinkState::uplinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.uplinkSignalQuality)
  return _internal_uplinksignalquality();
}
inline void AirLinkState::_internal_set_uplinksignalquality(int32_t value) {
  
  _impl_.uplinksignalquality_ = value;
}
inline void AirLinkState::set_uplinksignalquality(int32_t value) {
  _internal_set_uplinksignalquality(value);
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.uplinkSignalQuality)
}

// bool hasUplinkSignalQuality = 4;
inline void AirLinkState::clear_hasuplinksignalquality() {
  _impl_.hasuplinksignalquality_ = false;
}
inline bool AirLinkState::_internal_hasuplinksignalquality() const {
  return _impl_.hasuplinksignalquality_;
}
inline bool AirLinkState::hasuplinksignalquality() const {
  // @@protoc_insertion_point(field_get:DJIFRProto.Standard.AirLinkState.hasUplinkSignalQuality)
  return _internal_hasuplinksignalquality();
}
inline void AirLinkState::_internal_set_hasuplinksignalquality(bool value) {
  
  _impl_.hasuplinksignalquality_ = value;
}
inline void AirLinkState::set_hasuplinksignalquality(bool value) {
  _internal_set_hasuplinksignalquality(value);
  // @@protoc_insertion_point(field_set:DJIFRProto.Standard.AirLinkState.hasUplinkSignalQuality)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Standard
}  // namespace DJIFRProto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_AirLink_2fAirLink_2eproto
