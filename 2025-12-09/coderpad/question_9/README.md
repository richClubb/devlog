# Notes

This has a memory leak 

```
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_9$ gcc main.c
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_9$ ./a.out 
Value=42
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_9$ valgrind ./a.out 
==354406== Memcheck, a memory error detector
==354406== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==354406== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==354406== Command: ./a.out
==354406== 
Value=42
==354406== 
==354406== HEAP SUMMARY:
==354406==     in use at exit: 4 bytes in 1 blocks
==354406==   total heap usage: 2 allocs, 1 frees, 1,028 bytes allocated
==354406== 
==354406== LEAK SUMMARY:
==354406==    definitely lost: 4 bytes in 1 blocks
==354406==    indirectly lost: 0 bytes in 0 blocks
==354406==      possibly lost: 0 bytes in 0 blocks
==354406==    still reachable: 0 bytes in 0 blocks
==354406==         suppressed: 0 bytes in 0 blocks
==354406== Rerun with --leak-check=full to see details of leaked memory
==354406== 
==354406== For lists of detected and suppressed errors, rerun with: -s
==354406== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
ricclu@UKCARL-7LNZC44:~/personal/devlog/2025-12-09/coderpad/question_9$ 
```

this is probably detectable with `-fsanitize=address` as well.