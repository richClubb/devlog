# Notes on research

While reading up on the address and undefined behaviour sanitizers I found this page https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html which is a really good resource for understanding some of the instrumentation that is available in GCC

Especially interesting is the `-fhardened` 

It's frustrating that I've got so far in my career not knowing about this stuff and how good some of the optimisations can be. I wonder if a lot of Rust's benefits have actually been implemented in C already, or if there is very little for someone to create a similar "borrow checker" for C aplications.

