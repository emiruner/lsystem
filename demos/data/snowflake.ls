//
// Machine starts with:
//     - Turned with 90 degree north
//     - At position (0, 0)
//

generator main
{
    setDivisor 3
    setAngleStep 60
    
    turnBy 90
    call D
    turnCCW
    turnCCW
    call D
    turnCCW
    turnCCW
    call D
}

generator D
{
    call D
    turnCW
    call D
    turnCCW
    turnCCW
    call D
    turnCW
    call D
}

!divisor 2
!angleStep 90

generator S { F-F-F-F }
generator F { F+FF-FF-F-F+F+FF-F-F+F+FF+FF-F }

-------

!divisor 10
!angleStep 90

generator S { L }
generator L { L+R+ }
generator R { -L-R }
