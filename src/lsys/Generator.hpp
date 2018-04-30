/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_GENERATOR_HPP_INCLUDED
#define LSYS_GENERATOR_HPP_INCLUDED

#include <vector>
#include <lsys/Command.hpp>

namespace lsys
{
    
/**
 * Vector of heap allocated Command's.
 */
class Generator
{
public:
    /**
     * Add a copy of the given command.
     */
    void add(Command cmd);
        
    /**
     * Return specified element.
     */
    Command const& operator[](int index) const;

    /**
     * Return specified element.
     */
    Command& operator[](int index);

    /**
     * Get number of commands stored.
     */
    int size() const;
        
private:    
    std::vector<Command> commands_;
};

inline void Generator::add(Command cmd)
{
    commands_.push_back(cmd);
}
        
inline Command const& Generator::operator[](int index) const
{
    return commands_[index];
}

inline Command& Generator::operator[](int index)
{
    return commands_[index];
}

inline int Generator::size() const
{
    return commands_.size();
}

} // namespace lsys

#endif
