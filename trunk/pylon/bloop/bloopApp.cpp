/***************************************************************
 * Name:      bloopApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2011-06-23
 * Copyright:  ()
 * License:
 **************************************************************/

#include "bloopApp.h"

//(*AppHeaders
#include "bloopMain.h"
#include <wx/image.h>
//*)


IMPLEMENT_APP(bloopApp);

bool bloopApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	bloopFrame* Frame = new bloopFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
