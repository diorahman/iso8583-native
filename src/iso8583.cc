#include <nan.h>

#include "dl_iso8583.h"
#include "dl_iso8583_defs_1993.h"

using namespace v8;

NAN_METHOD(Hello) {
  NanScope();

  DL_ISO8583_HANDLER isoHandler;

  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("hello"), NanNew<FunctionTemplate>(Hello)->GetFunction());
}

NODE_MODULE(hello, Init)
