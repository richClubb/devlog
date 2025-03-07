# Language Interop 

The objective of this is to get a handle on using different languages from other languages to make sure that I understand how to interop.

If you have a project that wants to use a different language this shouldn't be a barrier. There are the obvious solutions of using them as different services and using an API to call between them but if you want more native interop then this should provide a guide for each language

## Objectives

* Each language should call the libraries of each other language
* All links and guides should be referenced for further use.
* Try to use the documentation for each project before going for a more general search

## Library Interop

|            | **C**      | **C++**    | **C#**     | **Python** | **Rust**   | **Erlang?** |   **F#?**   |
|------------|:----------:|:----------:|:----------:|:----------:|:----------:|:-----------:|:-----------:|
| **C**      | Done       | Done       | Done       | Done       | -          | -           | -           |
| **C++**    | Done       | Done       | Done       | Done       | -          | -           | -           |
| **C#**     | -          | -          | Done       | -          | -          | -           | -           |
| **Python** | -          | -          | -          | -          | -          | -           | -           |
| **Rust**   | -          | -          | -          | -          | -          | -           | -           |
| **Erlang** | -          | -          | -          | -          | -          | -           | -           |
| **F#**     | -          | -          | -          | -          | -          | -           | -           |

## Tests

| Test Type  | **C**      | **C++**    | **C#**     | **Python** | **Rust**   | **Erlang** |   **F#**   |
|------------|:----------:|------------|------------|------------|------------|------------|------------|
| Unit Tests | cunit      | cunit      | mstest     | -          | -          | -          | -          |