#include "keyframelist.h"

namespace ObjectLoader
{
    KeyFrameList::KeyFrameList()
    {

    }

    KeyFrameList::KeyFrameList(std::string dat)
    {
        char* csrtmp;
        std::string tmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"NumKeyFrames","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&NumKeyFrames);

        unsigned int p = 0;
        while(dat[p++] != '>');
        dat = dat.substr(p);

        for(unsigned int i = 0; i < NumKeyFrames; i++)
        {
            unsigned int len;
            std::string frame = ScriptEngine::Parse::getLabeledSection(dat,"CKeyFrame","{","}");
            len = frame.length();
            for(unsigned int s = 0; s < dat.length(); s++)
                if(dat[s] == ' ' || dat[s] == '\t' || dat[s] == '\n')
                    len++;
            _Frames.add(new KeyFrame(frame));
            if(i+1 < NumKeyFrames)
            {
                p = 0;
                while(dat[p++] != '}');
                dat = dat.substr(p);
            }
        }
    }

    KeyFrameList::~KeyFrameList()
    {
        for(unsigned int i = 0; i < _Frames.length(); i++)
            delete _Frames[i];
        _Frames.clear();
    }

    KeyFrame KeyFrameList::keyAt(float t)
    {
        if(!_Frames.length())
            return KeyFrame();
        float maxtime = _Frames[_Frames.length()-1]->gettime();
        if(!true) // looping
            t = fmod(t,maxtime);
        else if(!false) // ocilating
        {
            t = fmod(t,maxtime*2);
            if(t > maxtime)
                t = maxtime - (t - maxtime);
        }
        for(unsigned int i = 0; i < _Frames.length(); i++)
        {
            float ftime = _Frames[i]->gettime();
            if(ftime == t)
                return *_Frames[i];
            if(i+1 < _Frames.length() && t > ftime)
            {
                float nftime = _Frames[i+1]->gettime();
                if(t < nftime && t > ftime)
                    return KeyFrame(*_Frames[i+1],*_Frames[i],t);
                else if(nftime == t)
                    return *_Frames[i+1];
            }
        }
        return KeyFrame();
    }

    AnimKeyFrame::AnimKeyFrame()
    {

    }

    AnimKeyFrame::AnimKeyFrame(std::string dat)
    {
        char* csrtmp;
        std::string tmp;
        //float ftmp;

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"KeyFrame Type","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&KeyFrameType);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Name","<",">");
        Name = tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1));

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Time Start","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&TimeStart);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Time End","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%f",&TimeEnd);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"Flags","<",">");
        csrtmp = (char*)tmp.substr((tmp[0] == ' '?1:0),tmp.length()-(tmp[tmp.length()-1] == ' '?2:1)).c_str();
        sscanf(csrtmp,"%u",&Flags);

        tmp = ScriptEngine::Parse::getLabeledSection(dat,"CKeyFrame List","{","}");
        KFList = new KeyFrameList(tmp);
    }

    AnimKeyFrame::~AnimKeyFrame()
    {
        delete KFList;
    }

    std::string AnimKeyFrame::toString()
    {
        return "";
    }

    KeyFrame AnimKeyFrame::keyAt(float t)
    {
        return KFList->keyAt(t);
    }
}
