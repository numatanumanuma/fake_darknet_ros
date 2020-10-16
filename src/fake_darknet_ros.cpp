#include "fake_darknet_ros/fake_darknet_ros.h"
#include <sstream>
#include <fstream>
#include <cctype>

fakeObjectDetector::fakeObjectDetector(){
    ros::NodeHandle nh("~");
    yolo_pub_ = nh.advertise<darknet_ros_msgs::BoundingBoxes>("darknet_ros/bounding_boxes", 100);
    nh.param("filename", filename_, std::string("./ros/yolo_result.txt"));
    // ちょいまつ
    ros::Rate r(1);
    r.sleep();
    setResult(filename_);
}

fakeObjectDetector::~fakeObjectDetector(){
    
}

void fakeObjectDetector::timerCallback(const ros::TimerEvent&){
   
}

bool fakeObjectDetector::setResult(std::string filename){
    results_.clear();

    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs){
        ROS_INFO("cannot open result file");
        return false;
    }

    std::string str;
    std::vector<std::string> line;
    darknet_ros_msgs::BoundingBoxes boundingboxes;
    while (getline(ifs, str)) {
        line.clear();
        std::stringstream ss(str);
        while (getline(ss, str, ',')){
            line.push_back(str);
        }
        if (line[0] != "---"){
            darknet_ros_msgs::BoundingBox boundingbox;
            boundingbox.Class = line[0];
            boundingbox.probability = stof(line[1]);
            boundingboxes.bounding_boxes.push_back(boundingbox);
        } else {
            results_.push_back(boundingboxes);
            boundingboxes.bounding_boxes.clear();
        }
    }
    ROS_INFO("set result");
    return true;
}

void fakeObjectDetector::publishResult() {
    if (kbhit()) {
        std::cin >> key_;
    }
    if (!std::isdigit(static_cast<unsigned char>(key_)))
        return;
    int num = key_ - '0' - 1;
    if (num >= results_.size())
        return;
    yolo_pub_.publish(results_[num]);
    ROS_INFO("publish results");
}

int main(int argc, char **argv){
    ros::init(argc, argv, "fake_darknet_ros");

    fakeObjectDetector fakeObjectDetector;

    ros::Rate loop_rate(1);

    while(ros::ok()) {
        fakeObjectDetector.publishResult();

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
