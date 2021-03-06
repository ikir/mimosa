// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kv-db.proto

#ifndef PROTOBUF_kv_2ddb_2eproto__INCLUDED
#define PROTOBUF_kv_2ddb_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
#include <mimosa/rpc/service.hh>
#include <mimosa/rpc/call.hh>
#include <mimosa/rpc/channel.hh>
// @@protoc_insertion_point(includes)

namespace mimosa {
namespace rpc {
namespace samples {
namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_kv_2ddb_2eproto();
void protobuf_AssignDesc_kv_2ddb_2eproto();
void protobuf_ShutdownFile_kv_2ddb_2eproto();

class Key;
class KeyValue;
class Result;

enum Status {
  kOk = 0,
  kNotFound = 1,
  kInternalError = 2
};
bool Status_IsValid(int value);
const Status Status_MIN = kOk;
const Status Status_MAX = kInternalError;
const int Status_ARRAYSIZE = Status_MAX + 1;

const ::google::protobuf::EnumDescriptor* Status_descriptor();
inline const ::std::string& Status_Name(Status value) {
  return ::google::protobuf::internal::NameOfEnum(
    Status_descriptor(), value);
}
inline bool Status_Parse(
    const ::std::string& name, Status* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Status>(
    Status_descriptor(), name, value);
}
// ===================================================================

class Key : public ::google::protobuf::Message {
 public:
  Key();
  virtual ~Key();
  
  Key(const Key& from);
  
  inline Key& operator=(const Key& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Key& default_instance();
  
  void Swap(Key* other);
  
  // implements Message ----------------------------------------------
  
  Key* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Key& from);
  void MergeFrom(const Key& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const void* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  
  // @@protoc_insertion_point(class_scope:mimosa.rpc.samples.pb.Key)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* key_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2ddb_2eproto();
  friend void protobuf_AssignDesc_kv_2ddb_2eproto();
  friend void protobuf_ShutdownFile_kv_2ddb_2eproto();
  
  void InitAsDefaultInstance();
  static Key* default_instance_;
};
// -------------------------------------------------------------------

class KeyValue : public ::google::protobuf::Message {
 public:
  KeyValue();
  virtual ~KeyValue();
  
  KeyValue(const KeyValue& from);
  
  inline KeyValue& operator=(const KeyValue& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const KeyValue& default_instance();
  
  void Swap(KeyValue* other);
  
  // implements Message ----------------------------------------------
  
  KeyValue* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const KeyValue& from);
  void MergeFrom(const KeyValue& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required bytes key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const void* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  
  // required bytes value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const void* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  
  // @@protoc_insertion_point(class_scope:mimosa.rpc.samples.pb.KeyValue)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* key_;
  ::std::string* value_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2ddb_2eproto();
  friend void protobuf_AssignDesc_kv_2ddb_2eproto();
  friend void protobuf_ShutdownFile_kv_2ddb_2eproto();
  
  void InitAsDefaultInstance();
  static KeyValue* default_instance_;
};
// -------------------------------------------------------------------

class Result : public ::google::protobuf::Message {
 public:
  Result();
  virtual ~Result();
  
  Result(const Result& from);
  
