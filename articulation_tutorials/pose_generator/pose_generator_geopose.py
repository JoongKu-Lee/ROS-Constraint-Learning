#!/usr/bin/env python3

import rospy
import pandas as pd
from articulation_msgs.msg import TrackMsg
from geometry_msgs.msg import Pose, PoseStamped

def talker():
    pub = rospy.Publisher('pose',PoseStamped,queue_size=10)
    rate = rospy.Rate(50) #200hz
    while not rospy.is_shutdown():
        pose_msg = PoseStamped()
        pose_msg.header.frame_id = ""
        pose_msg.header.stamp = rospy.Time.now()
        pose = Pose()
        pose.position.x = data.iloc[talker.counter]['x']
        pose.position.y = data.iloc[talker.counter]['y']
        pose.position.z = data.iloc[talker.counter]['z']
        pose.orientation.x = data.iloc[talker.counter]['qx']
        pose.orientation.y = data.iloc[talker.counter]['qy']
        pose.orientation.z = data.iloc[talker.counter]['qz']
        pose.orientation.w = data.iloc[talker.counter]['qw']
        pose_msg.pose = pose;

        pub.publish(pose_msg)

        talker.counter += 1
        rate.sleep()

talker.counter = 0

if __name__=='__main__':
    
    rospy.init_node('pose_generator', anonymous = True)

    csv = pd.read_csv('demo_trajectory_cartesian.csv', \
                        names = ['time', 'x', 'y', 'z', 'qx', 'qy', 'qz', 'qw', 'clutch'])
    data = csv.loc[csv['clutch'] == 1]

    try:
            talker()
    except rospy.ROSInterruptException:
            pass

