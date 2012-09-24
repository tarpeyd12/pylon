#include "pogelscriptinterface.h"

namespace pogelInterface
{

    POGEL::OBJECT * GetObject( const std::string& simname, Object* pyobjreff )
    {
        if( PyString_CheckExact( pyobjreff ) )
        {
            const char* objname = PyString_AsString( pyobjreff );
            POGEL::OBJECT* ret = (POGEL::OBJECT*)Renderer::Physics::getObject( simname,  std::string( objname ) );
            objname = NULL;
            return ret;
        }
        if( PyTuple_CheckExact( pyobjreff ) )
        {
            int tlen = PyTuple_Size( pyobjreff );
            ClassList< std::string > declist( tlen );
            for( int i = 0; i < tlen; ++i )
            {
                Object * curpydec = PyTuple_GetItem( pyobjreff, i );
                if( !curpydec || !PyString_CheckExact( curpydec ) )
                {
                    declist.clear();
                    return NULL;
                }
                const char * dec = PyString_AsString( curpydec );
                //char * dec = (char*)memcpy( (void*)new char[strlen(tdec)], (const void *)tdec, strlen(tdec) );
                //tdec = NULL;
                declist += std::string(dec);
                dec = NULL;
                //delete [] dec;
            }
            POGEL::OBJECT * ret = Renderer::Physics::getObject( simname, declist );
            declist.clear();
            return ret;
        }
        return NULL;
    }

    ClassList<std::string> * GetObjectNameList( Object* pyobjreff )
    {
        Py_XINCREF( pyobjreff );
        if( PyString_CheckExact( pyobjreff ) )
        {
            ClassList< std::string > * ret = new ClassList<std::string>( 1 );
            const char* objname = PyString_AsString( pyobjreff );
            ret->add( std::string(objname) );
            objname = NULL;
            Py_XDECREF( pyobjreff );
            return ret;
        }
        if( PyTuple_CheckExact( pyobjreff ) )
        {
            int tlen = PyTuple_Size( pyobjreff );
            if( tlen <= 0 )
            {
                Py_XDECREF( pyobjreff );
                return NULL;
            }
            ClassList<std::string> * ret = new ClassList<std::string>( tlen );
            for( int i = 0; i < tlen; ++i )
            {
                Object * curpydec = PyTuple_GetItem( pyobjreff, i );
                Py_XINCREF( curpydec );
                if( !curpydec || !PyString_CheckExact( curpydec ) )
                {
                    delete ret;
                    Py_XDECREF( curpydec );
                    return NULL;
                }
                const char * dec = PyString_AsString( curpydec );
                ret->add( std::string(dec) );
                dec = NULL;
                Py_XDECREF( curpydec );
            }
            Py_XDECREF( pyobjreff );
            return ret;
        }
        Py_XDECREF( pyobjreff );
        return NULL;
    }

    Object * GetObjectTupleFromNameList( ClassList<std::string> * objref )
    {
        if( !objref || !objref->length() )
        {
            return NULL;
        }
        Object * ret = PyTuple_New( objref->length() );
        for( unsigned int i = 0; i < objref->length(); ++i )
        {
            PyTuple_SetItem(ret, i, Py_BuildValue("s",(objref->get(i)+"\0").c_str()) );
            //PyTuple_SET_ITEM(ret, i, Py_BuildValue("s",(objref->get(i)).c_str()) );
        }
        return ret;
    }

    std::string GetObjectName( Object * pyobjreff )
    {
        Py_XINCREF( pyobjreff );
        if( PyString_CheckExact( pyobjreff ) )
        {
            const char * objname = PyString_AsString( pyobjreff );
            std::string ret(objname);
            objname = NULL;
            Py_XDECREF( pyobjreff );
            return ret;
        }
        if( PyTuple_CheckExact( pyobjreff ) )
        {
            if( !PyTuple_Size( pyobjreff ) )
            {
                Py_XDECREF( pyobjreff );
                ThrowError(-1);
            }
            Object * curpydec = PyTuple_GetItem( pyobjreff,0 );
            if( !PyString_CheckExact( curpydec ) )
            {
                Py_XDECREF( pyobjreff );
                ThrowError(-2);
            }
            const char * dec = PyString_AsString( curpydec );
            std::string ret(dec);
            dec = NULL;
            Py_XDECREF( pyobjreff );
            return ret;
        }
        Py_XDECREF( pyobjreff );
        ThrowError(-3);
        return std::string();
    }

