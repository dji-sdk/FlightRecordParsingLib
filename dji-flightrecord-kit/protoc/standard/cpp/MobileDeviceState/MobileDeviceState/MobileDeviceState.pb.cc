// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MobileDeviceState/MobileDeviceState.proto

#include "MobileDeviceState/MobileDeviceState.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace DJIFRProto {
namespace Standard {
class MobileDeviceStateDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<MobileDeviceState>
      _instance;
} _MobileDeviceState_default_instance_;
}  // namespace Standard
}  // namespace DJIFRProto
namespace protobuf_MobileDeviceState_2fMobileDeviceState_2eproto {
void InitDefaultsMobileDeviceStateImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_Common_2fFRCommonModelProto_2eproto::InitDefaultsLocationCoordinate2D();
  {
    void* ptr = &::DJIFRProto::Standard::_MobileDeviceState_default_instance_;
    new (ptr) ::DJIFRProto::Standard::MobileDeviceState();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::DJIFRProto::Standard::MobileDeviceState::InitAsDefaultInstance();
}

void InitDefaultsMobileDeviceState() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsMobileDeviceStateImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::DJIFRProto::Standard::MobileDeviceState, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::DJIFRProto::Standard::MobileDeviceState, coordinate_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::DJIFRProto::Standard::MobileDeviceState, horizontalaccuracy_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::DJIFRProto::Standard::MobileDeviceState)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::DJIFRProto::Standard::_MobileDeviceState_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "MobileDeviceState/MobileDeviceState.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n)MobileDeviceState/MobileDeviceState.pr"
      "oto\022\023DJIFRProto.Standard\032\037Common/FRCommo"
      "nModelProto.proto\"n\n\021MobileDeviceState\022="
      "\n\ncoordinate\030\001 \001(\0132).DJIFRProto.Standard"
      ".LocationCoordinate2D\022\032\n\022horizontalAccur"
      "acy\030\002 \001(\001B\r\242\002\nDJIFRProtob\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 232);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MobileDeviceState/MobileDeviceState.proto", &protobuf_RegisterTypes);
  ::protobuf_Common_2fFRCommonModelProto_2eproto::AddDescriptors();
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_MobileDeviceState_2fMobileDeviceState_2eproto
namespace DJIFRProto {
namespace Standard {

// ===================================================================

void MobileDeviceState::InitAsDefaultInstance() {
  ::DJIFRProto::Standard::_MobileDeviceState_default_instance_._instance.get_mutable()->coordinate_ = const_cast< ::DJIFRProto::Standard::LocationCoordinate2D*>(
      ::DJIFRProto::Standard::LocationCoordinate2D::internal_default_instance());
}
void MobileDeviceState::clear_coordinate() {
  if (GetArenaNoVirtual() == NULL && coordinate_ != NULL) {
    delete coordinate_;
  }
  coordinate_ = NULL;
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int MobileDeviceState::kCoordinateFieldNumber;
const int MobileDeviceState::kHorizontalAccuracyFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

MobileDeviceState::MobileDeviceState()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::InitDefaultsMobileDeviceState();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:DJIFRProto.Standard.MobileDeviceState)
}
MobileDeviceState::MobileDeviceState(const MobileDeviceState& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_coordinate()) {
    coordinate_ = new ::DJIFRProto::Standard::LocationCoordinate2D(*from.coordinate_);
  } else {
    coordinate_ = NULL;
  }
  horizontalaccuracy_ = from.horizontalaccuracy_;
  // @@protoc_insertion_point(copy_constructor:DJIFRProto.Standard.MobileDeviceState)
}

void MobileDeviceState::SharedCtor() {
  ::memset(&coordinate_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&horizontalaccuracy_) -
      reinterpret_cast<char*>(&coordinate_)) + sizeof(horizontalaccuracy_));
  _cached_size_ = 0;
}

MobileDeviceState::~MobileDeviceState() {
  // @@protoc_insertion_point(destructor:DJIFRProto.Standard.MobileDeviceState)
  SharedDtor();
}

