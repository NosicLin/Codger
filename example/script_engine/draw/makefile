PROJECT=draw

SRC= main.cc canvas.cc DrawPlane.cc

DEBUG=

BIN= 



OBJ_NAME=$(SRC:%.cc=%.o) 
OBJ_NAME_WITH_PATH=$(addprefix obj/,$(OBJ_NAME))

DEBUG_OBJ_NAME=$(DEBUG:%.cc=%.o) 
DEBUG_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(DEBUG_OBJ_NAME))

ALL_OBJ=$(OBJ_NAME) $(DEBUG_OBJ_NAME)
ALL_OBJ_WITH_PATH= $(OBJ_NAME_WITH_PATH) $(DEBUG_OBJ_NAME_WITH_PATH)



BIN_NAME=$(BIN:%.cc=%.exe)
BIN_NAME_WITH_PATH=$(addprefix bin/,$(BIN_NAME))

BIN_OBJ_NAME=$(BIN:%.cc=%.o)
BIN_OBJ_NAME_WITH_PATH=$(addprefix obj/,$(BIN_OBJ_NAME))

CC=g++
FLAGS=-g -Wall  `wx-config --cxxflags --libs`  \
	`wx-config --libs --cxxflags --gl-libs`

INCLUDE= -I. -I$(codger) -include sys/types.h
LIB= -lGL -lGLU -L$(codger)/lib -llexical -lsyntax -lengine -lobject \
	 -lmemory -lutility_c -lm -lextends
	




main: $(OBJ_NAME_WITH_PATH)
	$(CC) -o bin/$(PROJECT) $(OBJ_NAME_WITH_PATH) $(FLAGS) $(INCLUDE) \
		-Xlinker "-(" $(LIB) -Xlinker "-)" 
   
obj/%.o:%.cc
	$(CC) $(FLAGS) -c -o $@ $< $(INCLUDE) 
	
init:
	mkdir -p obj 
	mkdir -p bin
obj:
	mkdir -p obj
bin:
	mkdir -p bin
lib:
	mkdir -p lib 

rm:
	rm -f obj/*
	rm -f $(PROJECT)
clear:
	rm -rf obj 
	rm -rf $(PROJECT)

depend:
	echo -n >.$(PROJECT).dep
	for element in $(addprefix debug/,$(BIN)) $(SRC) $(addprefix debug/,$(DEBUG));do \
		file_name=`basename $$element`;\
		result=`echo $$file_name | sed -e 's/.c/.o/'`;\
		gcc $(FLAGS) -M -MT "obj/$$result" $$element $(INCLUDE) >>.$(PROJECT).dep ;\
	done

-include .$(PROJECT).dep

