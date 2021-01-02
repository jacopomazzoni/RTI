/*
  Encoder.h - Library for easily managing rotary encoders
  Created by Jacopo Mazzoni, January 2, 2020.
  Released into the public domain.
*/
#ifndef Encoder_h
#define Encoder_h

 class Encoder {
  
  private: 
  int pCLK, pDT;
  int CLK0,CLK1;
  int value,mul;
  
  public: 
  Encoder(int , int , int);
  
  void read();
  int getValue();
 };
  
#endif
