#include "bloopMain.h"

#include "../threads/threads.h"

using namespace std;

std::string fstring(const char* fmt, ...);

string getStdoutFromCommand(string cmd);
void redirectStdoutFromCommand(string cmd);
void printert(std::string str);

#define _BUFFER_SIZE 10

class RunThread : public Threads::ExThread
{
        string cmmd;
    public:
        RunThread(string cmd)
        {
            cmmd = cmd;
            this->startThread();
        }

        ~RunThread()
        {
            this->joinThread();
        }

        void run()
        {
            string data;
            FILE *stream;
            int MAX_BUFFER = _BUFFER_SIZE;
            char buffer[MAX_BUFFER];
            cmmd.append(" 2>&1");
            stream = popen(cmmd.c_str(), "r");
            if (!stream){
                exit(1);
            }
            string buff = "";
            //print_ai("<pre><font size='3'>");
            unsigned int numlines = 0;
            while (!feof(stream))
            {
                if (fgets(buffer, MAX_BUFFER, stream) != NULL)
                {
                    //data.append(buffer);
                    string sdat(buffer);
                    for(unsigned int i = 0; i < sdat.length(); ++i)
                    {
                        if(sdat[i] == '\n' || sdat[i] == '\r')
                        {
                            data += buff + "\n";
                            if( !(++numlines % 100) )
                            {
                                print_ai("<pre><font size='3'>"+data+"</font></pre>");
                                data = "";
                            }
                            if(!buff.compare(0,5,"Frame"))
                            {
                                setStatus(buff);
                            }
                            buff = "";
                        }
                        //else if(sdat[i] == '\t') buff += "    ";
                        else buff += sdat[i];
                    }
                }
            }
            pclose(stream);
            //print_ai("</font></pre>");
            print_ai("<pre><font size='3'>"+data+"</font></pre>");
            print_ai("<pre>\n</pre>");
            print("<br><font color='#008800'>Pylon exicution finished.</font></ul>");
        }
};

RunThread * runningThread = NULL;

void bloopFrame::OnbuttonRUNClick(wxCommandEvent& event)
{
    if( runningThread )
    {
        delete runningThread;
        runningThread = NULL;
        //return;
    }

    clear_output();

    print("OnbuttonRUNClick: " + fstring("%d, %d", event.GetEventType(), event.GetSelection()));
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

    if( !runningThread )
    {
        print("Executing Pylon with the Command:");
        print("<font color='#FF8844'>" + cmmd + "</font>");
        runningThread = new RunThread(cmmd);
    }
}

string getStdoutFromCommand(string cmd) {
	string data;
	FILE *stream;
	int MAX_BUFFER = _BUFFER_SIZE;
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
                if(sdat[i] == '\n' || sdat[i] == '\r')
                {
                    //if(!buff.compare(0,5,"Frame")) setStatus(buff);
                    //print_ai(buff);
                    data += buff+"\n";
                    buff = "";
                }
                //else if(sdat[i] == '\t') buff += "    ";
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
    if(overbuff_count > 100)
    {
        print_ai(over_buff);
        over_buff = "";
        overbuff_count = 0;
    }
    //else {
        over_buff += str;
        overbuff_count++;
    //}
}