    Object* fps( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":fps"))
            return NULL;
        return Py_BuildValue("f", POGEL::GetFps());
    }

    Object* getruntime( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":getruntime"))
            return NULL;
        return Py_BuildValue("f", POGEL::GetTimePassed());
    }

    Object* getproperties( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":getproperties"))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* setproperties( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:setproperties", &p))
            return NULL;
        POGEL::setproperties((unsigned int)p);
        POGEL::removeproperty(POGEL_LOGTOFILE);
        return Py_BuildValue("i", POGEL::getproperties());
    }

    Object* hasproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:hasproperty", &p))
            return NULL;
        return Py_BuildValue("i", (int)POGEL::hasproperty((unsigned int)p));
    }

    Object* addproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:addproperty", &p))
            return NULL;
        POGEL::addproperty(p);
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* removeproperty( Object* self, Object* args )
    {
        int p;
        if(!PyArg_ParseTuple(args, "i:removeproperty", &p))
            return NULL;
        POGEL::removeproperty(p);
        return Py_BuildValue("i", (int)POGEL::getproperties());
    }

    Object* wait_sec_f( Object* self, Object* args )
    {
        float waittime;
        if(!PyArg_ParseTuple(args, "f:wait_sec_f", &waittime))
            return NULL;
        if( waittime < 0.0f )
        {
            return Py_BuildValue("f", POGEL::GetTimePassed());
        }
        if( waittime >= 1.0f )
        {
            #if defined(WINDOWS) || defined(_WIN32)
            Sleep( (unsigned int)(waittime) );
            #else
            if( sleep( (unsigned int)(waittime) ) )
            {
                cout << "sleep() error" << endl;
            }
            #endif
            waittime -= float( (unsigned int)(waittime) );
        }
        if( waittime <= 0.0f )
        {
            return Py_BuildValue("f", POGEL::GetTimePassed());
        }
        if( usleep( (unsigned int)(waittime * 1000000.0f) ) )
        {
            cout << "usleep() error" << endl;
        }
        return Py_BuildValue("f", POGEL::GetTimePassed());
    }

    Object* wait_usec_i( Object* self, Object* args )
    {
        int waittime;
        if(!PyArg_ParseTuple(args, "i:wait_usec_i", &waittime))
            return NULL;
        if( waittime < 0 )
        {
            return Py_BuildValue("f", POGEL::GetTimePassed());
        }
        if( waittime >= 1000000 )
        {
            int secwait = waittime / 1000000;
            #if defined(WINDOWS) || defined(_WIN32)
            Sleep( secwait );
            #else
            if( sleep( secwait ) )
            {
                cout << "sleep() error" << endl;
            }
            #endif
            waittime -= ( secwait ) * 1000000;
        }
        if( waittime <= 0 )
        {
            return Py_BuildValue("f", POGEL::GetTimePassed());
        }
        if( usleep( waittime ) )
        {
            cout << "usleep() error" << endl;
        }
        return Py_BuildValue("f", POGEL::GetTimePassed());
    }

    Object* key_ispressed( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_ispressed", &checkedKey))
            return NULL;
        //return Py_BuildValue("i", (int)Renderer::Key::keys[(unsigned int)checkedKey]);
        if( Renderer::Key::keys[(unsigned int)checkedKey] )
        {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    Object* key_when_pressed( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_when_pressed", &checkedKey))
            return NULL;
        return Py_BuildValue("f", Renderer::Key::lastpressed[(unsigned int)checkedKey]);
    }

    Object* key_when_released( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_when_released", &checkedKey))
            return NULL;
        return Py_BuildValue("f", Renderer::Key::lastreleased[(unsigned int)checkedKey]);
    }

    Object* key_pos_press_2i( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_pos_press_2i", &checkedKey))
            return NULL;
        return Py_BuildValue("[ii]", Renderer::Key::mousepospress[(unsigned int)checkedKey][0], Renderer::Key::mousepospress[(unsigned int)checkedKey][1] );
    }

    Object* key_pos_release_2i( Object* self, Object* args )
    {
        char checkedKey;
        if(!PyArg_ParseTuple(args, "c:key_pos_release_2i", &checkedKey))
            return NULL;
        return Py_BuildValue("[ii]", Renderer::Key::mouseposrelease[(unsigned int)checkedKey][0], Renderer::Key::mouseposrelease[(unsigned int)checkedKey][1] );
    }

    Object* key_last(Object* self, Object* args)
    {
        if(!PyArg_ParseTuple(args, ":key_last"))
            return NULL;
        return Py_BuildValue("c", (char)Renderer::Key::last);
    }

    Object* mouse_ispressed( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_ispressed"))
            return NULL;
        //return Py_BuildValue("i", (int)(Renderer::Mouse::state == GLUT_DOWN));
        if( Renderer::Mouse::state == GLUT_DOWN )
        {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    Object* mouse_getbutton( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_getbutton"))
            return NULL;
        return Py_BuildValue("i", (int)(Renderer::Mouse::button));
    }

    Object* mouse_pos_x( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_x"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::X);
    }

    Object* mouse_pos_y( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_y"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::Y);
    }

    Object* mouse_pos_sx( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sx"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_x);
    }

    Object* mouse_pos_sy( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":mouse_pos_sy"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Mouse::static_y);
    }

    Object* select_isgood( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":select_isgood"))
            return NULL;
        //return Py_BuildValue("i", (int)Renderer::Selection::lastwasselected);
        if( Renderer::Selection::lastwasselected )
        {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }

    Object* select_get_sim( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":select_get_sim"))
            return NULL;
        return Py_BuildValue("s", Renderer::Selection::lastsimname.c_str());
    }

    Object* select_get_obj( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":select_get_obj"))
            return NULL;
        return Py_BuildValue("s", Renderer::Selection::lastobjname.c_str());
    }

    Object* camera_set_pos_s( Object* self, Object* args )
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_pos_s", &newpos))
            return NULL;
        Renderer::Camera::campos = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::Camera::campos.toString().c_str());
    }

    Object* camera_set_pos_3f( Object* self, Object* args )
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_pos_3f", &x, &y, &z))
            return NULL;
        Renderer::Camera::campos = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::Camera::campos.toString().c_str());
    }

    Object* camera_set_rot_s( Object* self, Object* args )
    {
        char* newpos;
        if(!PyArg_ParseTuple(args, "s:camera_set_rot_s", &newpos))
            return NULL;
        Renderer::Camera::camrot = POGEL::POINT(std::string(newpos));
        return Py_BuildValue("s", Renderer::Camera::camrot.toString().c_str());
    }

    Object* camera_set_rot_3f( Object* self, Object* args )
    {
        float x, y, z;
        if(!PyArg_ParseTuple(args, "fff:camera_set_rot_3f", &x, &y, &z))
            return NULL;
        Renderer::Camera::camrot = POGEL::POINT(x,y,z);
        return Py_BuildValue("s", Renderer::Camera::camrot.toString().c_str());
    }

    Object* camera_get_pos_3f( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":camera_get_pos_3f"))
            return NULL;
        return Py_BuildValue("[fff]", Renderer::Camera::campos.x, Renderer::Camera::campos.y, Renderer::Camera::campos.z );
    }

    Object* camera_get_rot_3f( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":camera_get_rot_3f"))
            return NULL;
        return Py_BuildValue("[fff]", Renderer::Camera::camrot.x, Renderer::Camera::camrot.y, Renderer::Camera::camrot.z );
    }

    Object* window_height( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":window_height"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::height);
    }

    Object* window_width( Object* self, Object* args )
    {
        if(!PyArg_ParseTuple(args, ":window_width"))
            return NULL;
        return Py_BuildValue("i", (int)Renderer::Window::Size::width);
    }

    Object* getline( Object* self, Object* args )
    {
        char* filename;
        int line;
        if(!PyArg_ParseTuple(args, "si:getline", &filename, &line))
            return NULL;
        return Py_BuildValue("s", FileLoader::getline(std::string(filename),line).c_str());
    }

    Object* requestfile_ar( Object* self, Object* args )
    {
        char* filename;
        char* archive;
        if(!PyArg_ParseTuple(args, "ss:requestfile_ar", &filename, &archive))
            return NULL;
        int ret = FileLoader::extractfile(std::string(archive),std::string(filename),true,false,"",false,"");
        if(ret == 0)
            return Py_BuildValue("s", std::string("Sucessful file retrival from resource pylon, "+std::string(filename)).c_str());
        else if(ret == -1234)
            return Py_BuildValue("s", "Sucessful file retrival from resource directory");
        else
            return Py_BuildValue("s", std::string("File retrival from resource pylon unsucessful, "+std::string(filename)).c_str());
    }

    Object* requestfile( Object* self, Object* args )
    {
        char* filename;
        if(!PyArg_ParseTuple(args, "s:requestfile", &filename))
            return NULL;
        int ret = FileLoader::ArchiveHandler::extractKnownFile(std::string(filename));
        if(ret == 0)
            return Py_BuildValue("s", std::string("Sucessful file retrival from resource pylon, "+std::string(filename)).c_str());
        else if(ret == -1234)
            return Py_BuildValue("s", "Sucessful file retrival from resource directory");
        else
            return Py_BuildValue("s", std::string("File retrival from resource pylon unsucessful, "+std::string(filename)).c_str());
    }

}
