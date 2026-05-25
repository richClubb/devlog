#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef int (*CallbackCInt)(void);

typedef bool (*CallbackBool)(void);

typedef struct ALibObject {
  CallbackCInt a_thing_1;
  CallbackCInt a_thing_2;
  CallbackBool check_func;
} ALibObject;

bool a_rust_function(void);

struct ALibObject init_lib(void);

int process(struct ALibObject obj);
