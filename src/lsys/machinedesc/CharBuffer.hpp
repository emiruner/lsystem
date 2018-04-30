/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_CHARBUFFER_HPP_INCLUDED
#define LSYS_CHARBUFFER_HPP_INCLUDED

#include <istream>

namespace lsys { namespace machinedesc {
            
/**
 * A character buffer with one character putback capability.
 */
class CharBuffer
{
public:
    /**
     * A character buffer associated with the given stream.
     */
    CharBuffer(std::istream& in);
    
    /**
     * Return next character.
     * In case of eof return std::char_traits<char>::eof().
     */
    int get();
    
    /**
     * Return the last character read back.
     * This function may be called at most once without
     * calling get consequtively.
     */
    void unget();
    
    /**
     * Return true if last operation succeeded.
     */
    bool good() const;
    
private:
    std::istream& in_;
    int lastChar_;
    bool ungot_;
};
 
} } // namespace machinedesc / lsys

#endif
