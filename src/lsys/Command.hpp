/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_COMMAND_HPP_INCLUDED
#define LSYS_COMMAND_HPP_INCLUDED

namespace lsys
{

namespace CommandType
{
    enum type
    {
        CALL,
        CALL_OR_NOOP,
        DRAW_TILL_ZERO,
        PUSH_POS,
        POP_POS,
        TURN_CW,
        TURN_CCW,
        TURN_BY,
        SET_DIVISOR,
        SET_ANGLE_STEP
    };
} // namespace CommandType

class Machine;
    
struct Command
{
    CommandType::type type;
    
    union
    {      
        int generator;
        double fparam;
    } param;
    
    inline Command(CommandType::type ptype)
    : type(ptype)
    {
    }
    
    inline Command(CommandType::type ptype, int generator)
    : type(ptype)
    {
        param.generator = generator;
    }
    
    inline Command(CommandType::type ptype, double dparam)
    : type(ptype)
    {
        param.fparam = dparam;
    }
};    
    
} // namespace lsys

#endif
