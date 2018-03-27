#pragma once

#ifdef _DEBUG
#define FRESKY_OPENCV_DEBUG 1 
#define FRESKY_OPENCV_RELEASE 0
#else
#define FRESKY_OPENCV_DEBUG 0 
#define FRESKY_OPENCV_RELEASE 1
#endif

#if WIN64
#define FRESKY_OPENCV_X86 0
#define FRESKY_OPENCV_X64 1
#else
#define FRESKY_OPENCV_X86 1
#define FRESKY_OPENCV_X64 0
#endif

#if FRESKY_OPENCV_X86 && FRESKY_OPENCV_DEBUG
#define FRESKY_OPENCV_LIB_PATH "E:\\opencv\\opencv\\build\\x86\\vc11\\lib\\"
#define FRESKY_OPENCV_LIB_POSTFIX "d.lib"
#elif FRESKY_OPENCV_X86 && FRESKY_OPENCV_RELEASE
#define FRESKY_OPENCV_LIB_PATH "E:\\opencv\\opencv\\build\\x86\\vc11\\lib\\"
#define FRESKY_OPENCV_LIB_POSTFIX ".lib"
#elif FRESKY_OPENCV_X64 && FRESKY_OPENCV_DEBUG
#define FRESKY_OPENCV_LIB_PATH "E:\\opencv\\opencv\\build\\x64\\vc11\\lib\\"
#define FRESKY_OPENCV_LIB_POSTFIX "d.lib"
#elif FRESKY_OPENCV_X64 && FRESKY_OPENCV_RELEASE
#define FRESKY_OPENCV_LIB_PATH "E:\\opencv\\opencv\\build\\x64\\vc11\\lib\\"
#define FRESKY_OPENCV_LIB_POSTFIX ".lib"
#endif

#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_calib3d249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_contrib249"  FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_core249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_features2d249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_flann249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_gpu249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_highgui249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_imgproc249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_legacy249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_ml249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_nonfree249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_objdetect249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_ocl249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_photo249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_stitching249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_superres249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_ts249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_video249" FRESKY_OPENCV_LIB_POSTFIX)
#pragma comment (lib, FRESKY_OPENCV_LIB_PATH "opencv_videostab249" FRESKY_OPENCV_LIB_POSTFIX)
