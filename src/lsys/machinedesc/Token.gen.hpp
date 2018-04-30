    inline bool isInvalid() const
    {
        return TokenType::Invalid == type_;
    }

    inline bool isEof() const
    {
        return TokenType::Eof == type_;
    }

    inline bool isComma() const
    {
        return TokenType::Comma == type_;
    }

    inline bool isSemicolon() const
    {
        return TokenType::Semicolon == type_;
    }

    inline bool isLParen() const
    {
        return TokenType::LParen == type_;
    }

    inline bool isRParen() const
    {
        return TokenType::RParen == type_;
    }

    inline bool isLCurly() const
    {
        return TokenType::LCurly == type_;
    }

    inline bool isRCurly() const
    {
        return TokenType::RCurly == type_;
    }

    inline bool isLessThan() const
    {
        return TokenType::LessThan == type_;
    }

    inline bool isGreaterThan() const
    {
        return TokenType::GreaterThan == type_;
    }

    inline bool isDoubleLiteral() const
    {
        return TokenType::DoubleLiteral == type_;
    }

    inline bool isStringLiteral() const
    {
        return TokenType::StringLiteral == type_;
    }

    inline bool isIntegerLiteral() const
    {
        return TokenType::IntegerLiteral == type_;
    }

    inline bool isIdentifier() const
    {
        return TokenType::Identifier == type_;
    }

    inline bool isCall() const
    {
        return TokenType::Call == type_;
    }

    inline bool isCallOrNoOp() const
    {
        return TokenType::CallOrNoOp == type_;
    }

    inline bool isTurnBy() const
    {
        return TokenType::TurnBy == type_;
    }

    inline bool isGenerator() const
    {
        return TokenType::Generator == type_;
    }

    inline bool isTurnCW() const
    {
        return TokenType::TurnCW == type_;
    }

    inline bool isTurnCCW() const
    {
        return TokenType::TurnCCW == type_;
    }

    inline bool isPushPos() const
    {
        return TokenType::PushPos == type_;
    }

    inline bool isPopPos() const
    {
        return TokenType::PopPos == type_;
    }

    inline bool isSetDivisor() const
    {
        return TokenType::SetDivisor == type_;
    }

    inline bool isSetAngleStep() const
    {
        return TokenType::SetAngleStep == type_;
    }

