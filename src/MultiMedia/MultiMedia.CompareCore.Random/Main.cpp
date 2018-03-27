#include "Main.h"

#include <cstdlib>
#include <ctime>

DLLEX_IMPL_(int) PrepareCompare(wchar_t*)
{
    auto t = time(nullptr);
    srand(*reinterpret_cast<unsigned int*>(&t));
    return 0;
}

DLLEX_IMPL_(const wchar_t*) GetSolutionName() { return L"Random"; }

DLLEX_IMPL_(double) Compare(const wchar_t*, const wchar_t*)
{
    return rand();
}
