/*
 * model_fitting_demo.cpp
 *
 *  Created on: Jun 8, 2010
 *      Author: sturm
 */

#include <ros/ros.h>

#include "articulation_models/models/factory.h"

#include "articulation_msgs/ModelMsg.h"
#include "articulation_msgs/TrackMsg.h"
#include "articulation_msgs/ParamMsg.h"

#include "geometry_msgs/PoseArray.h"

using namespace std;
using namespace articulation_models;
using namespace articulation_msgs;

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>

#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"

class ModelFitting
{
public:
    ros::Publisher model_pub;
    ros::Publisher pose_pub;
    ros::Subscriber pose_sub;

    geometry_msgs::PoseStamped ps;
    ModelMsg model_msg;

    MultiModelFactory factory;

    void poseCallback(const geometry_msgs::PoseStampedPtr &p)
    {
        geometry_msgs::PoseStamped temp = *p;
        ps.header = temp.header;
        ps.pose = temp.pose;
        model_msg.track.pose.push_back(ps.pose);


        static geometry_msgs::PoseArray posearray;
        posearray.header.frame_id = "map";
        posearray.header.stamp = ros::Time::now();
        posearray.poses.push_back(ps.pose);
        pose_pub.publish(posearray);
        
        if(model_msg.track.pose.size()<3) return;

        cout <<"creating object"<<endl;
        GenericModelPtr model_instance = factory.restoreModel(model_msg);
        cout <<"fitting"<<endl;
        model_instance->fitModel();
        cout <<"evaluating"<<endl;
        model_instance->evaluateModel();
        cout <<"done"<<endl;

        cout << "model class = "<< model_instance->getModelName() << endl;
        cout << "	radius = "<<model_instance->getParam("rot_radius")<< endl;
        cout << "	center.x = "<<model_instance->getParam("rot_center.x")<< endl;
        cout << "	center.y = "<<model_instance->getParam("rot_center.y")<< endl;
        cout << "	center.z = "<<model_instance->getParam("rot_center.z")<< endl;
        cout << "	log LH = " << model_instance->getParam("loglikelihood")<< endl;

        ModelMsg fitted_model_msg= model_instance->getModel();
        model_pub.publish(fitted_model_msg);
    }

    int init()
    {
        ros::NodeHandle n;
        model_pub = n.advertise<ModelMsg> ("model", 5);
        pose_pub = n.advertise<geometry_msgs::PoseArray> ("given", 5);
        pose_sub = n.subscribe("pose", 5, &ModelFitting::poseCallback, this);

        model_msg.name = "rotational"; // ONLY FINDS ROTATION!
        ParamMsg sigma_param;
        sigma_param.name = "sigma_position";
        sigma_param.value = 0.02;
        sigma_param.type = ParamMsg::PRIOR;
        sigma_param.name = "sigma_orientation";
        sigma_param.value = M_PI*10; // 10 * PI --> IGNORE ORIENTATION! 
        sigma_param.type = ParamMsg::PRIOR;
        model_msg.params.push_back(sigma_param);

        return 0;
    }
};




int main(int argc, char** argv) {
	ros::init(argc, argv, "model_fitting");

    ModelFitting mf;
    if (mf.init())
    {
        ROS_FATAL("ModelFitting initialization failed");
		return -1;
    }

    ros::spin();
}
