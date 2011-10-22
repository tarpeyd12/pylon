/***************************************************************
 * Name:      bloopMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2011-06-23
 * Copyright:  ()
 * License:
 **************************************************************/

#include "bloopMain.h"
#include <wx/msgdlg.h>

bloopFrame* ___bloopFrame;

wxString str(const char* s)
{

    //size_t mbstowcs(wchar_t *dest, const char *src, size_t n);

    wchar_t* ws = new wchar_t[strlen(s)+1];

    mbstowcs(ws, s, strlen(s)+1);

    wxString ret = wxString(wxStdString(ws));

    delete ws;

    return ret;
}

wxString str(std::string s)
{
    return str(s.c_str());
}

std::string str(wxString s)
{
    char* cs = new char[s.length()+1];

    wcstombs(cs, s.c_str(), s.length()+1);

    std::string ret = std::string(cs);

    delete cs;

    return ret;
}

std::string fstring(const char* fmt, ...) {
	//char* tmpstr=(char*)malloc(sizeof(char)*1024*2); // create a temporary string of suffient size to handle this string
	char* tmpstr = new char[2048];
	char* output; // an empty string for later
	memset(tmpstr, '\0', 1024*2); // set the temporary string to all numm, as to avoid artifacts
	va_list args; // the argument list
	va_start(args, fmt); // initialize the argument list
	vsprintf(tmpstr, fmt, args); // take the format, and argument list and put it into the temporary string
	va_end(args);
	//output=(char*)malloc(sizeof(char)*(strlen(tmpstr)+1));
    output = new char[(strlen(tmpstr)+1)];
	memcpy(output, tmpstr, strlen(tmpstr)+1);
	//free(tmpstr);
	delete tmpstr;
	std::string ret(output);
	delete output;
	return ret;
};

unsigned int getOccurrencesInString(char c, std::string s) {
    unsigned int count = 0;
    for(unsigned int i = 0; i < s.length(); i++) if(s[i] == c) count++;
    return count;
};

std::string getStringComponentLevel(std::string startChar, bool firstInclusive, std::string endChar, bool lastInclusive, std::string s, std::string path_s)
{
    if( startChar.compare(endChar) == 0 || startChar.length() == 0 || endChar.length() == 0 || s.empty() || path_s.empty())
        return "";
    std::stringstream path(std::stringstream::in | std::stringstream::out); path << path_s;
    unsigned int numEndChars = 0;
    for(unsigned int i = 0; i < endChar.length(); i++)
         numEndChars += getOccurrencesInString(endChar[i], s);
    if(numEndChars == 0) return "";
    unsigned int level = 0, levelocc = 0, branchpos = 0, branch; path >> branch;
    bool isschr = false, isechr = false;
    unsigned int chlen = (startChar.length() > endChar.length() ? startChar.length() : endChar.length());
    for(unsigned int i = 0; i < s.length(); i++) {
        isschr = isechr = false;
        for(unsigned int p = 0; p < chlen; p++)
            if(p < startChar.length() && s[i] == startChar[p]) isschr = true;
            else if(p < endChar.length() && s[i] == endChar[p]) isechr = true;
        if(isschr && level++ == branchpos && levelocc++ >= branch) {
            branchpos++; levelocc = 0;
            if(path.good()) path >> branch;
            else for(unsigned int g = i; i < s.length(); i++) {
                bool uisschr = false, uisechr = false;
                for(unsigned int p = 0; p < chlen; p++)
                    if(p < startChar.length() && s[i] == startChar[p]) uisschr = true;
                    else if(p < endChar.length() && s[i] == endChar[p]) uisechr = true;
                if(uisschr) level++;
                else if(uisechr && level-- == branchpos+1)
                    return s.substr(g+(firstInclusive?0:1), i-g+(lastInclusive?1:0)-1);
            }
        }
        if(isechr) { level--; if(--numEndChars <= 0) return ""; }
    }
    return "";
}

