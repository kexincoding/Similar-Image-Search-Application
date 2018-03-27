#define _CRT_SECURE_NO_WARNINGS

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

#define PI 3.1415926
#define hashLength 64

//FILE* logfile;

/*
	功能：获取DCT系数
	n：矩阵大小
	quotient: 系数
	quotientT: 系数转置
*/
void coefficient(const int &n, double **quotient, double **quotientT){
	double sqr = 1.0/sqrt(n+0.0);
	for(int i = 0; i < n; i++){
		quotient[0][i] = sqr;
		quotientT[i][0] =  sqr;
	}

	for(int i = 1; i < n; i++){
		for(int j = 0; j < n; j++){
			quotient[i][j] = sqrt(2.0/n)*cos(i*(j+0.5)*PI/n);  // 由公式得到
			quotientT[j][i] = quotient[i][j];
		}
	}

}
/*
	功能：两矩阵相乘
	A和B：源输入矩阵
	result：输出矩阵
*/
void matrixMultiply(double **A, double **B, int n, double **result){  
	double t = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			t = 0;
			for(int k = 0; k < n; k++)
				t += A[i][k]*B[k][j];   
			result[i][j] = t;
		}
	}
}


void DCT(Mat_<uchar> image, const int &n, double **iMatrix){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			iMatrix[i][j] = (double)image(i,j);
		}
	}

	// 为系数分配空间
	double **quotient = new double*[n];
	double **quotientT = new double*[n];
	double **tmp = new double*[n];
	for(int i = 0; i < n; i++){
		quotient[i] = new double[n];
		quotientT[i] = new double[n]; 
		tmp[i] = new double[n];
	}
	// 计算系数矩阵
	coefficient(n, quotient, quotientT);
	matrixMultiply(quotient, iMatrix, n, tmp);  // 由公式成绩结果
	matrixMultiply(tmp, quotientT, n, iMatrix);

	for(int i = 0; i < n; i++){
		delete []tmp[i];
		delete []quotient[i];
		delete []quotientT[i];
	}
	delete []tmp;
	delete []quotient;
	delete []quotientT;
}

// 计算8*8图像的平均灰度
double calcAverage(double **iMatrix, const int &size){
	double sum = 0;
	for(int i = 0 ; i < size; i++){
		for(int j = 0; j < size; j++){
			sum += iMatrix[i][j];
		}
	}
	return sum/(size*size);
}

/* 计算hash值
	image:8*8的灰度图像
	size: 图像大小  8*8
	phash:存放64位hash值
	averagePix: 灰度值的平均值
*/
void fingerPrint(double **iMatrix, const int &size, bitset<hashLength> &phash, const float &averagePix){
	for(int i = 0; i < size; i++){
		int pos = i * size;
		for(int j = 0; j < size; j++){
			phash[pos+j] = iMatrix[i][j] >= averagePix ? 1:0;
		}
	}
}

/*计算汉明距离*/
int hammingDistance(const bitset<hashLength> &query, const bitset<hashLength> &target){
	int distance = 0;
	for(int i = 0; i < hashLength; i++){
		distance += (query[i] == target[i] ? 0 : 1);
	}
	return distance;
}

string bitTohex(const bitset<hashLength> &target){
	string str;
	for(int i = 0; i < hashLength; i=i+4){
		int sum = 0;
		string s;
		sum += target[i] + (target[i+1]<<1) + (target[i+2]<<2) + (target[i+3]<<3);
		stringstream ss;
		ss << hex <<sum;    // 以十六进制保存
		ss >> s;
		str += s;
	}
	return str;
}

DLLEX_IMPL_(int) PrepareCompare(char* directoryPath)
{
	//logfile=fopen("log","w");
	return 0;
}

