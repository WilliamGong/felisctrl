#include "statusinfo.h"
#include "canframe.h"
#include "aux.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "ros/ros.h"

const int BUFFSIZE = 1024;
const uint8_t MASK_H4BIT = htons(0xF0);
const uint8_t MASK_L4BIT = htons(0x0F);

void process(StatusInfo &info, char *buf);

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_reciver");
    ros::NodeHandle n;

    StatusInfo info = {poweroff, 0, 0, neutral, neutral, 0, 0, 0, 0, 0, 0, remote, 0, 0, 0};

    int fd = -1;
    int flagConnect = -1;
    sockaddr_in serverAddr = {
        AF_INET, 
        htons(4001), 
        inet_addr("192.168.1.221"), 
        0
    };
    socklen_t lenAddr = sizeof(sockaddr_in);
    char buf[BUFFSIZE] = {0};

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) {
        ROS_ERROR("Socket creation failed. ");
        return -1;
    }
    flagConnect = connect(fd, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if(flagConnect < 0) {
        ROS_ERROR("Connect failed. ");
    }else {
        ROS_INFO("Connect succeed. ");
    }

    while(ros::ok()) {
        send(fd, buf, BUFFSIZE, 0);
        recv(fd, buf, BUFFSIZE, 0);
        process(info, buf);
        /*
        ROS_INFO("Current mode: %d, Fault code: %d, Remote gear: %d, Real time gear: %d, Angle: %d, pressure: %d, Brake: %d, Switch: %d, emergency: %d, Remote status: %d", 
                info.currentMode, info.fault, info.remote, info.realtime, 
                info.angle, info.pressure, info.brake, info.remoteMode, info.emergencyStatus, info.remoteStatus);
        */
    }

    return 0;
}

void process(StatusInfo &info, char *buf) {
    int lenFrame = sizeof(buf) / 13;
    for(int i = 0; i < lenFrame; i++) {
        char tmp[13];
        memcpy(tmp, buf+i*13, 13);
        CanFrame frame = CanFrame(tmp);
        char id[4], data[8];
        frame.getId(id);
        frame.getData(data);
        ROS_INFO("Frame ID: %x, Data: %x",  charToUInt(id), charToUInt(data));
    }
}
