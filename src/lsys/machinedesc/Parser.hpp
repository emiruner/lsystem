/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_MACHINEDESC_PARSER_HPP_INCLUDED
#define LSYS_MACHINEDESC_PARSER_HPP_INCLUDED

#include <vector>
#include <string>
#include <lsys/Generator.hpp>

namespace lsys { namespace machinedesc {

/**
 * Reads the generators in the command file.
 * Fixes the references between the generators.
 * In case of an error throws std::exception compatible exception.
 * mainGen will be set to the index of the main generator. -1 if not present.
 */
void readMachineDesc(std::string filename, std::vector<Generator>& generators, int& mainGen);

} } // namespace machinedesc / lsys

#endif
