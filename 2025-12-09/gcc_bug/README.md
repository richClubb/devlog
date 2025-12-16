# GCC Bug

This is to document the GCC bug I've found with using `-fsanitize=address,undefined` actually hiding a bug with a value being set to an uninitialised pointer.

Expected
```
gcc main.c
./a.out
Segmentation fault (core dumped)
```

Expected
```
gcc -fsanitize=address main.c
./a.out 
AddressSanitizer:DEADLYSIGNAL
=================================================================
==509180==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x5ab6fb04622b bp 0x7ffe6597a930 sp 0x7ffe6597a920 T0)
==509180==The signal is caused by a READ memory access.
==509180==Hint: this fault was caused by a dereference of a high value address (see register values below).  Disassemble the provided pc to learn which register was used.
    #0 0x5ab6fb04622b in set_42 (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x122b) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #1 0x5ab6fb046274 in set_number (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x1274) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #2 0x5ab6fb0462cb in main (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x12cb) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #3 0x7a191602a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x7a191602a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x5ab6fb046144 in _start (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x1144) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x122b) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4) in set_42
==509180==ABORTING
```

Expected
```
gcc -fsanitize=undefined main.c
./a.out 
main.c:6:14: runtime error: store to misaligned address 0x6c6f6f705f68652e for type 'int', which requires 4 byte alignment
0x6c6f6f705f68652e: note: pointer points here
<memory cannot be printed>
Segmentation fault (core dumped)
```

Weird?
```
gcc -fsanitize=undefined,address main.c
./a.out 
value=42
```

Also Weird
```
gcc -fsanitize=undefined,address main.c
./a.out 
value=42
gcc -fsanitize=undefined,address -O0 main.c
./a.out 
value=42
gcc -fsanitize=undefined,address -O1 main.c
./a.out 
main.c:6:14: runtime error: store to null pointer of type 'int'
AddressSanitizer:DEADLYSIGNAL
=================================================================
==513570==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x5f501274d25b bp 0x7ffcec8a3e90 sp 0x7ffcec8a3dd0 T0)
==513570==The signal is caused by a WRITE memory access.
==513570==Hint: address points to the zero page.
    #0 0x5f501274d25b in set_42 (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x125b) (BuildId: 124e287934aa295c7893923925896d7798800ae0)
    #1 0x5f501274d28d in set_number (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x128d) (BuildId: 124e287934aa295c7893923925896d7798800ae0)
    #2 0x5f501274d2d3 in main (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x12d3) (BuildId: 124e287934aa295c7893923925896d7798800ae0)
    #3 0x77dd7cc2a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x77dd7cc2a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x5f501274d164 in _start (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x1164) (BuildId: 124e287934aa295c7893923925896d7798800ae0)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x125b) (BuildId: 124e287934aa295c7893923925896d7798800ae0) in set_42
==513570==ABORTING
```

Changing
```
int *p_value;
```

to 

```
int *p_value = NULL;
```

```
gcc -fsanitize=address,undefined main.c
./a.out 
main.c:6:14: runtime error: store to null pointer of type 'int'
AddressSanitizer:DEADLYSIGNAL
=================================================================
==517599==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x57c97fc9f29c bp 0x7ffff8bafed0 sp 0x7ffff8bafec0 T0)
==517599==The signal is caused by a WRITE memory access.
==517599==Hint: address points to the zero page.
    #0 0x57c97fc9f29c in set_42 (/home/ricclu/personal/devlog/2025-12-09/gcc_bug/a.out+0x129c) (BuildId: 438e2b383856c9458779e5307742df75d4f90986)
    #1 0x57c97fc9f2c4 in set_number (/home/ricclu/personal/devlog/2025-12-09/gcc_bug/a.out+0x12c4) (BuildId: 438e2b383856c9458779e5307742df75d4f90986)
    #2 0x57c97fc9f343 in main (/home/ricclu/personal/devlog/2025-12-09/gcc_bug/a.out+0x1343) (BuildId: 438e2b383856c9458779e5307742df75d4f90986)
    #3 0x7ac75422a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x7ac75422a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x57c97fc9f164 in _start (/home/ricclu/personal/devlog/2025-12-09/gcc_bug/a.out+0x1164) (BuildId: 438e2b383856c9458779e5307742df75d4f90986)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/ricclu/personal/devlog/2025-12-09/gcc_bug/a.out+0x129c) (BuildId: 438e2b383856c9458779e5307742df75d4f90986) in set_42
==517599==ABORTING
```

Using `clang` doesn't have the same results. 