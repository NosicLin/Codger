#ifndef _DRAW_FILE_LIST_H_
#define _DRAW_FILE_LIST_H_
#include<wx/listbox.h>
#include<wx/string.h>
#include<wx/dir.h>
#include<wx/treectrl.h>
#include"DrawPlane.h"
#include<wx/panel.h>
#include<wx/dynarray.h>

using namespace std;

class FileList:public wxPanel
{
	private:
		DrawPlane* m_draw_plane;
		wxString m_dir;
		//wxListBox* m_list;
		wxTreeCtrl* m_tree;
		wxTreeItemId m_tree_root;
		wxTreeItemId m_tree_ifs;
		wxTreeItemId m_tree_ls;
		wxTreeItemId m_tree_simple;

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
			//m_list=new wxListBox(this,-1);

			m_tree=new wxTreeCtrl(this,-1);
			m_tree_root=m_tree->AddRoot(wxT("Scripts"));
			m_tree_ifs=m_tree->AppendItem(m_tree_root,wxT("IFS"));
			m_tree_ls=m_tree->AppendItem(m_tree_root,wxT("LSystem"));
			m_tree_simple=m_tree->AppendItem(m_tree_root,wxT("Other"));




			m_brefresh=new wxButton(this,brefresh_id,wxT("Refresh"));
			m_bshow=new wxButton(this,bshow_id,wxT("Run"));
			wxBoxSizer* vsizer=new wxBoxSizer(wxVERTICAL);
   			wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);

			hsizer->Add(m_brefresh,1,wxALIGN_LEFT);
			hsizer->Add(m_bshow,1,wxALIGN_RIGHT);
			vsizer->Add(m_tree,1,wxEXPAND);
			vsizer->Add(hsizer,0,wxEXPAND);
			this->SetSizer(vsizer);
			this->SetAutoLayout(true);

			this->Connect(brefresh_id,wxEVT_COMMAND_BUTTON_CLICKED,
 					wxCommandEventHandler(FileList::OnRefresh));
			this->Connect(bshow_id,wxEVT_COMMAND_BUTTON_CLICKED,
					wxCommandEventHandler(FileList::OnShow));


		}
		void SetDir(wxString dir)
		{
			m_dir=dir;
		}
		void OnRefresh(wxCommandEvent& event)
		{
			ReloadFiles();
		}
		void ReloadFiles()
		{
			m_tree->DeleteChildren(m_tree_ifs);
			m_tree->DeleteChildren(m_tree_ls);
			m_tree->DeleteChildren(m_tree_simple);
			wxDir dir(m_dir);
			wxString file;
			bool cont=dir.GetFirst(&file,wxEmptyString,wxDIR_FILES);
			while(cont)
			{
				if(file.EndsWith(wxT(".gr")))
				{
					if(file.StartsWith(wxT("ifs")))
					{
						if(file.StartsWith(wxT("ifs_")))
						{
							m_tree->AppendItem(m_tree_ifs,file);
						}
					}
					else if(file.StartsWith(wxT("ls")))
					{
						if(file.StartsWith(wxT("ls_")))
						{
							m_tree->AppendItem(m_tree_ls,file);
						}
					}
					else 
					{
						m_tree->AppendItem(m_tree_simple,file);

					}
				}

				cont=dir.GetNext(&file);
			}
		}
		void OnShow(wxCommandEvent& event)
		{
			wxTreeItemId sel_id;
			sel_id=m_tree->GetSelection();

			wxString name=m_tree->GetItemText(sel_id);
			wxPuts(wxT("File")+name);
			if(name==wxT("")||name==wxT("Scripts")||
				name==wxT("LSystem")||name==wxT("Other"))
			{
				
				m_parent->SetStatusText(wxT("Please Selected An Script To Draw"));
			}
			else
			{
				m_parent->SetStatusText(wxT("Run File: ")+name);
				m_draw_plane->LoadFile(name);
			}
		}
};

#endif 



