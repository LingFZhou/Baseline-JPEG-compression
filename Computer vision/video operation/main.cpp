#include <stdlib.h>  
#include <stdio.h>  
#include <math.h>  
#include <cv.h>  
#include <opencv2/opencv.hpp>  
#include <highgui.h>  
using namespace std; 


  
int main( int argc, char* argv[] )  
{	
	IplImage *pSrcImage;
	IplImage *g_pGrayImage = NULL;  
	IplImage *g_pBinaryImage = NULL;  
	CvCapture* capture = cvCreateFileCapture(argv[1]);
	cvQueryFrame(capture);
	int p=atoi(argv[2]);
    cvNamedWindow( "mainWin", CV_WINDOW_AUTOSIZE );
	CvVideoWriter *writer = 0; 
	int isColor = 0;  
	int fps     = 15; 
	int frameW = 640;    
	int frameH = 480; 
	writer=cvCreateVideoWriter(argv[3],CV_FOURCC('M','J','P','G'),fps,cvSize(frameW,frameH),isColor);
	CvFont font;
	double hScale=1.0;
	double vScale=1.0;
	int lineWidth=8;
	int i=0;
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, hScale,vScale,0,lineWidth);
	while(i<180) 
	{
		 
		pSrcImage = cvQueryFrame(capture); //获取一帧图片 
		if(!pSrcImage)break;
		g_pGrayImage =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  // 转为灰度图  
		cvCvtColor(pSrcImage, g_pGrayImage, CV_BGR2GRAY);  		
		g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);    // 创建二值图    
		cvThreshold(g_pGrayImage, g_pBinaryImage, p, 255, CV_THRESH_BINARY);   // 转为二值图 
		cvPutText (g_pBinaryImage,"LYNN_3110101010",cvPoint(320,50), &font,cvScalar(255,255,0));
		
		cvShowImage("mainWin", g_pBinaryImage);
		
		cvWaitKey(20); 
		cvWriteFrame(writer,  g_pBinaryImage); 
		  
	}  
		cvReleaseVideoWriter(&writer); 
		cvReleaseCapture(&capture);  	 
		cvDestroyWindow("mainWin");
    return 0;  
}  