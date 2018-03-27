
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main2(  )
{
  Mat src,src1, dst;

 

 /// װ��ͼ��
  src = imread( "E:\\image\\red1.bmp");
  src1 = imread( "E:\\image\\red9.bmp");
 if( !src.data )
   { return -1; }

   MatND hist,hist1;       // ��cv����CvHistogram *hist = cvCreateHist  
        int dims = 3;        
        float r_hranges[] = {0, 255};  
        float g_hranges[] = {0, 255};  
        float b_hranges[] = {0, 255};  
        const float *ranges[] = {r_hranges, g_hranges, b_hranges};   // ������ҪΪconst����  
        int size[3] = {16, 16, 16};  
        int channels[] ={0, 1, 2};   //���� r gͨ�� 2����bͨ��  
        // ����ͼ���ֱ��ͼ  
        calcHist(&src, 1, channels, Mat(), hist, dims, size, ranges,true, false);    // cv ����cvCalcHist  
        calcHist(&src1, 1, channels, Mat(), hist1, dims, size, ranges,true, false);

 
  for( int i = 0; i < 4; i++ )
     { int compare_method = i;
       double base_base = compareHist( hist, hist1, compare_method );

       printf( " Method [%d]  : %f\n", i, base_base);
     }
 system("pause");

 return 0;

}