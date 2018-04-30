/**
 * This file is part of LSys.
 *
 * Copyright (C) 2010 Emir Uner
 */
#ifndef LSYS_MACHINEDESC_HPP_INCLUDED
#define LSYS_MACHINEDESC_HPP_INCLUDED

#include <lsys/machinedesc/Token.hpp>
#include <lsys/machinedesc/CharBuffer.hpp>

namespace lsys { namespace machinedesc {                     
            
/**
 * Analyzes the given input stream and return a stream
 * of tokens. Supports one token push back capability.
 */
class Lexer
{
public:
    /**
     * Construct a lexer that uses the given stream as source.
     */
    Lexer(std::istream& in, std::string filename);
    
    /**
     * Get next token.
     * Returns Eof token when end of file reached and
     * throws std::runtime_error when encounters an error.
     */
    Token getNextToken();

    /**
     * Return the next token. If an invalid token encountered or EOF
     * std::runtime_error is thrown.
     */
    Token expectAnyToken();
    
    /**
     * Return the next token. If and error occurs or the next token is not
     * one of the given types throw exception.
     */
    Token expectToken(TokenType::type t);
    Token expectToken(TokenType::type t1, TokenType::type t2);

    /**
     * Raise an exception prepending the filename and line number and
     * appending token string with the associated token to the given message.
     * This method can be used by other object to report an error at a
     * specified position in the token stream.
     */
    void raiseError(std::string message, Token const& offending) const;
    
    /**
     * Read and discard incoming token. If an error occurs or the next token
     * is not one of the given types throw exception.
     */
    void discardToken(TokenType::type t);
    
    /**
     * Pre-condition state accessor.
     *
     * bool pushedBack() const
     * {
     *     return pushedBack_;
     * }
     */

    /**
     * Push back last read token.
     *
     * @pre pushedBack() == false
     */
    void ungetToken();

    /**
     * Get current line number.
     */
    inline int getLineNumber() const
    {
        return lineNo_;
    }

    /**
     * Get the name of the file.
     */
    inline std::string const& getFilename() const
    {
        return filename_;
    }

    /**
     * Get a reference to the input stream of the lexer.
     */
    inline std::istream const& getStream() const
    {
        return inStream_;
    }
    
private:
    std::istream& inStream_;
    CharBuffer in_;
    std::string filename_;
    int lineNo_;
    bool pushedBack_;
    Token token_;
};
 
} } // namespace machinedesc / lsys

#endif
