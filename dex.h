//
// Created by Administrator on 2021/6/5.
//

#ifndef MDEX_DEX_H
#define MDEX_DEX_H

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;
typedef int8_t s1;
typedef int16_t s2;
typedef int32_t s4;
typedef int64_t s8;


enum UnzipToFileResult {
    kUTFRSuccess = 0,
    kUTFRGenericFailure,
    kUTFRBadArgs,
    kUTFRNotZip,
    kUTFRNoClassesDex,
    kUTFROutputFileProblem,
    kUTFRBadZip,
};
enum {
    kSHA1DigestLen = 20,
    kSHA1DigestOutputLen = kSHA1DigestLen * 2 + 1
};
enum {
    kDexEndianConstant = 0x12345678,    /* the endianness indicator */
    kDexNoIndex = 0xffffffff,           /* not a valid index value */
};
enum PrimitiveType {
    PRIM_NOT = 0,       /* value is a reference type, not a primitive type */
    PRIM_VOID = 1,
    PRIM_BOOLEAN = 2,
    PRIM_BYTE = 3,
    PRIM_SHORT = 4,
    PRIM_CHAR = 5,
    PRIM_INT = 6,
    PRIM_LONG = 7,
    PRIM_FLOAT = 8,
    PRIM_DOUBLE = 9,
};
enum {
    ACC_PUBLIC = 0x00000001,       // class, field, method, ic
    ACC_PRIVATE = 0x00000002,       // field, method, ic
    ACC_PROTECTED = 0x00000004,       // field, method, ic
    ACC_STATIC = 0x00000008,       // field, method, ic
    ACC_FINAL = 0x00000010,       // class, field, method, ic
    ACC_SYNCHRONIZED = 0x00000020,       // method (only allowed on natives)
    ACC_SUPER = 0x00000020,       // class (not used in Dalvik)
    ACC_VOLATILE = 0x00000040,       // field
    ACC_BRIDGE = 0x00000040,       // method (1.5)
    ACC_TRANSIENT = 0x00000080,       // field
    ACC_VARARGS = 0x00000080,       // method (1.5)
    ACC_NATIVE = 0x00000100,       // method
    ACC_INTERFACE = 0x00000200,       // class, ic
    ACC_ABSTRACT = 0x00000400,       // class, method, ic
    ACC_STRICT = 0x00000800,       // method
    ACC_SYNTHETIC = 0x00001000,       // field, method, ic
    ACC_ANNOTATION = 0x00002000,       // class, ic (1.5)
    ACC_ENUM = 0x00004000,       // class, field, ic (1.5)
    ACC_CONSTRUCTOR = 0x00010000,       // method (Dalvik only)
    ACC_DECLARED_SYNCHRONIZED =
    0x00020000,       // method (Dalvik only)
    ACC_CLASS_MASK =
    (ACC_PUBLIC | ACC_FINAL | ACC_INTERFACE | ACC_ABSTRACT
     | ACC_SYNTHETIC | ACC_ANNOTATION | ACC_ENUM),
    ACC_INNER_CLASS_MASK =
    (ACC_CLASS_MASK | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC),
    ACC_FIELD_MASK =
    (ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL
     | ACC_VOLATILE | ACC_TRANSIENT | ACC_SYNTHETIC | ACC_ENUM),
    ACC_METHOD_MASK =
    (ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL
     | ACC_SYNCHRONIZED | ACC_BRIDGE | ACC_VARARGS | ACC_NATIVE
     | ACC_ABSTRACT | ACC_STRICT | ACC_SYNTHETIC | ACC_CONSTRUCTOR
     | ACC_DECLARED_SYNCHRONIZED),
};
enum {
    kDexVisibilityBuild = 0x00,     /* annotation visibility */
    kDexVisibilityRuntime = 0x01,
    kDexVisibilitySystem = 0x02,

    kDexAnnotationByte = 0x00,
    kDexAnnotationShort = 0x02,
    kDexAnnotationChar = 0x03,
    kDexAnnotationInt = 0x04,
    kDexAnnotationLong = 0x06,
    kDexAnnotationFloat = 0x10,
    kDexAnnotationDouble = 0x11,
    kDexAnnotationString = 0x17,
    kDexAnnotationType = 0x18,
    kDexAnnotationField = 0x19,
    kDexAnnotationMethod = 0x1a,
    kDexAnnotationEnum = 0x1b,
    kDexAnnotationArray = 0x1c,
    kDexAnnotationAnnotation = 0x1d,
    kDexAnnotationNull = 0x1e,
    kDexAnnotationBoolean = 0x1f,

