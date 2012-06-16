#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifndef SCRIPTENGINE_H_INCLUDED
#include "scriptengine.h"
#endif // SCRIPTENGINE_H_INCLUDED

#define SIMPLE_EXECUTION

namespace ScriptEngine
{
    class Executor
    {
        protected:
            std::string instructions;
        public:
            Executor();
            Executor( const std::string& );
            virtual ~Executor();
            virtual Executor& operator=(const Executor& other);

            virtual void Execute();

            std::string getInstructions();
            virtual std::string getResult();
            virtual void setArgs(std::string*,unsigned int) {}
    };

    class FileExecutor : public Executor
    {
        public:
            FileExecutor( const std::string& );
            virtual ~FileExecutor();

            void Execute();
    };

    class FunctionCaller : public Executor
    {
        protected:
            ClassList<std::string> arguments;
            std::string function;
            std::string result;
            bool outsidefunction;
        public:
            FunctionCaller( const std::string& );
            FunctionCaller( const std::string&, bool );
            FunctionCaller( const std::string&, const std::string&, std::string*, unsigned int );
            FunctionCaller( const std::string&, const std::string&, std::string*, unsigned int, bool );
            virtual ~FunctionCaller();

            void setArgs( std::string*, unsigned int );

            void Execute();

            void call( const std::string&, std::string*, unsigned int, std::string* );

            std::string getResult();
    };
}

#endif // EXECUTOR_H
