/*
  TimeDiff.h - Library for easily managing rotary encoders
  Created by Jacopo Mazzoni, January 2, 2020.
  Released into the public domain.
*/
#ifndef TimeDiff_h
#define TimeDiff_h

 class TimeDiff {
  
  private: 
    int m;
    int s;
    unsigned long int start;
    unsigned long int stop;
    void calc();

  public: 
  TimeDiff();
  TimeDiff(unsigned long int,unsigned long int);
  void setStart(unsigned long int);
  void setStop(unsigned long int);
  void setStart();
  void setStop();
  int getMinutes();
  int getSeconds(); 
 };
  
#endif