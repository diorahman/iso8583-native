#ifndef ISO8583_H
#define ISO8583_H

#include <nan.h>

class ISO8583 : public node::ObjectWrap {
  
  public:
    static void Init(v8::Handle<v8::Object> exports);
    static v8::Persistent<v8::Function> constructor;

  private:
    explicit ISO8583();
    ~ISO8583();

    static NAN_METHOD(New);
    static NAN_METHOD(UnpackSync);
    static NAN_METHOD(PackSync);
};

#endif
