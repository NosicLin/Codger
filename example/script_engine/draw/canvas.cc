#include"canvas.h"
#include<wx/glcanvas.h> 
#include<object/gr_float.h>
GrObject* drawLine(GrObject* host,GrArray* args)
{
	float pos[4];
	GrObject* cur;
	for(int i=0;i<4;i++)
	{
		cur=GrArray_Get(args,i);
		cur=GrObject_ToGrFloat(cur);
		if(cur==NULL)
		{
			return NULL;
		}
		pos[i]=((GrFloat*)cur)->f_value;

	}
	glBegin(GL_LINES);
	glVertex2f(pos[0],pos[1]);
	glVertex2f(pos[2],pos[3]);
	glEnd();
	return Gr_Object_Nil;

}





GrObject* drawPixel(GrObject* host,GrArray* args)
{
	GrObject* x=GrArray_Get(args,0);
	GrObject* y=GrArray_Get(args,1);
	float x_pos,y_pos;
	x=GrObject_ToGrFloat(x);
	if(x==NULL) return NULL;
	y=GrObject_ToGrFloat(y);
	if(y==NULL) return NULL;

	x_pos=((GrFloat*)x)->f_value;
	y_pos=((GrFloat*)y)->f_value;

	glBegin(GL_POINTS);
	glVertex2f(x_pos,y_pos);
	glEnd();

	return Gr_Object_Nil;
}
GrObject* setColor(GrObject* host,GrArray* args)
{
	float c[3];
	GrObject* cur;
	for(int i=0;i<3;i++)
	{
		cur=GrArray_Get(args,i);
		cur=GrObject_ToGrFloat(cur);
		if(cur==NULL)
		{
			return NULL;
		}
		c[i]=((GrFloat*)cur)->f_value;

	}
	glColor3f(c[0],c[1],c[2]);
	return Gr_Object_Nil;
}