    kDexAnnotationValueTypeMask = 0x1f,     /* low 5 bits */
    kDexAnnotationValueArgShift = 5,
};
enum {
    kDexTypeHeaderItem = 0x0000,
    kDexTypeStringIdItem = 0x0001,
    kDexTypeTypeIdItem = 0x0002,
    kDexTypeProtoIdItem = 0x0003,
    kDexTypeFieldIdItem = 0x0004,
    kDexTypeMethodIdItem = 0x0005,
    kDexTypeClassDefItem = 0x0006,
    kDexTypeMapList = 0x1000,
    kDexTypeTypeList = 0x1001,
    kDexTypeAnnotationSetRefList = 0x1002,
    kDexTypeAnnotationSetItem = 0x1003,
    kDexTypeClassDataItem = 0x2000,
    kDexTypeCodeItem = 0x2001,
    kDexTypeStringDataItem = 0x2002,
    kDexTypeDebugInfoItem = 0x2003,
    kDexTypeAnnotationItem = 0x2004,
    kDexTypeEncodedArrayItem = 0x2005,
    kDexTypeAnnotationsDirectoryItem = 0x2006,
};
enum {
    kDexChunkClassLookup = 0x434c4b50,   /* CLKP */
    kDexChunkRegisterMaps = 0x524d4150,   /* RMAP */

