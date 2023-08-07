// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Error/Error.proto

#include "Error/Error.pb.h"

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
}  // namespace Standard
}  // namespace DJIFRProto
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Error_2fError_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Error_2fError_2eproto = nullptr;
const uint32_t TableStruct_Error_2fError_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_Error_2fError_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021Error/Error.proto\022\023DJIFRProto.Standard"
  "*\367\001\n\007FRError\022\013\n\007Success\020\000\022\025\n\021InvalidPara"
  "meters\020\001\022\026\n\022IllegalFileContent\020\002\022\025\n\021Vers"
  "ionNotSupport\020\003\022\014\n\010NoParser\020\004\022\027\n\023Feature"
  "NotSupported\020\005\022\021\n\rDecoderFailed\020\006\022\027\n\023Fil"
  "eOperationFailed\020\007\022\031\n\025FileDataContaminat"
  "ion\020\010\022\035\n\031DataFormatChecksumFailure\020\t\022\014\n\007"
  "Failure\020\377\001B\r\242\002\nDJIFRProtob\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_Error_2fError_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Error_2fError_2eproto = {
    false, false, 313, descriptor_table_protodef_Error_2fError_2eproto,
    "Error/Error.proto",
    &descriptor_table_Error_2fError_2eproto_once, nullptr, 0, 0,
    schemas, file_default_instances, TableStruct_Error_2fError_2eproto::offsets,
    nullptr, file_level_enum_descriptors_Error_2fError_2eproto,
    file_level_service_descriptors_Error_2fError_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Error_2fError_2eproto_getter() {
  return &descriptor_table_Error_2fError_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Error_2fError_2eproto(&descriptor_table_Error_2fError_2eproto);
namespace DJIFRProto {
namespace Standard {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* FRError_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Error_2fError_2eproto);
  return file_level_enum_descriptors_Error_2fError_2eproto[0];
}
bool FRError_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 255:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace Standard
}  // namespace DJIFRProto
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
