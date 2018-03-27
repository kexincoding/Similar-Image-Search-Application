#include <iostream>
#include <bitset>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;



// ��άֱ��ͼ ��ʽһ  
MatND getHistogram(Mat &image){  
        MatND hist;       // ��cv����CvHistogram *hist = cvCreateHist  
        int dims = 3;        
        float r_hranges[] = {0, 255};  
        float g_hranges[] = {0, 255};  
        float b_hranges[] = {0, 255};  
        const float *ranges[] = {r_hranges, g_hranges, b_hranges};   // ������ҪΪconst����  
        int size[3] = {16, 16, 16};  
        int channels[] ={0, 1, 2};   //���� r gͨ�� 2����bͨ��  
        // ����ͼ���ֱ��ͼ  
        calcHist(&image, 1, channels, Mat(), hist, dims, size, ranges);    // cv ����cvCalcHist  
          
      
        /*for(int i = 0; i < 16; i++)  
        {  
            for(int j = 0; j < 16; j++)  
            {  
                for(int k = 0; k < 16; k++)  
                {  
                    float value = hist.at<float>(i,j,k);           //   ע��ֱ��ͼ��ֵ��float����    cv����cvQueryHistValue_1D  
                    int realValue = saturate_cast<int>(value);  
                    int index = i + (j<<4) + (k<<8);  
                    histValue[index] = realValue;  
      
                }  
            }  
        }  */
       return hist;  

    }  


int main(){
	Mat img = imread("E:\\image\\pt1.jpg", 1);
	if(!img.data)
	{
		cout << "the image is not exist" << endl;
		return 0;
	}
	//int *HistValue = new int[4096];
	//for(int i = 0; i < 4096; i++)
	//	HistValue[i] = 0;
	MatND hist=getHistogram(img);
	string img_dir = "E:\\image";
	for(int i = 1; i <= 13; i++)
	{
		string pos;
		stringstream ss;
		ss << i;
		ss >> pos;
		string img_name = img_dir +"\\pt"+ pos +".jpg"; 
		Mat target = imread(img_name , 1);
		if(!target.data){
			cout << "the target image" << img_name << " is not exist" << endl;
			continue;
		}

		MatND hist1=getHistogram(target);
		double a=compareHist(hist,hist1,CV_COMP_INTERSECT);  
		cout <<"[" << i <<"-" <<  a << "] \n";
	}
	system("pause");
	return 0;
}