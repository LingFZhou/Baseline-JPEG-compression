#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include <opencv2/nonfree/features2d.hpp>
#include<opencv2/legacy/legacy.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

void readme();

int main()
{
    Mat img_1=imread("image01.jpg",CV_LOAD_IMAGE_GRAYSCALE);//宏定义时CV_LOAD_IMAGE_GRAYSCALE=0，也就是读取灰度图像
    Mat img_2=imread("image02.jpg",CV_LOAD_IMAGE_GRAYSCALE);//一定要记得这里路径的斜线方向，这与Matlab里面是相反的

    //第一步，用SIFT算子检测关键点
    
    SiftFeatureDetector detector;//构造函数采用内部默认的
    std::vector<KeyPoint> keypoints_1,keypoints_2;//构造2个专门由点组成的点向量用来存储特征点

    detector.detect(img_1,keypoints_1);//将img_1图像中检测到的特征点存储起来放在keypoints_1中
    detector.detect(img_2,keypoints_2);//同理
	
    //在图像中画出特征点
    Mat img_keypoints_1,img_keypoints_2;

    drawKeypoints(img_1,keypoints_1,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);//在内存中画出特征点
    drawKeypoints(img_2,keypoints_2,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
	
    

    //计算特征向量
    SiftDescriptorExtractor extractor;//定义描述子对象

    Mat descriptors_1,descriptors_2;//存放特征向量的矩阵

    extractor.compute(img_1,keypoints_1,descriptors_1);//计算特征向量
    extractor.compute(img_2,keypoints_2,descriptors_2);

    //用burte force进行匹配特征向量
    BruteForceMatcher<L2<float>>matcher;//定义一个burte force matcher对象
    vector<DMatch>matches;
    matcher.match(descriptors_1,descriptors_2,matches);
	CvFont font;
	double hScale=1.0;
	double vScale=1.0;
	int lineWidth=3;
	int i=0;
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, hScale,vScale,0,lineWidth);
	char num[10];
	itoa(matches.size(),num,10);
	IplImage *img1 = &IplImage(img_keypoints_1);
	IplImage *img2 = &IplImage(img_keypoints_2);
	cvPutText (img1,num,cvPoint(320,450), &font,cvScalar(255,0,0));
	cvPutText (img2,num,cvPoint(320,450), &font,cvScalar(255,0,0));
	imshow("sift_keypoints_1",img_keypoints_1);//显示特征点
    imshow("sift_keypoints_2",img_keypoints_2);
    //绘制匹配线段
    Mat img_matches;
    drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);//将匹配出来的结果放入内存img_matches中

    //显示匹配线段
    imshow("sift_Matches",img_matches);//显示的标题为Matches
    waitKey(0);
    return 0;
}