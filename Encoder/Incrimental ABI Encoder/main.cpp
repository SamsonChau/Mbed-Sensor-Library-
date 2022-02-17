#include "mbed.h"
#include "QEI.h"

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

// Use AMT102V encoder as an example 
const int Encoder_PPR = 2048;                           //setup the pulse per rotation of the encoder 
QEI EncoderX(EncoderX_A, EncoderX_B, NC, Encoder_PPR);  
QEI EncoderY(EncoderY_A, EncoderY_B, NC, Encoder_PPR);

using namespace std::chrono;
Timer t1;

// timers for the sub-main loop
int dt = 0;
int loopTime = 5;       // 10 milliseconds

int main() {
  int Encoder_x = 0;
  int Encoder_y = 0;
  int Encoder_vx = 0;
  int Encoder_vy = 0;
  t1.start();
  while (true){
    dt = duration_cast<milliseconds>(t1.elapsed_time()).count();
    if (dt >= loopTime) { // run a loop every 10ms
      t1.stop();
      // calculate the Encoder rotation in degree / second
      Encoder_vx = (int)((EncoderX.getPulses() / Encoder_PPR) * 360) - Encoder_x;
      Encoder_vy = (int)((EncoderY.getPulses() / Encoder_PPR) * 360) - Encoder_y;
      
      // calculate the Encoder rotation in degree
      Encoder_x = (int)(EncoderX.getPulses() / Encoder_PPR) * 360;
      Encoder_y = (int)(EncoderY.getPulses() / Encoder_PPR) * 360;

      t1.reset(); // reset the clock to time it
      t1.start();
    }
  }
}
