// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <queue>
#include <string>
#include <iostream>
#include <fstream>


std::vector<Point> rect;

void MyCallBackFuncRedEye(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Point p = Point(x,y);
		if (rect.size() < 4) rect.push_back(p);
		printf("The content of rectangle is : ");
		for (int i = 0; i < rect.size();i++) {
			printf("%d %d\n", rect.at(i).x, rect.at(i).y);
		}

		if (rect.size() == 4) {

				int x1 = rect.at(0).x;
				int y1 = rect.at(0).y;
				
				int x2 = rect.at(1).x;
				int y2 = rect.at(1).y;

				int x3 = rect.at(2).x;
				int y3 = rect.at(2).y;

				int x4 = rect.at(3).x;
				int y4 = rect.at(3).y;

				rect.clear();
				Mat res = (*src).clone();
				for (int i = y1; i <= y2; i++) {
					for (int j = x1; j <= x2; j++) {
						float redIntensity = (float)res.at<Vec3b>(i, j)[2] / ((res.at<Vec3b>(i, j)[0] + res.at<Vec3b>(i, j)[1]) / 2);
						if (redIntensity > 1.5) {
							res.at<Vec3b>(i, j)[2] = (res.at<Vec3b>(i, j)[1] + res.at<Vec3b>(i, j)[0]) / 2;
						}
					}
				}

				for (int i = y3; i <= y4; i++) {
					for (int j = x3; j <= x4; j++) {
						float redIntensity = (float)res.at<Vec3b>(i, j)[2] / (res.at<Vec3b>(i, j)[0] + res.at<Vec3b>(i, j)[1] / 2);
						if (redIntensity > 1.5) {
							res.at<Vec3b>(i, j)[2] = (res.at<Vec3b>(i, j)[1] + res.at<Vec3b>(i, j)[0]) / 2;
						}
					}
				}

				imshow("Transformed image", res);
			}
		}
	}

void MyCallBackFuncRedEye2(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Point p = Point(x, y);
		if (rect.size() < 2) rect.push_back(p);
		printf("The content of rectangle is : ");
		for (int i = 0; i < rect.size(); i++) {
			printf("%d %d\n", rect.at(i).x, rect.at(i).y);
		}

		if (rect.size() == 2) {
			
			std::queue<Point2d> queue;
			queue.push(Point2d(rect.at(0).x,rect.at(0).y));
			
			Mat res = (*src).clone();

			int R = (*src).at<Vec3b>(rect.at(0).y, rect.at(0).x)[2];
			int G = (*src).at<Vec3b>(rect.at(0).y, rect.at(0).x)[1];
			int B = (*src).at<Vec3b>(rect.at(0).y, rect.at(0).x)[0];
			
			int dx[] = {-1, 0, 1,-1,1,-1,0,1};
			int dy[] = {-1,-1,-1, 0,0, 1,1,1};

			while (!queue.empty()) {
				
				Point2d point = queue.front();
				res.at<Vec3b>(point.y, point.x)[2] = 0;
				queue.pop();

				for (int i = 0; i < 8; i++) {
					float redIntensity = (float)res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[2] / ((res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[0] + res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[1]) / 2);
					if (redIntensity > 2) {

						queue.push(Point2d(point.x+dx[i],point.y+dy[i]));
					}
				}
			}

			queue.push(Point2d(rect.at(1).x, rect.at(1).y));
			while (!queue.empty()) {

				Point2d point = queue.front();
				res.at<Vec3b>(point.y, point.x)[2] = 0;
				queue.pop();

				for (int i = 0; i < 8; i++) {
					float redIntensity = (float)res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[2] / ((res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[0] + res.at<Vec3b>(point.y + dy[i], point.x + dx[i])[1]) / 2);
					if (redIntensity > 2) {

						queue.push(Point2d(point.x + dx[i], point.y + dy[i]));
					}
				}
			}
			rect.clear();

			imshow("Transformed image", res);
		}
	}
}

void MyCallBackFuncRedEye3(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Point p = Point(x, y);
		if (rect.size() < 4) rect.push_back(p);
		printf("The content of rectangle is : ");
		for (int i = 0; i < rect.size(); i++) {
			printf("%d %d\n", rect.at(i).x, rect.at(i).y);
		}

		if (rect.size() == 4) {


			Mat res = (*src).clone();	
			
			float r1 = sqrt((rect.at(1).x - rect.at(0).x)*(rect.at(1).x - rect.at(0).x)+ (rect.at(1).y - rect.at(0).y)*(rect.at(1).y - rect.at(0).y));
			int Xmin1 = rect.at(0).x - rect.at(1).x;
			int Xmax1 = rect.at(0).x + rect.at(1).x;
			int Ymin1 = rect.at(0).y - rect.at(1).y;
			int Ymax1 = rect.at(0).y + rect.at(1).y;
			
			for (int i = Ymin1; i < Ymax1;i++) {
				for (int j = Xmin1; j < Xmax1; j++) {
					float rp = sqrt((j -rect.at(0).x)*(j - rect.at(0).x) + (i - rect.at(0).y)*(i - rect.at(0).y));
					if (rp < r1) {
						res.at<Vec3b>(i,j)[2] = (res.at<Vec3b>(i,j)[0] + res.at<Vec3b>(i,j)[1])/2;
					}
				}

			}

			float r2 = sqrt((rect.at(3).x - rect.at(2).x)*(rect.at(3).x - rect.at(2).x) + (rect.at(3).y - rect.at(2).y)*(rect.at(3).y - rect.at(2).y));
			int Xmin2 = rect.at(2).x - rect.at(3).x;
			int Xmax2 = rect.at(2).x + rect.at(3).x;
			int Ymin2 = rect.at(2).y - rect.at(3).y;
			int Ymax2 = rect.at(2).y + rect.at(3).y;

			for (int i = Ymin2; i < Ymax2; i++) {
				for (int j = Xmin2; j < Xmax2; j++) {
					float rp = sqrt((j - rect.at(2).x)*(j - rect.at(2).x) + (i - rect.at(2).y)*(i - rect.at(2).y));
					if (rp < r1) {
						res.at<Vec3b>(i, j)[2] = (res.at<Vec3b>(i, j)[0] + res.at<Vec3b>(i, j)[1]) / 2;
					}
				}

			}
			rect.clear();
			imshow("Transformed image", res);
		}
	}
}

void redEye()
{
	Mat src;
	rect.clear();
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname);
		//Create a window
		namedWindow("My Window", 1);

		//set the callback function for any mouse event
		setMouseCallback("My Window", MyCallBackFuncRedEye2, &src);
		if (rect.size() == 2) {
			destroyAllWindows();
			break;
		}
		//show the image
		imshow("My Window", src);
		// Wait until user press some key
		waitKey(0);
		
	}

	
}



int main()
{
	int op;
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 42 - Red eye removal\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d",&op);
		
		switch (op)
		{
		
			case 42:
				redEye();
				break;
		}

	}
	while (op!=0);
	return 0;
}