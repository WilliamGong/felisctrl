/**
 * @file teleop.cpp
 * @author William Gong (gtl119@live.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "chassisctrl/carctrl.h"

#include "ros/ros.h"
#include <cstdio>
#include <termios.h>
#include <stdint.h>

const double RATE_ANGLE = 1;    // rate of change in steering, range: [-100, 100]
const double RATE_ACC = 1;      // growth rate of accelerater, range: [0, 100]

static struct termios initial_settings, new_settings;
static int peek_character = -1;
void initKeyboard();
void closeKeyboard();
int kbhit();
int readch(); 

int main(int argc, char **argv) {
    ros::init(argc, argv, "chassisctrl_teleop");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<chassisctrl::carctrl>("teleop", 1);
    chassisctrl::carctrl msg;
    msg.angle = 0;
    msg.acc = 0;

    short current_angle = 0;
    int8_t current_acc = 0;

    printf("Use WASD to move");

    initKeyboard();
    int count = 0;
    while(ros::ok()) {
        count++;
        kbhit();
        if(kbhit()) {

            int ch = readch();
            //printf("\n%d\n",ch);

            if(ch == 119) {    // w
                current_acc += RATE_ACC;
                if(current_acc > 100) {
                    current_acc = 100;
                }
            }else if(ch == 97) {    // a
                current_angle += RATE_ANGLE;
                if(current_angle > 100) {
                    current_angle = 100;
                }
            }else if(ch == 100) {   // d
                current_angle -= RATE_ANGLE;
                if(current_angle < -100 ) {
                    current_angle = -100;
                }
            }else if(ch == 115) {   // s
                if(current_acc > 0) {
                    current_acc -= RATE_ACC;
                }
            }

            msg.acc = (uint8_t)current_acc;
            msg.angle = current_angle;

            printf("ACC: %d, Angle: %d\n", msg.acc, msg.angle);

            pub.publish(msg);

        }else {

            /*
            if(current_angle > 0) {
                current_angle -= RATE_ANGLE;
            }else if(current_angle < 0) {
                current_angle += RATE_ANGLE;
            }
            current_acc = 0;

            msg.acc = current_acc;
            msg.angle = current_angle;

            //printf("ACC: %d, Angle: %d", current_acc, current_angle);

            pub.publish(msg);
            */

        }
        

        ros::spinOnce();
    }
    closeKeyboard();

    return 0;
}

void initKeyboard() {
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= (~ICANON);
    //new_settings.c_lflag |= ECHO;
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_lflag |= ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void closeKeyboard() {
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit() {
    unsigned char ch;
    int nread;
 
    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1) {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch() {
    char ch;
 
    if(peek_character != -1) {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}