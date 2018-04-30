/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#include <lsys/machinedesc/CharBuffer.hpp>
#include <cassert>

namespace lsys { namespace machinedesc {

CharBuffer::CharBuffer(std::istream& in)
: in_(in), lastChar_(std::char_traits<char>::eof()), ungot_(false)
{
}

int CharBuffer::get()
{
    if(ungot_)
    {
        ungot_ = false;
        return lastChar_;
    }
    
    return lastChar_ = in_.get();
}

void CharBuffer::unget()
{
    assert(ungot_ == false);    
    ungot_ = true;
}

bool CharBuffer::good() const
{
    return in_.good();
}
 
} } // namespace machinedesc / lsys