DLLEX_IMPL_(double) Compare(const char* pattern, const char* source)
{
	//fprintf(logfile, "Compare called, parameter 1 = '%s', parameter 2 = '%s'\n", 
	//	pattern, source);

	 initModule_nonfree();//初始化模块，使用SIFT或SURF时用到  
    Ptr<FeatureDetector> detector = FeatureDetector::create( "SIFT" );//创建SIFT特征检测器  
    Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create( "SIFT" );//创建特征向量生成器  
    Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create( "BruteForce" );//创建特征匹配器  
    if( detector.empty() || descriptor_extractor.empty() )  
        cout<<"fail to create detector!";  

	Mat img = imread(pattern, 1);
	if(!img.data){
		/*FILE* patternimage= fopen(pattern, "rb");
		if (patternimage != nullptr)
			fwprintf(logfile, L"Compare returned with error: read pattern image failed but open file succeed\n");
		else
			fwprintf(logfile, L"Compare returned with error: read pattern image failed with open file failed, errno: %d\n", errno);*/
		return 100000000;
	}

	vector<KeyPoint> keypoints1,keypoints2;  
    detector->detect( img, keypoints1 );
	Mat descriptors1,descriptors2;  
    descriptor_extractor->compute( img, keypoints1, descriptors1 );  
	//fwprintf(logfile, L"sift keypoints (pattern) Done\n");

		MatND hist,hist1;        // 在cv中用CvHistogram *hist = cvCreateHist  
        int dims = 3;        
        float r_hranges[] = {0, 255};  
        float g_hranges[] = {0, 255};  
        float b_hranges[] = {0, 255};  
        const float *range[] = {r_hranges, g_hranges, b_hranges};   // 这里需要为const类型  
        int s[3] = {16, 16, 16};  
        int channel[] ={0, 1, 2};   //代表 r g通道 2代表b通道  
        // 计算图像的直方图  
        calcHist(&img, 1, channel, Mat(), hist, dims, s, range,true, false); 
		//fwprintf(logfile, L"rgb hist (pattern) Done\n");


	Mat hsv_base, hsv_base1;
	cvtColor( img, hsv_base, CV_BGR2HSV );

	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

  // hue的取值范围从0到256, saturation取值范围从0到180
  float h_ranges[] = { 0, 256 };
  float s_ranges[] = { 0, 180 };

  const float* ranges[] = { h_ranges, s_ranges };

  // 使用第0和第1通道
  int channels[] = { 0, 1 };

  /// 直方图
  MatND hist_base,hist_base1;

  /// 计算HSV图像的直方图
  calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
  normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
  //fwprintf(logfile, L"hsv hist (pattern) Done\n");

	int size = 32;  // 图片缩放后大小

	resize(img, img, Size(size,size));      // 缩放到32*32
	cvtColor(img, img, COLOR_BGR2GRAY);       // 灰度化

	double **iMatrix = new double*[size];
	for(int i = 0; i < size; i++)
		iMatrix[i] = new double[size];
	DCT(img, size, iMatrix);   // 离散余弦变换
	float averagePix = calcAverage(iMatrix, 8);
	cout << averagePix << endl;
	bitset<hashLength> phash;
	fingerPrint(iMatrix, 8, phash, averagePix);

	//cout << phash << endl;
	string str = bitTohex(phash);
	cout << str << endl;

		Mat target = imread(source, 1);
		if(!target.data)
		{
		/*FILE* patternimage= fopen(source, "rb");
		if (patternimage != nullptr)
			fwprintf(logfile, L"Compare returned with error: read source image failed but open file succeed\n");
		else
			fwprintf(logfile, L"Compare returned with error: read spirce image failed with open file failed, errno: %d\n", errno);*/
			return 100000000;
		}

		detector->detect( target, keypoints2 );
		descriptor_extractor->compute( target, keypoints2, descriptors2 );  
		//fwprintf(logfile, L"sift keypoints (source) Done\n");

		 vector<DMatch> matches;//匹配结果  
		 descriptor_matcher->match( descriptors1, descriptors2, matches );//匹配两个图像的特征矩阵  
		double max_dist = 0;  
    double min_dist = 100;  
    for(int k=0; k<matches.size(); k++)  
    {  
        double dist = matches[k].distance;  
        if(dist < min_dist) min_dist = dist;  
        if(dist > max_dist) max_dist = dist;  
    }  
	vector<DMatch> goodMatches;  
    for(int k=0; k<matches.size(); k++)  
    {  
        if(matches[k].distance < 0.5 * max_dist)  
        {  
            goodMatches.push_back(matches[k]);  
        }  
    }  
	size_t a=goodMatches.size();
	if(max_dist==0)
		a=keypoints1.size();
    //cout<<"goodMatch个数："<<goodMatches.size()<<endl;  


		cvtColor( target, hsv_base1, CV_BGR2HSV );
		calcHist( &hsv_base1, 1, channels, Mat(), hist_base1, 2, histSize, ranges, true, false );
        normalize( hist_base1, hist_base1, 0, 1, NORM_MINMAX, -1, Mat() );
		/*fwprintf(logfile, L"hsv hist (source) Done\n");*/

		calcHist(&target, 1, channel, Mat(), hist1, dims, s, range,true, false);
		/*fwprintf(logfile, L"rgb hist (source) Done\n");*/

		resize(target, target, Size(size,size));
		cvtColor(target, target, COLOR_BGR2GRAY);
		DCT(target, size, iMatrix);

		float averagePix2 = calcAverage(iMatrix, 8);
		bitset<hashLength> phash2;
		fingerPrint(iMatrix, 8, phash2, averagePix2);

		int distance = hammingDistance(phash, phash2);      // 计算汉明距离

		//fwprintf(logfile, L"Compare Phash returned with value: %d\n", distance);

		double base = compareHist( hist_base, hist_base1, 3 );

		//fwprintf(logfile, L"Compare hsv returned with value: %lf\n", base);

		double b = compareHist( hist, hist1,3);

		//fwprintf(logfile, L"Compare rgb returned with value: %lf\n", b);

		double a1=keypoints1.size()-a;

		//fwprintf(logfile, L"Compare sift good match points: %d\n", a1);

		double ans=distance*base*b*a1;
	
	for(int i = 0; i < size; i++)
		delete []iMatrix[i];
	delete []iMatrix;

	//fwprintf(logfile, L"Compare returned with value: %lf\n", a1*1.00);
	//return static_cast<double>(a1);
	return b;
}