/* 
 * Struck: Structured Output Tracking with Kernels
 * 
 * Code to accompany the paper:
 *   Struck: Structured Output Tracking with Kernels
 *   Sam Hare, Amir Saffari, Philip H. S. Torr
 *   International Conference on Computer Vision (ICCV), 2011
 * 
 * Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK
 * 
 * This file is part of Struck.
 * 
 * Struck is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Struck is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Struck.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
 
#include "Tracker.h"
#include "Config.h"

#include <iostream>
#include <fstream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "vot.h"

using namespace std;
using namespace cv;

static const int kLiveBoxWidth = 80;
static const int kLiveBoxHeight = 80;

void rectangle(Mat& rMat, const FloatRect& rRect, const Scalar& rColour)
{
	IntRect r(rRect);
	rectangle(rMat, Point(r.XMin(), r.YMin()), Point(r.XMax(), r.YMax()), rColour);
}

int main(int argc, char* argv[])
{
	// read config file
   string configPath = "/home/fanxiang/trackers/VOT/vot-workspaceCplus/Struck2/config.txt";
   Config conf(configPath);
   
   //vot must be first decalared
    VOT vot;
    
   //load region, images and prepare for output
    Mat frameOrig;
    Mat frame;
    frameOrig = cv::imread(vot.frame());
    conf.frameWidth = frameOrig.cols;
    conf.frameHeight = frameOrig.rows;
    resize(frameOrig, frame, Size(conf.frameWidth, conf.frameHeight));
    
    //using config things and init after set the config
    Tracker tracker(conf);
   
    
    cv::Rect initPos;
    initPos << vot.region();
    
    float scaleW = (float)conf.frameWidth/frameOrig.cols;
    float scaleH = (float)conf.frameHeight/frameOrig.rows;
    
    FloatRect initBB_vot = FloatRect(initPos.x*scaleW, initPos.y*scaleH, initPos.width*scaleW, initPos.height*scaleH);
    tracker.Initialise(frame, initBB_vot);
    
    while (!vot.end())
    {    
        //standard process
        
        string imagepath = vot.frame();

        if (imagepath.empty()) break;

        cv::Mat frameOrig = cv::imread(imagepath); 
        conf.frameWidth = frameOrig.cols;
        conf.frameHeight = frameOrig.rows;
        resize(frameOrig, frame, Size(conf.frameWidth, conf.frameHeight));       
        tracker.Track(frame);
        
        const FloatRect& bb = tracker.GetBB();
        float x = bb.XMin()/scaleW;
        float y = bb.YMin()/scaleH;
        float w = bb.Width()/scaleW;
        float h = bb.Height()/scaleH;
        
        cv::Rect rect = cv::Rect(x,y,w,h);
        vot.report(rect);
    }
    
    return 0;
	
	
}
