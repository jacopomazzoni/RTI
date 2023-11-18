#include "Arduino.h"
#include "PhotoTimer.h"

PhotoTimer::PhotoTimer(int i) { this->index = (i >= 0 && i <= this->n ? i : 0); }

PhotoTimer::PhotoTimer() { this->index = 0; }

int PhotoTimer::getMillis()
{
    int x = this->times[this->index];
    if (x != 0)
    {
        if (x < 0)
        {
            return abs(x) * 1000;
        }
        else
        {
            return round(1000. / x);
        }
    }
    else
    {
        return 0;
    }
}

int PhotoTimer::getFraction()
{
    this->index = (this->index < this->n ? this->index : this->n - 1);
    return this->times[this->index];
}

void PhotoTimer::increase()
{
    if (this->index < this->n)
    {
        this->index++;
    }
}

void PhotoTimer::decrease()
{
    if (this->index > 0)
    {
        this->index--;
    }
}

void PhotoTimer::goTo(int i)
{
    this->index = abs(i) % this->n;
    /*
    if (i >= 0 && i < this->n)
    {
        this->index = i;
    }*/
}
/*
int PhotoTimer::count()
{
    return sizeof(this->times) / sizeof(this->times[0]);
}*/