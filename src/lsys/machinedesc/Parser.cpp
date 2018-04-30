/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#include <lsys/machinedesc/Parser.hpp>
#include <lsys/machinedesc/Lexer.hpp>

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace lsys;
using namespace lsys::machinedesc;

namespace
{
    typedef std::vector<std::string> StringVec;

    /**
     * Checks whether all the elements in the given collection are unique.
     */
    template <typename Collection>
    bool allUnique(Collection const& orig)
    {
        Collection copy(orig);
        Collection unique;
        
        std::sort(copy.begin(), copy.end());
        std::unique_copy(copy.begin(), copy.end(), std::back_inserter(unique));

        return copy.size() == unique.size();
    }
    
    /**
     * Finds the names of the generators in the input file.
     * This is used to find the index of generators.
     */
    StringVec findGeneratorNames(std::string const& filename)
    {
        std::ifstream infile(filename.c_str());
        
        if(!infile.is_open())
        {
            throw std::runtime_error("Cannot open input file.");
        }
        
        Lexer in(infile, filename);     
        StringVec names;        
        Token token(Token::invalidToken());

        while((token = in.getNextToken()).getType() != TokenType::Eof)
        {
            if(token.getType() == TokenType::Generator)
            {
                names.push_back(in.expectToken(TokenType::Identifier).asString());
            }
        }

        if(!allUnique(names))
        {
            throw std::runtime_error("Duplicate generator name exist.");
        }
        
        return names;
    }

    /**
     * Return the index of the given element in the given collection.
     * Return -1 if not found.
     */
    template <typename Collection>
    int indexOf(Collection const& coll, typename Collection::value_type item)
    {
        typename Collection::const_iterator i, end;
        int idx;
        
        for(i = coll.begin(), end = coll.end(), idx = 0; i != end; ++i, ++idx)
        {
            if(*i == item)
            {
                return idx;
            }
        }
        
        return -1;
    }
    
    Command readCall(Lexer& in, StringVec const& generatorNames, CommandType::type type)
    {
        Token name = in.expectToken(TokenType::Identifier);
        int generator = indexOf(generatorNames, name.asString());

        if(generator == -1)
        {
            in.raiseError("Unknown generator.", name);
        }
        
        return Command(type, generator);
    }

    Command readDoubleArgCmd(Lexer& in, CommandType::type type)
    {
        return Command(type, in.expectToken(TokenType::DoubleLiteral).asFloat());
    }
    
    Generator readGenerator(Lexer& in, StringVec const& generatorNames)
    {
        Generator generator;

        in.discardToken(TokenType::Identifier);
        in.discardToken(TokenType::LCurly);

        Token token(Token::invalidToken());
        
        while((token = in.getNextToken()).getType() != TokenType::RCurly)
        {
            switch(token.getType())
            {
            case TokenType::Call:
                generator.add(readCall(in, generatorNames, CommandType::CALL));
                break;

            case TokenType::CallOrNoOp:
                generator.add(readCall(in, generatorNames, CommandType::CALL_OR_NOOP));
                break;

            case TokenType::TurnBy:
                generator.add(readDoubleArgCmd(in, CommandType::TURN_BY));
                break;

            case TokenType::TurnCW:
                generator.add(Command(CommandType::TURN_CW));
                break;
                
            case TokenType::TurnCCW:
                generator.add(Command(CommandType::TURN_CCW));
                break;
                
            case TokenType::PushPos:
                generator.add(Command(CommandType::PUSH_POS));
                break;
                
            case TokenType::PopPos:
                generator.add(Command(CommandType::POP_POS));
                break;

            case TokenType::SetDivisor:
                generator.add(readDoubleArgCmd(in, CommandType::SET_DIVISOR));
                break;
                
            case TokenType::SetAngleStep:
                generator.add(readDoubleArgCmd(in, CommandType::SET_ANGLE_STEP));
                break;
                
            default:
                in.raiseError("unexpected token", token);
                break;
            }
        }
        
        return generator;
    }
    
} // namespace <unnamed>

namespace lsys { namespace machinedesc {

void readMachineDesc(std::string filename, std::vector<Generator>& generators, int& mainGen)
{
    StringVec generatorNames;

    generatorNames = findGeneratorNames(filename);
    
    std::ifstream infile(filename.c_str());
    if(!infile.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }
    
    mainGen = indexOf(generatorNames, "main");
    Lexer in(infile, filename);
    
    Token token(Token::invalidToken());

    while((token = in.getNextToken()).getType() != TokenType::Eof)
    {
        if(token.getType() == TokenType::Generator)
        {
            generators.push_back(readGenerator(in, generatorNames));
        }
        else
        {
            in.raiseError("unexpected token", token);
        }
    }
}    

} } // namespace machinedesc / lsys
