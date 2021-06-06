#include <fstream>
#include <iostream>

#include <sstream>
#include <vector>
#include <map>
#include <cstring>
#include "dex.h"

using namespace std;

u1 *readString(u1 *address) {
    u1 **stream = &address;
    int length = readSignedLeb128(stream);
    return *stream;
}

map<int, string> map1;
map<string, int> codeLength;

string GetAccess(uint32_t flag) {
    basic_string<char> &basicString = map1[flag];
    return map1[flag] == "" ? "" : map1[flag] + "\t";
}


string GetOpCodeStr(u1 opcode) {
    if (opcode == 0x00) return "nop";
    if (opcode == 0x01) return "move vA, vB";;
    if (opcode == 0x02) return "move/from16 vAA, vBBBB";
    if (opcode == 0x03) return "move/16 vAAAA, vBBBB";
    if (opcode == 0x04) return "move-wide vA, vB";
    if (opcode == 0x05) return "move-wide/from16 vAA, vBBBB";
    if (opcode == 0x06) return "move-wide/16 vAAAA, vBBBB";
    if (opcode == 0x07) return "move-object vA, vB";
    if (opcode == 0x08) return "move-object/from16 vAA, vBBBB";
    if (opcode == 0x09) return "move-object/16 vAAAA, vBBBB";
    if (opcode == 0xa) return "move-result vAA";
    if (opcode == 0xb) return "move-result-wide vAA";
    if (opcode == 0xc) return "move-result-object vAA";
    if (opcode == 0xd) return "move-exception vAA";
    if (opcode == 0xe) return "return-void";
    if (opcode == 0xf) return "return vAA";
    if (opcode == 0x10) return "return-wide";
    if (opcode == 0x11) return "return-object vAA";
    if (opcode == 0x12) return "const/4 vA, #+B";
    if (opcode == 0x13) return "const/16 vAA, #+BBBB";
    if (opcode == 0x14) return "const vAA, #+BBBBBBBB";
    if (opcode == 0x15) return "const/high16 vAA, #+BBBB0000";
    if (opcode == 0x16) return "const-wide/16 vAA, #+BBBB";
    if (opcode == 0x17) return "const-wide/32 vAA, #+BBBBBBBB";
    if (opcode == 0x18) return "const-wide vAA, #+BBBBBBBBBBBBBBBB";
    if (opcode == 0x19) return "const-wide/high16 vAA, #+BBBB000000000000";
    if (opcode == 0x1a) return "const-string vAA, string@BBBB";
    if (opcode == 0x1b) return "const-string/jumbo vAA, string@BBBBBBBB";
    if (opcode == 0x1c) return "const-class vAA, type@BBBB";
    if (opcode == 0x1d) return "monitor-enter vAA";
    if (opcode == 0x1e) return "monitor-exit vAA";
    if (opcode == 0x1f) return "check-cast vAA, type@BBBB";
    if (opcode == 0x20) return "instance-of vA, vB, type@CCCC";
    if (opcode == 0x21) return "array-length vA, vB";
    if (opcode == 0x22) return "new-instance vAA, type@BBBB";
    if (opcode == 0x23) return "new-array vA, vB, type@CCCC";
    if (opcode == 0x24) return "filled-new-array {vD, vE, vF, vG, vA}, type@CCCC";
    if (opcode == 0x25) return "filled-new-array/range {vCCCC .. vNNNN}, type@BBBB";
    if (opcode == 0x26) return "fill-array-data vAA, +BBBBBBBB";
    if (opcode == 0x27) return "throw vAA";
    if (opcode == 0x28) return "goto +AA";
    if (opcode == 0x29) return "goto/16 +AAAA";
    if (opcode == 0x2a) return "goto/32 +AAAAAAAA";
    if (opcode == 0x2b) return "packed-switch vAA, +BBBBBBBB";
    if (opcode == 0x2c) return "sparse-switch vAA, +BBBBBBBB";
    if (opcode >= 0x2d and opcode <= 0x31) return "cmpkind vAA, vBB, vCC";
    if (opcode >= 0x32 and opcode <= 0x37) return "if-test vA, vB, +CCCC";
    if (opcode >= 0x38 and opcode <= 0x3d) return "if-testz vAA, +BBBB";
    if (opcode >= 0x3e and opcode <= 0x43) return "unused";
    if (opcode >= 0x44 and opcode <= 0x51) return "arrayop vAA, vBB, vCC";
    if (opcode >= 0x52 and opcode <= 0x5f) return "iinstanceop vA, vB, field@CCCC";
    if (opcode >= 0x60 and opcode <= 0x6d) return "sstaticop vAA, field@BBBB";
    if (opcode >= 0x6e and opcode <= 0x72) return "invoke-kind {vD, vE, vF, vG, vA}, meth@CCCC";
    if (opcode == 0x73) return "unused";
    if (opcode >= 0x74 and opcode <= 0x78) return "invoke-kind/range {vCCCC .. vNNNN}, meth@BBBB";
    if (opcode >= 0x79 and opcode <= 0x7a) return "unused";
    if (opcode >= 0x7b and opcode <= 0x8f) return "unop vA, vB";
    if (opcode >= 0x90 and opcode <= 0xaf) return "binop vAA, vBB, vCC";
    if (opcode >= 0xb0 and opcode <= 0xcf) return "binop/2addr vA, vB";
    if (opcode >= 0xd0 and opcode <= 0xd7) return "binop/lit16 vA, vB, #+CCCC";
    if (opcode >= 0xd8 and opcode <= 0xe2) return "binop/lit8 vAA, vBB, #+CC";
    if (opcode >= 0xe3 and opcode <= 0xfe) return "unused";
    if (opcode == 0x00ff) return "const-class/jumbo vAAAA, type@BBBBBBBB";
    if (opcode == 0x01ff) return "check-cast/jumbo vAAAA, type@BBBBBBBB";
    if (opcode == 0x02ff) return "instance-of/jumbo vAAAA, vBBBB, type@CCCCCCCC";
    if (opcode == 0x03ff) return "new-instance/jumbo vAAAA, type@BBBBBBBB";
    if (opcode == 0x04ff) return "new-array/jumbo vAAAA, vBBBB, type@CCCCCCCC";
    if (opcode == 0x05ff) return "filled-new-array/jumbo {vCCCC .. vNNNN}, type@BBBBBBBB";
    if (opcode >= 0x06ff and opcode <= 0x13ff) return "iinstanceop/jumbo vAAAA, vBBBB, field@CCCCCCCC";
    if (opcode >= 0x14ff and opcode <= 0x21ff) return "sstaticop/jumbo vAAAA, field@BBBBBBBB";
    if (opcode >= 0x22ff and opcode <= 0x26ff)return "invoke-kind/jumbo {vCCCC .. vNNNN}, meth@BBBBBBBB";
}

