#include <nan.h>
#include "iso8583.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  ISO8583::Init(exports);
}

NODE_MODULE(addon, InitAll)
