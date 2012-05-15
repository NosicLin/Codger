#include"canvas.h"
#include<wx/glcanvas.h> 
GrObject* drawLine(GrObject* host,GrArray* args)
{
	int pos[4];
	GrObject* cur;
	for(int i=0;i<4;i++)
	{
		cur=GrArray_Get(args,i);

		if(GrInt_Verify(cur))
		{
			pos[i]=((GrInt*)cur)->i_value;
		}
		/*
		else if(GrFloat_Verify(cur))
		{
			pos[i]=((GrFloat*)cur)->f_vaule;
		}
		*/
		else 
		{
			goto type_err;
		}
	}
	glBegin(GL_LINES);
	glVertex2i(pos[0],pos[1]);
	glVertex2i(pos[2],pos[3]);
	glEnd();
	return Gr_Object_Nil;
type_err:
	GrErr_TypeFormat("drawPixel Except Number");
	return Gr_Object_Nil;

}





GrObject* drawPixel(GrObject* host,GrArray* args)
{
	GrObject* x=GrArray_Get(args,0);
	GrObject* y=GrArray_Get(args,1);
	int x_pos,y_pos;
	if(GrInt_Verify(x))
	{
		x_pos=((GrInt*)x)->i_value;
	}
	/*
	   else if(GrFloat_Verify(x))
	   {
	   x_pos=((GrFloat*)x)->f_vaule;
	   }
	   */
	else 
	{
		goto type_err;
	}

	if(GrInt_Verify(y))
	{
		y_pos=((GrInt*)y)->i_value;
	}
	/*
	   else if(GrFloat_Verify(y))
	   {
	   y_pos=((GrFloat*)y)->f_vaule;
	   }
	   */
	else 
	{
		goto type_err;
	}
	//fprintf(stderr,"drawPixel x,y=(%d,%d)\n",x_pos,y_pos);
	glBegin(GL_POINTS);
	glVertex2i(x_pos,y_pos);
	glEnd();
	return Gr_Object_Nil;
type_err:
	GrErr_TypeFormat("drawPixel Except Number");
	return Gr_Object_Nil;
}
GrObject* setColor(GrObject* host,GrArray* args)
{
	GrObject* g_r=GrArray_Get(args,0);
	GrObject* g_g=GrArray_Get(args,1);
	GrObject* g_b=GrArray_Get(args,2);

	int r,g,b;
	if(GrInt_Verify(g_r))
	{
		r=((GrInt*)g_r)->i_value;
	}
	/*
	   else if(GrFloat_Verify(g_r))
	   {
	   r=((GrFloat*)g_r)->f_vaule;
	   }
	   */
	else 
	{
		goto type_err;
	}
	if(GrInt_Verify(g_g))
	{
		g=((GrInt*)g_g)->i_value;
	}
	/*
	   else if(GrFloat_Verify(g_g))
	   {
	   g=((GrFloat*)g_g)->f_vaule;
	   }
	   */
	else 
	{
		goto type_err;
	}
	if(GrInt_Verify(g_b))
	{
		b=((GrInt*)g_b)->i_value;
	}
	/*
	   else if(GrFloat_Verify(g_b))
	   {
	   b=((GrFloat*)g_b)->f_vaule;
	   }
	   */
	else 
	{
		goto type_err;
	}

	glColor3f((float)r/255,(float)g/255,(float)b/255);
	return Gr_Object_Nil;
type_err:
	GrErr_TypeFormat("setColor Except Number");
	return Gr_Object_Nil;
}