string GetOpCode(u1 opcode) {
    if (opcode == 0x00) return "10x";
    if (opcode == 0x01) return "12x";
    if (opcode == 0x02) return "22x";
    if (opcode == 0x03) return "32x";
    if (opcode == 0x04) return "12x";
    if (opcode == 0x05) return "22x";
    if (opcode == 0x06) return "32x";
    if (opcode == 0x07) return "12x";
    if (opcode == 0x08) return "22x";
    if (opcode == 0x09) return "32x";
    if (opcode == 0xa) return "11x";
    if (opcode == 0xb) return "11x";
    if (opcode == 0xc) return "11x";
    if (opcode == 0xd) return "11x";
    if (opcode == 0xe) return "10x";
    if (opcode == 0xf) return "11x";
    if (opcode == 0x10) return "11x";
    if (opcode == 0x11) return "11x";
    if (opcode == 0x12) return "11n";
    if (opcode == 0x13) return "21s";
    if (opcode == 0x14) return "31i";
    if (opcode == 0x15) return "21h";
    if (opcode == 0x16) return "21s";
    if (opcode == 0x17) return "31i";
    if (opcode == 0x18) return "51l";
    if (opcode == 0x19) return "21h";
    if (opcode == 0x1a) return "21c";
    if (opcode == 0x1b) return "31c";
    if (opcode == 0x1c) return "21c";
    if (opcode == 0x1d) return "11x";
    if (opcode == 0x1e) return "11x";
    if (opcode == 0x1f) return "21c";
    if (opcode == 0x20) return "22c";
    if (opcode == 0x21) return "12x";
    if (opcode == 0x22) return "21c";
    if (opcode == 0x23) return "22c";
    if (opcode == 0x24) return "35c";
    if (opcode == 0x25) return "3rc";
    if (opcode == 0x26) return "31t";
    if (opcode == 0x27) return "11x";
    if (opcode == 0x28) return "10t";
    if (opcode == 0x29) return "20t";
    if (opcode == 0x2a) return "30t";
    if (opcode == 0x2b) return "31t";
    if (opcode == 0x2c) return "31t";
    if (opcode >= 0x2d and opcode <= 0x31) return "23x";
    if (opcode >= 0x32 and opcode <= 0x37) return "22t";
    if (opcode >= 0x38 and opcode <= 0x3d) return "21t";
    if (opcode >= 0x3e and opcode <= 0x43) return "10x";
    if (opcode >= 0x44 and opcode <= 0x51) return "23x";
    if (opcode >= 0x52 and opcode <= 0x5f) return "22c";
    if (opcode >= 0x60 and opcode <= 0x6d) return "21c";
    if (opcode >= 0x6e and opcode <= 0x72) return "35c";
    if (opcode == 0x73) return "10x";
    if (opcode >= 0x74 and opcode <= 0x78) return "3rc";
    if (opcode >= 0x79 and opcode <= 0x7a) return "10x";
    if (opcode >= 0x7b and opcode <= 0x8f) return "12x";
    if (opcode >= 0x90 and opcode <= 0xaf) return "23x";
    if (opcode >= 0xb0 and opcode <= 0xcf) return "12x";
    if (opcode >= 0xd0 and opcode <= 0xd7) return "22s";
    if (opcode >= 0xd8 and opcode <= 0xe2) return "22b";
    if (opcode >= 0xe3 and opcode <= 0xfe) return "10x";
    if (opcode == 0x00ff) return "41c";
    if (opcode == 0x01ff) return "41c";
    if (opcode == 0x02ff) return "52c";
    if (opcode == 0x03ff) return "41c";
    if (opcode == 0x04ff) return "52c";
    if (opcode == 0x05ff) return "52rc";
    if (opcode >= 0x06ff and opcode <= 0x13ff)return "52c";
    if (opcode >= 0x14ff and opcode <= 0x21ff) return "41c";
    if (opcode >= 0x22ff and opcode <= 0x26ff) return "5rc";
}