    kDexChunkEnd = 0x41454e44,   /* AEND */
};
enum {
    DBG_END_SEQUENCE = 0x00,
    DBG_ADVANCE_PC = 0x01,
    DBG_ADVANCE_LINE = 0x02,
    DBG_START_LOCAL = 0x03,
    DBG_START_LOCAL_EXTENDED = 0x04,
    DBG_END_LOCAL = 0x05,
    DBG_RESTART_LOCAL = 0x06,
    DBG_SET_PROLOGUE_END = 0x07,
    DBG_SET_EPILOGUE_BEGIN = 0x08,
    DBG_SET_FILE = 0x09,
    DBG_FIRST_SPECIAL = 0x0a,
    DBG_LINE_BASE = -4,
    DBG_LINE_RANGE = 15,
};
enum {
    kDexParseDefault = 0,
    kDexParseVerifyChecksum = 1,
    kDexParseContinueOnError = (1 << 1),
};
enum Opcode {
    // BEGIN(libdex-opcode-enum); GENERATED AUTOMATICALLY BY opcode-gen
    OP_NOP = 0x00,
    OP_MOVE = 0x01,
    OP_MOVE_FROM16 = 0x02,
    OP_MOVE_16 = 0x03,
    OP_MOVE_WIDE = 0x04,
    OP_MOVE_WIDE_FROM16 = 0x05,
    OP_MOVE_WIDE_16 = 0x06,
    OP_MOVE_OBJECT = 0x07,
    OP_MOVE_OBJECT_FROM16 = 0x08,
    OP_MOVE_OBJECT_16 = 0x09,
    OP_MOVE_RESULT = 0x0a,
    OP_MOVE_RESULT_WIDE = 0x0b,
    OP_MOVE_RESULT_OBJECT = 0x0c,
    OP_MOVE_EXCEPTION = 0x0d,
    OP_RETURN_VOID = 0x0e,
    OP_RETURN = 0x0f,
    OP_RETURN_WIDE = 0x10,
    OP_RETURN_OBJECT = 0x11,
    OP_CONST_4 = 0x12,
    OP_CONST_16 = 0x13,
    OP_CONST = 0x14,
    OP_CONST_HIGH16 = 0x15,
    OP_CONST_WIDE_16 = 0x16,
    OP_CONST_WIDE_32 = 0x17,
    OP_CONST_WIDE = 0x18,
    OP_CONST_WIDE_HIGH16 = 0x19,
    OP_CONST_STRING = 0x1a,
    OP_CONST_STRING_JUMBO = 0x1b,
    OP_CONST_CLASS = 0x1c,
    OP_MONITOR_ENTER = 0x1d,
    OP_MONITOR_EXIT = 0x1e,
    OP_CHECK_CAST = 0x1f,
    OP_INSTANCE_OF = 0x20,
    OP_ARRAY_LENGTH = 0x21,
    OP_NEW_INSTANCE = 0x22,
    OP_NEW_ARRAY = 0x23,
    OP_FILLED_NEW_ARRAY = 0x24,
    OP_FILLED_NEW_ARRAY_RANGE = 0x25,
    OP_FILL_ARRAY_DATA = 0x26,
    OP_THROW = 0x27,
    OP_GOTO = 0x28,
    OP_GOTO_16 = 0x29,
    OP_GOTO_32 = 0x2a,
    OP_PACKED_SWITCH = 0x2b,
    OP_SPARSE_SWITCH = 0x2c,
    OP_CMPL_FLOAT = 0x2d,
    OP_CMPG_FLOAT = 0x2e,
    OP_CMPL_DOUBLE = 0x2f,
    OP_CMPG_DOUBLE = 0x30,
    OP_CMP_LONG = 0x31,
    OP_IF_EQ = 0x32,
    OP_IF_NE = 0x33,
    OP_IF_LT = 0x34,
    OP_IF_GE = 0x35,
    OP_IF_GT = 0x36,
    OP_IF_LE = 0x37,
    OP_IF_EQZ = 0x38,
    OP_IF_NEZ = 0x39,
    OP_IF_LTZ = 0x3a,
    OP_IF_GEZ = 0x3b,
    OP_IF_GTZ = 0x3c,
    OP_IF_LEZ = 0x3d,
    OP_UNUSED_3E = 0x3e,
    OP_UNUSED_3F = 0x3f,
    OP_UNUSED_40 = 0x40,
    OP_UNUSED_41 = 0x41,
    OP_UNUSED_42 = 0x42,
    OP_UNUSED_43 = 0x43,
    OP_AGET = 0x44,
    OP_AGET_WIDE = 0x45,
    OP_AGET_OBJECT = 0x46,
    OP_AGET_BOOLEAN = 0x47,
    OP_AGET_BYTE = 0x48,
    OP_AGET_CHAR = 0x49,
    OP_AGET_SHORT = 0x4a,
    OP_APUT = 0x4b,
    OP_APUT_WIDE = 0x4c,
    OP_APUT_OBJECT = 0x4d,
    OP_APUT_BOOLEAN = 0x4e,
    OP_APUT_BYTE = 0x4f,
    OP_APUT_CHAR = 0x50,
    OP_APUT_SHORT = 0x51,
    OP_IGET = 0x52,
    OP_IGET_WIDE = 0x53,
    OP_IGET_OBJECT = 0x54,
    OP_IGET_BOOLEAN = 0x55,
    OP_IGET_BYTE = 0x56,
    OP_IGET_CHAR = 0x57,
    OP_IGET_SHORT = 0x58,
    OP_IPUT = 0x59,
    OP_IPUT_WIDE = 0x5a,
    OP_IPUT_OBJECT = 0x5b,
    OP_IPUT_BOOLEAN = 0x5c,
    OP_IPUT_BYTE = 0x5d,
    OP_IPUT_CHAR = 0x5e,
    OP_IPUT_SHORT = 0x5f,
    OP_SGET = 0x60,
    OP_SGET_WIDE = 0x61,
    OP_SGET_OBJECT = 0x62,
    OP_SGET_BOOLEAN = 0x63,
    OP_SGET_BYTE = 0x64,
    OP_SGET_CHAR = 0x65,
    OP_SGET_SHORT = 0x66,
    OP_SPUT = 0x67,
    OP_SPUT_WIDE = 0x68,
    OP_SPUT_OBJECT = 0x69,
    OP_SPUT_BOOLEAN = 0x6a,
    OP_SPUT_BYTE = 0x6b,
    OP_SPUT_CHAR = 0x6c,
    OP_SPUT_SHORT = 0x6d,
    OP_INVOKE_VIRTUAL = 0x6e,
    OP_INVOKE_SUPER = 0x6f,
    OP_INVOKE_DIRECT = 0x70,
    OP_INVOKE_STATIC = 0x71,
    OP_INVOKE_INTERFACE = 0x72,
    OP_UNUSED_73 = 0x73,
    OP_INVOKE_VIRTUAL_RANGE = 0x74,
    OP_INVOKE_SUPER_RANGE = 0x75,
    OP_INVOKE_DIRECT_RANGE = 0x76,
    OP_INVOKE_STATIC_RANGE = 0x77,
    OP_INVOKE_INTERFACE_RANGE = 0x78,
    OP_UNUSED_79 = 0x79,
    OP_UNUSED_7A = 0x7a,
    OP_NEG_INT = 0x7b,
    OP_NOT_INT = 0x7c,
    OP_NEG_LONG = 0x7d,
    OP_NOT_LONG = 0x7e,
    OP_NEG_FLOAT = 0x7f,
    OP_NEG_DOUBLE = 0x80,
    OP_INT_TO_LONG = 0x81,
    OP_INT_TO_FLOAT = 0x82,
    OP_INT_TO_DOUBLE = 0x83,
    OP_LONG_TO_INT = 0x84,
    OP_LONG_TO_FLOAT = 0x85,
    OP_LONG_TO_DOUBLE = 0x86,
    OP_FLOAT_TO_INT = 0x87,
    OP_FLOAT_TO_LONG = 0x88,
    OP_FLOAT_TO_DOUBLE = 0x89,
    OP_DOUBLE_TO_INT = 0x8a,
    OP_DOUBLE_TO_LONG = 0x8b,
    OP_DOUBLE_TO_FLOAT = 0x8c,
    OP_INT_TO_BYTE = 0x8d,
    OP_INT_TO_CHAR = 0x8e,
    OP_INT_TO_SHORT = 0x8f,
    OP_ADD_INT = 0x90,
    OP_SUB_INT = 0x91,
    OP_MUL_INT = 0x92,
    OP_DIV_INT = 0x93,
    OP_REM_INT = 0x94,
    OP_AND_INT = 0x95,
    OP_OR_INT = 0x96,
    OP_XOR_INT = 0x97,
    OP_SHL_INT = 0x98,
    OP_SHR_INT = 0x99,
    OP_USHR_INT = 0x9a,
    OP_ADD_LONG = 0x9b,
    OP_SUB_LONG = 0x9c,
    OP_MUL_LONG = 0x9d,
    OP_DIV_LONG = 0x9e,
    OP_REM_LONG = 0x9f,
    OP_AND_LONG = 0xa0,
    OP_OR_LONG = 0xa1,
    OP_XOR_LONG = 0xa2,
    OP_SHL_LONG = 0xa3,
    OP_SHR_LONG = 0xa4,
    OP_USHR_LONG = 0xa5,
    OP_ADD_FLOAT = 0xa6,
    OP_SUB_FLOAT = 0xa7,
    OP_MUL_FLOAT = 0xa8,
    OP_DIV_FLOAT = 0xa9,
    OP_REM_FLOAT = 0xaa,
    OP_ADD_DOUBLE = 0xab,
    OP_SUB_DOUBLE = 0xac,
    OP_MUL_DOUBLE = 0xad,
    OP_DIV_DOUBLE = 0xae,
    OP_REM_DOUBLE = 0xaf,
    OP_ADD_INT_2ADDR = 0xb0,
    OP_SUB_INT_2ADDR = 0xb1,
    OP_MUL_INT_2ADDR = 0xb2,
    OP_DIV_INT_2ADDR = 0xb3,
    OP_REM_INT_2ADDR = 0xb4,
    OP_AND_INT_2ADDR = 0xb5,
    OP_OR_INT_2ADDR = 0xb6,
    OP_XOR_INT_2ADDR = 0xb7,
    OP_SHL_INT_2ADDR = 0xb8,
    OP_SHR_INT_2ADDR = 0xb9,
    OP_USHR_INT_2ADDR = 0xba,
    OP_ADD_LONG_2ADDR = 0xbb,
    OP_SUB_LONG_2ADDR = 0xbc,
    OP_MUL_LONG_2ADDR = 0xbd,
    OP_DIV_LONG_2ADDR = 0xbe,
    OP_REM_LONG_2ADDR = 0xbf,
    OP_AND_LONG_2ADDR = 0xc0,
    OP_OR_LONG_2ADDR = 0xc1,
    OP_XOR_LONG_2ADDR = 0xc2,
    OP_SHL_LONG_2ADDR = 0xc3,
    OP_SHR_LONG_2ADDR = 0xc4,
    OP_USHR_LONG_2ADDR = 0xc5,
    OP_ADD_FLOAT_2ADDR = 0xc6,
    OP_SUB_FLOAT_2ADDR = 0xc7,
    OP_MUL_FLOAT_2ADDR = 0xc8,
    OP_DIV_FLOAT_2ADDR = 0xc9,
    OP_REM_FLOAT_2ADDR = 0xca,
    OP_ADD_DOUBLE_2ADDR = 0xcb,
    OP_SUB_DOUBLE_2ADDR = 0xcc,
    OP_MUL_DOUBLE_2ADDR = 0xcd,
    OP_DIV_DOUBLE_2ADDR = 0xce,
    OP_REM_DOUBLE_2ADDR = 0xcf,
    OP_ADD_INT_LIT16 = 0xd0,
    OP_RSUB_INT = 0xd1,
    OP_MUL_INT_LIT16 = 0xd2,
    OP_DIV_INT_LIT16 = 0xd3,
    OP_REM_INT_LIT16 = 0xd4,
    OP_AND_INT_LIT16 = 0xd5,
    OP_OR_INT_LIT16 = 0xd6,
    OP_XOR_INT_LIT16 = 0xd7,
    OP_ADD_INT_LIT8 = 0xd8,
    OP_RSUB_INT_LIT8 = 0xd9,
    OP_MUL_INT_LIT8 = 0xda,
    OP_DIV_INT_LIT8 = 0xdb,
    OP_REM_INT_LIT8 = 0xdc,
    OP_AND_INT_LIT8 = 0xdd,
    OP_OR_INT_LIT8 = 0xde,
    OP_XOR_INT_LIT8 = 0xdf,
    OP_SHL_INT_LIT8 = 0xe0,
    OP_SHR_INT_LIT8 = 0xe1,
    OP_USHR_INT_LIT8 = 0xe2,
    OP_IGET_VOLATILE = 0xe3,
    OP_IPUT_VOLATILE = 0xe4,
    OP_SGET_VOLATILE = 0xe5,
    OP_SPUT_VOLATILE = 0xe6,
    OP_IGET_OBJECT_VOLATILE = 0xe7,
    OP_IGET_WIDE_VOLATILE = 0xe8,
    OP_IPUT_WIDE_VOLATILE = 0xe9,
    OP_SGET_WIDE_VOLATILE = 0xea,
    OP_SPUT_WIDE_VOLATILE = 0xeb,
    OP_BREAKPOINT = 0xec,
    OP_THROW_VERIFICATION_ERROR = 0xed,
    OP_EXECUTE_INLINE = 0xee,
    OP_EXECUTE_INLINE_RANGE = 0xef,
    OP_INVOKE_OBJECT_INIT_RANGE = 0xf0,
    OP_RETURN_VOID_BARRIER = 0xf1,
    OP_IGET_QUICK = 0xf2,
    OP_IGET_WIDE_QUICK = 0xf3,
    OP_IGET_OBJECT_QUICK = 0xf4,
    OP_IPUT_QUICK = 0xf5,
    OP_IPUT_WIDE_QUICK = 0xf6,
    OP_IPUT_OBJECT_QUICK = 0xf7,
    OP_INVOKE_VIRTUAL_QUICK = 0xf8,
    OP_INVOKE_VIRTUAL_QUICK_RANGE = 0xf9,
    OP_INVOKE_SUPER_QUICK = 0xfa,
    OP_INVOKE_SUPER_QUICK_RANGE = 0xfb,
    OP_IPUT_OBJECT_VOLATILE = 0xfc,
    OP_SGET_OBJECT_VOLATILE = 0xfd,
    OP_SPUT_OBJECT_VOLATILE = 0xfe,
    OP_UNUSED_FF = 0xff,
    // END(libdex-opcode-enum)
};
enum InstructionFormat {
    kFmt00x = 0,    // unknown format (also used for "breakpoint" opcode)
    kFmt10x,        // op
    kFmt12x,        // op vA, vB
    kFmt11n,        // op vA, #+B
    kFmt11x,        // op vAA
    kFmt10t,        // op +AA
    kFmt20bc,       // [opt] op AA, thing@BBBB
    kFmt20t,        // op +AAAA
    kFmt22x,        // op vAA, vBBBB
    kFmt21t,        // op vAA, +BBBB
    kFmt21s,        // op vAA, #+BBBB
    kFmt21h,        // op vAA, #+BBBB00000[00000000]
    kFmt21c,        // op vAA, thing@BBBB
    kFmt23x,        // op vAA, vBB, vCC
    kFmt22b,        // op vAA, vBB, #+CC
    kFmt22t,        // op vA, vB, +CCCC
    kFmt22s,        // op vA, vB, #+CCCC
    kFmt22c,        // op vA, vB, thing@CCCC
    kFmt22cs,       // [opt] op vA, vB, field offset CCCC
    kFmt30t,        // op +AAAAAAAA
    kFmt32x,        // op vAAAA, vBBBB
    kFmt31i,        // op vAA, #+BBBBBBBB
    kFmt31t,        // op vAA, +BBBBBBBB
    kFmt31c,        // op vAA, string@BBBBBBBB
    kFmt35c,        // op {vC,vD,vE,vF,vG}, thing@BBBB
    kFmt35ms,       // [opt] invoke-virtual+super
    kFmt3rc,        // op {vCCCC .. v(CCCC+AA-1)}, thing@BBBB
    kFmt3rms,       // [opt] invoke-virtual+super/range
    kFmt51l,        // op vAA, #+BBBBBBBBBBBBBBBB
    kFmt35mi,       // [opt] inline invoke
    kFmt3rmi,       // [opt] inline invoke/range
};
enum InstructionIndexType {
    kIndexUnknown = 0,
    kIndexNone,         // has no index
    kIndexVaries,       // "It depends." Used for throw-verification-error
    kIndexTypeRef,      // type reference index
    kIndexStringRef,    // string reference index
    kIndexMethodRef,    // method reference index
    kIndexFieldRef,     // field reference index
    kIndexInlineMethod, // inline method index (for inline linked methods)
    kIndexVtableOffset, // vtable offset (for static linked methods)
    kIndexFieldOffset   // field offset (for static linked fields)
};
enum OpcodeFlagsBits {
    kInstrCanBranch = 1,        // conditional or unconditional branch
    kInstrCanContinue = 1 << 1,   // flow can continue to next statement
    kInstrCanSwitch = 1 << 2,   // switch statement
    kInstrCanThrow = 1 << 3,   // could cause an exception to be thrown
    kInstrCanReturn = 1 << 4,   // returns, no additional statements
    kInstrInvoke = 1 << 5,   // a flavor of invoke
};
enum {
    kCompressStored = 0,        // no compression
    kCompressDeflated = 8,        // standard deflate
};

 int readSignedLeb128(u1 **pStream) {
    u1 *ptr = *pStream;
    unsigned int result = *(ptr++);

    if (result <= 0x7f) {
        result = (result << 25) >> 25;
    } else {
        int cur = *(ptr++);
        result = (result & 0x7f) | ((cur & 0x7f) << 7);
        if (cur <= 0x7f) {
            result = (result << 18) >> 18;
        } else {
            cur = *(ptr++);
            result |= (cur & 0x7f) << 14;
            if (cur <= 0x7f) {
                result = (result << 11) >> 11;
            } else {
                cur = *(ptr++);
                result |= (cur & 0x7f) << 21;
                if (cur <= 0x7f) {
                    result = (result << 4) >> 4;
                } else {
                    cur = *(ptr++);
                    result |= cur << 28;
                }
            }
        }
    }

    *pStream = ptr;
    return result;
}

