#ifndef ISO8583_H
#define ISO8583_H

#include "dl_iso8583.h"
#include "dl_iso8583_defs_1993.h"

#include <nan.h>

class ISO8583 : public node::ObjectWrap {
  
  public:
    static void Init(v8::Handle<v8::Object> exports);
    static v8::Persistent<v8::Function> constructor;

  private:
    explicit ISO8583();
    ~ISO8583();

    DL_ISO8583_HANDLER isoHandler;
    DL_ISO8583_MSG isoMsg;
    DL_UINT8 packBuf[1024];
    DL_UINT16 packedSize;

    static NAN_METHOD(New);
    static NAN_METHOD(UnpackSync);
    static NAN_METHOD(PackSync);
    static NAN_METHOD(SetField);
    static NAN_METHOD(Dump);
    static NAN_METHOD(OutputHex);
    static NAN_METHOD(Clear);
};

#endif
