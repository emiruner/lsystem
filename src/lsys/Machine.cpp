/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#include <lsys/Machine.hpp>
#include <stdexcept>

namespace lsys
{
    
void Machine::oneLevelDown()
{
    --level_;
//    step_ /= divisor_;
}

void Machine::oneLevelUp()
{
    ++level_;
  //  step_ *= divisor_;
}

void Machine::startFrom(int generator)
{
    Generator const& gen = generators_[generator];
    
    for(int i = 0, size = gen.size(); i < size; ++i)
    {
        Command const& cmd = gen[i];

        switch(cmd.type)
        {
            case CommandType::CALL:
                callOrDraw(cmd.param.generator);
                break;
            case CommandType::CALL_OR_NOOP:
                callOrDoNothing(cmd.param.generator);
                break;
            case CommandType::DRAW_TILL_ZERO:
                drawTillZero();
                break;
            case CommandType::PUSH_POS:
                pushPos();
                break;
            case CommandType::POP_POS:
                popPos();
                break;
            case CommandType::SET_ANGLE_STEP:
                setAngleStep(cmd.param.fparam);
                break;
            case CommandType::SET_DIVISOR:
                setDivisor(cmd.param.fparam);
                break;
            case CommandType::TURN_BY:
                turnBy(cmd.param.fparam);
                break;
            case CommandType::TURN_CW:
                turnCW();
                break;
            case CommandType::TURN_CCW:
                turnCCW();
                break;
            default:
                throw std::runtime_error("must not reach here");
        }
    }
}

void Machine::drawTillZero()
{
    double x0, y0, x1, y1;
    
    turtle_.forward(step_, x0, y0, x1, y1);
    trace_->draw(x0, y0, x1, y1);
    
    if(level_ != 0)
    {
        oneLevelDown();
        drawTillZero();
        oneLevelUp();
    }
}

void Machine::callOrDraw(int generator)
{
    if(level_ == 0)
    {
        double x0, y0, x1, y1;
        
        turtle_.forward(step_, x0, y0, x1, y1);
        trace_->draw(x0, y0, x1, y1);
    }
    else
    {
        oneLevelDown();
        startFrom(generator);
        oneLevelUp();
    }
}

void Machine::callOrDoNothing(int generator)
{
    if(level_ != 0)
    {
        oneLevelDown();
        startFrom(generator);
        oneLevelUp();
    }
}

} // namespace lsys