struct DexCatchHandler {
    u4 typeIdx;    /* type index of the caught exception type */
    u4 address;    /* handler address */
};
struct DexCatchIterator {
    const u1 *pEncodedData;
    bool catchesAll;
    u4 countRemaining;
    DexCatchHandler handler;
};
struct DexClassDataHeader {
    u4 staticFieldsSize;
    u4 instanceFieldsSize;
    u4 directMethodsSize;
    u4 virtualMethodsSize;
};
struct DexField {
    u4 fieldIdx;    /* index to a field_id_item */
    u4 accessFlags;
};
struct DexMethod {
    u4 methodIdx;    /* index to a method_id_item */
    u4 accessFlags;
    u4 codeOff;      /* file offset to a code_item */
};
struct DexClassData {
    DexClassDataHeader header;
    std::vector<DexField *> *staticFields;
    std::vector<DexField *> *instanceFields;
    std::vector<DexMethod *> *directMethods;
    std::vector<DexMethod *> *virtualMethods;
};
struct DexDataMap {
    u4 count;    /* number of items currently in the map */
    u4 max;      /* maximum number of items that may be held */
    u4 *offsets; /* array of item offsets */
    u2 *types;   /* corresponding array of item types */
};
struct DexHeader {
    u1 magic[8];           /* includes version number */
    u4 checksum;           /* adler32 checksum */
    u1 signature[kSHA1DigestLen]; /* SHA-1 hash */
    u4 fileSize;           /* length of entire file */
    u4 headerSize;         /* offset to start of next section */
    u4 endianTag;
    u4 linkSize;
    u4 linkOff;
    u4 mapOff;
    u4 stringIdsSize;
    u4 stringIdsOff;
    u4 typeIdsSize;
    u4 typeIdsOff;
    u4 protoIdsSize;
    u4 protoIdsOff;
    u4 fieldIdsSize;
    u4 fieldIdsOff;
    u4 methodIdsSize;
    u4 methodIdsOff;
    u4 classDefsSize;
    u4 classDefsOff;
    u4 dataSize;
    u4 dataOff;
};
struct DexMapItem {
    u2 type;              /* type code (see kDexType* above) */
    u2 unused;
    u4 size;              /* count of items of the indicated type */
    u4 offset;            /* file offset to the start of data */
};
struct DexMapList {
    u4 size;               /* #of entries in list */
    DexMapItem list[1];     /* entries */
};
struct DexStringId {
    u4 stringDataOff;      /* file offset to string_data_item */
};
struct DexTypeId {
    u4 descriptorIdx;      /* index into stringIds list for type descriptor */
};
struct DexFieldId {
    u2 classIdx;           /* index into typeIds list for defining class */
    u2 typeIdx;            /* index into typeIds for field type */
    u4 nameIdx;            /* index into stringIds for field name */
};
struct DexMethodId {
    u2 classIdx;           /* index into typeIds list for defining class */
    u2 protoIdx;           /* index into protoIds for method prototype */
    u4 nameIdx;            /* index into stringIds for method name */
};
struct DexProtoId {
    u4 shortyIdx;          /* index into stringIds for shorty descriptor */
    u4 returnTypeIdx;      /* index into typeIds list for return type */
    u4 parametersOff;      /* file offset to type_list for parameter types */
};
struct DexClassDef {
    u4 classIdx;           /* index into typeIds for this class */
    u4 accessFlags;
    u4 superclassIdx;      /* index into typeIds for superclass */
    u4 interfacesOff;      /* file offset to DexTypeList */
    u4 sourceFileIdx;      /* index into stringIds for source file name */
    u4 annotationsOff;     /* file offset to annotations_directory_item */
    u4 classDataOff;       /* file offset to class_data_item */
    u4 staticValuesOff;    /* file offset to DexEncodedArray */
};