void init() {
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("22x", 8));
    codeLength.insert(make_pair("32x", 10));
    codeLength.insert(make_pair("41c", 16));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("22x", 8));
    codeLength.insert(make_pair("32x", 10));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("22x", 8));
    codeLength.insert(make_pair("32x", 10));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11n", 4));
    codeLength.insert(make_pair("21s", 8));
    codeLength.insert(make_pair("31i", 12));
    codeLength.insert(make_pair("21h", 8));
    codeLength.insert(make_pair("21s", 8));
    codeLength.insert(make_pair("31i", 12));
    codeLength.insert(make_pair("21h", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("31c", 12));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("31t", 12));
    codeLength.insert(make_pair("11x", 4));
    codeLength.insert(make_pair("10t", 4));
    codeLength.insert(make_pair("20t", 8));
    codeLength.insert(make_pair("30t", 12));
    codeLength.insert(make_pair("31t", 12));
    codeLength.insert(make_pair("31t", 12));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("22t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("21t", 8));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("22c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("21c", 8));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("35c", 12));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("3rc", 12));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("23x", 8));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("12x", 4));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22s", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("22b", 8));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));
    codeLength.insert(make_pair("10x", 4));


    map1.insert(make_pair(0x00000001, "public"));
    map1.insert(make_pair(0x00000002, "private"));
    map1.insert(make_pair(0x00000004, "protect"));
    map1.insert(make_pair(0x00000008, "static"));
    map1.insert(make_pair(0x00000001, "final"));
    map1.insert(make_pair(0x00000010, "public"));
    map1.insert(make_pair(0x00000020, "synchronized"));
    map1.insert(make_pair(0x00000040, "volatile"));
    map1.insert(make_pair(0x00000040, "bridge"));
    map1.insert(make_pair(0x00000080, "transient"));
    map1.insert(make_pair(0x00000080, "varargs"));
    map1.insert(make_pair(0x00000100, "native"));
    map1.insert(make_pair(0x00000200, "interface"));
    map1.insert(make_pair(0x00000400, "abstract"));
    map1.insert(make_pair(0x00000800, "strict"));
    map1.insert(make_pair(0x00001000, "synthetic"));
    map1.insert(make_pair(0x00002000, "annotation"));
    map1.insert(make_pair(0x00004000, "enum"));
    map1.insert(make_pair(0x00010000, "constructor"));
    map1.insert(make_pair(0x00020000, "synchronized"));
}

