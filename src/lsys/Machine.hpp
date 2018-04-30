/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_MACHINE_HPP_INCLUDED
#define LSYS_MACHINE_HPP_INCLUDED

#include <stack>
#include <vector>

#include <lsys/Generator.hpp>
#include <lsys/Trace.hpp>
#include <lsys/Turtle.hpp>

namespace lsys
{

/**
 * L-Systems virtual machine. Executes fractal generating programs.
 */
class Machine
{
public:
    typedef std::vector<Generator> GeneratorVec;
    
    /**
     * Construct a Machine with given configuration.
     */
    Machine(GeneratorVec const& gens, int depth, double step);

    /**
     * Attach tracer.
     */
    void attachTracer(Trace* trace);

    /**
     * Remove tracer.
     */
    void removeTracer();
    
    /**
     * Reset to initial configuration parameters.
     */
    void reset();
    
    /**
     * Start running from given generator.
     */
    void startFrom(int generator);

    /**
     * Turn clockwise.
     */
    void turnCW();

    /**
     * Turn counter clockwise.
     */
    void turnCCW();

    /**
     * Change current divisor.
     */
    void setDivisor(double divisor);
    
    /**
     * Change angle steps.
     */
    void setAngleStep(double angleStep);
    
    /**
     * Save current position and direction to the stack.
     */
    void pushPos();

    /**
     * Restore position and direction from stack.
     */
    void popPos();
    
    /**
     * Turn by a given degree.
     */
    void turnBy(double angle);

    /**
     * Draw a line from current position until
     * the level hits zero.
     */
    void drawTillZero();

    /**
     * Calls the given generator if above zero level,
     * draws a line otherwise.
     */
    void callOrDraw(int generator);

    /**
     * Calls the given generator if above zero level,
     * otherwise do nothing.
     */
    void callOrDoNothing(int generator);

private:
    /**
     * Goes one level down.
     */
    void oneLevelDown();
    
    /**
     * Goes one level up.
     */
    void oneLevelUp();
    
    // Configuration
    GeneratorVec generators_;
    double divisor_;
    double turnAngle_;
    int initialLevel_;
    double initialStep_;
    
    // Current status
    int level_;
    double step_;
    Trace* trace_;
    std::stack<Turtle> positionStack_;
    Turtle turtle_;
};

// Inline implementations.    
inline Machine::Machine(GeneratorVec const&gens, int depth, double step)
: generators_(gens), level_(depth), step_(step), trace_(0)
{
    initialLevel_ = depth;
    initialStep_ = step;
}

inline void Machine::attachTracer(Trace* trace)
{
    trace_ = trace;
}

inline void Machine::removeTracer()
{
    trace_ = 0;
}

inline void Machine::reset()
{
    level_ = initialLevel_;
    step_ = initialStep_;
    turtle_ = Turtle();
}
    
inline void Machine::turnCW()
{
    turtle_.turn(turnAngle_);
}

inline void Machine::turnCCW()
{
    turtle_.turn(-turnAngle_);
}

inline void Machine::setDivisor(double divisor)
{
    divisor_ = divisor;
}
    
inline void Machine::setAngleStep(double angleStep)
{
    turnAngle_ = angleStep;
}
    
inline void Machine::pushPos()
{
    positionStack_.push(turtle_);
}

inline void Machine::popPos()
{
    turtle_ = positionStack_.top();
    positionStack_.pop();
}

inline void Machine::turnBy(double angle)
{
    turtle_.turn(angle);
}

} // namespace lsys

#endif
