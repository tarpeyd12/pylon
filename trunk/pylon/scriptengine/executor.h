#ifndef EXECUTOR_H
#define EXECUTOR_H

#ifndef SCRIPTENGINE_H_INCLUDED
#include "scriptengine.h"
#endif // SCRIPTENGINE_H_INCLUDED

namespace ScriptEngine
{
    class Executor
    {
        protected:
            std::string instructions;
        public:
            Executor();
            Executor(std::string);
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
            FileExecutor(std::string inst);
            virtual ~FileExecutor();

            void Execute();
    };

    class FunctionCaller : public Executor
    {
        protected:
            ClassList<std::string> arguments;
            std::string function;
            std::string result;
        public:
            FunctionCaller(std::string);
            FunctionCaller(std::string,std::string,std::string*,unsigned int);
            virtual ~FunctionCaller();

            void setArgs(std::string*,unsigned int);

            void Execute();

            void call(std::string func, std::string* args, unsigned int numArgs, std::string* res);

            std::string getResult();
    };
}

#endif // EXECUTOR_H
