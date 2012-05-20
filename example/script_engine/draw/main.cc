#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/glcanvas.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include<wx/dir.h>
#include<wx/filefn.h>
#include"DrawPlane.h"
#include"FileList.h"

extern "C" {
#include<engine/eg_codger.h>
}
 
class MyApp: public wxApp
{
    wxFrame* m_frame;

	FileList* m_files;
	DrawPlane* m_plane;
public:
	virtual bool OnInit();
};
    
 
IMPLEMENT_APP(MyApp);

bool  MyApp::OnInit()
{
	if(EgCodger_ModuleInit()<0)
	{
		return false;
	}

	m_frame=new wxFrame(NULL,-1,wxT("Draw Script"),
			wxPoint(50,50),wxSize(800,600));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	m_plane=new DrawPlane(m_frame);
	m_files=new FileList(m_frame,m_plane);

	m_files->SetDir(wxGetCwd());
	//m_files->Refresh();

	sizer->Add(m_files, 2, wxEXPAND);
	sizer->Add(m_plane, 5, wxEXPAND);

	m_frame->SetSizer(sizer);
	m_frame->SetAutoLayout(true);
	m_frame->CreateStatusBar();

	m_frame->Show(true);
	m_files->ReloadFiles();

	return true;


}




