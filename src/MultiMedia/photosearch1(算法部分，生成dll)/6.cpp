
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
  Mat src, dst;

 

 /// 装载图像
 src = imread( "E:\\image\\red1.bmp");

 if( !src.data )
   { return -1; }

 

 /// 分割成3个单通道图像 ( R, G 和 B )
 vector<Mat> rgb_planes;
 split( src, rgb_planes );

 

 /// 设定bin数目
 int histSize = 256;
 
 /// 设定取值范围 ( R,G,B) )
 float range[] = { 0, 255 } ;       //上下界区间
 const float* histRange = { range }; 

 

 bool uniform = true; bool accumulate = false;

 

 //储存直方图的矩阵
 Mat r_hist, g_hist, b_hist;

 

 /// 计算直方图:
 //&rgb_planes[0]: 输入数组(或数组集)
//1: 输入数组的个数 (这里我们使用了一个单通道图像，我们也可以输入数组集 )
//0: 需要统计的通道 (dim)索引 ，这里我们只是统计了灰度 (且每个数组都是单通道)所以只要写 0 就行了。
//Mat(): 掩码( 0 表示忽略该像素)， 如果未定义，则不使用掩码
//r_hist: 储存直方图的矩阵
//1: 直方图维数
//histSize: 每个维度的bin数目
//histRange: 每个维度的取值范围
//uniform 和 accumulate: bin大小相同，清楚直方图痕迹
 calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
 calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
 calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

 

 // 创建直方图画布
 int hist_h = 400;
 int hist_w=256*3;
 //int bin_w = cvRound( (double) 256/histSize );             //bin的宽度

 

 Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );  //行数400，列数1200的直方图图像     


 /// 将直方图归一化到范围 [ 0, histImage.rows ]，这样画直方图的时候不会超出图片的高度，高度400
 normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

 

 
  for( int i = 1; i < histSize; i++ )
   {   
  rectangle(histImage,Point(i-1,hist_h-1),Point(i,hist_h -cvRound(r_hist.at<float>(i))),Scalar( 0, 0, 255),1,8,0);
  rectangle(histImage,Point(i-1+256,hist_h-1),Point(i+256,hist_h -cvRound(g_hist.at<float>(i))),Scalar( 0, 255, 0),1,8,0);
  rectangle(histImage,Point(i-1+512,hist_h-1),Point(i+512,hist_h -cvRound(b_hist.at<float>(i))),Scalar( 255, 0, 0),1,8,0);
 

    }

 

 /// 显示直方图
 namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
 imshow("calcHist Demo", histImage );

 waitKey(0);

 return 0;

}