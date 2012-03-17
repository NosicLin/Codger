PROJECT=rtype
SRC=big_integer.c bt_int.c bt_float.c bt_long.c bt_common.c \
	rtype.c robject.c
DEBUG=gen_lib.c 
BIN=bg_bin.c bg_oct.c bg_dec.c bg_hex.c  bg_expr.c  bg_expr2.c \
	gen_expr.c gen_expr2.c  gen_bits.c gen_bits2.c \
	gen_shift.c gen_shift2.c gen_div.c  gen_div2.c \
	gen_cmp2.c  gen_bl_str.c \
	bi_str_to_int.c  bg_to_float.c bl_from_str.c rtype_unit_test.c



OBJ_NAME=$(SRC:%.c=%.o) $(DEBUG:%.c=%.o)
OBJ_NAME_WITH_PATH=$(addprefix obj/,$(OBJ_NAME))

BIN_NAME=$(BIN:%.c=%.exe)
BIN_NAME_WITH_PATH=$(addprefix bin/,$(BIN_NAME))

BIN_OBJ_NAME=$(BIN:%.c=%.o)
BIN_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(BIN_OBJ_NAME))

CC=gcc
FLAGS=-g -Wall  -Werror
INCLUDE=-I. -I./debug  -I../../
LIB=-Llib -l$(PROJECT) -L../../lib -lutility_c




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
	rm -f bin/*.exe
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
