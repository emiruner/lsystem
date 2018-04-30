/**
 * This file is part of the LSys.
 *
 * Copyright (C) 2010, Emir Uner
 */

#ifndef LSYS_MACHINEDESC_TOKENTYPE_HPP_INCLUDED
#define LSYS_MACHINEDESC_TOKENTYPE_HPP_INCLUDED

namespace lsys
{

namespace machinedesc
{

namespace TokenType
{
    enum type
    {
        Invalid,
        Eof,
        Comma,
        Semicolon,
        LParen,
        RParen,
        LCurly,
        RCurly,
        LessThan,
        GreaterThan,
        DoubleLiteral,
        StringLiteral,
        IntegerLiteral,
        Identifier,
        Call,
        CallOrNoOp,
        TurnBy,
        Generator,
        TurnCW,
        TurnCCW,
        PushPos,
        PopPos,
        SetDivisor,
        SetAngleStep,
    };

    inline char const* toStr(type t)
    {
        switch(t)
        {
            case Invalid: return "Invalid";
            case Eof: return "Eof";
            case Comma: return "Comma";
            case Semicolon: return "Semicolon";
            case LParen: return "LParen";
            case RParen: return "RParen";
            case LCurly: return "LCurly";
            case RCurly: return "RCurly";
            case LessThan: return "LessThan";
            case GreaterThan: return "GreaterThan";
            case DoubleLiteral: return "DoubleLiteral";
            case StringLiteral: return "StringLiteral";
            case IntegerLiteral: return "IntegerLiteral";
            case Identifier: return "Identifier";
            case Call: return "Call";
            case CallOrNoOp: return "CallOrNoOp";
            case TurnBy: return "TurnBy";
            case Generator: return "Generator";
            case TurnCW: return "TurnCW";
            case TurnCCW: return "TurnCCW";
            case PushPos: return "PushPos";
            case PopPos: return "PopPos";
            case SetDivisor: return "SetDivisor";
            case SetAngleStep: return "SetAngleStep";
            default: return "<INVALID TOKEN TYPE>";
        }
    }
}

}

}

#endif
