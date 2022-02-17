## STM32 program for Reading the encoder data of the ABI Encoder
This is the mbed program using mbed online complier to transfre the data to can bus on a stm32 F446RE

## mbed environment setup
1. Use mbed os 6.8+
2. Download the code and install the ros.lib in your mbed environment via the links<br/>
   ros_lib_melodic https://github.com/PolyU-Robocon/ros_lib_melodic
3. modifly the baudrate in directory ros_lib_melodic-master/MbedHardware.h
   ```cpp
	 /*
	 * MbedHardware
	 *
	 *  Created on: Aug 17, 2011
	 *      Author: nucho
	 */

	#ifndef ROS_MBED_HARDWARE_H_
	#define ROS_MBED_HARDWARE_H_

	#include "mbed.h"


	class MbedHardware {
	  public:
	    MbedHardware(PinName tx, PinName rx, long baud = 115200) // Modify Here 
	      :iostream(tx, rx){
	      baud_ = baud;
	      //iostream.set_blocking(true);
	      t.start();
	    }


	    MbedHardware()
	      :iostream(USBTX, USBRX) {
		baud_ = 115200;					// and Modify Here 
		//iostream.set_blocking(true);
		t.start();      
	    }


	    void setBaud(long baud){
	      this->baud_= baud;
	    }

	    int getBaud(){return baud_;}

	    void init(){
		iostream.set_baud(baud_);
	    }


	    int read(){
		if (iostream.readable()) {
		     iostream.read(rbuf, 1);
		    return rbuf[0];
		} else {
		    return -1;
		}
	    };

	    void write(uint8_t* data, int length) {
		//while (!iostream.writable()) {
		iostream.write(data,length);
		//}
		/* 
		for (int i=0; i<length; i++){
		     iostream.putc(data[i]);
		     }
		     */
	    }

	    unsigned long time(){return  std::chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();}

	protected:
	    BufferedSerial iostream;
	    int rbuf[1]={0};
	    long baud_;
	    Timer t;
	};


	#endif /* ROS_MBED_HARDWARE_H_ */
	```
4. Compile it and debug
5. use the printf function to check the output data before connect to ros
 
* Check out the other repo for more details  
