PROJECT=syntax
SRC= ast_object.c node_literal.c  node_stmts.c \
	 node_uexpr.c node_bexpr.c node_var.c \
	 node_assign.c node_print.c node_while.c \
	 node_if.c node_array.c node_square.c \
	 node_for.c \
	 parser.c yylex.c grammar.tab.c ast_machine.c \
	 symbol_table.c 

DEBUG=
BIN=test_literal.c codger.c gcheck.c

CC=gcc
FLAGS=-g -Wall  -Werror -include sys/types.h  -D AST_MACHINE
INCLUDE=-I. -I./debug   -I../
LIB=-Llib -l$(PROJECT) -l$(PROJECT)debug -L../../lib -lutility_c  \
	-L../lib/ -lrtype -llexical -lvm -lrstd -lobject 



OBJ_NAME=$(SRC:%.c=%.o) 
OBJ_NAME_WITH_PATH=$(addprefix obj/,$(OBJ_NAME))

DEBUG_OBJ_NAME=$(DEBUG:%.c=%.o) 
DEBUG_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(DEBUG_OBJ_NAME))

ALL_OBJ=$(OBJ_NAME) $(DEBUG_OBJ_NAME)
ALL_OBJ_WITH_PATH= $(OBJ_NAME_WITH_PATH) $(DEBUG_OBJ_NAME_WITH_PATH)



BIN_NAME=$(BIN:%.c=%.exe)
BIN_NAME_WITH_PATH=$(addprefix bin/,$(BIN_NAME))

BIN_OBJ_NAME=$(BIN:%.c=%.o)
BIN_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(BIN_OBJ_NAME))




main: obj lib bin $(ALL_OBJ_WITH_PATH) $(BIN_OBJ_NAME_WITH_PATH) \
   	$(BIN_NAME_WITH_PATH)  lib/lib$(PROJECT).a

lib/lib$(PROJECT).a:$(OBJ_NAME_WITH_PATH) ../lib 
	ar cr $@ $(OBJ_NAME_WITH_PATH)
	cp $@ ../lib/

lib/lib$(PROJECT)debug.a:$(DEBUG_OBJ_NAME_WITH_PATH)
	ar cr $@ $(DEBUG_OBJ_NAME_WITH_PATH)


bin/%.exe:obj/%.o lib/lib$(PROJECT).a lib/lib$(PROJECT)debug.a 
	$(CC) $(FLAGS) -o $@ $< $(LIB)

obj/%.o:%.c
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE) 

obj/%.o:debug/%.c
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE) 
	
grammar.tab.c: grammar.y
	bison grammar.y
	
init:
	mkdir -p obj 
	mkdir -p bin
	mkdir -p lib
obj:
	mkdir -p obj
bin:
	mkdir -p bin
lib:
	mkdir -p lib 
../lib:
	mkdir -p ../lib 

rm:
	rm -f obj/*
	rm -f lib/*
	rm -f bin/*.exe
	rm -f ../lib/lib$(PROJECT).a
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

-include .$(PROJECT).dep
