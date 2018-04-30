/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_MACHINEDESC_TOKEN_HPP_INCLUDED
#define LSYS_MACHINEDESC_TOKEN_HPP_INCLUDED

#include <string>
#include <cassert>
#include <sstream>
#include <stdexcept>

#include "TokenType.hpp"

namespace lsys { namespace machinedesc {
            
class Token
{
public:
    static inline Token invalidToken()
    {
        return Token(TokenType::Invalid, -1);
    }

    /**
     * Used with tokens which has no data other than type.
     * lineNo specifies the line number this token encountered
     * in the input stream.
     */
    Token(TokenType::type type, int lineNo)
    : type_(type), lineNo_(lineNo)
    {
    }

    /**
     * Used for tokens containing a string value and a type.
     */
    Token(TokenType::type type, int lineNo, char const* value)
    : type_(type), lineNo_(lineNo)
    {
        strVal_ = value;
    }

    static inline Token doubleToken(int lineNo, double value)
    {
    	Token token(TokenType::DoubleLiteral, lineNo);

    	token.floatVal_ = value;

		std::ostringstream oss;
		oss << value;
		token.strVal_ = oss.str();

		return token;
    }

    /**
     * Get string value of the token.
     */
    std::string const& asString() const
    {
        return strVal_;
    }

    /**
     * Get integer value of the token.
     * The token type must be IntegerLiteral
     */
    int asInteger() const
    {
        assert(type_ == TokenType::IntegerLiteral);
        return intVal_;
    }

    double asFloat() const
    {
        assert(type_ == TokenType::DoubleLiteral);
        return floatVal_;
    }

    inline int getLineNo() const
    {
        return lineNo_;
    }

    inline TokenType::type getType() const
    {
        return type_;
    }

#include "Token.gen.hpp"

private:
    TokenType::type type_;
    std::string strVal_;
    int intVal_;
    double floatVal_;
    int lineNo_;
};

inline bool operator==(Token const& lhs, Token const& rhs)
{
    return lhs.asString() == rhs.asString();
}

} } // namespace machinedesc / lsys

#endif
