generator D
{
    call D
    call D
}

generator L
{
    call D
    pushPos
    turnCW
    callOrNoOp L
    popPos
    call D
    pushPos
    turnCCW
    callOrNoOp L
    popPos
    turnCW
    callOrNoOp L
}

generator main
{
    setDivisor 2
    setAngleStep 22.5
    
    call L
}

