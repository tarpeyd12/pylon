#include "bloopMain.h"

#include "filesindir.h"

using namespace std;

std::string fstring(const char* fmt, ...);

void bloopFrame::OntextPathDirTextEnter(wxCommandEvent& event)
{
    //print("OntextPathDirTextEnter: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
    wxString pth = textPathDir->GetValue();
    print("changing dir to: <font color='#0000FF'>" + str(pth) + "</font>");
    checklistFiles->Clear();


    std::string dir = str(pth);
    vector<std::string> files = vector<std::string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        checklistFiles->Append(str(files[i]));
    }
}

void bloopFrame::OnbuttonBrowseDirClick(wxCommandEvent& event)
{
    //print("OnbuttonBrowseDirClick: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
    wxDirDialog *openDialog = new wxDirDialog(this, wxT("Brows for Dir"));
    wxString pth = openDialog->GetPath();
    if(openDialog->ShowModal() == wxID_OK)
    {
        pth = openDialog->GetPath();
        print("changing dir to: <font color='#0000FF'>" + str(pth) + "</font>");
    }
    textPathDir->SetValue(pth);

    checklistFiles->Clear();

    std::string dir = str(pth);
    vector<std::string> files = vector<std::string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        checklistFiles->Append(str(files[i]));
    }

    delete openDialog;
}

void bloopFrame::OnchecklistFilesDClick(wxCommandEvent& event)
{
    std::string cmmd = fstring(str(textEditorCMD->GetValue()).c_str(), str(textPathDir->GetValue() + event.GetString()).c_str());
    print("Executing: <font color='#0000FF'>" + cmmd + "</font>");
    system(cmmd.c_str());
}
