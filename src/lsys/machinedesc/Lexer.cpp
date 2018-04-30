/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#include <lsys/machinedesc/Lexer.hpp>

#include <ctype.h>

#include <cassert>
#include <sstream>
#include <stdexcept>

using namespace lsys::machinedesc;

namespace
{
    /**
     * If returns true the given character is a character
     * that ends any token when encountered.
     */
    inline bool separatorChar(int ch)
    {
        return isspace(ch) ||
            ch == ',' ||
            ch == ';' ||
            ch == '{' ||
            ch == '}' ||
            ch == '(' ||
            ch == ')' ||
            ch == '<' ||
            ch == '>' ||
            ch == '"' || // string literal beginning
            ch == '/' || // comment beginning
            ch == ':' || // a type name with scope specifier
            ch == std::char_traits<char>::eof();
    }

    /**
     * Reads an invalid token until finding a separator character.
     */
    inline std::string consumeInvalid(CharBuffer& in)
    {
        std::string result;
        int ch;
        
        while((ch = in.get()) != std::char_traits<char>::eof())
        {
            if(separatorChar(ch))
            {
                in.unget();
                break;
            }
            
            result += ch;
        }

        return result;
    }
    
    /**
     * Returns true if successfully reads a double number.
     * Token must be terminated by a separatorChar.
     * In case of erroneous integer return false and up to first separator
     * write the token string to invalid parameter.
     */
    inline bool consumeDoubleLiteral(CharBuffer& in, double& result, std::string& invalid)
    {
        std::string strnum;
        bool dotRead, firstChar;
        int ch;
        
        dotRead = false;
        firstChar = true;
        
        while((ch = in.get()) != std::char_traits<char>::eof())
        {
            if(isdigit(ch))
            {
                strnum += ch;
            }
            else if(ch == '.' && !dotRead)
            {
                strnum += ch;
                dotRead = true;
            }
            else if(ch == '-' && firstChar)
            {
                strnum += ch;
                firstChar = false;
            }
            else if(separatorChar(ch))
            {
                in.unget();
                break;
            }
            else
            {
                in.unget();
                invalid = strnum + consumeInvalid(in);
                return false;
            }
        }

        std::istringstream iss(strnum);
        iss >> result;
        return true;
    }

    /**
     * Checks whether the identifier is well formed.
     * Actually contains even ::'s and the place of ::
     * is not at end.
     */
    bool validIdentifier(std::string const& id)
    {
        std::string::const_iterator i = id.begin(), end = id.end();
        
        while(i != end)
        {
            if(*i == ':')
            {
                ++i;
                if(i == end)
                {
                    return false;
                }
                else if(*i != ':')
                {
                    return false;
                }
                else
                {
                    ++i;
                    if(i == end)
                    {
                        return false;
                    }
                }
            }
            else
            {
                ++i;
            }
        }

        return true;
    }
    
    /**
     * Reads a string literal whose opening quote is read.
     * Returns false if an error occurs before string literal completes.
     */
    bool readStringLiteral(std::istream& in, int& lineNo, std::string& result)
    {
        int ch;
        
        while(true)
        {
            ch = in.get();
            if(in.fail() || in.eof())
            {
                return false;
            }
            
            if(ch == '\n')
            {
                ++lineNo;
            }
            else if(ch == '"')
            {
                break;
            }
            else
            {
                result += ch;
            }
        }
        
        return true;
    }

    /**
     * Reads a comment whose first character '/' is read. It can handle
     * both single and multi line comments. If an error occurs return false
     * and the invalid input in result otherwise returns true and
     * result is empty.
     */
    bool readComment(std::istream& in, int& lineNo, std::string& result)
    {
        int ch;
        
        ch = in.get();
        if(!in.fail())
        {
            if(ch == '/')
            {
                while((ch = in.get()) != std::char_traits<char>::eof())
                {
                    if(ch == '\n')
                    {
                        ++lineNo;
                        break;
                    }
                }
                return true;
            }
            else if(ch == '*')
            {
                result += ch;
                
                while((ch = in.get()) != std::char_traits<char>::eof())
                {
                    result += ch;

                    if(ch == '*')
                    {
                        ch = in.get();
                        if(!in.fail() && ch != std::char_traits<char>::eof())
                        {
                            result += ch;
                        }
                        
                        if(in.fail())
                        {
                            return false;
                        }
                        else if(ch == '/')
                        {
                            result = "";
                            return true;
                        }
                        else if(ch == '\n')
                        {
                            ++lineNo;
                        }
                    }
                    else if(ch == '\n')
                    {
                        ++lineNo;
                    }
                }
                return false;
            }
            else
            {
                result = "";
                result += ch;
                return false;
            }
        }
        
        result = "";
        result += ch;
        return false;
    }

    /**
     * Tries to read an identifier whose first letter is read.
     */
    bool consumeIdentifierOrKeyword(CharBuffer& in, std::string& result)
    {
        int ch;
        result = "";
        
        while((ch = in.get()) != std::char_traits<char>::eof())
        {
            if(isdigit(ch) || isalpha(ch))
            {
                result += ch;
            }
            else if(ch == ':')
            {
                result += ch;
            }
            else if(separatorChar(ch))
            {
                in.unget();
                return true;
            }
            else
            {
                break;
            }
        }
        
        if(ch == std::char_traits<char>::eof())
        {
            return true;
        }
        
        return false;
    }

    struct KeywordTokenId
    {
        char const* keyword;
        TokenType::type type;
    };
    
