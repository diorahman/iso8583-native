#include "iso8583.h"
#include "dl_output.h"

using namespace v8;

ISO8583::ISO8583() {
  DL_ISO8583_DEFS_1993_GetHandler(&isoHandler);
  DL_ISO8583_MSG_Init(NULL, 0, &isoMsg);
}

ISO8583::~ISO8583() {

}

Persistent<Function> ISO8583::constructor;

NAN_METHOD(ISO8583::New) {
  NanScope();
  if (args.IsConstructCall()) {
    // invoked as contructor
    ISO8583* iso8583 = new ISO8583();
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
  NanReturnUndefined();
}

NAN_METHOD(ISO8583::PackSync) {
  NanScope();
  ISO8583 * iso8583 = ObjectWrap::Unwrap<ISO8583>(args.Holder());
  DL_ISO8583_MSG_Pack(&iso8583->isoHandler, &iso8583->isoMsg, iso8583->packBuf, &iso8583->packedSize);
  DL_ISO8583_MSG_Free(&iso8583->isoMsg);
  NanReturnValue(NanNew<Number>(iso8583->packedSize));
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
  
  NanAssignPersistent(constructor, tpl->GetFunction());
  exports->Set(NanNew("ISO8583"), tpl->GetFunction());
}

