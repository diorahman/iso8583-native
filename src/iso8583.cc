#include "iso8583.h"
#include "dl_output.h"
#include <sstream>
using namespace v8;

ISO8583::ISO8583() {
  DL_ISO8583_DEFS_1993_GetHandler(&isoHandler);
  DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);
}

ISO8583::~ISO8583() {
  DL_ISO8583_MSG_Free(&isoMsg);
}

void ISO8583::set1987() {
  DL_ISO8583_DEFS_1987_GetHandler(&isoHandler);
  DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);
}

void ISO8583::set1993() {
  DL_ISO8583_DEFS_1993_GetHandler(&isoHandler);
  DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);
}

Persistent<Function> ISO8583::constructor;

NAN_METHOD(ISO8583::New) {
  NanScope();
  if (args.IsConstructCall()) {
    // invoked as contructor
    ISO8583* iso8583 = new ISO8583();
    if (args.Length() > 0) {
      Local<Object> obj = args[0]->ToObject();
      if (!node::Buffer::HasInstance(obj))
        return NanThrowError("Feed me a buffer.");

      char* packBuf = node::Buffer::Data(obj);
      size_t packedSize = node::Buffer::Length(obj);

      // fill the packedBuffer and packedSize of the wrapped object
      iso8583->packedSize = packedSize;
      memcpy(&iso8583->packBuf, packBuf, packedSize * sizeof(DL_UINT8));
    }
    iso8583->Wrap(args.This());
    NanReturnValue(args.This());
  } else {
    // invoked as plain function
    Local<Function> cons = NanNew<Function>(constructor);
    NanReturnValue(cons->NewInstance());
  }
}

NAN_METHOD(ISO8583::UnpackSync) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  const DL_ISO8583_HANDLER * isoHandler = &iso8583->isoHandler;
  DL_ISO8583_MSG * isoMsg = &iso8583->isoMsg;
  DL_ISO8583_MSG_Unpack(isoHandler, iso8583->packBuf, iso8583->packedSize, isoMsg);
  Local<Object> obj = NanNew<Object>();
  for (DL_UINT16 i = 0; i < isoHandler->fieldItems; i++) {
    if (NULL != isoMsg->field[i].ptr) {
      DL_ISO8583_FIELD_DEF * fieldDef = DL_ISO8583_GetFieldDef(i, &iso8583->isoHandler);
      obj->Set(NanNew(i), 
          NanNewBufferHandle((const char *)isoMsg->field[i].ptr, 
            strlen((const char*) isoMsg->field[i].ptr)));
    }
  }
  NanReturnValue(obj);
}

NAN_METHOD(ISO8583::PackSync) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_ISO8583_MSG_Pack(&iso8583->isoHandler, &iso8583->isoMsg, iso8583->packBuf, &iso8583->packedSize);
  // the message is freed, so please don't dump after this
  DL_ISO8583_MSG_Free(&iso8583->isoMsg);
  NanReturnValue(NanNewBufferHandle((char *)iso8583->packBuf, iso8583->packedSize));
}

NAN_METHOD(ISO8583::SetField) {
  NanScope();

  if (args.Length() < 2) {
    NanThrowTypeError("Wrong number of arguments");
    NanReturnUndefined();
  }

  if (!args[0]->IsNumber()) {
    NanThrowTypeError("Bit is required");
    NanReturnUndefined();
  }

  if (!args[1]->IsString()) {
    NanThrowTypeError("Message is required");
    NanReturnUndefined();
  }

  DL_UINT16 bit = args[0]->NumberValue();
  NanUtf8String * message = new NanUtf8String(args[1]);

  // there are two args: bit and the message
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_ISO8583_MSG_SetField_Str(bit, (const DL_UINT8*) **message, &iso8583->isoMsg);
  delete message;
  NanReturnUndefined();
}

// Re-init
NAN_METHOD(ISO8583::Clear) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_ISO8583_MSG_Init(NULL, 0, &iso8583->isoMsg);
  NanReturnUndefined();
}

NAN_METHOD(ISO8583::Dump) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_ISO8583_MSG_Dump(stdout, NULL, &iso8583->isoHandler, &iso8583->isoMsg);
  NanReturnUndefined();
}

NAN_METHOD(ISO8583::OutputHex) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_OUTPUT_Hex(stdout, NULL, iso8583->packBuf, iso8583->packedSize);
  NanReturnUndefined();
}

NAN_METHOD(ISO8583::Set1987) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  iso8583->set1987();
  NanReturnUndefined();
}

NAN_METHOD(ISO8583::Set1993) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  iso8583->set1993();
  NanReturnUndefined();
}

void ISO8583::Init(Handle<Object> exports) {
  NanScope();
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
  tpl->SetClassName(NanNew("ISO8583"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  
  // set methods
  NODE_SET_PROTOTYPE_METHOD(tpl, "unpackSync", UnpackSync);
  NODE_SET_PROTOTYPE_METHOD(tpl, "packSync", PackSync);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setField", SetField);
  NODE_SET_PROTOTYPE_METHOD(tpl, "clear", Clear);
  NODE_SET_PROTOTYPE_METHOD(tpl, "dump", Dump);
  NODE_SET_PROTOTYPE_METHOD(tpl, "outputHex", OutputHex);
  NODE_SET_PROTOTYPE_METHOD(tpl, "use1987", Set1987);
  NODE_SET_PROTOTYPE_METHOD(tpl, "use1993", Set1993);
  
  NanAssignPersistent(constructor, tpl->GetFunction());
  exports->Set(NanNew("ISO8583"), tpl->GetFunction());
}

