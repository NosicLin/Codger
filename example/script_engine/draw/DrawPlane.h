#ifndef _DRAW_DRAW_PLANE_H_
#define _DRAW_DRAW_PLANE_H_
#include<wx/glcanvas.h> 
#include<canvas.h>
extern "C" {
#include<syntax/parser.h>
#include<syntax/yylex.h>
#include<object/gr_module.h>
#include<object/gr_opcode.h>
#include<object/gr_consts.h>
#include<object/gr_inner_func.h>
#include<object/gr_scope.h>
#include<memory/memory.h>
#include<memory/gc.h>
#include<engine/eg_thread.h>
#include<engine/eg_sframe.h>
#include<object/gr_int.h>
#include<memory/mem_base.h>
}

class DrawPlane:public wxGLCanvas
{
	private:
		wxString m_file_name;
		int m_draw;
		float m_i;
	public:
		DrawPlane(wxFrame* parent)
			:wxGLCanvas(parent,wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
		{
			this->Connect(wxEVT_PAINT,wxPaintEventHandler(DrawPlane::OnPaint));
			m_draw=false;
			m_i=0.0;

		}
		void LoadFile(wxString& name)
		{
			m_file_name=name;
			wxPuts(wxT("file_name:")+m_file_name);
			m_draw=true;
			this->Refresh();
		}

		void OnPaint(wxPaintEvent& WXUNUSED(event))
		{
			Render();
		}
		void Render()
		{
			SetCurrent();
			wxPaintDC(this);
			glClearColor(0,0,0,0);
			glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
			glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
			gluOrtho2D(0,(GLint)GetSize().x,0,(GLint)GetSize().y);
				glColor3f(1.0, 1.0, 1.0);
			if(m_draw)
			{
				DrawScript();
			} 
			glFlush();
			SwapBuffers();

		}
		void DrawScript()
		{
			fprintf(stderr,"Paint Begin\n");
			int ret;
			GrModule_GcInit();
			GrModule_IntInit();
			GrModule_ConstsInit();
			GrModule_ExceptInit();
			GrString* s_setcolor=GrString_GcNewFlag("setColor",
					GRGC_HEAP_STATIC);
			GrString* s_drawpixel=GrString_GcNewFlag("drawPixel",
					GRGC_HEAP_STATIC);
			GrString* s_drawline=GrString_GcNewFlag("drawLine",
					GRGC_HEAP_STATIC);
			GrString* s_width=GrString_GcNewFlag("width",GRGC_HEAP_STATIC);
			GrString* s_height=GrString_GcNewFlag("height",GRGC_HEAP_STATIC);



			GrInnerFunc* f_drawLine=GrInnerFunc_GcNewFlag(
					(GrCFunc)drawLine,4,GRGC_HEAP_STATIC);

			GrInnerFunc* f_setcolor=GrInnerFunc_GcNewFlag(
					(GrCFunc) setColor,3,GRGC_HEAP_STATIC);
			GrInnerFunc* f_drawPixel=GrInnerFunc_GcNewFlag(
					(GrCFunc)drawPixel,2,GRGC_HEAP_STATIC);
			GrInt* i_width=GrInt_GcNew(GetSize().x);
			GrInt* i_height=GrInt_GcNew(GetSize().y);

			GrScope* s=0;
			Scanner* sc=0;
			AstObject* root=0;
			GrModule* module=0;
			GrString* module_name=0;
			EgThread* thread=0;
			EgSframe* sf=0;
			char name_buf[1000];
			strcpy(name_buf,m_file_name.mb_str(wxConvUTF8));
			char* name=name_buf;
			sc=sc_create(name);
			if(sc==NULL)
			{
				fprintf(stderr,"Open file %s failed\n",name);
				goto error;
			}
			yl_set_scanner(sc);
			ret=yyparse();
			if(ret!=0)
			{
				fprintf(stderr,"parser <%s> failed\n",name);
				goto error;
			}

			AstPending_Clear();
			root=parser_get_root();
			module=Ast_ToModule(root);
			module_name=GrString_GcNewFlag("main",GRGC_HEAP_STATIC);

			if(module==NULL||module_name==NULL)
			{
				goto error;
			}
			GrModule_SetName(module,module_name);
			thread=EgThread_New();
			if(thread==NULL) goto error;

			sf=EgSframe_NewFromModule(module);
			if(sf==NULL) goto error;

			EgThread_PushSframe(thread,sf);
			s=sf->f_scope;
			GrScope_Map(s,(GrObject*)s_setcolor,(GrObject*)f_setcolor);
			GrScope_Map(s,(GrObject*)s_drawpixel,(GrObject*)f_drawPixel);
			GrScope_Map(s,(GrObject*)s_drawline,(GrObject*)f_drawLine);
			GrScope_Map(s,(GrObject*)s_width,(GrObject*)i_width);
			GrScope_Map(s,(GrObject*)s_height,(GrObject*)i_height);
			EgThread_Run(thread);
error:
			if(root) AstTree_Free(root);
			if(sc) sc_destory(sc);
			if(thread) EgThread_Delete(thread);
			GrModule_GcExit();
			printf("Paint Over\n");

		}
};



#endif 

