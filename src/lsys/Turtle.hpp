/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_TURTLE_HPP_INCLUDED
#define LSYS_TURTLE_HPP_INCLUDED

namespace lsys
{
    
/**
 * Holds position.
 */
class Turtle
{
public:
    /**
     * Positions itself at (0, 0) directed to 90 degree north.
     */
    Turtle()
    : angle_(90), x_(0), y_(0)
    {
    }

    /**
     * Turn relative.
     */
    void turn(double diff);
    
    /**
     * Move dist distance in current dimension.
     */
    void forward(double dist);

    /**
     * Move dist distance in current direction. Report
     * before and after positions.
     */
    void forward(double dist, double& x0, double& y0, double& x1, double& y1)
    {
        x0 = x_;
        y0 = y_;

        forward(dist);

        x1 = x_;
        y1 = y_;
    }
    
private:
    double angle_;
    double x_;
    double y_;
};

} // namespace lsys

#endif