std::string getStringComponentLevelNoMore(std::string startChar, bool firstInclusive, std::string endChar, bool lastInclusive, std::string s, std::string path_s)
{
    std::string level_str = getStringComponentLevel(startChar,firstInclusive,endChar,lastInclusive,s,path_s);
    unsigned int level = 0, beg = 0;
    for(unsigned int i = 0; i < level_str.length(); i++) {
        for(unsigned int p = 0; p < startChar.length(); p++)
            if(level_str[i] == startChar[p] && level++ == 0) beg = i;
        for(unsigned int p = 0; p < endChar.length(); p++) if(level_str[i] == endChar[p] && --level == 0) {
            level_str = level_str.substr(0,beg) + level_str.substr(i+1);
            i = beg = 0;
        }
    }
    return level_str;
}

void print(std::string s)
{
    wxString ws = str(s);
    ___bloopFrame->htmlOutput->AppendToPage(s("<br><font size=\"3\">" + s + "</font></ul>"));
    ___bloopFrame->StatusBar->SetStatusText(str(getStringComponentLevelNoMore("<",false,">",false,"<"+s+">","0")), 0);
    //___bloopFrame->StatusBar->SetStatusText(str(s), 0);
    ___bloopFrame->htmlOutput->Scroll(0,___bloopFrame->htmlOutput->GetScrollLines(0));
}

void print_ai(std::string s)
{
    ___bloopFrame->htmlOutput->AppendToPage(str(s));
    //___bloopFrame->StatusBar->SetStatusText(str(s));
    ___bloopFrame->htmlOutput->Scroll(0,___bloopFrame->htmlOutput->GetScrollLines(0));
}

void setStatus(std::string s)
{
    ___bloopFrame->StatusBar->SetStatusText(str(s));
}

void clear_output()
{
    ___bloopFrame->htmlOutput->SetPage(str(""));
}

//(*InternalHeaders(bloopFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(bloopFrame)
const long bloopFrame::ID_STATICTEXT1 = wxNewId();
const long bloopFrame::idTextInitFile = wxNewId();
const long bloopFrame::ID_STATICTEXT2 = wxNewId();
const long bloopFrame::idTextMainFile = wxNewId();
const long bloopFrame::ID_STATICTEXT3 = wxNewId();
const long bloopFrame::idTextExtractDir = wxNewId();
const long bloopFrame::ID_STATICTEXT4 = wxNewId();
const long bloopFrame::idTextWindowName = wxNewId();
const long bloopFrame::ID_STATICTEXT5 = wxNewId();
const long bloopFrame::idTextWindowWidth = wxNewId();
const long bloopFrame::ID_STATICTEXT6 = wxNewId();
const long bloopFrame::idTextWindowHeight = wxNewId();
const long bloopFrame::idCheckboxEnableArchiving = wxNewId();
const long bloopFrame::idTextArchiveList = wxNewId();
const long bloopFrame::idPanelConfiguration = wxNewId();
const long bloopFrame::idTextPathDir = wxNewId();
const long bloopFrame::idButtonBrowseDir = wxNewId();
const long bloopFrame::ID_PANEL1 = wxNewId();
const long bloopFrame::idChecklistFiles = wxNewId();
const long bloopFrame::ID_BUTTON1 = wxNewId();
const long bloopFrame::ID_BUTTON3 = wxNewId();
const long bloopFrame::ID_BUTTON2 = wxNewId();
const long bloopFrame::ID_BUTTON4 = wxNewId();
const long bloopFrame::ID_PANEL2 = wxNewId();
const long bloopFrame::ID_NOTEBOOK2 = wxNewId();
const long bloopFrame::idPanelFiles = wxNewId();
const long bloopFrame::ID_STATICTEXT7 = wxNewId();
const long bloopFrame::idTextPathToPylonExe = wxNewId();
const long bloopFrame::ID_STATICTEXT9 = wxNewId();
const long bloopFrame::idTextPathToPylonDLL = wxNewId();
const long bloopFrame::ID_STATICTEXT8 = wxNewId();
const long bloopFrame::idTextPathToGameFile = wxNewId();
const long bloopFrame::ID_STATICTEXT10 = wxNewId();
const long bloopFrame::idTextEditorCMD = wxNewId();
const long bloopFrame::ID_STATICTEXT11 = wxNewId();
const long bloopFrame::idText3dEditorCMD = wxNewId();
const long bloopFrame::ID_STATICTEXT12 = wxNewId();
const long bloopFrame::idTextZipProgram = wxNewId();
const long bloopFrame::idPannelSettings = wxNewId();
const long bloopFrame::idHtmlOutput = wxNewId();
const long bloopFrame::idPanelOutput = wxNewId();
const long bloopFrame::idTextFileToSaveTo = wxNewId();
const long bloopFrame::idButtonSaveButton = wxNewId();
const long bloopFrame::idButtonSaveAs = wxNewId();
const long bloopFrame::ID_TEXTCTRL1 = wxNewId();
const long bloopFrame::ID_BUTTON5 = wxNewId();
const long bloopFrame::ID_BUTTON6 = wxNewId();
const long bloopFrame::idPanelSave = wxNewId();
const long bloopFrame::idChecklistRunTimeOptions = wxNewId();
const long bloopFrame::idTextOtherRunTimeOptions = wxNewId();
const long bloopFrame::idButtonRUN = wxNewId();
const long bloopFrame::idPanelRun = wxNewId();
const long bloopFrame::ID_NOTEBOOK1 = wxNewId();
const long bloopFrame::ID_STATUSBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(bloopFrame,wxFrame)
    //(*EventTable(bloopFrame)
    //*)
