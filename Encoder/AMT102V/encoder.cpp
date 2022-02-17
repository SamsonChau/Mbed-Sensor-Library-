
#include "encoder.h"

Encoder::Encoder(PinName int_a, PinName int_b,int PPR, bool speed) : pin_a(int_a), pin_b(int_b)
{
    m_speed_enabled = speed;
    if(m_speed_enabled)
    EncoderTimer.start();
    //pin_a.fall(this,&Encoder::encoderFalling);
    pin_a.rise(this,&Encoder::encoderRising);
    m_position = 0;
    m_rotation = 0;
    m_speed = 0;
    ppr = PPR;
    zero_speed = false;
}
 
void Encoder::encoderFalling(void)
{
    //temporary speed storage, in case higher interrupt level does stuff
    
    /*if(m_speed_enabled)
    {
        float temp_speed=0;
        int motortime_now;
        motortime_now = EncoderTimer.read_us();
        EncoderTimer.reset();
        EncoderTimeout.attach(this,&Encoder::timeouthandler,0.1);
        //calculate as ticks per second
        if(zero_speed)
            temp_speed  = 0;
        else
            temp_speed = 1000000./motortime_now;
        zero_speed = false;
    }*/
    if(pin_b)
    {
        m_position--;
        //m_speed = temp_speed;
    }
    else
    {
        m_position++;    
        //m_speed  = -temp_speed; //negative speed
    }
}

void Encoder::encoderRising(void)
{
    //temporary speed storage, in case higher interrupt level does stuff

    /*
    if(m_speed_enabled)
    {
        float temp_speed=0;
        int motortime_now;
        EncoderTimer.reset();
        EncoderTimeout.attach(this,&Encoder::encoderFalling,0.1);
        //calculate as ticks per second
        if(zero_speed)
            temp_speed  = 0;
        else
            temp_speed = 1000000./motortime_now;
        zero_speed = false;
    }*/
    if(pin_b)
    {
        m_position--;
        /*if(m_position<=-ppr){
            m_position=0;
            m_rotation--;
        }*/   
        //m_speed = temp_speed; //negative speed
    }
    else
    {
        m_position++;  
        /*if(m_position>=ppr){
            m_position=0;
            m_rotation++;
        }*/      
        //m_speed  = -temp_speed; 
    }
}

void Encoder::timeouthandler(void)
{
    m_speed  = 0;
    zero_speed = true;
}
