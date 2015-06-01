#include <nan.h>

#include "dl_iso8583.h"
#include "dl_iso8583_defs_1993.h"
#include "dl_output.h" // for 'DL_OUTPUT_Hex'

using namespace v8;

NAN_METHOD(Method) {
  NanScope();

  DL_ISO8583_HANDLER isoHandler;
  DL_ISO8583_MSG     isoMsg;
  DL_UINT8           packBuf[1000];
  DL_UINT16          packedSize;

  /* get ISO-8583 1993 handler */
  DL_ISO8583_DEFS_1993_GetHandler(&isoHandler);

  DL_ISO8583_MSG_SetField_Str(0, (const DL_UINT8*) "1234", &isoMsg);

  DL_ISO8583_MSG_Free(&isoMsg);

  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("hello"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(hello, Init)

