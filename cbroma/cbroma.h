#ifndef __CBROMA_H__
#define __CBROMA_H__


#ifdef __cplusplus
extern "C" {
#else 
#include <stdbool.h>
#include <stdlib.h> // size_t should be in there...
#endif 



typedef enum Platform {
	None = 0,
	Windows = 2,
	iOS = 4,
	Android32 = 8,
	Android64 = 16,
	Android = 24,
	MacIntel = 32,
	MacArm = 64,
	Mac = 96
} Platform;

/* Had to expand all the macros for scripts like clang if planned or used... */

long long cbroma_PlatformNumber_imac(void* ctx); 
long long cbroma_PlatformNumber_m1(void* ctx);
long long cbroma_PlatformNumber_ios(void* ctx);
long long cbroma_PlatformNumber_win(void* ctx);
long long cbroma_PlatformNumber_android32(void* ctx);
long long cbroma_PlatformNumber_android64(void* ctx);


bool cbroma_Type__is_struct(void* ctx);
const char* cbroma_Type__name(void* ctx);

const char* cbroma_Attributes__depends_get(void* ctx, size_t idx);
size_t cbroma_Attributes__depends_size(void* ctx);

const char* cbroma_FunctionProto__args_get_str(void* ctx, size_t idx);
void* cbroma_FunctionProto__args_get_type(void* ctx, size_t idx);
size_t cbroma_FunctionProto__args_size(void* ctx);


const char* cbroma_FunctionProto__name(void* ctx);

typedef enum FunctionType {
    Normal,
    Ctor,
    Dtor
} FunctionType;

FunctionType cbroma_MemberFunctionProto__type(void* ctx);


bool cbroma_MemberFunctionProto__is_const(void* ctx);
bool cbroma_MemberFunctionProto__is_virtual(void* ctx);
bool cbroma_MemberFunctionProto__is_callback(void* ctx);
bool cbroma_MemberFunctionProto__is_static(void* ctx);

void* cbroma_PadField__amount(void* ctx);

void* cbroma_FunctionBindField__prototype(void* ctx);
void* cbroma_FunctionBindField__binds(void* ctx);
const char* cbroma_FunctionBindField__inner(void* ctx);

const char* cbroma_InlineField__inner(void* ctx);

size_t cbroma_Field__field_id(void* ctx);
const char* cbroma_Field__parent(void* ctx);


Platform cbroma_MemberField__platform(void* ctx);
const char* cbroma_MemberField__name(void* ctx);
void* cbroma_MemberField__type(void* ctx);
size_t cbroma_MemberField__count(void* ctx);


/* STD Variant does not have a clean way to determine types so we have to figure that our ourselves... */
typedef enum FieldType {
    FieldType_Inline,
    FieldType_FunctionBind,
    FieldType_Pad,
    FieldType_Member
} FieldType;

FieldType cbroma_Field__get_field_type(void* ctx);
void* cbroma_Field__get_field(void* ctx);


/* CLASS */

void* cbroma_Class__attributes(void* ctx);
const char* cbroma_Class__name(void* ctx);
const char* cbroma_Class__superclasses_get(void* ctx, size_t idx); 
size_t cbroma_Class__superclasses_size(void* ctx);
void* cbroma_Class__fields_get(void* ctx, size_t idx); 
size_t cbroma_Class__fields_len(void* ctx);


/* FUNCTIONS */

void* cbroma_Function__prototype(void* ctx);
void* cbroma_Function__binds(void* ctx);


/* ROOT */
void* cbroma_Root__classes_get(void* ctx, size_t idx); 
size_t cbroma_Root__classes_len(void* ctx);
void* cbroma_Root__functions_get(void* ctx, size_t idx); 
size_t cbroma_Root__functions_len(void* ctx);


bool cbroma_SafeRootResult__is_error(void* ctx);
const char** cbroma_SafeRootResult__get_errors(void* ctx);
void* cbroma_SafeRootResult__get_root(void* ctx);

void* cbroma__parse_file_safely(const char* filename);
void* cbroma__parse_file(const char* filename);


#ifdef __cplusplus
}
#endif 


#endif // __CBROMA_H__
