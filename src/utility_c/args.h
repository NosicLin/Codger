#ifndef ARGS_H_
#define ARGS_H_



struct args 
{
	int num;
	char** parg;
};
#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus*/
struct args* create_args(char* buffer,const char* divide);
void free_args(struct args* arg);
#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
