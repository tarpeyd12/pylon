#include "bloopMain.h"

using namespace std;

std::string fstring(const char* fmt, ...);

string getStdoutFromCommand(string cmd);
void redirectStdoutFromCommand(string cmd);
void printert(std::string str);

int pipe_id[2];

void bloopFrame::OnbuttonRUNClick(wxCommandEvent& event)
{
    //print("OnbuttonRUNClick: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
    Notebook1->ChangeSelection(3);
    std::string cmmd = "";

    if(checklistRunTimeOptions->IsChecked(0))
        cmmd += " -debug";
    if(checklistRunTimeOptions->IsChecked(1))
        cmmd += " -wireframe";
    if(checklistRunTimeOptions->IsChecked(2))
        cmmd += " -boundingbox";
    if(checklistRunTimeOptions->IsChecked(3))
        cmmd += " -collisions";
    if(checklistRunTimeOptions->IsChecked(4))
        cmmd += " -version";
    if(checklistRunTimeOptions->IsChecked(5))
        cmmd += " -help";
    if(checklistRunTimeOptions->IsChecked(6))
        cmmd += " -trails";
    if(checklistRunTimeOptions->IsChecked(7))
        cmmd += " -dnrm";
    if(checklistRunTimeOptions->IsChecked(8))
        cmmd += " -usedirdata -dir " + str(textPathDir->GetValue());
    if(checklistRunTimeOptions->IsChecked(9))
        cmmd += " " + str(textOtherRunTimeOptions->GetValue());

    if(!checklistRunTimeOptions->IsChecked(8))
        cmmd += " -f " + str(textPathToGameFile->GetValue()) + str(textFileToSaveTo->GetValue());

    std::string libpaths = "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"+str(textPathToPylonDLL->GetValue())+":/usr/lib:/usr/lib/python2.7";

    cmmd = libpaths + " " + str(textPathToPylonExe->GetValue()) + cmmd;

    clear_output();

    print("Executing Pylon with the Command:");
    print("     <font color='#FF8844'>" + cmmd + "</font>");

    /*pipe(pipe_id);
    if(fork() == 0) {
        close(pipe_id[0]);
        redirectStdoutFromCommand(cmmd);
        _exit(0);
        exit(0);
    }
    else
    //if(fork() == 0)
    {
        close(pipe_id[1]);
        char dat[2];
        std::string buff = "";
        Notebook1->ChangeSelection(3);
        while(read(pipe_id[0], dat, sizeof(dat)) != 0)
        {
            std::string sdat(dat);
            for(unsigned int i = 0; i < sdat.length(); i++)
            {
                if(dat[i] == '\n' || dat[i] == '\r') { printert("<br>"+buff+"</ul>");  buff = "";  }
                else if(dat[i] == '\t') buff += "_   ";
                else buff += dat[i];
                dat[i] = '\0';
            }
        }
        //exit(0);
    }*/
    /*{
        std::string buff = "";
        std::string sdat = getStdoutFromCommand(cmmd);
        for(unsigned int i = 0; i < sdat.length(); i++)
        {
            if(sdat[i] == '\n' || sdat[i] == '\r') { print_ai("<br>"+buff+"</ul>");  buff = "";  }
            else if(sdat[i] == '\t') buff += "_   ";
            else buff += sdat[i];
        }
        //_exit(0);
    }*/
    print_ai(getStdoutFromCommand(cmmd));
    print("");
    print("<font color='#008800'>Pylon exicution finished.</font>");
}

string getStdoutFromCommand(string cmd) {
	string data;
	FILE *stream;
	int MAX_BUFFER = 256;
	char buffer[MAX_BUFFER];
	cmd.append(" 2>&1");
	stream = popen(cmd.c_str(), "r");
	if (!stream){
		exit(1);
	}
	string buff = "<pre><font size='3'>";
	while (!feof(stream)){
		if (fgets(buffer, MAX_BUFFER, stream) != NULL){
			//data.append(buffer);
			string sdat(buffer);
            for(unsigned int i = 0; i < sdat.length(); i++)
            {
                if(sdat[i] == '\n' || sdat[i] == '\r') { data += "<br>"+buff+"</ul>";  buff = "";  }
                else if(sdat[i] == '\t') buff += "    ";
                else buff += sdat[i];
            }
		}
	}
	pclose(stream);
	return data+"</font></pre>";
}

std::string over_buff = "";
int overbuff_count = 0;

void printert(std::string str)
{
    if(overbuff_count > 10)
    {
        print_ai(over_buff);
        over_buff = "";
        overbuff_count = 0;
    }
    else
    {
        over_buff += str;
        overbuff_count++;
    }
}

void redirectStdoutFromCommand(string cmd) {
	FILE *stream;
	int MAX_BUFFER = 2;
	char buffer[MAX_BUFFER];
	for(int i = 0; i < MAX_BUFFER; i++)
        buffer[i] = '\0';
	cmd.append(" 2>&1");
	stream = popen(cmd.c_str(), "r");
	if (!stream){
		exit(1);
	}
	string buff = "";
	while (!feof(stream)){
		if (fgets(buffer, MAX_BUFFER, stream) != NULL){
            write(pipe_id[1], buffer, (strlen(buffer)+1));
            //print(std::string(buffer));
            //int i=0;
            /*for(int i = 0; i < MAX_BUFFER; i++)
            {
                if(buffer[i] == '\n' || buffer[i] == '\r') { printert("<br>"+buff+"</ul>");  buff = "";  }
                else if(buffer[i] == '\t') buff += "_   ";
                else buff += buffer[i];
                buffer[i] = '\0';
            }*/
		}
	}
	pclose(stream);
}