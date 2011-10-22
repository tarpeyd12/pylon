/***************************************************************
 * Name:      bloopMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2011-06-23
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef BLOOPMAIN_H
#define BLOOPMAIN_H

#include <string.h>
#include <sstream>

//(*Headers(bloopFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/html/htmlwin.h>
#include <wx/statusbr.h>
//*)

wxString str(const char* );
wxString str(std::string );
std::string str(wxString );

void print(std::string s);
void print_ai(std::string s);
void setStatus(std::string s);
void clear_output();

#define s(a) str(a)

class bloopFrame: public wxFrame
{
    public:

        bloopFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~bloopFrame();

    private:

        //(*Handlers(bloopFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbuttonRUNClick(wxCommandEvent& event);
        void OncheckboxEnableArchivingClick(wxCommandEvent& event);
        void OnchecklistFilesToggled(wxCommandEvent& event);
        void OnchecklistFilesSelect(wxCommandEvent& event);
        void OnchecklistFilesDClick(wxCommandEvent& event);
        void OnbuttonBrowseDirClick(wxCommandEvent& event);
        void OntextPathDirTextEnter(wxCommandEvent& event);
        //*)

        //(*Identifiers(bloopFrame)
        static const long ID_STATICTEXT1;
        static const long idTextInitFile;
        static const long ID_STATICTEXT2;
        static const long idTextMainFile;
        static const long ID_STATICTEXT3;
        static const long idTextExtractDir;
        static const long ID_STATICTEXT4;
        static const long idTextWindowName;
        static const long ID_STATICTEXT5;
        static const long idTextWindowWidth;
        static const long ID_STATICTEXT6;
        static const long idTextWindowHeight;
        static const long idCheckboxEnableArchiving;
        static const long idTextArchiveList;
        static const long idPanelConfiguration;
        static const long idTextPathDir;
        static const long idButtonBrowseDir;
        static const long ID_PANEL1;
        static const long idChecklistFiles;
        static const long ID_BUTTON1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON2;
        static const long ID_BUTTON4;
        static const long ID_PANEL2;
        static const long ID_NOTEBOOK2;
        static const long idPanelFiles;
        static const long ID_STATICTEXT7;
        static const long idTextPathToPylonExe;
        static const long ID_STATICTEXT9;
        static const long idTextPathToPylonDLL;
        static const long ID_STATICTEXT8;
        static const long idTextPathToGameFile;
        static const long ID_STATICTEXT10;
        static const long idTextEditorCMD;
        static const long ID_STATICTEXT11;
        static const long idText3dEditorCMD;
        static const long ID_STATICTEXT12;
        static const long idTextZipProgram;
        static const long idPannelSettings;
        static const long idHtmlOutput;
        static const long idPanelOutput;
        static const long idTextFileToSaveTo;
        static const long idButtonSaveButton;
        static const long idButtonSaveAs;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long idPanelSave;
        static const long idChecklistRunTimeOptions;
        static const long idTextOtherRunTimeOptions;
        static const long idButtonRUN;
        static const long idPanelRun;
        static const long ID_NOTEBOOK1;
        static const long ID_STATUSBAR;
        //*)

        //(*Declarations(bloopFrame)
        wxStaticText* StaticText10;
        wxTextCtrl* textPathToGameFile;
        wxStaticText* StaticText9;
        wxButton* buttonBrowseDir;
        wxTextCtrl* textPathDir;
        wxTextCtrl* textFileToSaveTo;
        wxPanel* panelOutput;
        wxButton* buttonSaveButton;
        wxButton* Button4;
        wxNotebook* Notebook1;
        wxTextCtrl* textOtherRunTimeOptions;
        wxTextCtrl* textPathToPylonDLL;
        wxTextCtrl* textWindowHeight;
        wxStaticText* StaticText2;
        wxTextCtrl* textMainFile;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxHtmlWindow* htmlOutput;
        wxTextCtrl* textZipProgram;
        wxButton* buttonRUN;
        wxTextCtrl* textArchiveList;
        wxTextCtrl* text3dEditorCMD;
        wxStaticText* StaticText8;
        wxStaticText* StaticText11;
        wxTextCtrl* textWindowWidth;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxPanel* panelSettings;
        wxTextCtrl* textEditorCMD;
        wxCheckListBox* checklistRunTimeOptions;
        wxStaticText* StaticText3;
        wxButton* Button2;
        wxTextCtrl* textExtractDir;
        wxButton* Button6;
        wxButton* Button5;
        wxPanel* panelConfiguration;
        wxButton* Button3;
        wxTextCtrl* textWindowName;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxDirDialog* DirDialog1;
        wxPanel* panelRun;
        wxCheckBox* checkboxEnableArchiving;
        wxTextCtrl* textInitFile;
        wxTextCtrl* textPathToPylonExe;
        wxTextCtrl* TextCtrl1;
        wxCheckListBox* checklistFiles;
        wxStaticText* StaticText12;
        wxPanel* panelSave;
        wxPanel* Panel2;
        wxButton* buttonSaveAs;
        wxPanel* panelFiles;
        wxNotebook* Notebook2;
        wxStaticText* StaticText4;
        wxStatusBar* StatusBar;
        //*)

        friend wxString str(const char* );
        friend void print(std::string s);
        friend void print_ai(std::string s);
        friend void setStatus(std::string s);
        friend void clear_output();
        friend class outbuf;

        DECLARE_EVENT_TABLE()
};

extern bloopFrame* ___bloopFrame;

#endif // BLOOPMAIN_H
