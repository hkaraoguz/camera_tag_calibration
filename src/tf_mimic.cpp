/*
 * tf_publisher.cpp
 *
 *  Created on: December 18, 2016
 *      Author: Silvia Cruciani
*/

#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <ros/package.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]){
	//this node publishes the transformation read from a file in tf
	ros::init(argc, argv, "tf_publisher");	
	ros::NodeHandle n("~");

	std::string base_frame, end_frame, detected_frame;
	//read names of base frame and end frame from parameters
	n.param<std::string>("base_frame", base_frame, "world_tag");
	n.param<std::string>("end_frame", end_frame, "kinect2_link");
	n.param<std::string>("detected_frame", detected_frame, "world_tag2");

	ROS_INFO("publishing transform between %s and %s", base_frame.c_str(), end_frame.c_str());

	std::string path=ros::package::getPath("camera_tag_calibration");

	tf::TransformBroadcaster br;
	tf::TransformListener listener;
	ros::Rate r(100.0);

	//read the transformation 
	tf::StampedTransform transform;
    try{
    	listener.waitForTransform(detected_frame, end_frame, ros::Time::now(), ros::Duration(3.0));
		listener.lookupTransform(detected_frame, end_frame, ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
    	ROS_ERROR("%s",ex.what());
    	ros::Duration(1.0).sleep();
    }
	

	tf::StampedTransform transform_bk;
	
	
	while(ros::ok()){
		tf::StampedTransform transform;
	    try{
			listener.lookupTransform(detected_frame, end_frame, ros::Time(0), transform);
	    }
	    catch (tf::TransformException ex){
	    	ROS_ERROR("%s",ex.what());
	    	ros::Duration(1.0).sleep();
	    	transform = transform_bk;
	    }
	    transform_bk = transform;
		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), base_frame, end_frame));
		r.sleep();
	}

	return 0;
}
