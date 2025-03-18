namespace fsharp_int_math

open System

module IntMath  =
    let add (a: byte, b: byte): byte = 
        if ((int)255 - (int)a) < (int)b then (byte)255
        else a + b

    let sub (a: byte, b: byte): byte =
        if (b > a) then (byte)0
        else a - b
