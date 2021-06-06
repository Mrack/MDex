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

string GetAccess(uint32_t flag) {
    basic_string<char> &basicString = map1[flag];
    return map1[flag] == "" ? "" : map1[flag] + "\t";
}

void init() {
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

int main(int argc, char *argv[]) {
    init();
    ifstream t(argv[1], ios::in | ios::binary);
    string contents((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

    const char *base = contents.data();
    auto *H = (DexHeader *) base;
    auto stringIdArr = (DexStringId *) (H->stringIdsOff + base);
    vector<u1 *> stringIds;
    stringIds.reserve(H->stringIdsSize);
    for (int i = 0; i < H->stringIdsSize; ++i) {
        stringIds.push_back((u1 *) (stringIdArr[i].stringDataOff + base));
    }

    auto *typeIdArr = (DexTypeId *) (H->typeIdsOff + base);
    vector<DexTypeId *> typeIds;
    typeIds.reserve(H->typeIdsSize);
    for (int i = 0; i < H->typeIdsSize; ++i) {
        typeIds.push_back(&typeIdArr[i]);
    }
    auto *protoIdArr = (DexProtoId *) (H->protoIdsOff + base);
    vector<DexProtoId *> protoIds;
    protoIds.reserve(H->protoIdsSize);
    for (int i = 0; i < H->protoIdsSize; ++i) {
        protoIds.push_back(&protoIdArr[i]);
    }

    auto *fieldIdArr = (DexFieldId *) (H->fieldIdsOff + base);
    vector<DexFieldId *> fieldIds;
    fieldIds.reserve(H->fieldIdsSize);
    for (int i = 0; i < H->fieldIdsSize; ++i) {
        fieldIds.push_back(&fieldIdArr[i]);
    }

    auto *methodIdArr = (DexMethodId *) (H->methodIdsOff + base);
    vector<DexMethodId *> methodIds;
    methodIds.reserve(H->methodIdsSize);
    for (int i = 0; i < H->methodIdsSize; ++i) {
        methodIds.push_back(&methodIdArr[i]);
    }


    vector<DexClassInfo *> classInfos;


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
                DexTypeList *typeList = (DexTypeList *) (protoIds[pId->protoIdx]->parametersOff + base);

                for (int i1 = 0; i1 < typeList->size; ++i1) {
                    cout << readString(stringIds[typeIds[typeList->list[i1].typeIdx]->descriptorIdx]);
                }
            }
            cout << readString(stringIds[typeIds[protoIds[pId->protoIdx]->returnTypeIdx]->descriptorIdx])
                 << endl;
            auto *code = (DexCode *) (item1->codeOff + base);
            cout << "\t\t";
            int i1 = 0;
            for (i1 = 0; i1 < 20; ++i1) {
                printf("%02X ", code->insns[i1]);
            }
            if (i1 == 20) {
                cout << "..More " << code->insnsSize;
            }

            cout << endl << endl;

        }
        cout << endl;
    }
    system("pause");
    return 0;
}
