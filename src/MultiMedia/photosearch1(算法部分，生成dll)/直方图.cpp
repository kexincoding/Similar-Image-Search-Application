#include <iostream>
#include <bitset>
#include <string>
#include <iomanip>
#include <cmath>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

void getHistogram(Mat &image, int **HistValue){  
    for(int i = 0; i < image.rows; i++){  
        for(int j = 0; j < image.cols; j++){  
            HistValue[0][image.at<Vec3b>(i,j)[0]] ++;  
            HistValue[1][image.at<Vec3b>(i,j)[1]] ++;  
            HistValue[2][image.at<Vec3b>(i,j)[2]] ++;  
        }  
    }  
      
}  

// ŷʽ����  
float getDistance(int **sur, int **dst){  
    float sum = 0;  
    for(int i = 0; i < 3; i++){  
        for(int j = 0; j < 256; j++){  
            sum += pow(sur[i][j]-dst[i][j]+0.0,2);  
        }  
          
    }  
    return sqrt(sum);  
}  
  
// ���Ҿ���  
float getCosDistance(int **sur, int **dst){  
    float surSum = 0, dstSum = 0, sum = 0;  
    for(int i = 0; i < 3; i++){  
        for(int j = 0; j < 256; j++){  
            surSum += pow(sur[i][j]+0.0,2);  
            dstSum += pow(dst[i][j]+0.0,2);  
            sum += sur[i][j]*dst[i][j];  
        }  
          
    }  
    surSum = sqrt(surSum);  
    dstSum = sqrt(dstSum);  
    return sum/(surSum*dstSum);  
}  
  
// ���Ͼ���,  ��Ҫ������Ԫ�ظ�����    
// ע�⣺����ɫֱ��ͼ�����ƶȱȽ��У����Ͼ���Ч�����  
  
float getPSDistance(int **sur, int**dst, const float sTotal, const float dTotal){  
    float sum = 0;  
    for(int i = 0; i < 3; i++){  
        for(int j = 0; j < 256; j++){  
            sum += sqrt((sur[i][j]/sTotal)*(dst[i][j]/dTotal));  
        }  
    }  
    return sum/3;    // ��Ϊ����������  
}  


int main2(){
	Mat img = imread("E:\\image\\red1.bmp", 1);
	if(!img.data)
	{
		cout << "the image is not exist" << endl;
		return 0;
	}
	int **HistValue = new int*[256];
	getHistogram(img, HistValue);
	string img_dir = "E:\\image";
	for(int i = 1; i <= 13; i++)
	{
		string pos;
		stringstream ss;
		ss << i;
		ss >> pos;
		string img_name = img_dir +"\\red"+ pos +".bmp"; 
		Mat target = imread(img_name , 1);
		if(!target.data){
			cout << "the target image" << img_name << " is not exist" << endl;
			continue;
		}
		int **H = new int*[256];
		getHistogram(target, H);
		float a=getCosDistance(HistValue, H);
		cout <<"��" << i <<"-" <<  a << "�� \n";
	}
	system("pause");
	return 0;
}