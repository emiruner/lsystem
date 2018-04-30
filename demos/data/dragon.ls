generator main
{
    setDivisor 2
    setAngleStep 90

    call L
}

generator L
{
    call L
    turnCW
    call R
    turnCW
}

generator R
{
    turnCCW
    call L
    turnCCW
    call R
}