void MobileDeviceState::SharedDtor() {
  if (this != internal_default_instance()) delete coordinate_;
}

void MobileDeviceState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MobileDeviceState::descriptor() {
  ::protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const MobileDeviceState& MobileDeviceState::default_instance() {
  ::protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::InitDefaultsMobileDeviceState();
  return *internal_default_instance();
}

MobileDeviceState* MobileDeviceState::New(::google::protobuf::Arena* arena) const {
  MobileDeviceState* n = new MobileDeviceState;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MobileDeviceState::Clear() {
// @@protoc_insertion_point(message_clear_start:DJIFRProto.Standard.MobileDeviceState)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == NULL && coordinate_ != NULL) {
    delete coordinate_;
  }
  coordinate_ = NULL;
  horizontalaccuracy_ = 0;
  _internal_metadata_.Clear();
}

bool MobileDeviceState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:DJIFRProto.Standard.MobileDeviceState)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .DJIFRProto.Standard.LocationCoordinate2D coordinate = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_coordinate()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double horizontalAccuracy = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(17u /* 17 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &horizontalaccuracy_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:DJIFRProto.Standard.MobileDeviceState)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:DJIFRProto.Standard.MobileDeviceState)
  return false;
#undef DO_
}

void MobileDeviceState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:DJIFRProto.Standard.MobileDeviceState)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .DJIFRProto.Standard.LocationCoordinate2D coordinate = 1;
  if (this->has_coordinate()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->coordinate_, output);
  }

  // double horizontalAccuracy = 2;
  if (this->horizontalaccuracy() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->horizontalaccuracy(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:DJIFRProto.Standard.MobileDeviceState)
}

::google::protobuf::uint8* MobileDeviceState::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:DJIFRProto.Standard.MobileDeviceState)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .DJIFRProto.Standard.LocationCoordinate2D coordinate = 1;
  if (this->has_coordinate()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, *this->coordinate_, deterministic, target);
  }

  // double horizontalAccuracy = 2;
  if (this->horizontalaccuracy() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->horizontalaccuracy(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:DJIFRProto.Standard.MobileDeviceState)
  return target;
}

size_t MobileDeviceState::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:DJIFRProto.Standard.MobileDeviceState)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // .DJIFRProto.Standard.LocationCoordinate2D coordinate = 1;
  if (this->has_coordinate()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *this->coordinate_);
  }

  // double horizontalAccuracy = 2;
  if (this->horizontalaccuracy() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MobileDeviceState::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:DJIFRProto.Standard.MobileDeviceState)
  GOOGLE_DCHECK_NE(&from, this);
  const MobileDeviceState* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const MobileDeviceState>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:DJIFRProto.Standard.MobileDeviceState)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:DJIFRProto.Standard.MobileDeviceState)
    MergeFrom(*source);
  }
}

void MobileDeviceState::MergeFrom(const MobileDeviceState& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:DJIFRProto.Standard.MobileDeviceState)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_coordinate()) {
    mutable_coordinate()->::DJIFRProto::Standard::LocationCoordinate2D::MergeFrom(from.coordinate());
  }
  if (from.horizontalaccuracy() != 0) {
    set_horizontalaccuracy(from.horizontalaccuracy());
  }
}

void MobileDeviceState::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:DJIFRProto.Standard.MobileDeviceState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MobileDeviceState::CopyFrom(const MobileDeviceState& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:DJIFRProto.Standard.MobileDeviceState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MobileDeviceState::IsInitialized() const {
  return true;
}

void MobileDeviceState::Swap(MobileDeviceState* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MobileDeviceState::InternalSwap(MobileDeviceState* other) {
  using std::swap;
  swap(coordinate_, other->coordinate_);
  swap(horizontalaccuracy_, other->horizontalaccuracy_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MobileDeviceState::GetMetadata() const {
  protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_MobileDeviceState_2fMobileDeviceState_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Standard
}  // namespace DJIFRProto

// @@protoc_insertion_point(global_scope)
