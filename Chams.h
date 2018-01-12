#pragma once
#include "SDK.h"

void InitKeyValues(KeyValues* keyValues, const char* name);

void LoadFromBuffer(KeyValues* keyValues, char const* resourceName, const char* pBuffer);

void ForceMaterial(Color color, IMaterial* material, bool useColor = true, bool forceMaterial = true);

void *operator new(size_t iAllocSize);
void operator delete(void *pMem);


IMaterial *CreateMaterial(bool shouldIgnoreZ, bool isLit = true, bool isWireframe = false);