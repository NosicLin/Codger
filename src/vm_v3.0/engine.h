#ifndef _CODGER_VM_ENGINE_H_
#define _CODGER_VM_ENGINE_H_
struct module_object;
struct stack_frame;

int engine_init();
int engine_exit();
int engine_run();

int engine_push(struct  stack_frame* s);
struct stack_frame* engine_pop();
struct robject;
struct robject* stack_data_pop();

#endif 

