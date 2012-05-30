#ifndef _DRAW_FILE_LIST_H_
#define _DRAW_FILE_LIST_H_
#include<wx/listbox.h>
#include<wx/string.h>
#include<wx/dynarray.h>
#include<wx/dir.h>
#include<wx/treectrl.h>
#include"DrawPlane.h"
#include<wx/panel.h>
#include<wx/dynarray.h>
#include<vector>

using namespace std;
struct type_entry
{
	const char* show_name;
	const char* prefix;
};

const struct type_entry type_name[]=
{
	{
		"IFS",
		"ifs",
	},
	{
		"LSystem",
		"ls",
	},
	{
		"Julia",
		"julia",
	},
	{
		"TimeOut",
		"timeout",
	},
	{
		"NewTon",
		"newton",
	}


};

#define type_nu (sizeof(type_name)/sizeof(struct type_entry))

class FileList:public wxPanel
{
	private:
		DrawPlane* m_draw_plane;
		wxString m_dir;
		//wxListBox* m_list;
		wxTreeCtrl* m_tree;

		wxTreeItemId m_tree_root;
		wxTreeItemId m_tree_simple;

		vector<wxTreeItemId> m_category;

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

			for(unsigned int i=0;i<type_nu;i++)
			{
				wxTreeItemId id=m_tree->AppendItem(m_tree_root, wxString::FromAscii(type_name[i].show_name));
				m_category.push_back(id);
			}

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
			for(unsigned int i=0;i<type_nu;i++)
			{
				m_tree->DeleteChildren(m_category[i]);
			}
			m_tree->DeleteChildren(m_tree_simple);
			wxDir dir(m_dir);
			wxString file;
			bool cont=dir.GetFirst(&file,wxEmptyString,wxDIR_FILES);
			while(cont)
			{
				bool add=false;
				if(file.EndsWith(wxT(".gr")))
				{
					for(unsigned int i=0;i<type_nu;i++)
					{
						wxString prefix=wxString::FromAscii(type_name[i].prefix);
						prefix.MakeLower();
						if(file.StartsWith(prefix))
						{
							if(file.StartsWith(prefix+wxT("_")))
							{
								m_tree->AppendItem(m_category[i],file);
							}
							add=true;
						}
					}
					if(!add)
					{
						m_tree->AppendItem(m_tree_simple,file);
					}
				}

				cont=dir.GetNext(&file);
			}
			for(unsigned int i=0;i<type_nu;i++)
			{
				m_tree->SortChildren(m_category[i]);
			}
		}
		void OnShow(wxCommandEvent& event)
		{
			wxTreeItemId sel_id;
			sel_id=m_tree->GetSelection();

			wxString name=m_tree->GetItemText(sel_id);
			wxPuts(wxT("File")+name);
			for(unsigned int i=0;i<type_nu;i++)
			{
				if( name==wxString::FromAscii(type_name[i].prefix))
				{
					m_parent->SetStatusText(wxT("Please Selected An Script To Draw"));
					return ;
				}
			}

			if(name==wxT("")||name==wxT("Other"))
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