    KeywordTokenId keywordTokenMap[] =
    {
        { "call",         TokenType::Call },
        { "callOrNoOp",   TokenType::CallOrNoOp },
        { "turnBy",       TokenType::TurnBy },
        { "generator",    TokenType::Generator },
        { "turnCW",       TokenType::TurnCW },
        { "turnCCW",      TokenType::TurnCCW },
        { "pushPos",      TokenType::PushPos },
        { "popPos",       TokenType::PopPos },
        { "setDivisor",   TokenType::SetDivisor },
        { "setAngleStep", TokenType::SetAngleStep },
        { 0,              TokenType::Invalid}
    };
    
    /**
     * Token from identifier of keyword string.
     */
    Token tokenFromIdentifier(std::string id, int lineNo)
    {
        for(int i = 0; keywordTokenMap[i].keyword != 0; ++i)
        {
            if(keywordTokenMap[i].keyword == id)
            {
                return Token(keywordTokenMap[i].type, lineNo);
            }
        }
        
        if(validIdentifier(id))
        {
            return Token(TokenType::Identifier, lineNo, id.c_str());
        }
        else
        {
            return Token(TokenType::Invalid, lineNo, id.c_str());
        }
    }
} // namespace <unnamed>

Lexer::Lexer(std::istream& in, std::string filename)
: inStream_(in), in_(in), filename_(filename), lineNo_(1), pushedBack_(false),
  token_(Token::invalidToken())
{
}

Token Lexer::expectAnyToken()
{
    Token result(getNextToken());

    if(result.getType() == TokenType::Invalid || result.getType() == TokenType::Eof)
    {
        raiseError("a token is needed", result);
    }

    return result;
}
    
Token Lexer::expectToken(TokenType::type t)
{
    Token result(getNextToken());

    if(result.getType() != t)
    {
        raiseError("unexpected token", result);
    }

    return result;
}

Token Lexer::expectToken(TokenType::type t1, TokenType::type t2)
{
    Token result(getNextToken());

    if(result.getType() != t1 && result.getType() != t2)
    {
        raiseError("unexpected token", result);
    }

    return result;
}

void Lexer::discardToken(TokenType::type t)
{
    Token token(getNextToken());
    
    if(token.getType() != t)
    {
        raiseError("unexpected token", token);
    }
}

void Lexer::raiseError(std::string message, Token const& offending) const
{
    std::ostringstream oss;
    
    oss << getFilename() << ':' << offending.getLineNo()
        << ": error: " << message << ": " << offending.asString();
    
    throw std::runtime_error(oss.str());
}
    
void Lexer::ungetToken()
{
    assert(pushedBack_ == false);
    pushedBack_ = true;
}

Token Lexer::getNextToken()
{
    if(pushedBack_)
    {
        pushedBack_ = false;
        return token_;
    }
    
    int ch = 3;
    
    while((ch = in_.get()) != std::char_traits<char>::eof())
    {
        switch(ch)
        {

        case '\n':
        {
            ++lineNo_;
        }
        break;

        case '\r':
        case '\t':
        case ' ':
            break;
            
        case ',':
        {
            return token_ = Token(TokenType::Comma, lineNo_);
        }
        break;
        
        case ';':
        {
            return token_ = Token(TokenType::Semicolon, lineNo_);
        }
        break;
        
        case '(':
        {
            return token_ = Token(TokenType::LParen, lineNo_);
        }
        break;
        
        case ')':
        {
            return token_ = Token(TokenType::RParen, lineNo_);
        }
        break;
        
        case '{':
        {
            return token_ = Token(TokenType::LCurly, lineNo_);
        }
        break;
        
        case '}':
        {
            return token_ = Token(TokenType::RCurly, lineNo_);
        }
        break;
        
        case '<':
        {
            return token_ = Token(TokenType::LessThan, lineNo_);
        }
        break;
        
        case '>':
        {
            return token_ = Token(TokenType::GreaterThan, lineNo_);
        }
        break;

        case '"':
        {
            std::string sl;
            
            if(readStringLiteral(inStream_, lineNo_, sl))
            {
                return token_ = Token(TokenType::StringLiteral, lineNo_,
                                      sl.c_str());
            }
            else
            {
                return token_ = Token(TokenType::Invalid, lineNo_,
                                      ("\"" + sl).c_str());
            }
        }
        break;
        
        case '/':
        {
            std::string sl;
            
            if(readComment(inStream_, lineNo_, sl))
            {
                continue;
            }
            else
            {
                return token_ = Token(TokenType::Invalid, lineNo_,
                                      ("/" + sl).c_str());
            }
        }
        break;

        case '-':
        case '.':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            double result;
            std::string offending;
            
            in_.unget();
            if(consumeDoubleLiteral(in_, result, offending))
            {
                return token_ = Token::doubleToken(lineNo_, result);
            }
            else
            {
                return token_ = Token(TokenType::Invalid, lineNo_, offending.c_str());
            }
        }
        break;

        default:
        {
            std::string result;
            
            if(consumeIdentifierOrKeyword(in_, result))
            {
                return token_ = tokenFromIdentifier((char)ch + result, lineNo_);
            }
            
            // If we are here an unrecognized input is present.
            return token_ = Token(TokenType::Invalid, lineNo_, ((char)ch + result + consumeInvalid(in_)).c_str());
        }
        break;
        
        }
    }
    
    return token_ = Token(TokenType::Eof, lineNo_);
}
