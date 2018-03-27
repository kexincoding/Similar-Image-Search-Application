
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main2(  )
{
  Mat src,src1, dst;

 

 /// 装载图像
  src = imread( "E:\\image\\red1.bmp");
  src1 = imread( "E:\\image\\red9.bmp");
 if( !src.data )
   { return -1; }

   MatND hist,hist1;       // 在cv中用CvHistogram *hist = cvCreateHist  
        int dims = 3;        
        float r_hranges[] = {0, 255};  
        float g_hranges[] = {0, 255};  
        float b_hranges[] = {0, 255};  
        const float *ranges[] = {r_hranges, g_hranges, b_hranges};   // 这里需要为const类型  
        int size[3] = {16, 16, 16};  
        int channels[] ={0, 1, 2};   //代表 r g通道 2代表b通道  
        // 计算图像的直方图  
        calcHist(&src, 1, channels, Mat(), hist, dims, size, ranges,true, false);    // cv 中是cvCalcHist  
        calcHist(&src1, 1, channels, Mat(), hist1, dims, size, ranges,true, false);

 
  for( int i = 0; i < 4; i++ )
     { int compare_method = i;
       double base_base = compareHist( hist, hist1, compare_method );

       printf( " Method [%d]  : %f\n", i, base_base);
     }
 system("pause");

 return 0;

}