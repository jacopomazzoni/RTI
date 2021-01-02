#include "Arduino.h"
#include "Encoder.h"


Encoder::Encoder(int pinCLK, int pinDT, int multiplier = 1) {
      this->pCLK = pinCLK;
      this->pDT = pinDT;
      this->mul = multiplier;
      pinMode(this->pCLK,INPUT);
      pinMode(this->pDT,INPUT);
      this->value = 0;
      this->CLK0 = digitalRead(this->pCLK);
  }
  
  void Encoder::read() {
    // read current value
    this->CLK1 = digitalRead(this->pCLK);
    // compare with previous value
    if (this->CLK1 != this->CLK0){   
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise ( see table below)
     if (digitalRead(this->pDT) != this->CLK1) { 
       this->value--;
     } else {
       // Encoder is rotating clockwise
       this->value++;  
     }
    }
    this->CLK0 = this->CLK1;
  }

  
  int Encoder::getValue() {
    this->read();
    return ( (this->value)/2 ) * mul;
  }

/*  
 *   Encoder States Sequence 
 *  _______________________
 * | CW        | CCW       |
 * | CLK | DT  | CLK | DT  |
 * |-----------|-----------|
 * |  0  |  0  |  0  |  0  |
 * |  0  |  1  |  1  |  0  |
 * |  1  |  1  |  1  |  1  |
 * |  1  |  0  |  0  |  1  |
 *  -----------------------
 */
