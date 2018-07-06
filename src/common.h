#ifndef COMMON_H
#define COMMON_H

#include <nan.h>

#include "gss/kerberos_gss.h"
typedef gss_client_state krb_client_state;
typedef gss_server_state krb_server_state;
typedef gss_result krb_result;

struct FreeDeleter {
    void operator()(void* result) {
        free(result);
    }
};

// Useful methods for optional value handling
NAN_INLINE std::string StringOptionValue(v8::Local<v8::Object> options, const char* _key) {
    Nan::HandleScope scope;
    v8::Local<v8::String> key = Nan::New(_key).ToLocalChecked();
    return !options.IsEmpty() && options->Has(key) && options->Get(key)->IsString()
               ? std::string(*(Nan::Utf8String(options->Get(key))))
               : std::string();
}

NAN_INLINE uint32_t UInt32OptionValue(v8::Local<v8::Object> options,
                                      const char* _key,
                                      uint32_t def) {
    Nan::HandleScope scope;
    v8::Local<v8::String> key = Nan::New(_key).ToLocalChecked();
    return !options.IsEmpty() && options->Has(key) && options->Get(key)->IsNumber()
               ? options->Get(key)->Uint32Value()
               : def;
}

#endif
