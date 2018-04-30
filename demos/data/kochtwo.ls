generator main
{
    setDivisor 4
    setAngleStep 90

    call F
    turnCCW
    call F
    turnCCW
    call F
    turnCCW
    call F
}

generator F
{
    call F
    call F
    turnCCW
    call F
    turnCCW
    call F
    turnCCW
    call F
    turnCCW
    call F
    call F
}
