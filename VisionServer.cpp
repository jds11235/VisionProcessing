#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdint.h>
#include "VisionSettings.h"
#include "FisheyeCalib.h"
#include <networktables/NetworkTable.h>

#define SIDES		8
#define CONCAVITY	true
#define IP_ADDRESS	("roboRIO-" TEAM_NUMBER "-FRC.local")
#define TEAM_NUMBER	"1234"

std::shared_ptr<NetworkTable> table;

using namespace cv; using namespace std; class VisionServer {
        public:
                static int ProcessFrame(Mat frame);
};
int main() {
	//setup the network tables
	NetworkTable::SetClientMode();
	NetworkTable::SetIPAddress(IP_ADDRESS);
	table = NetworkTable::GetTable("vision");
        //open the video capture
        VideoCapture cap = VideoCapture(0);
        //check to make sure the capture was successful
	float i = 0;
	float s = 0;
       	if(cap.isOpened()) {
		std::cout << "Found Camera" << std::endl;
		while (cap.isOpened()) {
			Mat frame;
			//read in the current camera picture
                	cap.read(frame);
                	if (frame.empty()) {
                	        return -1;
                	}
			Mat temp = frame.clone();
			undistort(temp,frame,CAMERA_MATRIX,DIST_COEFS);
			// Process the frame
			VisionServer::ProcessFrame(frame);
		}
        } else {
                printf("Error Openning Camera");
                return -1;
        }
        return 0;
}
int VisionServer::ProcessFrame(Mat bgrframe) {
        //create a mat to hold the frame in hsv
	Mat hsvframe;
	//create a mat to hold the thresholded frame
	Mat filteredframe;
	//create a mat to hold the image with circles around the contours found
	//Mat contourimg;
	//create a holder for the contours
        vector< vector<Point > > contours;
	//create a holder for the final contour
        vector<Point > outputcontour;
	// blur the original frame
	GaussianBlur(bgrframe, bgrframe, Size(5 , 5), 0, 0 );
        //create the hsv frame
	cvtColor(bgrframe,hsvframe,COLOR_BGR2HSV,3);
	//perform the process on the hsv frame
	//imwrite("unfiltered.jpg",bgrframe);
	// threshold the image
	inRange(hsvframe,cv::Scalar(THRESH[0],THRESH[2],THRESH[4]),cv::Scalar(THRESH[1],THRESH[3],THRESH[5]),filteredframe);
        //write out the thresholded image
	//imwrite("filteredimg.jpg",filteredframe);
	// Find contours
        findContours(filteredframe, contours, CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
	//contourimg = Mat::zeros(filteredframe.size(), CV_8UC3);
        //filter out all convex contours and contours with not enough area
        int currentcontour = 0;
        int lastarea = 0;
	//loop through all the contours
        for (int i = 0; i < contours.size(); i++) {
		//find the current contour's angle
                int area = contourArea(contours[i],false);
		//create a point for the bounding circle's radius and a float for it's center
		//Point2f center;
		//float radius;
		//check to make sure the contour is concave
                if(area > 200 && area>lastarea && (CONCAVITY == isContourConvex(contours[i]))) {
			// create a polygon holder so we can get some data on the shape
                        vector<Point > poly;
			//create a polygon approximation of the shape
			approxPolyDP(Mat(contours[i]),poly,arcLength(contours[i],true)*0.015,true);
			//create a circle that encloses the whole target
           		//minEnclosingCircle((Mat)poly, center, radius);
			//create the color white
                        //Scalar color = Scalar(255,255,255);
			//if the polygon had the right ammount of sides
			if(poly.size()==SIDES){
				//create a white circle where the object was on the original image
				//circle(contourimg,center,(int)radius,color,2,8,0);
				//store contour data
				lastarea = area;
				outputcontour = contours[i];
                        }
                }
        }
	//set the contour image to be the bitwise xor of the origional image and the circled image to combine them
	//bitwise_xor(contourimg,bgrframe,contourimg);
	//if a contour was found
	if(outputcontour.size()!=0) {
		//calculate the position data of the contour
		Moments M = moments(outputcontour,false);
		//display its location
		//std::cout << "Found contour at " << (M.m10/M.m00) << std::endl;
		//write out the image with the contour circled
		//imwrite("contours.jpg",contourimg);
    		//return the x position of the contour
		table->PutNumber("xpos",M.m10/M.m00);
		table->PutNumber("ypos",M.m01/M.m00);
		table->PutNumber("area",M.m00);
	} else {
		table->PutNumber("xpos",-1);
		table->PutNumber("ypos",-1);
		table->PutNumber("area",-1);
	}
}
