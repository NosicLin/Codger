#ifndef _DRAW_FILE_LIST_H_
#define _DRAW_FILE_LIST_H_
#include<vector>
#include<wx/listctrl.h>
#include<wx/string.h>
#include<wx/dir.h>
#include"DrawPlane.h"
#include<wx/panel.h>
#include<wx/dynarray.h>

using namespace std;

class FileList:public wxPanel
{
	private:
		DrawPlane* m_draw_plane;
		wxString m_dir;
		wxListCtrl* m_list;
		vector<wxString>* m_files;

		wxFrame* m_parent;

		wxButton* m_brefresh;
		wxButton* m_bshow;

	public:
		FileList(wxFrame* parent,DrawPlane* draw_plane)
			:wxPanel(parent,-1)
		{
			m_parent=parent;
			int bshow_id=wxNewId();
			int brefresh_id=wxNewId();

			m_draw_plane=draw_plane;
			m_list=new wxListCtrl(this,-1);
			m_brefresh=new wxButton(this,brefresh_id,wxT("Refresh"));
			m_bshow=new wxButton(this,bshow_id,wxT("Run"));
			wxBoxSizer* vsizer=new wxBoxSizer(wxVERTICAL);
   			wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);

			hsizer->Add(m_brefresh,1,wxALIGN_LEFT);
			hsizer->Add(m_bshow,1,wxALIGN_RIGHT);
			vsizer->Add(m_list,1,wxEXPAND);
			vsizer->Add(hsizer,0,wxEXPAND);
			this->SetSizer(vsizer);
			this->SetAutoLayout(true);

			this->Connect(brefresh_id,wxEVT_COMMAND_BUTTON_CLICKED,
 					wxCommandEventHandler(FileList::OnRefresh));
			this->Connect(bshow_id,wxEVT_COMMAND_BUTTON_CLICKED,
					wxCommandEventHandler(FileList::OnShow));

			m_files=new vector<wxString>();

		}
		void SetDir(wxString dir)
		{
			m_dir=dir;
		}
		void OnRefresh(wxCommandEvent& event)
		{
			m_list->ClearAll();
			m_files->clear();
			wxDir dir(m_dir);
			wxString file;
			bool cont=dir.GetFirst(&file,wxEmptyString,wxDIR_FILES);
			int i=0;
			while(cont)
			{
				if(file.EndsWith(wxT(".gr")))
				{
					m_list->InsertItem(i,file);
					m_files->push_back(file);
					i++;
				}

				cont=dir.GetNext(&file);
			}
		}
		void OnShow(wxCommandEvent& event)
		{
			long item=-1;
			item=m_list->GetNextItem(item,
					wxLIST_NEXT_ALL,
					wxLIST_STATE_SELECTED);
			if(item==-1)
			{
				
				m_parent->SetStatusText(wxT("Please Selected An Item"));
			}
			else
			{
				m_parent->SetStatusText(wxT("Run File: ")+m_files->at(item));
				m_draw_plane->LoadFile(m_files->at(item));
			}
		}
};

#endif 



