#pragma once
#include "HookIncludes.h"
#include <intrin.h>  
typedef bool(__thiscall* in_prediction_t)(PVOID);

bool __stdcall hkInPrediction()
{
    static auto sig = U::FindPattern("client.dll", (PBYTE)"\x84\xC0\x75\x08\x57\x8B\xCE\xE8\x00\x00\x00\x00\x8B\x06", "xxxxxxxx????xx");
	bool result;
    static auto ofunc = hooks::prediction.get_original<in_prediction_t>(14);
	static IPrediction *ecxVal = g_Prediction;
	result = ofunc(ecxVal);
	return result;
}