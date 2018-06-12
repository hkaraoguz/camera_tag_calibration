/*
 * tf_publisher.cpp
 *
 *  Created on: December 18, 2016
 *      Author: Silvia Cruciani
*/

#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <ros/package.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]){
	//this node publishes the transformation read from a file in tf
	ros::init(argc, argv, "tf_publisher");	
	ros::NodeHandle n("~");

	std::string base_frame, end_frame, file;
	//read names of base frame and end frame from parameters
	n.param<std::string>("base_frame", base_frame, "world");
	n.param<std::string>("end_frame", end_frame, "world_tag");
	n.param<std::string>("file_name", file, "/config/robot_calib.txt");

	ROS_INFO("publishing transform between %s and %s", base_frame.c_str(), end_frame.c_str());

	std::string path=ros::package::getPath("camera_tag_calibration");

	//read the transformation from file, in the format x y z qx qy qz qw
	std::string s, filename;
	filename=path+file;
	std::ifstream f;
	f.open(filename.c_str());

	std::getline(f, s);
	std::istringstream iss(s);

	double tx, ty, tz, qx, qy, qz, qw;
	iss>>tx;
	iss>>ty;
	iss>>tz;
	iss>>qx;
	iss>>qy;
	iss>>qz;
	iss>>qw;
	f.close();

	//create the transform and publish (add fixed rate as parameter?)
	tf::Quaternion q(qx, qy, qz, qw);
	tf::Vector3 v(tx, ty, tz);	
	tf::Transform transform(q, v);
	tf::TransformBroadcaster br;
	ros::Rate r(100.0);
	while(ros::ok()){
		br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), base_frame, end_frame));
		r.sleep();
	}

	return 0;
}
