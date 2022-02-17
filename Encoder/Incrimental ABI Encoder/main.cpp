#include "mbed.h"
#include "QEI.h"
#include <geometry_msgs/Point.h>
#include <ros.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Encoder parameter setup
// Encoder X pin
#define EncoderX_A PB_0
#define EncoderX_B PB_7

// Encoder Y pin
#define EncoderY_A PB_6
#define EncoderY_B PB_1

const int Encoder_PPR = 2048;
const float Encoder_Omni_Wheel_Radius = 0.0254; // Radius of the Omni Wheel
const float omni_wheel = 2 * M_PI * Encoder_Omni_Wheel_Radius;

QEI EncoderX(EncoderX_A, EncoderX_B, NC, Encoder_PPR);
QEI EncoderY(EncoderY_A, EncoderY_B, NC, Encoder_PPR);

using namespace std::chrono;
Timer t1;

// timers for the sub-main loop
int dt = 0;
int loopTime = 5;       // 10 milliseconds

ros::NodeHandle nh;
geometry_msgs::Point Encoder_msg;

ros::Publisher Encoder_publisher("encoder/position", &Encoder_msg);

int main() {
  nh.getHardware()->setBaud(128000); // Maximum for f303K8
  nh.initNode();
  nh.advertise(Encoder_publisher);
  t1.start();
  while (true) {
    dt = duration_cast<milliseconds>(t1.elapsed_time()).count();
    if (dt >= loopTime) { // run a loop every 10ms
      t1.stop();
      // calculat the Encoder distance in mm
      Encoder_msg.x = ((float)EncoderX.getPulses() * omni_wheel / Encoder_PPR) ;
      Encoder_msg.y = ((float)EncoderY.getPulses() * omni_wheel / Encoder_PPR) ;
      Encoder_publisher.publish(&Encoder_msg);
      nh.spinOnce();
      t1.reset(); // reset the clock to time it
      t1.start();
    }
  }
}
