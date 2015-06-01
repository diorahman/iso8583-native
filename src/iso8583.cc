#include "iso8583.h"

#include "dl_iso8583.h"
#include "dl_iso8583_defs_1993.h"
#include "dl_output.h" // for 'DL_OUTPUT_Hex'

using namespace v8;

ISO8583::ISO8583() {
  
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
  
  NanAssignPersistent(constructor, tpl->GetFunction());
  exports->Set(NanNew("ISO8583"), tpl->GetFunction());
}

