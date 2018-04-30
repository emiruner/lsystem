/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_TRACE_HPP_INCLUDED
#define LSYS_TRACE_HPP_INCLUDED

namespace lsys
{

/**
 * Interface which is used to watch the execution of an
 * l-systems virtual machine.
 */
class Trace
{
public:
    virtual void draw(double x0, double y0, double x1, double y1) = 0;
};
    
} // namespace lsys

#endif
