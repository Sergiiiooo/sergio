#include "ros/ros.h"
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>

tf::Transform transform;
tf::Quaternion q;

void pose_callback(const geometry_msgs::Point::ConstPtr& pose)
{
   static tf::TransformBroadcaster br;
   q.setRPY(0,0,pose->z);
   transform.setOrigin(tf::Vector3(pose->x, pose->y, 0.0));
   transform.setRotation(q);

   br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "driver");
   ros::NodeHandle n("~");
   ros::Subscriber pose_sub = n.subscribe("/hulk_node/odometria", 1, pose_callback);
   ros::Rate loop_rate(100);
   while (ros::ok())
   {
      ros::spinOnce();
      loop_rate.sleep();
   }
}