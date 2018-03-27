#include <iostream>
#include <bitset>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <Windows.h>

#include "OpenCV.h"
#include "Main.h"

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\features2d\features2d.hpp>  
#include <opencv2\nonfree\nonfree.hpp>
#include <opencv2\legacy\legacy.hpp> 


using namespace std;
using namespace cv;

string ToString(const wchar_t* source)
{
	int length = WideCharToMultiByte(CP_OEMCP, 0, source, wcslen(source), nullptr, 0, nullptr, nullptr);
	char* retVal = new char[length + 1];
	WideCharToMultiByte(CP_OEMCP, 0, source, wcslen(source), retVal, length, nullptr, nullptr);
	return string(retVal);
}

int main()
{
	const wchar_t* source="E:\\image\\red1.bmp";
	const char* source="E:\\image\\red1.bmp";
}