vector<u1 *> stringIds;
vector<DexMethodId *> methodIds;
vector<DexTypeId *> typeIds;
vector<DexProtoId *> protoIds;
vector<DexFieldId *> fieldIds;
vector<DexClassInfo *> classInfos;

int main(int argc, char *argv[]) {
    init();
    ifstream t(argv[1], ios::in | ios::binary);
    string contents((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

    const char *base = contents.data();
    auto *H = (DexHeader *) base;
    auto stringIdArr = (DexStringId *) (H->stringIdsOff + base);
    stringIds.reserve(H->stringIdsSize);
    for (int i = 0; i < H->stringIdsSize; ++i) {
        stringIds.push_back((u1 *) (stringIdArr[i].stringDataOff + base));
    }

    auto *typeIdArr = (DexTypeId *) (H->typeIdsOff + base);

    typeIds.reserve(H->typeIdsSize);
    for (int i = 0; i < H->typeIdsSize; ++i) {
        typeIds.push_back(&typeIdArr[i]);
    }
    auto *protoIdArr = (DexProtoId *) (H->protoIdsOff + base);

    protoIds.reserve(H->protoIdsSize);
    for (int i = 0; i < H->protoIdsSize; ++i) {
        protoIds.push_back(&protoIdArr[i]);
    }

    auto *fieldIdArr = (DexFieldId *) (H->fieldIdsOff + base);

    fieldIds.reserve(H->fieldIdsSize);
    for (int i = 0; i < H->fieldIdsSize; ++i) {
        fieldIds.push_back(&fieldIdArr[i]);
    }

    auto *methodIdArr = (DexMethodId *) (H->methodIdsOff + base);

    methodIds.reserve(H->methodIdsSize);
    for (int i = 0; i < H->methodIdsSize; ++i) {
        methodIds.push_back(&methodIdArr[i]);
    }


    classInfos.reserve(H->classDefsSize);
    for (int i = 0; i < H->classDefsSize; ++i) {

        auto *classInfo = new DexClassInfo;
        auto *classData = new DexClassData;
        auto *pDef = (DexClassDef *) (H->classDefsOff + base + i * sizeof(DexClassDef));


        u1 *c1 = stringIds[typeIds[pDef->classIdx]->descriptorIdx];
        u1 **stream1 = &c1;
        int length = readSignedLeb128(stream1);

        u1 *address = (u1 *) (pDef->classDataOff + base);
        u1 **stream = &address;
        classInfo->classDef = pDef;
        classInfo->classDataOff = classData;
        classData->header.staticFieldsSize = readSignedLeb128(stream);
        classData->header.instanceFieldsSize = readSignedLeb128(stream);
        classData->header.directMethodsSize = readSignedLeb128(stream);
        classData->header.virtualMethodsSize = readSignedLeb128(stream);
        try {
            auto *staticFields = new vector<DexField *>;
            for (int i1 = 0; i1 < classData->header.staticFieldsSize; ++i1) {
                auto *dexField = new DexField;
                dexField->fieldIdx = readSignedLeb128(stream);
                dexField->accessFlags = readSignedLeb128(stream);
                staticFields->push_back(dexField);
            }
            classData->staticFields = staticFields;
        } catch (exception &e) {
            cout << classData->header.virtualMethodsSize << endl;
        }


        auto *instanceFields = new vector<DexField *>;
        for (int i1 = 0; i1 < classData->header.instanceFieldsSize; ++i1) {
            auto *dexField = new DexField;
            dexField->fieldIdx = readSignedLeb128(stream);
            dexField->accessFlags = readSignedLeb128(stream);
            instanceFields->push_back(dexField);
        }
        classData->instanceFields = instanceFields;


        auto *directMethods = new vector<DexMethod *>;
        for (int i1 = 0; i1 < classData->header.directMethodsSize; ++i1) {
            auto *dexMethod = new DexMethod;
            dexMethod->methodIdx = readSignedLeb128(stream);
            dexMethod->accessFlags = readSignedLeb128(stream);
            dexMethod->codeOff = readSignedLeb128(stream);
            directMethods->push_back(dexMethod);
        }
        classData->directMethods = directMethods;

        auto *virtualMethods = new vector<DexMethod *>;
        for (int i1 = 0; i1 < classData->header.virtualMethodsSize; ++i1) {

            auto *dexMethod = new DexMethod;
            dexMethod->methodIdx = readSignedLeb128(stream);
            dexMethod->accessFlags = readSignedLeb128(stream);
            dexMethod->codeOff = readSignedLeb128(stream);
            virtualMethods->push_back(dexMethod);
        }
        classData->virtualMethods = virtualMethods;

        classInfos.push_back(classInfo);
    }

    for (const auto &item : classInfos) {
        u1 *c = stringIds[typeIds[item->classDef->classIdx]->descriptorIdx];
        u1 **stream = &c;
        int length = readSignedLeb128(stream);
        cout << GetAccess(item->classDef->accessFlags) << "class " << c << endl;
        int prior = 0;
        for (const auto &item1 : *item->classDataOff->virtualMethods) {
            prior += item1->methodIdx;

            DexMethodId *&pId = methodIds[prior];

            cout << "\t" << GetAccess(item1->accessFlags) << readString(stringIds[pId->nameIdx])
                 << "(";
            if (protoIds[pId->protoIdx]->parametersOff != 0) {
                auto *typeList = (DexTypeList *) (protoIds[pId->protoIdx]->parametersOff + base);

                for (int i1 = 0; i1 < typeList->size; ++i1) {
                    cout << readString(stringIds[typeIds[typeList->list[i1].typeIdx]->descriptorIdx]);
                }
            }
            cout << readString(stringIds[typeIds[protoIds[pId->protoIdx]->returnTypeIdx]->descriptorIdx])
                 << endl;
            if (item1->codeOff == 0 || item->classDef->classDataOff == 0)
                continue;

            auto *code = (DexCode *) (item1->codeOff + base);
            int i1 = 0;
            for (i1 = 0; i1 < code->insnsSize * 2; i1++) {
                const string &basicString = GetOpCode(code->insns[i1]);


                printf("\t\t%s\n", GetOpCodeStr(code->insns[i1]).data());
                i1 += codeLength[basicString] / 2 - 1;

            }

            cout << endl << endl;

        }
        cout << endl;
    }
   // system("pause");
    return 0;
}
