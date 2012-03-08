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

            void Execute();

            std::string getInstructions();
    };

    class FileExecutor : public Executor
    {
        public:
            FileExecutor(std::string inst);
            FileExecutor(const Executor&);
            virtual ~FileExecutor();

            void Execute();
    };

    class FunctionCaller : public ScriptEngine::Executor
    {
        public:
            FunctionCaller(std::string);
            virtual ~FunctionCaller();

            void call(std::string func, std::string* args, unsigned int numArgs);
    };
}

#endif // EXECUTOR_H
