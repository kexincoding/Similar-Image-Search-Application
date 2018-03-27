#pragma once

#define CONVENTION __stdcall

#define DLLEX_(type) extern "C" __declspec(dllexport) type CONVENTION 
#define DLLEX_IMPL_(type) type CONVENTION

DLLEX_(int) PrepareCompare(char* directoryPath);
DLLEX_(double) Compare(const char* pattern, const char* source);