  inline Result& operator=(const Result& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Result& default_instance();
  
  void Swap(Result* other);
  
  // implements Message ----------------------------------------------
  
  Result* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Result& from);
  void MergeFrom(const Result& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required .mimosa.rpc.samples.pb.Status status = 1;
  inline bool has_status() const;
  inline void clear_status();
  static const int kStatusFieldNumber = 1;
  inline mimosa::rpc::samples::pb::Status status() const;
  inline void set_status(mimosa::rpc::samples::pb::Status value);
  
  // optional bytes value = 2;
  inline bool has_value() const;
  inline void clear_value();
  static const int kValueFieldNumber = 2;
  inline const ::std::string& value() const;
  inline void set_value(const ::std::string& value);
  inline void set_value(const char* value);
  inline void set_value(const void* value, size_t size);
  inline ::std::string* mutable_value();
  inline ::std::string* release_value();
  
  // @@protoc_insertion_point(class_scope:mimosa.rpc.samples.pb.Result)
 private:
  inline void set_has_status();
  inline void clear_has_status();
  inline void set_has_value();
  inline void clear_has_value();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* value_;
  int status_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_kv_2ddb_2eproto();
  friend void protobuf_AssignDesc_kv_2ddb_2eproto();
  friend void protobuf_ShutdownFile_kv_2ddb_2eproto();
  
  void InitAsDefaultInstance();
  static Result* default_instance_;
};
// ===================================================================


// ===================================================================

// Key

// required bytes key = 1;
inline bool Key::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Key::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Key::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Key::clear_key() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& Key::key() const {
  return *key_;
}
inline void Key::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void Key::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void Key::set_key(const void* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Key::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  return key_;
}
inline ::std::string* Key::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// KeyValue

// required bytes key = 1;
inline bool KeyValue::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void KeyValue::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void KeyValue::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void KeyValue::clear_key() {
  if (key_ != &::google::protobuf::internal::kEmptyString) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& KeyValue::key() const {
  return *key_;
}
inline void KeyValue::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void KeyValue::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(value);
}
inline void KeyValue::set_key(const void* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* KeyValue::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    key_ = new ::std::string;
  }
  return key_;
}
inline ::std::string* KeyValue::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required bytes value = 2;
inline bool KeyValue::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void KeyValue::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void KeyValue::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void KeyValue::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& KeyValue::value() const {
  return *value_;
}
inline void KeyValue::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void KeyValue::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void KeyValue::set_value(const void* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* KeyValue::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* KeyValue::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// Result

// required .mimosa.rpc.samples.pb.Status status = 1;
inline bool Result::has_status() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Result::set_has_status() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Result::clear_has_status() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Result::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline mimosa::rpc::samples::pb::Status Result::status() const {
  return static_cast< mimosa::rpc::samples::pb::Status >(status_);
}
inline void Result::set_status(mimosa::rpc::samples::pb::Status value) {
  GOOGLE_DCHECK(mimosa::rpc::samples::pb::Status_IsValid(value));
  set_has_status();
  status_ = value;
}

// optional bytes value = 2;
inline bool Result::has_value() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Result::set_has_value() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Result::clear_has_value() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Result::clear_value() {
  if (value_ != &::google::protobuf::internal::kEmptyString) {
    value_->clear();
  }
  clear_has_value();
}
inline const ::std::string& Result::value() const {
  return *value_;
}
inline void Result::set_value(const ::std::string& value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void Result::set_value(const char* value) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(value);
}
inline void Result::set_value(const void* value, size_t size) {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  value_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Result::mutable_value() {
  set_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    value_ = new ::std::string;
  }
  return value_;
}
inline ::std::string* Result::release_value() {
  clear_has_value();
  if (value_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = value_;
    value_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


class Database_Client;
class Database_Server;
class Database : public ::mimosa::rpc::Service
{
public:
  MIMOSA_DEF_PTR(Database);
  typedef Database_Client Client;
  typedef Database_Server Server;
  inline virtual uint32_t id() const { return 2753234432UL; }
  inline virtual const char * name() const { return "mimosa.rpc.samples.pb.Database"; }
};

class Database_Server : public Database
{
public:
  MIMOSA_DEF_PTR(Database_Server);

  // You have to implement the following rpc methods
  virtual void get(::mimosa::rpc::Call<
    ::mimosa::rpc::samples::pb::Key,
    ::mimosa::rpc::samples::pb::Result>::Ptr call) = 0;
  
  virtual void set(::mimosa::rpc::Call<
    ::mimosa::rpc::samples::pb::KeyValue,
    ::mimosa::rpc::samples::pb::Result>::Ptr call) = 0;
  
  virtual void del(::mimosa::rpc::Call<
    ::mimosa::rpc::samples::pb::Key,
    ::mimosa::rpc::samples::pb::Result>::Ptr call) = 0;
  // End of rpc methods
  
protected:
  inline virtual ::mimosa::rpc::Service::CallMethodStatus callMethod(
    ::mimosa::rpc::BasicCall::Ptr basic_call,
    const char *                  request_data,
    uint32_t                      request_size)
  {
    switch (basic_call->methodId())
    {
    case 4248514160UL: // get()
    {
      ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                           ::mimosa::rpc::samples::pb::Result>::Ptr call(
        reinterpret_cast< ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                                               ::mimosa::rpc::samples::pb::Result> *> (basic_call.get()));
      call->allocateMessages();
      if (!call->request().ParseFromArray(request_data, request_size))
        return ::mimosa::rpc::Service::kInvalidMsg;
      get(call);
      return ::mimosa::rpc::Service::kSucceed;
    }
    case 3860080092UL: // set()
    {
      ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::KeyValue,
                           ::mimosa::rpc::samples::pb::Result>::Ptr call(
        reinterpret_cast< ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::KeyValue,
                                               ::mimosa::rpc::samples::pb::Result> *> (basic_call.get()));
      call->allocateMessages();
      if (!call->request().ParseFromArray(request_data, request_size))
        return ::mimosa::rpc::Service::kInvalidMsg;
      set(call);
      return ::mimosa::rpc::Service::kSucceed;
    }
    case 3960539263UL: // del()
    {
      ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                           ::mimosa::rpc::samples::pb::Result>::Ptr call(
        reinterpret_cast< ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                                               ::mimosa::rpc::samples::pb::Result> *> (basic_call.get()));
      call->allocateMessages();
      if (!call->request().ParseFromArray(request_data, request_size))
        return ::mimosa::rpc::Service::kInvalidMsg;
      del(call);
      return ::mimosa::rpc::Service::kSucceed;
    }
    default:
      return ::mimosa::rpc::Service::kMethodNotFound;
    }
  }
}; // End of service

class Database_Client : public Database
{
public:
  MIMOSA_DEF_PTR(Database_Client);
  inline Database_Client(::mimosa::rpc::Channel::Ptr channel)
    : channel_(channel)
  {
  }

  inline ::mimosa::rpc::Channel::Ptr channel() const { return channel_; }

  // Rpc methods
  inline ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                              ::mimosa::rpc::samples::pb::Result>::Ptr
  get(::mimosa::rpc::samples::pb::Key * request)
  {
    ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                         ::mimosa::rpc::samples::pb::Result>::Ptr call(
      new ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                               ::mimosa::rpc::samples::pb::Result>(request));
    call->setServiceId(2753234432UL);
    call->setMethodId(4248514160UL);
    channel_->sendCall(call);
    return call;
  }
  
  inline ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::KeyValue,
                              ::mimosa::rpc::samples::pb::Result>::Ptr
  set(::mimosa::rpc::samples::pb::KeyValue * request)
  {
    ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::KeyValue,
                         ::mimosa::rpc::samples::pb::Result>::Ptr call(
      new ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::KeyValue,
                               ::mimosa::rpc::samples::pb::Result>(request));
    call->setServiceId(2753234432UL);
    call->setMethodId(3860080092UL);
    channel_->sendCall(call);
    return call;
  }
  
  inline ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                              ::mimosa::rpc::samples::pb::Result>::Ptr
  del(::mimosa::rpc::samples::pb::Key * request)
  {
    ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                         ::mimosa::rpc::samples::pb::Result>::Ptr call(
      new ::mimosa::rpc::Call< ::mimosa::rpc::samples::pb::Key,
                               ::mimosa::rpc::samples::pb::Result>(request));
    call->setServiceId(2753234432UL);
    call->setMethodId(3960539263UL);
    channel_->sendCall(call);
    return call;
  }
  
  // End of rpc methods
protected:
  ::mimosa::rpc::Channel::Ptr channel_;
}; // End of service's client

// @@protoc_insertion_point(namespace_scope)

}  // namespace pb
}  // namespace samples
}  // namespace rpc
}  // namespace mimosa

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< mimosa::rpc::samples::pb::Status>() {
  return mimosa::rpc::samples::pb::Status_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_kv_2ddb_2eproto__INCLUDED
