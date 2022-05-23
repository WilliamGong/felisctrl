#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ros/ros.h"

#include "statusinfo.h"

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
        inet_addr("192.168.1.194"), 
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
        sendto(fd, buf, BUFFSIZE, 0, (sockaddr *)&serverAddr, lenAddr);
        recvfrom(fd, buf, BUFFSIZE, 0, (sockaddr *)&serverAddr, &lenAddr);
        process(info, buf);
        ROS_INFO("Current mode: %d, Fault code: %d, Remote gear: %d, Real time gear: %d, Angle: %d, pressure: %d, Brake: %d, Switch: %d, emergency: %d, Remote status: %d", 
                info.currentMode, info.fault, info.remote, info.realtime, 
                info.angle, info.pressure, info.brake, info.remoteMode, info.emergencyStatus, info.remoteStatus);
    }

    return 0;
}

void process(StatusInfo &info, char *buf) {
    int id = 0;
    for(int i = 0; i < 4; i++) {
        id = id | buf[i];
        id << 8;
    }

    if(id == htonl(0x18F014D1)) {
        info.currentMode = (Mode)ntohs(buf[4]);
        info.fault = ntohs(((unsigned short)buf[6] << 8) | (unsigned short)buf[7]);
        info.countStatus1 = ntohs((buf[11] & MASK_H4BIT) >> 4);

    }else if(id == htonl(0x18F015D1)) {
        info.remote = (Gear)ntohs(buf[4] & MASK_L4BIT);
        info.realtime = (Gear)ntohs((buf[4] & MASK_H4BIT) >> 4);
        info.remoteAccelerator = ntohs(buf[5]);
        info.realtimeAccelerator = ntohs(buf[6]);
        info.angle = ntohs(((unsigned short)buf[7] << 8) | (unsigned short)buf[8]);
        info.countStatus2 = ntohs((buf[11] & MASK_H4BIT) >> 4);

    }else if(id == htonl(0x18F016D1)) {
        info.pressure = ntohs(buf[5]);
        info.brake = ntohs((buf[6] & MASK_H4BIT) >> 4);
        info.remoteMode = (GearSwitch)ntohs((buf[9] & htons(0x0C)) >> 2);
        info.emergencyStatus = ntohs((buf[9] & htons(0xC0)) >> 6);
        info.remoteStatus = ntohs(buf[11] & MASK_L4BIT);
        info.countStatus3 = ntohs((buf[11] & MASK_H4BIT) >> 4);

    }
}
