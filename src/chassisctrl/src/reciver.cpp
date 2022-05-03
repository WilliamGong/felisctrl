#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ros/ros.h"

#include "statusinfo.h"

const int BUFFSIZE = 1024;

StatusInfo process(char *buf, int length);

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_reciver");
    ros::NodeHandle n;

    StatusInfo info = {poweroff, 0, neutral, neutral, 0, 0, 0, 0, 0, 0, remote, 0, 0, 0};

    int fd = -1;
    int flagConnect = -1;
    sockaddr_in serverAddr = {
        AF_INET, 
        htons(4001), 
        inet_addr("192.168.1.194"), 
        0
    };
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
        sendto(fd, buf, BUFFSIZE, 0, (sockaddr *)&serverAddr, sizeof(serverAddr));
        recvfrom(fd, buf, BUFFSIZE, 0, (sockaddr *)&serverAddr, sizeof(serverAddr));
    }

    return 0;
}

void process(StatusInfo &info, char *buf, int length) {
    int id = 0;
    for(int i = 0; i < 4; i++) {
        id = id | buf[i];
        id << 8;
    }

    if(id == 0x18F014D1) {

    }else if(id == 0x18F015D1) {

    }else if(id == 0x18F016D1) {

    }
}
