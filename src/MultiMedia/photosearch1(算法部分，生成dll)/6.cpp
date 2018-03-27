
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
  Mat src, dst;

 

 /// װ��ͼ��
 src = imread( "E:\\image\\red1.bmp");

 if( !src.data )
   { return -1; }

 

 /// �ָ��3����ͨ��ͼ�� ( R, G �� B )
 vector<Mat> rgb_planes;
 split( src, rgb_planes );

 

 /// �趨bin��Ŀ
 int histSize = 256;
 
 /// �趨ȡֵ��Χ ( R,G,B) )
 float range[] = { 0, 255 } ;       //���½�����
 const float* histRange = { range }; 

 

 bool uniform = true; bool accumulate = false;

 

 //����ֱ��ͼ�ľ���
 Mat r_hist, g_hist, b_hist;

 

 /// ����ֱ��ͼ:
 //&rgb_planes[0]: ��������(�����鼯)
//1: ��������ĸ��� (��������ʹ����һ����ͨ��ͼ������Ҳ�����������鼯 )
//0: ��Ҫͳ�Ƶ�ͨ�� (dim)���� ����������ֻ��ͳ���˻Ҷ� (��ÿ�����鶼�ǵ�ͨ��)����ֻҪд 0 �����ˡ�
//Mat(): ����( 0 ��ʾ���Ը�����)�� ���δ���壬��ʹ������
//r_hist: ����ֱ��ͼ�ľ���
//1: ֱ��ͼά��
//histSize: ÿ��ά�ȵ�bin��Ŀ
//histRange: ÿ��ά�ȵ�ȡֵ��Χ
//uniform �� accumulate: bin��С��ͬ�����ֱ��ͼ�ۼ�
 calcHist( &rgb_planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
 calcHist( &rgb_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
 calcHist( &rgb_planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

 

 // ����ֱ��ͼ����
 int hist_h = 400;
 int hist_w=256*3;
 //int bin_w = cvRound( (double) 256/histSize );             //bin�Ŀ��

 

 Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );  //����400������1200��ֱ��ͼͼ��     


 /// ��ֱ��ͼ��һ������Χ [ 0, histImage.rows ]��������ֱ��ͼ��ʱ�򲻻ᳬ��ͼƬ�ĸ߶ȣ��߶�400
 normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

 

 
  for( int i = 1; i < histSize; i++ )
   {   
  rectangle(histImage,Point(i-1,hist_h-1),Point(i,hist_h -cvRound(r_hist.at<float>(i))),Scalar( 0, 0, 255),1,8,0);
  rectangle(histImage,Point(i-1+256,hist_h-1),Point(i+256,hist_h -cvRound(g_hist.at<float>(i))),Scalar( 0, 255, 0),1,8,0);
  rectangle(histImage,Point(i-1+512,hist_h-1),Point(i+512,hist_h -cvRound(b_hist.at<float>(i))),Scalar( 255, 0, 0),1,8,0);
 

    }

 

 /// ��ʾֱ��ͼ
 namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
 imshow("calcHist Demo", histImage );

 waitKey(0);

 return 0;

}