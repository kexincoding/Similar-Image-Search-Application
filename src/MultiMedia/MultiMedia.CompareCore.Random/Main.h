#pragma once

#define CONVENTION __stdcall

#define DLLEX_(type) extern "C" __declspec(dllexport) type CONVENTION 
#define DLLEX_IMPL_(type) type CONVENTION

DLLEX_(const wchar_t*) GetSolutionName();
DLLEX_(int) PrepareCompare(wchar_t* directoryPath);
DLLEX_(double) Compare(const wchar_t* pattern, const wchar_t* source);