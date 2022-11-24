#include "motionctrl.h"
#include "canframe.h"
#include "aux.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "ros/ros.h"

const int BUFFSIZE = 13;
const uint8_t MASK_H4BIT = htons(0xF0);
const uint8_t MASK_L4BIT = htons(0x0F);

void writeData(unsigned char* sendbuf);

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_sender");
    ros::NodeHandle n;

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
        /*
        ROS_INFO("Current mode: %d, Fault code: %d, Remote gear: %d, Real time gear: %d, Angle: %d, pressure: %d, Brake: %d, Switch: %d, emergency: %d, Remote status: %d", 
                info.currentMode, info.fault, info.remote, info.realtime, 
                info.angle, info.pressure, info.brake, info.remoteMode, info.emergencyStatus, info.remoteStatus);
        */
       writeData(sendbuf);
       ROS_INFO("frame: %llx", charToULL(sendbuf, 8));
       write(fd, sendbuf, BUFFSIZE);
    }

    return 0;
}

void writeData(unsigned char* sendbuf) {
    MotionCtrl motion = MotionCtrl();
    unsigned char data[8] = {0};
    CanFrame frame = CanFrame();

    unsigned char write_id[4];
    write_id[0] = 0x0c;
    write_id[1] = 0x08;
    write_id[2] = 0xd1;
    write_id[3] = 0xd0;

    motion.setCtrlMode(WIRE_);
    motion.setAngle(0);
    if(!motion.getData(data)) {
        ROS_ERROR("Error: motion control data set failed. ");
    }

    if(!frame.setId(write_id)) {
        ROS_ERROR("ID set failed. ");
    }

    if(!frame.setData(data)) {
        ROS_ERROR("Data set failed. ");
    }

    //ROS_INFO("len of sendbuf: %d", sizeof(sendbuf));
    if(!frame.getFrame(sendbuf, BUFFSIZE)) {
        ROS_ERROR("write buffer set failed. ");
    }
}