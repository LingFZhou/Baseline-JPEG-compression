#include "cv.h"  
#include "highgui.h" 
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace cv;
using namespace std;
IplImage *pSrcImage=0;
IplImage *g_pGrayImage = 0; 
IplImage *g_pBinaryImage = 0;
int slider_pos = 100;
char filename[100];
void process_image(int h);
int main( int argc, char* argv[] )  
{	
	for(int i = 1; i <= 2; i++)
	{
		sprintf(filename,"%s%d%s","seal",i, ".jpg");
		pSrcImage = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED);// 加载原始图片  
		g_pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  // 转为灰度图  
		cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);  		
		g_pBinaryImage = cvCloneImage(g_pGrayImage);  
		cvNamedWindow("Source",1);  
		cvNamedWindow("Result",1);  
		cvShowImage("Source",pSrcImage);  
		cvCreateTrackbar("Threshold","Result",&slider_pos,255,process_image);  
		process_image(0);
		cvWaitKey();
		cvReleaseImage(&g_pBinaryImage);  
		cvReleaseImage(&g_pGrayImage);  
		cvDestroyWindow("Source");  
		cvDestroyWindow("Result"); 
	}
		pSrcImage = cvLoadImage("coin1.jpg", CV_LOAD_IMAGE_UNCHANGED);// 加载原始图片  
		g_pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  // 转为灰度图  
		cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);  		
		g_pBinaryImage = cvCloneImage(g_pGrayImage);  
		cvNamedWindow("Source",1);  
		cvNamedWindow("Result",1);  
		cvShowImage("Source",pSrcImage);  
		cvCreateTrackbar("Threshold","Result",&slider_pos,255,process_image);  
		process_image(0);
		cvWaitKey();
		cvReleaseImage(&g_pBinaryImage);  
		cvReleaseImage(&g_pGrayImage);  
		cvDestroyWindow("Source");  
		cvDestroyWindow("Result"); 
	return 0;
}
void process_image(int h)
{
	CvMemStorage *stor;  
    CvSeq *cont;  
    CvBox2D32f *box;  
    CvPoint *PointArray;  
    CvPoint2D32f *PointArray2D32f;  
  
    stor = cvCreateMemStorage(0);  
    cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),stor);  
	cvThreshold(g_pGrayImage,g_pBinaryImage,slider_pos,255,CV_THRESH_BINARY);  
  
	cvFindContours(g_pBinaryImage,stor,&cont,sizeof(CvContour),  
		CV_RETR_LIST,CV_CHAIN_APPROX_NONE,cvPoint(0,0));  
	
	cvZero(g_pBinaryImage);  
	cvZero(pSrcImage); 
  
    //绘制所有轮廓并用椭圆拟合  
    for (;cont;cont = cont ->h_next)  
    {  
        int i;  
        int count= cont->total;//轮廓个数  
        CvPoint center;  
        CvSize size;  
  
        
        if (count<6)  
        {  
            continue;  
        }  
      
        //分配内存给点集  
        PointArray = (CvPoint *)malloc(count*sizeof(CvPoint));  
        PointArray2D32f = (CvPoint2D32f*)malloc(count*sizeof(CvPoint2D32f));  
      
        //分配内存给椭圆数据  
        box = (CvBox2D32f *)malloc(sizeof(CvBox2D32f));  
  
        //得到点集  
        cvCvtSeqToArray(cont,PointArray,CV_WHOLE_SEQ);  
      
        //将CvPoint点集转化为CvBox2D32f集合  
        for (i=0;i<count;i++)  
        {  
            PointArray2D32f[i].x=(float)PointArray[i].x;  
            PointArray2D32f[i].y=(float)PointArray[i].y;  
        }  
  
        //拟合当前轮廓  
        cvFitEllipse(PointArray2D32f,count,box);  
  
        //绘制当前轮廓  
		cvDrawContours(pSrcImage,cont,CV_RGB(255,255,255),CV_RGB(255,255,255),  
            0,1,8,cvPoint(0,0));  
  
        //将椭圆数据从浮点转化为整数表示  
        center.x = cvRound(box->center.x);  
        center.y = cvRound(box->center.y);  
        size.width = cvRound(box->size.width*0.5);  
        size.height = cvRound(box->size.height*0.5);  
        box->angle = -box->angle;  
		int a,b,c,d,e;
		a=center.x;
		b=center.y;
		c=size.width;
		d=size.height;
		if(c<d) {e=c;c=d;d=e;}
		printf("圆/椭圆的中心坐标：x=%d, y=%d, 长轴：l=%d, 短轴s=%d \n", a, b, c, d);
        //画椭圆  
		cvEllipse(pSrcImage,center,size,box->angle,0,360,CV_RGB(0,0,255),1,CV_AA,0);  
  
        free(PointArray);  
        free(PointArray2D32f);  
        free(box);  
    }  
	cvShowImage("Result",pSrcImage);  

 
	
}  
