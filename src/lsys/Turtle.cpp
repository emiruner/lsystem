/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#include <lsys/Turtle.hpp>
#include <cmath>

namespace
{
    const double kRadPerDeg = .01745329251994329576;
    
    inline double degToRad(double deg)
    {
        return deg * kRadPerDeg;
    }
}

namespace lsys
{
        
void Turtle::turn(double diff)
{
    angle_ += diff;

    while(angle_ > 360)
    {
        angle_ -= 360.0;
    }
    
    while(angle_ < 0)
    {
        angle_ += 360.0;
    }
}

void Turtle::forward(double dist)
{
    double x, y;
    
    if(angle_ == 90)
    {
        x = x_;
        y = y_ + dist;
    }
    else
    {
        x = x_ + dist * cos(degToRad(angle_));
        y = y_ + dist * sin(degToRad(angle_));
    }

    x_ = x;
    y_ = y;
}

} // namespace lsys