struct DexClassInfo {
    DexClassDef* classDef;
    u4 interfacesOff;      /* file offset to DexTypeList */
    u4 annotationsOff;     /* file offset to annotations_directory_item */
    DexClassData* classDataOff;       /* file offset to class_data_item */
    u4 staticValuesOff;    /* file offset to DexEncodedArray */
};
struct DexTypeItem {
    u2 typeIdx;            /* index into typeIds */
};
struct DexTypeList {
    u4 size;               /* #of entries in list */
    DexTypeItem list[];    /* entries */
};
struct DexCode {
    u2 registersSize;
    u2 insSize;
    u2 outsSize;
    u2 triesSize;
    u4 debugInfoOff;       /* file offset to debug info stream */
    u4 insnsSize;          /* size of the insns array, in u2 units */
    u1 insns[1];
    /* followed by optional u2 padding */
    /* followed by try_item[triesSize] */
    /* followed by uleb128 handlersSize */
    /* followed by catch_handler_item[handlersSize] */
};
struct DexTry {
    u4 startAddr;          /* start address, in 16-bit code units */
    u2 insnCount;          /* instruction count, in 16-bit code units */
    u2 handlerOff;         /* offset in encoded handler data to handlers */
};
struct DexLink {
    u1 bleargh;
};
struct DexAnnotationsDirectoryItem {
    u4 classAnnotationsOff;  /* offset to DexAnnotationSetItem */
    u4 fieldsSize;           /* count of DexFieldAnnotationsItem */
    u4 methodsSize;          /* count of DexMethodAnnotationsItem */
    u4 parametersSize;       /* count of DexParameterAnnotationsItem */
    /* followed by DexFieldAnnotationsItem[fieldsSize] */
    /* followed by DexMethodAnnotationsItem[methodsSize] */
    /* followed by DexParameterAnnotationsItem[parametersSize] */
};
struct DexFieldAnnotationsItem {
    u4 fieldIdx;
    u4 annotationsOff;             /* offset to DexAnnotationSetItem */
};
struct DexMethodAnnotationsItem {
    u4 methodIdx;
    u4 annotationsOff;             /* offset to DexAnnotationSetItem */
};
struct DexParameterAnnotationsItem {
    u4 methodIdx;
    u4 annotationsOff;             /* offset to DexAnotationSetRefList */
};
struct DexAnnotationSetRefItem {
    u4 annotationsOff;             /* offset to DexAnnotationSetItem */
};
struct DexAnnotationSetRefList {
    u4 size;
    DexAnnotationSetRefItem list[1];
};
struct DexAnnotationSetItem {
    u4 size;
    u4 entries[1];                 /* offset to DexAnnotationItem */
};
struct DexAnnotationItem {
    u1 visibility;
    u1 annotation[1];              /* data in encoded_annotation format */
};
struct DexEncodedArray {
    u1 array[1];                   /* data in encoded_array format */
};
struct DexClassLookup {
    int size;                       // total size, including "size"
    int numEntries;                 // size of table[]; always power of 2
    struct {
        u4 classDescriptorHash;    // class descriptor hash code
        int classDescriptorOffset;  // in bytes, from start of DEX
        int classDefOffset;         // in bytes, from start of DEX
    } table[1];
};
struct DexOptHeader {
    u1 magic[8];           /* includes version number */

