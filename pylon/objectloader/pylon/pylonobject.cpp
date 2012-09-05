#include "../../scriptengine/scriptengine.h"

#include "pylon.h"

namespace ObjectLoader
{
    namespace pylon
    {

        int executeObjectArchive( POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname )
        {
            std::string objectnamespace = ini->getvalue("object", "namespace");

            ScriptEngine::Executor("sys.path.append('./" + location+codeDir + "')\n"/*"import " + objectnamespace + "\n"*/ ).Execute();
            //ScriptEngine::Executor("sys.path.append('./" + location + "')\n"/*"import " + objectnamespace + "\n"*/ ).Execute();

            std::string constructor = ini->getvalue("object", "constructor");

            std::string args[3] = { "str:"+simname, "str:"+objname, "str:"+location };

            ScriptEngine::FunctionCaller function(objectnamespace,constructor,args,3);

            cout << "Executing " << objectnamespace << ", " << constructor << ", " << endl;

            if( object != object->getprogenitor() )
                function.setArg( Py_BuildValue("(ss)", object->getprogenitor()->getsname().c_str(), (":"+objname).c_str()), 1 );

            function.Execute();

            return 0;
        }

        class fractalObject;

        class fractalObjectData
        {
            public:
                std::string simname;
                std::string objname;
                std::string location;
                std::string spawner;
                std::string objectnamespace;
                std::string filler;
                POGEL::OBJECT* object;
                fractalObjectData() {}
        };

        void __fractalObjectFunc( POGEL::FRACTAL* frc, unsigned long itter )
        {
            //fractalObjectData * data = (fractalObjectData*)static_cast<POGEL::FRACTAL*>(frc->getprogenitor())->getData();
            fractalObjectData * data = (fractalObjectData*)frc->getData();

            char * tmp = POGEL::string( "%d", itter );
            std::string itr(tmp);
            delete [] tmp;

            char * ancest = frc->getancestoryhash();
            std::string ancestory(ancest);
            //delete [] ancest;

            //cout << " executing fractal growth " << itter << endl;

            std::string args[5] = { "str:"+data->simname, "str:"+data->objname, "str:"+data->location, "int:"+itr, "str:"+ancestory };
            ScriptEngine::FunctionCaller(data->objectnamespace,data->spawner,args,5).Execute();

            //cout << "node object has " << data->object->getnumfaces() << " faces" << endl;

            //frc->stealtriangles(data->object);
            //data->object->cleartriangles();

            //if( itter < frc->getMaxItteration() )
            {
                //frc->stealChildren(data->object);

                //std::string args2[5] = { "str:"+data->simname, "str:"+data->objname, "str:"+data->location, "int:"+itr, "str:"+ancestory };
                ScriptEngine::FunctionCaller caller(data->objectnamespace,data->filler,args,5);
                //caller.setArgs(args,5);

                unsigned int numchildren = ((POGEL::OBJECT*)data->object)->getNumChildren();

                for( unsigned int i = 0; i < numchildren; ++i )
                {
                    POGEL::FRACTAL * spawnling = frc->spawn();
                    char* name = ((POGEL::OBJECT*)data->object)->getChild(i)->getname();
                    spawnling->setname( name );

                    caller.Execute();

                    spawnling->stealtriangles((POGEL::OBJECT*)data->object);

                    //data->object->getChild(i)->setname(NULL);
                }
            }
            ((POGEL::OBJECT*)data->object)->killchildren();
        }


        int executeFractalArchive( POGEL::OBJECT* object, FileLoader::Ini* ini, const std::string& location, const std::string& codeDir, const std::string& simname, const std::string& objname )
        {
            std::string objectnamespace = ini->getvalue("fractal", "namespace");

            ScriptEngine::Executor("sys.path.append('./" + location+codeDir + "')\n"/*"import " + objectnamespace + "\n"*/ ).Execute();

            std::string constructor = ini->getvalue("fractal", "constructor");
            std::string iterations = ini->getvalue("fractal", "iterations");
            std::string spawner = ini->getvalue("fractal", "spawner");
            std::string filler = ini->getvalue("fractal", "filler");
            unsigned int numItters = 0;
            sscanf( iterations.c_str(), "%d", &numItters );

            fractalObjectData * data = new fractalObjectData();
            data->simname = simname;
            data->objname = objname;
            data->location = location;
            data->object = object;
            data->spawner = spawner;
            data->objectnamespace = objectnamespace;
            data->filler = filler;

            POGEL::FRACTAL * fractal = new POGEL::FRACTAL( (void*)data, __fractalObjectFunc, NULL, numItters );

            fractal->setname((objname+"\0").c_str());

            cout << "creating fractal" << endl;

            fractal->create();

            cout << "condenseing fractal" << endl;

            POGEL::OBJECT * condfractal = fractal->condense();
            object->copytriangles( condfractal );

            cout << "condensed object has " << object->getnumfaces() << " faces" << endl;

            //object->stealtriangles(fractal);
            //object->stealChildren(fractal);
            //object->addobject(condfractal);
            //object->addproperty(OBJECT_DRAW_CHILDREN);

            //cout << "condensed object has " << object->getnumfaces() << " faces" << endl;

            delete condfractal;
            delete fractal;
            delete data;


            std::string args[3] = { "str:"+simname, "str:"+objname, "str:"+location };
            ScriptEngine::FunctionCaller(objectnamespace,constructor,args,3).Execute();

            return 0;
        }
    }
}
