#ifndef _DRAW_DRAW_PLANE_H_
#define _DRAW_DRAW_PLANE_H_
#include<wx/glcanvas.h> 
#include<canvas.h>
#include<wx/frame.h>
#include<wx/wx.h>
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
#include<engine/eg_buildin.h>
#include<engine/eg_codger.h>
#include<engine/except.h>
}

class DrawPlane:public wxGLCanvas
{
	private:
		wxFrame* m_parent;
		wxString m_file_name;
		int m_draw;
		float m_i;
		GrString* m_s_width;
		GrString* m_s_height;
		EgThread* m_thread;
	public:
		DrawPlane(wxFrame* parent);
		void LoadFile(wxString& name);
		void OnPaint(wxPaintEvent& WXUNUSED(event))
		{
			Render();
		}
		void Render();
		void DrawScript();
};



#endif 