END_EVENT_TABLE()




bloopFrame::bloopFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(bloopFrame)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxGridSizer* GridSizer4;
    wxStaticBoxSizer* StaticBoxSizer12;
    wxGridSizer* GridSizer15;
    wxGridSizer* GridSizer10;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxGridSizer* GridSizer13;
    wxFlexGridSizer* FlexGridSizer3;
    wxGridSizer* GridSizer11;
    wxGridSizer* GridSizer23;
    wxGridSizer* GridSizer18;
    wxGridSizer* GridSizer5;
    wxGridSizer* GridSizer7;
    wxGridSizer* GridSizer8;
    wxFlexGridSizer* FlexGridSizer2;
    wxStaticBoxSizer* StaticBoxSizer9;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxStaticBoxSizer* StaticBoxSizer10;
    wxGridSizer* GridSizer16;
    wxGridSizer* GridSizer9;
    wxGridSizer* GridSizer6;
    wxGridSizer* GridSizer19;
    wxGridSizer* GridSizer25;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxGridSizer* GridSizer1;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxGridSizer* GridSizer3;
    wxStaticBoxSizer* StaticBoxSizer11;
    wxGridSizer* GridSizer21;
    wxGridSizer* GridSizer20;
    wxGridSizer* GridSizer14;
    wxGridSizer* GridSizer26;
    wxGridSizer* GridSizer17;
    wxGridSizer* GridSizer12;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxGridSizer* GridSizer27;
    wxGridSizer* GridSizer22;
    wxGridSizer* GridSizer2;
    wxGridSizer* GridSizer24;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX, _T("wxID_ANY"));
    GridSizer1 = new wxGridSizer(2, 1, 0, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(520,414), 0, _T("ID_NOTEBOOK1"));
    panelConfiguration = new wxPanel(Notebook1, idPanelConfiguration, wxDefaultPosition, wxSize(498,379), wxTAB_TRAVERSAL, _T("idPanelConfiguration"));
    GridSizer2 = new wxGridSizer(0, 2, 0, 0);
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, panelConfiguration, _("Pylon Required"));
    GridSizer3 = new wxGridSizer(3, 2, 0, 0);
    StaticText1 = new wxStaticText(panelConfiguration, ID_STATICTEXT1, _("Init File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textInitFile = new wxTextCtrl(panelConfiguration, idTextInitFile, _("init.py"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextInitFile"));
    GridSizer3->Add(textInitFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(panelConfiguration, ID_STATICTEXT2, _("Main File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textMainFile = new wxTextCtrl(panelConfiguration, idTextMainFile, _("main.py"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextMainFile"));
    GridSizer3->Add(textMainFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(panelConfiguration, ID_STATICTEXT3, _("Extraction Dir:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    GridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textExtractDir = new wxTextCtrl(panelConfiguration, idTextExtractDir, _("Data"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextExtractDir"));
    GridSizer3->Add(textExtractDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(GridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, panelConfiguration, _("Window Properties"));
    FlexGridSizer2 = new wxFlexGridSizer(2, 1, 0, 0);
    GridSizer4 = new wxGridSizer(1, 2, 0, 0);
    StaticText4 = new wxStaticText(panelConfiguration, ID_STATICTEXT4, _("Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    GridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textWindowName = new wxTextCtrl(panelConfiguration, idTextWindowName, _("Pylon"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextWindowName"));
    GridSizer4->Add(textWindowName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(GridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, panelConfiguration, _("Resolution"));
    GridSizer5 = new wxGridSizer(2, 2, 0, 0);
    StaticText5 = new wxStaticText(panelConfiguration, ID_STATICTEXT5, _("Width (X)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    GridSizer5->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textWindowWidth = new wxTextCtrl(panelConfiguration, idTextWindowWidth, _("640"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextWindowWidth"));
    GridSizer5->Add(textWindowWidth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(panelConfiguration, ID_STATICTEXT6, _("Height (Y)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    GridSizer5->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textWindowHeight = new wxTextCtrl(panelConfiguration, idTextWindowHeight, _("480"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idTextWindowHeight"));
    GridSizer5->Add(textWindowHeight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4->Add(GridSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, panelConfiguration, _("Archives"));
    GridSizer6 = new wxGridSizer(1, 1, 0, 0);
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    checkboxEnableArchiving = new wxCheckBox(panelConfiguration, idCheckboxEnableArchiving, _("Enable Archive Indexing"), wxDefaultPosition, wxSize(203,24), 0, wxDefaultValidator, _T("idCheckboxEnableArchiving"));
    checkboxEnableArchiving->SetValue(true);
    FlexGridSizer3->Add(checkboxEnableArchiving, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textArchiveList = new wxTextCtrl(panelConfiguration, idTextArchiveList, _("#main = ./rc.pylon.zip"), wxDefaultPosition, wxSize(206,283), wxTE_MULTILINE, wxDefaultValidator, _T("idTextArchiveList"));
    FlexGridSizer3->Add(textArchiveList, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer6->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(GridSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelConfiguration->SetSizer(GridSizer2);
    GridSizer2->SetSizeHints(panelConfiguration);
    panelFiles = new wxPanel(Notebook1, idPanelFiles, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelFiles"));
    GridSizer18 = new wxGridSizer(0, 1, 0, 0);
    Notebook2 = new wxNotebook(panelFiles, ID_NOTEBOOK2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK2"));
    Panel1 = new wxPanel(Notebook2, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    GridSizer24 = new wxGridSizer(2, 1, 0, 0);
    GridSizer25 = new wxGridSizer(0, 1, 0, 0);
    textPathDir = new wxTextCtrl(Panel1, idTextPathDir, _("./"), wxDefaultPosition, wxSize(446,27), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("idTextPathDir"));
    GridSizer25->Add(textPathDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer24->Add(GridSizer25, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer26 = new wxGridSizer(0, 1, 0, 0);
    buttonBrowseDir = new wxButton(Panel1, idButtonBrowseDir, _("Browse"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonBrowseDir"));
    GridSizer26->Add(buttonBrowseDir, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer24->Add(GridSizer26, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(GridSizer24);
    GridSizer24->Fit(Panel1);
    GridSizer24->SetSizeHints(Panel1);
    Panel2 = new wxPanel(Notebook2, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    GridSizer20 = new wxGridSizer(0, 2, 0, 0);
    StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Files:"));
    GridSizer21 = new wxGridSizer(0, 1, 0, 0);
    checklistFiles = new wxCheckListBox(Panel2, idChecklistFiles, wxDefaultPosition, wxDefaultSize, 0, 0, wxLB_SORT|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, _T("idChecklistFiles"));
    GridSizer21->Add(checklistFiles, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer8->Add(GridSizer21, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer20->Add(StaticBoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Options:"));
    GridSizer22 = new wxGridSizer(2, 1, 0, 0);
    GridSizer23 = new wxGridSizer(0, 2, 0, 0);
    Button1 = new wxButton(Panel2, ID_BUTTON1, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    GridSizer23->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(Panel2, ID_BUTTON3, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer23->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel2, ID_BUTTON2, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    GridSizer23->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(Panel2, ID_BUTTON4, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    GridSizer23->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer22->Add(GridSizer23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(GridSizer22, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer20->Add(StaticBoxSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(GridSizer20);
    GridSizer20->Fit(Panel2);
    GridSizer20->SetSizeHints(Panel2);
    Notebook2->AddPage(Panel1, _("Dir"), false);
    Notebook2->AddPage(Panel2, _("Files"), false);
    GridSizer18->Add(Notebook2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelFiles->SetSizer(GridSizer18);
    GridSizer18->Fit(panelFiles);
    GridSizer18->SetSizeHints(panelFiles);
    panelSettings = new wxPanel(Notebook1, idPannelSettings, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPannelSettings"));
    GridSizer8 = new wxGridSizer(2, 0, 0, 0);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, panelSettings, _("Pylon Directories"));
    GridSizer9 = new wxGridSizer(3, 2, 0, 0);
    StaticText7 = new wxStaticText(panelSettings, ID_STATICTEXT7, _("Path to Pylon Executible:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    GridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textPathToPylonExe = new wxTextCtrl(panelSettings, idTextPathToPylonExe, _("./pylon"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idTextPathToPylonExe"));
    GridSizer9->Add(textPathToPylonExe, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(panelSettings, ID_STATICTEXT9, _("Path to Pylon dlls:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    GridSizer9->Add(StaticText9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textPathToPylonDLL = new wxTextCtrl(panelSettings, idTextPathToPylonDLL, _("./"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idTextPathToPylonDLL"));
    GridSizer9->Add(textPathToPylonDLL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(panelSettings, ID_STATICTEXT8, _("Path to Game Files:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    GridSizer9->Add(StaticText8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textPathToGameFile = new wxTextCtrl(panelSettings, idTextPathToGameFile, _("./"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idTextPathToGameFile"));
    GridSizer9->Add(textPathToGameFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5->Add(GridSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer8->Add(StaticBoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, panelSettings, _("Other"));
    GridSizer10 = new wxGridSizer(2, 2, 0, 0);
    StaticText10 = new wxStaticText(panelSettings, ID_STATICTEXT10, _("Text Editor Command"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    GridSizer10->Add(StaticText10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textEditorCMD = new wxTextCtrl(panelSettings, idTextEditorCMD, _("gedit %s"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idTextEditorCMD"));
    GridSizer10->Add(textEditorCMD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(panelSettings, ID_STATICTEXT11, _("3D Editor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    GridSizer10->Add(StaticText11, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    text3dEditorCMD = new wxTextCtrl(panelSettings, idText3dEditorCMD, _("thing -f %s \?"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idText3dEditorCMD"));
    GridSizer10->Add(text3dEditorCMD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(panelSettings, ID_STATICTEXT12, _("Zip Program:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    GridSizer10->Add(StaticText12, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textZipProgram = new wxTextCtrl(panelSettings, idTextZipProgram, _("zip -f %f -o %o \?\?\?"), wxDefaultPosition, wxSize(226,27), 0, wxDefaultValidator, _T("idTextZipProgram"));
    GridSizer10->Add(textZipProgram, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(GridSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer8->Add(StaticBoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelSettings->SetSizer(GridSizer8);
    GridSizer8->Fit(panelSettings);
    GridSizer8->SetSizeHints(panelSettings);
    panelOutput = new wxPanel(Notebook1, idPanelOutput, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelOutput"));
    GridSizer7 = new wxGridSizer(1, 1, 0, 0);
    htmlOutput = new wxHtmlWindow(panelOutput, idHtmlOutput, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO, _T("idHtmlOutput"));
    GridSizer7->Add(htmlOutput, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelOutput->SetSizer(GridSizer7);
    GridSizer7->Fit(panelOutput);
    GridSizer7->SetSizeHints(panelOutput);
    panelSave = new wxPanel(Notebook1, idPanelSave, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelSave"));
    GridSizer11 = new wxGridSizer(6, 1, 0, 0);
    StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, panelSave, _("Save To Main Archive"));
    GridSizer12 = new wxGridSizer(0, 2, 0, 0);
    textFileToSaveTo = new wxTextCtrl(panelSave, idTextFileToSaveTo, _("rc.pylon"), wxDefaultPosition, wxSize(169,26), 0, wxDefaultValidator, _T("idTextFileToSaveTo"));
    GridSizer12->Add(textFileToSaveTo, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer16 = new wxGridSizer(0, 2, 0, 0);
    buttonSaveButton = new wxButton(panelSave, idButtonSaveButton, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonSaveButton"));
    GridSizer16->Add(buttonSaveButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonSaveAs = new wxButton(panelSave, idButtonSaveAs, _("Save As"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonSaveAs"));
    GridSizer16->Add(buttonSaveAs, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer12->Add(GridSizer16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticBoxSizer11->Add(GridSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer11->Add(StaticBoxSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer12 = new wxStaticBoxSizer(wxHORIZONTAL, panelSave, _("Save As Refference Archive"));
    GridSizer19 = new wxGridSizer(0, 2, 0, 0);
    TextCtrl1 = new wxTextCtrl(panelSave, ID_TEXTCTRL1, _("refference/reff.pylon"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridSizer19->Add(TextCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer27 = new wxGridSizer(0, 2, 0, 0);
    Button5 = new wxButton(panelSave, ID_BUTTON5, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    GridSizer27->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button6 = new wxButton(panelSave, ID_BUTTON6, _("Label"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    GridSizer27->Add(Button6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer19->Add(GridSizer27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticBoxSizer12->Add(GridSizer19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer11->Add(StaticBoxSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelSave->SetSizer(GridSizer11);
    GridSizer11->Fit(panelSave);
    GridSizer11->SetSizeHints(panelSave);
    panelRun = new wxPanel(Notebook1, idPanelRun, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("idPanelRun"));
    GridSizer13 = new wxGridSizer(1, 0, 0, 0);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, panelRun, _("Runtime Options"));
    GridSizer14 = new wxGridSizer(0, 2, 0, 0);
    checklistRunTimeOptions = new wxCheckListBox(panelRun, idChecklistRunTimeOptions, wxDefaultPosition, wxDefaultSize, 0, 0, wxALWAYS_SHOW_SB, wxDefaultValidator, _T("idChecklistRunTimeOptions"));
    checklistRunTimeOptions->Check(checklistRunTimeOptions->Append(_("Debug")));
    checklistRunTimeOptions->Append(_("Wireframe"));
    checklistRunTimeOptions->Append(_("Bounding"));
    checklistRunTimeOptions->Append(_("Collisions"));
    checklistRunTimeOptions->Append(_("Version"));
    checklistRunTimeOptions->Append(_("Help"));
    checklistRunTimeOptions->Append(_("Trails"));
    checklistRunTimeOptions->Append(_("Do Not Remove Data"));
    checklistRunTimeOptions->Append(_("Use Dir Data"));
    checklistRunTimeOptions->Check(checklistRunTimeOptions->Append(_("Other Options")));
    GridSizer14->Add(checklistRunTimeOptions, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer15 = new wxGridSizer(2, 0, 0, 0);
    StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, panelRun, _("Other Options"));
    textOtherRunTimeOptions = new wxTextCtrl(panelRun, idTextOtherRunTimeOptions, wxEmptyString, wxDefaultPosition, wxSize(172,27), wxTE_MULTILINE|wxTE_CHARWRAP, wxDefaultValidator, _T("idTextOtherRunTimeOptions"));
    StaticBoxSizer10->Add(textOtherRunTimeOptions, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer15->Add(StaticBoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer17 = new wxGridSizer(0, 0, 0, 0);
    buttonRUN = new wxButton(panelRun, idButtonRUN, _("RUN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("idButtonRUN"));
    GridSizer17->Add(buttonRUN, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer15->Add(GridSizer17, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer14->Add(GridSizer15, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer7->Add(GridSizer14, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer13->Add(StaticBoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelRun->SetSizer(GridSizer13);
    GridSizer13->Fit(panelRun);
    GridSizer13->SetSizeHints(panelRun);
    Notebook1->AddPage(panelConfiguration, _("Pylon Configuration"), false);
    Notebook1->AddPage(panelFiles, _("Files"), false);
    Notebook1->AddPage(panelSettings, _("Settings"), false);
    Notebook1->AddPage(panelOutput, _("Output"), false);
    Notebook1->AddPage(panelSave, _("Save"), false);
    Notebook1->AddPage(panelRun, _("Run"), false);
    GridSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridSizer1);
    StatusBar = new wxStatusBar(this, ID_STATUSBAR, wxFULL_REPAINT_ON_RESIZE, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar);
    DirDialog1 = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    GridSizer1->Fit(this);
    GridSizer1->SetSizeHints(this);

    Connect(idCheckboxEnableArchiving,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&bloopFrame::OncheckboxEnableArchivingClick);
    Connect(idTextPathDir,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&bloopFrame::OntextPathDirTextEnter);
    Connect(idButtonBrowseDir,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bloopFrame::OnbuttonBrowseDirClick);
    Connect(idChecklistFiles,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&bloopFrame::OnchecklistFilesToggled);
    Connect(idChecklistFiles,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&bloopFrame::OnchecklistFilesSelect);
    Connect(idChecklistFiles,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&bloopFrame::OnchecklistFilesDClick);
    Connect(idButtonRUN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&bloopFrame::OnbuttonRUNClick);
    //*)

    int fontsizes[] = {6,7,8,9,10,11,12};
    htmlOutput->SetFonts(str(""),str(""),fontsizes);
}

bloopFrame::~bloopFrame()
{
    //(*Destroy(bloopFrame)
    //*)
}

void bloopFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void bloopFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void bloopFrame::OncheckboxEnableArchivingClick(wxCommandEvent& event)
{
    print("OncheckboxEnableArchivingClick: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
    if(checkboxEnableArchiving->GetValue())
    {
        print("Archive Indexing Enabled");
        textArchiveList->Enable();
    }
    else
    {
        print("Archive Indexing Disabled");
        textArchiveList->Disable();
    }
}

void bloopFrame::OnchecklistFilesToggled(wxCommandEvent& event)
{
    //checklistFiles->GetCount();
    print("OnchecklistFilesToggled: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
}

void bloopFrame::OnchecklistFilesSelect(wxCommandEvent& event)
{
    print("OnchecklistFilesSelect: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
}
