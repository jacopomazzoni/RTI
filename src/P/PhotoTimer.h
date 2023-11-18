/*
  PhotoTimer.h - Library for easily managing Photographic Shutter release times
  Created by Jacopo Mazzoni, January 11, 2020.

  Released into the public domain.
*/
#ifndef PhotoTimer_h
#define PhotoTimer_h

// number of elements in the array
#define nel 23

class PhotoTimer
{

private:
  int index;
  int n = nel;
  int times[nel] = {-5, -4, -3, -2, 1, 2, 5, 10, 15, 20, 25, 30, 40, 50, 60, 80, 100, 125, 180, 250, 320, 400, 500};
  // int count();
  // int round(float,int);
public:
  PhotoTimer();
  PhotoTimer(int);
  int getMillis();
  int getFraction();
  void increase();
  void decrease();
  void goTo(int);
};

#endif
