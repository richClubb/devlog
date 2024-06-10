Functional Programming Experiments
----------------------------------

This came out of a debate on how best to handle certain exception handling cases


# XOR Swapping 

This works for swapping 2 integer variables, but won't work for floats (without some intermediate steps) because of the way they are encoded, but works very quickly for ints.

This can be useful in situations where you don't want to create an intermediate variable.

```python
a = 10
b = 15
a = a ^ b
b = a ^ b
a = a ^ b
```

I set out 2 examples, `c_control` which is a control example using an intermediate variable `c` and `c_example` which uses the C `^` operator to perform the 3 XOR examples.

Getting the intermediate assembler using the `gcc -S main.c swap_c_assembly.s` shows that this only saves 3 lines, and at least one of these could be removed by not clearing a variable, but I don't currently have an example on how much this saves in terms of cycles. It would probably be minimal as all of the instructions are pretty basic.