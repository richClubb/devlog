# Things I got wrong

I assumed that they wouldn't give me a trick question. I thought it was incorrect but assumed that it was fine. If it had been multiple choice I would have answered invalid / segfault

# How to fix it

```
#include <stdio.h>
#include <stdlib.h>

void set_42(int* p_value)
{
    *p_value = 42;
}

int set_number(void)
{
    int *p_value = (int *)calloc(1, sizeof(int));

    set_42(p_value);

    return *p_value;
}

int main(int argc, char *argv[])
{
    printf("value=%d\n", set_number());
    return 0;
}
```

This results in a memory leak which is detectable with `-fsanitize=address`

The condition would be detectable with `-fsanitize=address` or `-fsanitize=undefined` the latter was a much better detection.

## BAD THING

```
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ gcc -fsanitize=address main.c
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ ./a.out 
AddressSanitizer:DEADLYSIGNAL
=================================================================
==350371==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x652c5615522b bp 0x7ffdb119fe20 sp 0x7ffdb119fe10 T0)
==350371==The signal is caused by a READ memory access.
==350371==Hint: this fault was caused by a dereference of a high value address (see register values below).  Disassemble the provided pc to learn which register was used.
    #0 0x652c5615522b in set_42 (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x122b) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #1 0x652c56155274 in set_number (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x1274) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #2 0x652c561552cb in main (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x12cb) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)
    #3 0x755a8582a1c9 in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #4 0x755a8582a28a in __libc_start_main_impl ../csu/libc-start.c:360
    #5 0x652c56155144 in _start (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x1144) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/ricclu/personal/devlog/2025-12-09/coderpad/question_8/a.out+0x122b) (BuildId: 454fdf23556dbc9131686d122c720dfb59594fe4) in set_42
==350371==ABORTING
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ gcc -fsanitize=undefined main.c
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ ./a.out 
main.c:6:14: runtime error: store to misaligned address 0x6c6f6f705f68652e for type 'int', which requires 4 byte alignment
0x6c6f6f705f68652e: note: pointer points here
<memory cannot be printed>
Segmentation fault (core dumped)
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ gcc -fsanitize=undefined,address main.c
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ ./a.out 
value=42
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ valgrind ./a.out 
==350678== Memcheck, a memory error detector
==350678== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==350678== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==350678== Command: ./a.out
==350678== 
==350678==ASan runtime does not come first in initial library list; you should either link runtime to your application or manually preload it with LD_PRELOAD.
==350678== 
==350678== HEAP SUMMARY:
==350678==     in use at exit: 0 bytes in 0 blocks
==350678==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==350678== 
==350678== All heap blocks were freed -- no leaks are possible
==350678== 
==350678== For lists of detected and suppressed errors, rerun with: -s
==350678== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_8$ 
```

This is super strange behaviour and I can't really explain it. The use of both `-fsanitize=address,undefined` causes weird unexpected behaviour where it actually allocates the memory and frees it correctly.