
#include "broma/include/broma.hpp"

#include <stdlib.h>
#include <stdbool.h>

#include "cbroma.h"

#ifndef __cplusplus
extern "C" {
#endif

#define PLATFORM_NUMBER_CHAIN(XX) \
    XX(imac) \
    XX(m1) \
    XX(ios) \
    XX(win) \
    XX(android32) \
    XX(android64)


#define PLATFORM_NUMBER_GETTER(NAME) \
    long long cbroma_PlatformNumber_##NAME(void* ctx){ \
        broma::PlatformNumber* handle = (broma::PlatformNumber*)ctx; \
        return handle->##NAME;\
    }

PLATFORM_NUMBER_CHAIN(PLATFORM_NUMBER_GETTER);




bool cbroma_Type__is_struct(void* ctx){
    return ((broma::Type*)ctx)->is_struct;
}

const char* cbroma_Type__name(void* ctx){
    return ((broma::Type*)ctx)->name.c_str();
}


// Scrapped but in the future we will make these items manipulatable...

// void* cbroma_Type__new(bool is_struct, const char* name){
//     broma::Type* t = new broma::Type{is_struct, name};
//     return reinterpret_cast<void*>(t);
// }


#define CBROMA_TYPE_ATTR(TYPE, ATTR, RETTYPE) \
RETTYPE cbroma_##TYPE##__##ATTR(void* ctx){ \
    return ((broma::##TYPE*)ctx)->##ATTR;}

#define CBROMA_STRING_ATTR(TYPE, ATTR) \
const char* cbroma_##TYPE##__##ATTR(void* ctx){ \
    return ((broma::##TYPE*)ctx)->##ATTR##.c_str();}


#define CBROMA_HANDLE_ATTR(TYPE, ATTR) \
void* cbroma_##TYPE##__##ATTR(void* ctx){ \
    return reinterpret_cast<void*>(&((broma::##TYPE*)ctx)->##ATTR);\
}

#define CBROMA_ENUM_ATTR(TYPE, ATTR, ENUM) \
ENUM cbroma_##TYPE##__##ATTR(void* ctx){ \
    return (ENUM)(((broma::##TYPE*)ctx)->##ATTR);\
}

CBROMA_STRING_ATTR(Attributes, docs)
CBROMA_ENUM_ATTR(Attributes, links, Platform);
CBROMA_ENUM_ATTR(Attributes, missing, Platform);

#define CBROMA_VECTOR_HANDLE_ATTR(TYPE, ATTR) \
    void* cbroma_##TYPE##__##ATTR##_get(void* ctx, size_t idx){\
        return reinterpret_cast<void*>(&(((broma::##TYPE*)ctx)->##ATTR[idx]));\
    }\
    \
    size_t cbroma_##TYPE##__##ATTR##_len(void* ctx){ \
        return ((broma::##TYPE*)ctx)->##ATTR.size();\
    }\


#define CBROMA_VECTOR_STRING_ATTR(TYPE, ATTR) \
    const char* cbroma_##TYPE##__##ATTR##_get(void* ctx, size_t idx){\
        return ((broma::##TYPE*)ctx)->##ATTR[idx].c_str();\
    }\
    \
    size_t cbroma_##TYPE##__##ATTR##_size(void* ctx){ \
        return ((broma::##TYPE*)ctx)->##ATTR.size();\
    }\


CBROMA_VECTOR_STRING_ATTR(Attributes, depends);


CBROMA_HANDLE_ATTR(FunctionProto, attributes);
CBROMA_HANDLE_ATTR(FunctionProto, ret);


const char* cbroma_FunctionProto__args_get_str(void* ctx, size_t idx){\
    return ((broma::FunctionProto*)ctx)->args[idx].second.c_str();\
}

void* cbroma_FunctionProto__args_get_type(void* ctx, size_t idx){\
    return reinterpret_cast<void*>(&((broma::FunctionProto*)ctx)->args[idx].first);\
}

size_t cbroma_FunctionProto__args_size(void* ctx){
    return ((broma::FunctionProto*)ctx)->args.size();
}

CBROMA_STRING_ATTR(FunctionProto, name);





CBROMA_ENUM_ATTR(MemberFunctionProto, type, FunctionType);
CBROMA_TYPE_ATTR(MemberFunctionProto, is_const, bool);
CBROMA_TYPE_ATTR(MemberFunctionProto, is_virtual, bool);
CBROMA_TYPE_ATTR(MemberFunctionProto, is_callback, bool);
CBROMA_TYPE_ATTR(MemberFunctionProto, is_static, bool);



CBROMA_ENUM_ATTR(MemberField, platform, Platform);
CBROMA_STRING_ATTR(MemberField, name);
CBROMA_HANDLE_ATTR(MemberField, type);
CBROMA_TYPE_ATTR(MemberField, count, size_t);

CBROMA_HANDLE_ATTR(PadField, amount)

CBROMA_HANDLE_ATTR(FunctionBindField, prototype);
CBROMA_HANDLE_ATTR(FunctionBindField, binds);
CBROMA_STRING_ATTR(FunctionBindField, inner);

CBROMA_STRING_ATTR(InlineField, inner);

CBROMA_TYPE_ATTR(Field, field_id, size_t);
CBROMA_STRING_ATTR(Field, parent);




// These two functions were a pain in the ass but should never fail...

FieldType cbroma_Field__get_field_type(void* ctx){
    broma::Field *handle = (broma::Field*)ctx;
    if (auto a = handle->get_as<broma::InlineField>()){
        return FieldType_Inline;
    }
    if (auto a = handle->get_as<broma::FunctionBindField>()){
        return FieldType_FunctionBind;
    }
    if (auto a = handle->get_as<broma::PadField>()){
        return FieldType_Pad;
    }
    /* There should almost never be an unreachable case so no need to check the last one... */ 
    return FieldType_Member;
}

void* cbroma_Field__get_field(void* ctx){
    broma::Field *handle = (broma::Field*)ctx;
    if (auto a = handle->get_as<broma::InlineField>()){
        return reinterpret_cast<void*>(a);
    }
    if (auto a = handle->get_as<broma::FunctionBindField>()){
        return reinterpret_cast<void*>(a);
    }
    if (auto a = handle->get_as<broma::PadField>()){
        return reinterpret_cast<void*>(a);
    }
    return reinterpret_cast<void*>(handle->get_as<broma::MemberField>());
}


// Now were onto the last 4

/* CLASSES */

CBROMA_HANDLE_ATTR(Class, attributes);
CBROMA_STRING_ATTR(Class, name);
CBROMA_VECTOR_STRING_ATTR(Class, superclasses);
CBROMA_VECTOR_HANDLE_ATTR(Class, fields);

/* FUNCTIONS */

CBROMA_HANDLE_ATTR(Function, prototype);
CBROMA_HANDLE_ATTR(Function, binds);


/* ROOT */
CBROMA_VECTOR_HANDLE_ATTR(Root, classes);
CBROMA_VECTOR_HANDLE_ATTR(Root, functions);


/* CUSTOM Class Object */

const char** cbroma_SafeRootResult__get_errors(void* ctx){
    broma::SafeRootResult* handle = (broma::SafeRootResult*)(ctx);
    if (handle->is_error){
        return reinterpret_cast<std::vector<const char*>*>(handle->result)->data();
    }
    return nullptr;
};

void* cbroma_SafeRootResult__get_root(void* ctx){
    broma::SafeRootResult* handle = (broma::SafeRootResult*)(ctx);
    if (handle->is_error) return nullptr;
    return handle->result;
}

CBROMA_TYPE_ATTR(SafeRootResult, is_error, bool);

void* cbroma__parse_file_safely(const char* filename){
    return reinterpret_cast<void*>(&broma::parse_file_safely(filename));
}

void* cbroma__parse_file(const char* filename){
    return reinterpret_cast<void*>(&broma::parse_file(filename));
}

#ifndef __cplusplus
}; // extern "C" ...
#endif
