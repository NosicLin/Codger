#include"DrawPlane.h"

DrawPlane::DrawPlane(wxFrame* parent)
	:wxGLCanvas(parent,wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
{
	this->Connect(wxEVT_PAINT,wxPaintEventHandler(DrawPlane::OnPaint));
	m_draw=false;
	m_i=0.0;
	m_parent=parent;

	GrString* s_setcolor=GrString_GcNewFlag("setColor",
			GRGC_HEAP_STATIC);
	GrString* s_drawpixel=GrString_GcNewFlag("drawPixel",
			GRGC_HEAP_STATIC);
	GrString* s_drawline=GrString_GcNewFlag("drawLine",
			GRGC_HEAP_STATIC);

	m_s_width=GrString_GcNewFlag("width",GRGC_HEAP_STATIC);
	m_s_height=GrString_GcNewFlag("height",GRGC_HEAP_STATIC);


	GrInnerFunc* f_drawLine=GrInnerFunc_GcNewFlag(
			(GrCFunc)drawLine,4,GRGC_HEAP_STATIC);

	GrInnerFunc* f_setcolor=GrInnerFunc_GcNewFlag(
			(GrCFunc) setColor,3,GRGC_HEAP_STATIC);
	GrInnerFunc* f_drawPixel=GrInnerFunc_GcNewFlag(
			(GrCFunc)drawPixel,2,GRGC_HEAP_STATIC);

	EgCodger_BuildinAdd((GrObject*)s_setcolor,(GrObject*)f_setcolor);
	EgCodger_BuildinAdd((GrObject*)s_drawpixel,(GrObject*)f_drawPixel);
	EgCodger_BuildinAdd((GrObject*)s_drawline,(GrObject*)f_drawLine);

	m_thread=EgThread_New();

}
void DrawPlane::LoadFile(wxString& name)
{
	m_file_name=name;
	wxPuts(wxT("file_name:")+m_file_name);
	m_draw=true;
	this->Refresh();
}
void DrawPlane::Render()
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
void DrawPlane::DrawScript()
{
	GrExcept_Clr();
	char name_buf[1000];
	strcpy(name_buf,m_file_name.mb_str(wxConvUTF8));
	GrModule* module=EgCodger_ParseFile(name_buf);
	if(module==NULL)
	{
		m_parent->SetStatusText(wxT("Can't Parse File: ")+m_file_name);
		return ;
	}
	GrInt* i_width=GrInt_GcNew(GetSize().x);
	GrInt* i_height=GrInt_GcNew(GetSize().y);

	EgCodger_BuildinAdd((GrObject*)m_s_width,(GrObject*)i_width);
	EgCodger_BuildinAdd((GrObject*)m_s_height,(GrObject*)i_height);

	EgSframe* sf=EgSframe_NewFromModule(module);
	EgThread_PushSframe(m_thread,sf);
	EgThread_Run(m_thread);
}





