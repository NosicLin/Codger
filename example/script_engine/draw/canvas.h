#ifndef _DRAW_CANVAS_H_
#define _DRAW_CANVAS_H_
extern "C" {
#include<object/gr_object.h>
#include<object/gr_array.h>
#include<object/gr_object.h>
#include<object/gr_consts.h>
#include<object/gr_int.h>
#include<object/gr_module.h>
//#include<object/gr_float.h>
#include<engine/except.h>
}

GrObject* setColor(GrObject* host,GrArray* args);
GrObject* drawPixel(GrObject* host,GrArray* args);
GrObject* drawLine(GrObject* host,GrArray* args);

#endif 



