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

class ColorHistogram  
{  
private:  
    int histSize[3];  
    float hranges[2];  
    const float* ranges[3];  
    int channels[3];  
public:  
  
    //���캯��  
    ColorHistogram()  
    {  
        histSize[0]= histSize[1]= histSize[2]= 256;  
        hranges[0] = 0.0;  
        hranges[1] = 255.0;  
        ranges[0] = hranges;  
        ranges[1] = hranges;  
        ranges[2] = hranges;  
        channels[0] = 0;  
        channels[1] = 1;  
        channels[2] = 2;  
    }  
  
    //�����ɫͼ��ֱ��ͼ  
    Mat getHistogram(const Mat& image)  
    {  
        Mat hist;  
  
        //BGRֱ��ͼ  
        hranges[0]= 0.0;      
        hranges[1]= 255.0;  
        channels[0]= 0;   
        channels[1]= 1;   
        channels[2]= 2;   
  
        //����  
        calcHist(&image,1,channels,Mat(),hist,3,histSize,ranges);  
        return hist;  
    }  
  
    //������ɫ��ֱ��ͼ  
    Mat getHueHistogram(const Mat &image)  
    {  
        Mat hist;  
        Mat hue;  
        //ת����HSV�ռ�  
        cvtColor(image,hue,CV_BGR2HSV);  
  
        //����1άֱ��ͼʹ�õĲ���  
        hranges[0] = 0.0;  
        hranges[1] = 180.0;  
        channels[0] = 0;  
        //����ֱ��ͼ  
        calcHist(&hue,1,channels,Mat(),hist,1,histSize,ranges);  
        return hist;  
  
    }  
  
    //������ɫ  
    Mat colorReduce(const Mat &image,int div = 64)  
    {  
        int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));  
        uchar mask = 0xFF<<n;  
        Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();  
        Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();  
        //�������ͼ��  
        Mat result(image.rows,image.cols,image.type());  
        Mat_<Vec3b>::iterator itr = result.begin<Vec3b>();  
        for(;it != itend;++it,++itr)  
        {  
            (*itr)[0] = ((*it)[0]&mask) + div/2;  
            (*itr)[1] = ((*it)[1]&mask) + div/2;  
            (*itr)[2] = ((*it)[2]&mask) + div/2;  
        }  
        return result;  
    }  
  
}  ;


class ImageComparator  
{  
private:  
    Mat reference;  
    Mat input;  
    Mat refH;  
    Mat inputH;  
    ColorHistogram hist;  
    int div;  
public:  
    ImageComparator():div(32){}  
  
    void setColorReducation(int factor)  
    {  
        div = factor;  
    }  
  
    int getColorReduction()  
    {  
        return div;  
    }  
  
    void setRefrenceImage(const Mat &image)  
    {  
        reference = hist.colorReduce(image,div);  
        refH = hist.getHistogram(reference);  
    }  
  
    double compare(const Mat &image)  
    {  
        input = hist.colorReduce(image,div);  
        inputH = hist.getHistogram(input);  
        return compareHist(refH,inputH,CV_COMP_INTERSECT);  
    }  
};  

int main()  
{  
    Mat image = imread("E:\\image\\red1.bmp");  
    if(!image.data)  
        return -1;  
    imshow("�����ͼ��",image);  
    cout<<"ͼ��������Ϊ��"<<image.cols*image.rows<<endl;  
  
    ImageComparator c;  
    c.setRefrenceImage(image);  
  
    //���Լ���  
    Mat input = imread("E:\\image\\red1.bmp");  
    imshow("�Լ�",input);  
    cout<<"waves VS waves:"<<c.compare(input)<<endl;  
  
    input = imread("E:\\image\\red2.bmp");  
    imshow("dog",input);  
    cout<<"waves VS dog:"<<c.compare(input)<<endl;  
  
    input = imread("E:\\image\\red3.bmp");  
    imshow("����",input);  
    cout<<"waves VS marsh:"<<c.compare(input)<<endl;  
  
    input= cv::imread("E:\\image\\red4.bmp");  
    imshow("��",input);  
    cout<<"waves VS bear:"<<c.compare(input)<<endl;  
  
  
    waitKey(0);  
    return 0;  
}  