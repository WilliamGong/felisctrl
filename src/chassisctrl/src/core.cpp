/**
 * @file core.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * Core node of chassisctrl. 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ctrl.h"
#include "info.h"
#include "aux.h"
#include "chassisctrl/frame.h"
#include "chassisctrl/carctrl.h"

#include "ros/ros.h"
#include <cstdio>

const unsigned int INFO_ID_STATUS_1 = 0x18f014d1;
const unsigned int INFO_ID_STATUS_2 = 0x18f015d1;
const unsigned int INFO_ID_STATUS_3 = 0x18f016d1;
const unsigned int INFO_ID_MILEAGE = 0x18f01ad1;
const unsigned int INFO_ID_WHEELSPEED = 0x18f01bd1;
const unsigned int INFO_ID_BATTERY_1 = 0x18f020d1;
const unsigned int INFO_ID_BATTERY_2 = 0x18f021d1;
const unsigned int INFO_ID_DRIVE = 0x18f026d1;

void infoCallBack(const chassisctrl::frame::ConstPtr& msg);
void carCtrlCallBack(const chassisctrl::carctrl::ConstPtr& msg);

unsigned char id[4] = {0};
unsigned char data[8] = {0};

ros::Publisher pub_ctrl;
ros::Subscriber sub_info;
ros::Subscriber sub_carctrl;

StatusInfo status_info;
MileageInfo milage_info;
WheelSpeedInfo wheel_speed_info;
BatteryInfo battery_info;
DriveInfo drive_info;

MotionCtrl motion;

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_core");
    ros::NodeHandle n;

    pub_ctrl = n.advertise<chassisctrl::frame>("frame_ctrl", 1);
    sub_info = n.subscribe<chassisctrl::frame>("frame_info", 1, infoCallBack);
    sub_carctrl = n.subscribe<chassisctrl::carctrl>("teleop", 100, carCtrlCallBack);

    status_info = StatusInfo();
    milage_info = MileageInfo();
    wheel_speed_info = WheelSpeedInfo();
    battery_info = BatteryInfo();
    drive_info = DriveInfo();

    motion = MotionCtrl();

    motion.getId(id);
    motion.setCtrlMode(WIRE_);
    motion.setGear(FORWARD);

    ROS_INFO("Init completed. ");

    while(ros::ok()) {
        ros::spinOnce();
    }
    return 0;
}

void infoCallBack(const chassisctrl::frame::ConstPtr& msg) {
    unsigned int id = msg->id;
    unsigned char data[8];
    ullToChar(msg->data, data, 8);

    //ROS_INFO("id: %x, data: %llx", msg->id, msg->data);

    if(id == INFO_ID_STATUS_1 || id == INFO_ID_STATUS_2 || id == INFO_ID_STATUS_3) {
        status_info.setData(id, data);
    }else if(id == INFO_ID_MILEAGE) {
        milage_info.setData(id, data);
    }else if(id == INFO_ID_WHEELSPEED) {
        wheel_speed_info.setData(id, data);
    }else if(id == INFO_ID_BATTERY_1 || id == INFO_ID_BATTERY_2) {
        battery_info.setData(id, data);
    }else if(id == INFO_ID_DRIVE) {
        drive_info.setData(id, data);
    }

    //ROS_INFO("data seted. ");

    printf("Car ststus: \n");
    printf("Mode: %s, Error code: %x, Remote gear: %s, Current gear: %s, remote acc: %d, current acc: %d, angle: %d\n", 
            getStr(status_info.getMode()).c_str(), 
            (unsigned short)status_info.getError(), 
            getStr(status_info.getRemoteGear()).c_str(), 
            getStr(status_info.getCurrentGear()).c_str(), 
            status_info.getRemoteAcc(), 
            status_info.getCurrentAcc(), 
            status_info.getAngle());
    printf("Brake pressure: %d, Parking: %s, Switch: %s, Emergency: %s, remote: %s\n", 
            status_info.getBrakePressure(), 
            getStr(status_info.getIsParking()).c_str(), 
            getStr(status_info.getGearSwitch()).c_str(), 
            getStr(status_info.getIsEmergency()).c_str(), 
            getStr(status_info.getIsRemoteOn()).c_str());

    printf("Milage: \n");
    printf("Speed: %d, Trip: %d, ODO: %d\n", 
            milage_info.getSpeed(), 
            milage_info.getTrip(), 
            milage_info.getOdo());

    printf("Wheel speed: \n");
    printf("Left rear: %d, Right rear: %d\n", 
            wheel_speed_info.getSpeedLeft(), 
            wheel_speed_info.getSpeedRight());

    printf("Battery: \n");
    printf("48V    Level: %d, Voltage: %d, Current: %d\n", 
            battery_info.getLevel(), 
            battery_info.getVoltageHigh(), 
            battery_info.getCurrent());
    printf("12V    Voltage: %d\n", battery_info.getVoltageLow());

    printf("Drive system: \n");
    printf("Rev: %d\n", drive_info.getRev());
}

void carCtrlCallBack(const chassisctrl::carctrl::ConstPtr& msg) {
    //ROS_INFO("ctrl callback");
    //ROS_WARN("acc: %d, angle: %d", msg->acc, msg->angle);
    chassisctrl::frame frame_ctrl;

    motion.setAngle(msg->angle);
    motion.setAccelerator(msg->acc);
    if(!motion.getData(data)) {
        ROS_ERROR("Error: motion control data set failed. ");
    }

    frame_ctrl.id = charToUInt(id, 4);
    frame_ctrl.data = charToULL(data, 8);
    //ROS_WARN("%lx", frame_ctrl.data);

    pub_ctrl.publish(frame_ctrl);
}