    u4 dexOffset;          /* file offset of DEX header */
    u4 dexLength;
    u4 depsOffset;         /* offset of optimized DEX dependency table */
    u4 depsLength;
    u4 optOffset;          /* file offset of optimized data tables */
    u4 optLength;

    u4 flags;              /* some info flags */
    u4 checksum;           /* adler32 checksum covering deps/opt */

    /* pad for 64-bit alignment if necessary */
};
struct DexFile {
    /* directly-mapped "opt" header */
    const DexOptHeader *pOptHeader;

    /* pointers to directly-mapped structs and arrays in base DEX */
    const DexHeader *pHeader;
    const DexStringId *pStringIds;
    const DexTypeId *pTypeIds;
    const DexFieldId *pFieldIds;
    const DexMethodId *pMethodIds;
    const DexProtoId *pProtoIds;
    const DexClassDef *pClassDefs;
    const DexLink *pLinkData;

    /*
     * These are mapped out of the "auxillary" section, and may not be
     * included in the file.
     */
    const DexClassLookup *pClassLookup;
    const void *pRegisterMapPool;       // RegisterMapClassPool

    /* points to start of DEX file data */
    const u1 *baseAddr;

    /* track memory overhead for auxillary structures */
    int overhead;

    /* additional app-specific data structures associated with the DEX */
    //void*               auxData;
};
struct DexStringCache {
    char *value;          /* the latest value */
    size_t allocatedSize; /* size of the allocated buffer, if allocated */
    char buffer[120];     /* buffer used to hold small-enough results */
};
struct DexProto {
    const DexFile *dexFile;     /* file the idx refers to */
    u4 protoIdx;                /* index into proto_ids table of dexFile */
};
struct DexParameterIterator {
    const DexProto *proto;
    const DexTypeList *parameters;
    int parameterCount;
    int cursor;
};
#endif //MDEX_DEX_H
