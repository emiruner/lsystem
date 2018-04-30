generator main
{
    setDivisor 4
    setAngleStep 90

    call F
    turnCW
    call F
    turnCW
    call F
    turnCW
    call F
}

generator F
{
    call F
    turnCW
    callOrNoOp X
    turnCCW
    call F
    call F
    turnCW
    call F
    turnCW
    call F
    call F
    turnCW
    call F
    callOrNoOp X
    turnCW
    call F
    call F
    turnCCW
    callOrNoOp X
    turnCW
    call F
    call F
    turnCCW
    call F
    turnCCW
    call F
    call F
    turnCCW
    call F
    callOrNoOp X
    turnCCW
    call F
    call F    
    call F
}

generator X
{
    callOrNoOp X
    callOrNoOp X
    callOrNoOp X
    callOrNoOp X
    callOrNoOp X
    callOrNoOp X
}
