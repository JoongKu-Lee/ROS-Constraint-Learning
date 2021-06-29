#!/usr/bin/env python3

import rospy
import pandas as pd
from articulation_msgs.msg import TrackMsg
from geometry_msgs.msg import Pose

def talker():
    pub = rospy.Publisher('track',TrackMsg,queue_size=10)
    rate = rospy.Rate(1) # LOOP RATE
    while not rospy.is_shutdown():
        track_msg.header.frame_id = ""
        track_msg.header.stamp = rospy.Time.now()
        pose = Pose()
        pose.position.x = data.iloc[talker.counter]['x']
        pose.position.y = data.iloc[talker.counter]['y']
        pose.position.z = data.iloc[talker.counter]['z']
        pose.orientation.x = data.iloc[talker.counter]['qx']
        pose.orientation.y = data.iloc[talker.counter]['qy']
        pose.orientation.z = data.iloc[talker.counter]['qz']
        pose.orientation.w = data.iloc[talker.counter]['qw']
        track_msg.pose.append(pose)
        
        print(track_msg)

        pub.publish(track_msg)

        talker.counter += 1
        rate.sleep()

talker.counter = 0

if __name__=='__main__':
    
    rospy.init_node('pose_generator', anonymous = True)

    track_msg = TrackMsg()

#     csv = pd.read_csv('demo_trajectory_cartesian.csv', \
#                         names = ['time', 'x', 'y', 'z', 'qx', 'qy', 'qz', 'qw', 'clutch'])
    csv = pd.read_csv('stationary_rotational_demo.csv', \
                        names = ['time', 'x', 'y', 'z', 'qx', 'qy', 'qz', 'qw', 'clutch'])
    data = csv.loc[csv['clutch'] == 1]

    try:
            talker()
    except rospy.ROSInterruptException:
            pass

