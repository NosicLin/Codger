PROJECT=lexical
SRC=lexical.c sl_integer.c 
DEBUG=driver.c
BIN=main_t1.c main_t2.c

OBJ_NAME=$(SRC:%.c=%.o) $(DEBUG:%.c=%.o)
OBJ_NAME_WITH_PATH=$(addprefix obj/,$(OBJ_NAME))

BIN_NAME=$(BIN:%.c=%.exe)
BIN_NAME_WITH_PATH=$(addprefix bin/,$(BIN_NAME))

BIN_OBJ_NAME=$(BIN:%.c=%.o)
BIN_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(BIN_OBJ_NAME))

CC=gcc
FLAGS=-g -Wall
INCLUDE=-I. -I./debug  
LIB=-Llib -l$(PROJECT)




main: $(OBJ_NAME_WITH_PATH) $(BIN_OBJ_NAME_WITH_PATH)  $(BIN_NAME_WITH_PATH)

lib/lib$(PROJECT).a:$(OBJ_NAME_WITH_PATH)
	ar cr $@ $(OBJ_NAME_WITH_PATH)


bin/%.exe:obj/%.o lib/lib$(PROJECT).a
	$(CC) $(FLAGS) -o $@ $< $(LIB)

obj/%.o:%.c
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE) 

obj/%.o:debug/%.c
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE) 
	
	
init:
	mkdir -p obj 
	mkdir -p bin
	mkdir -p lib
rm:
	rm -f obj/*
	rm -f lib/*
	rm -f bin/*
clear:
	rm -rf obj 
	rm -rf bin 
	rm -rf lib 


depend:
	echo -n >.$(PROJECT).dep
	for element in $(addprefix debug/,$(BIN)) $(SRC) $(addprefix debug/,$(DEBUG));do \
		file_name=`basename $$element`;\
		result=`echo $$file_name | sed -e 's/.c/.o/'`;\
		gcc -M -MT "obj/$$result" $$element $(INCLUDE) >>.$(PROJECT).dep ;\
	done

include .$(PROJECT).dep
