#include <iostream>
#include <bitset>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2/features2d/features2d.hpp>  
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp> 

using namespace cv;  
using namespace std;  
  
int main2()  
{  
    initModule_nonfree();//初始化模块，使用SIFT或SURF时用到  
    Ptr<FeatureDetector> detector = FeatureDetector::create( "SIFT" );//创建SIFT特征检测器  
    Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create( "SIFT" );//创建特征向量生成器  
    Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create( "BruteForce" );//创建特征匹配器  
    if( detector.empty() || descriptor_extractor.empty() )  
        cout<<"fail to create detector!";  
  
    //读入图像  
    Mat img1 = imread("E:\\image\\2.bmp");  
    Mat img2 = imread("E:\\image\\23.bmp");  
  
    //特征点检测  
    double t = getTickCount();//当前滴答数  
    vector<KeyPoint> keypoints1,keypoints2;  
    detector->detect( img1, keypoints1 );//检测img1中的SIFT特征点，存储到keypoints1中  
    detector->detect( img2, keypoints2 );  
    cout<<"图像1特征点个数:"<<keypoints1.size()<<endl;  
    cout<<"图像2特征点个数:"<<keypoints2.size()<<endl;  
  
    //根据特征点计算特征描述子矩阵，即特征向量矩阵  
    Mat descriptors1,descriptors2;  
    descriptor_extractor->compute( img1, keypoints1, descriptors1 );  
    descriptor_extractor->compute( img2, keypoints2, descriptors2 );  
    t = ((double)getTickCount() - t)/getTickFrequency();  
    cout<<"SIFT算法用时："<<t<<"秒"<<endl;  
  
  
    cout<<"图像1特征描述矩阵大小："<<descriptors1.size()  
        <<"，特征向量个数："<<descriptors1.rows<<"，维数："<<descriptors1.cols<<endl;  
    cout<<"图像2特征描述矩阵大小："<<descriptors2.size()  
        <<"，特征向量个数："<<descriptors2.rows<<"，维数："<<descriptors2.cols<<endl;  
  
    //画出特征点  
    Mat img_keypoints1,img_keypoints2;  
    drawKeypoints(img1,keypoints1,img_keypoints1,Scalar::all(-1),0);  
    drawKeypoints(img2,keypoints2,img_keypoints2,Scalar::all(-1),0);  
    //imshow("Src1",img_keypoints1);  
    //imshow("Src2",img_keypoints2);  
  
    //特征匹配  
    vector<DMatch> matches;//匹配结果  
    descriptor_matcher->match( descriptors1, descriptors2, matches );//匹配两个图像的特征矩阵  
    cout<<"Match个数："<<matches.size()<<endl;  
  
    //计算匹配结果中距离的最大和最小值  
    //距离是指两个特征向量间的欧式距离，表明两个特征的差异，值越小表明两个特征点越接近  
    double max_dist = 0;  
    double min_dist = 100;  
    for(int i=0; i<matches.size(); i++)  
    {  
        double dist = matches[i].distance;  
        if(dist < min_dist) min_dist = dist;  
        if(dist > max_dist) max_dist = dist;  
    }  
    cout<<"最大距离："<<max_dist<<endl;  
    cout<<"最小距离："<<min_dist<<endl;  
  
    //筛选出较好的匹配点  
    vector<DMatch> goodMatches;  
    for(int i=0; i<matches.size(); i++)  
    {  
        if(matches[i].distance < 0.5 * max_dist)  
        {  
            goodMatches.push_back(matches[i]);  
        }  
    }  
    cout<<"goodMatch个数："<<goodMatches.size()<<endl;  
    cout<<"goodMatch："<<goodMatches.size()/keypoints2.size()<<endl;  
    //画出匹配结果  
    Mat img_matches;  
    //红色连接的是匹配的特征点对，绿色是未匹配的特征点  
    drawMatches(img1,keypoints1,img2,keypoints2,goodMatches,img_matches,  
                Scalar::all(-1)/*CV_RGB(255,0,0)*/,CV_RGB(0,255,0),Mat(),2);  
  
    imshow("MatchSIFT",img_matches);  
    waitKey(0);  
    return 0;  
}  