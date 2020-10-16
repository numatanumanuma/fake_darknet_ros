#ifndef FAKE_DARKNET_ROS_H
#define FAKE_DARKNET_ROS_H

#include "ros/ros.h"                        
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "kbhit.h"

#include <vector>

class fakeObjectDetector{
    public:
        fakeObjectDetector();
        ~fakeObjectDetector();
        void publishResult();

    private:
        ros::Publisher yolo_pub_;
        ros::Timer timer_;

        void timerCallback(const ros::TimerEvent&);
        bool setResult(std::string filename);

        std::vector<darknet_ros_msgs::BoundingBoxes> results_;
        std::string filename_;
        char key_;

};

#endif
