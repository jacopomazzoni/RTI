#include "Arduino.h"
#include "TimeDiff.h"

TimeDiff::TimeDiff()
{
    this->start = 0;
    this->stop = 0;
    this->calc();
}

void TimeDiff::calc()
{
    this->s = round((this->stop - this->start) / 1000.);
    this->m = this->s / 60;
    // this->s %= 60;
}

TimeDiff::TimeDiff(unsigned long int b, unsigned long int a)
{
    this->start = b;
    this->stop = a;
    this->calc();
}

int TimeDiff::getMinutes()
{
    return this->m;
}

int TimeDiff::getSeconds()
{
    return this->s;
}

void TimeDiff::setStart(unsigned long int before)
{
    this->start = before;
    this->calc();
}

void TimeDiff::setStop(unsigned long int after)
{
    this->stop = after;
    this->calc();
}
void TimeDiff::setStart()
{
    this->start = millis();
    this->calc();
}

void TimeDiff::setStop()
{
    this->stop = millis();
    this->calc();
}