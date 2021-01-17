/*
  Encoder.h - Library for easily managing rotary encoders
  Created by Jacopo Mazzoni, January 2, 2020.
  Main logic adapted from: https://dronebotworkshop.com/rotary-encoders-arduino/
  Released into the public domain.
*/
#ifndef Encoder_h
#define Encoder_h

 class Encoder {
  
  private: 
  int pCLK, pDT;
  int CLK0,CLK1;
  int value, mul;
  int min, max;
  
  public: 
  Encoder(int, int, int);
  Encoder(int, int, int, int, int);
  void read();
  int getValue();
 };
  
#endif
