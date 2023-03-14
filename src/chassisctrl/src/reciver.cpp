#include "canframe.h"
#include "aux.h"
#include "chassisctrl/frame.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "ros/ros.h"

const int BUFFSIZE = 13;
const uint8_t MASK_H4BIT = htons(0xF0);
const uint8_t MASK_L4BIT = htons(0x0F);

void process(unsigned char *buf, ros::Publisher pub);

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_reciver");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<chassisctrl::frame>("frame_info", 1);

    int fd = -1;
    int flag_connect = -1;
    sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4001);
    server_addr.sin_addr.s_addr = inet_addr("10.168.1.178");
    
    socklen_t len_addr = sizeof(sockaddr_in);
    unsigned char recvbuf[BUFFSIZE] = {0};
    unsigned char sendbuf[BUFFSIZE] = {0};

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {
        ROS_ERROR("Socket creation failed. ");
        return -1;
    }
    flag_connect = connect(fd, (sockaddr *)&server_addr, sizeof(server_addr));
    if(flag_connect < 0) {
        ROS_ERROR("Connect failed. ");
        return -1;
    }else {
        ROS_INFO("Connect succeed. ");
    }

    while(ros::ok()) {
        read(fd, recvbuf, BUFFSIZE);
        //ROS_INFO("buf: %llx: ", charToULL(recvbuf, 8));
        process(recvbuf, pub);
        /*
        ROS_INFO("Current mode: %d, Fault code: %d, Remote gear: %d, Real time gear: %d, Angle: %d, pressure: %d, Brake: %d, Switch: %d, emergency: %d, Remote status: %d", 
                info.currentMode, info.fault, info.remote, info.realtime, 
                info.angle, info.pressure, info.brake, info.remoteMode, info.emergencyStatus, info.remoteStatus);
        */
       ros::spinOnce();
    }

    return 0;
}

void process(unsigned char *buf, ros::Publisher pub) {

    chassisctrl::frame frame_info;
    unsigned char tmp[13];
    memcpy(tmp, buf, 13);
    CanFrame frame = CanFrame(tmp);
    unsigned char id[4], data[8];

    frame.getId(id);
    frame.getData(data);
    frame_info.id = charToUInt(id, 4);
    frame_info.data = charToULL(data, 8);

    //ROS_INFO("Frame ID: %x, Data: %llx",  charToUInt(id, 4), charToULL(data, 8));
    pub.publish(frame_info);
    
}
