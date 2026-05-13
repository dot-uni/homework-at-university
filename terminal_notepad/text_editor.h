#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include <string>
#include "stack.h"

/*

add() -> +stack_undo, stack_redu - пуст
del() -> +stack_undo, stack_redu - пуст
undo() -> -stack_undo, +stack_redu
redu() -> +stack_undo, -stack_redu

*/

class TextEditor 
{   
    std::string str_;
    Stack<std::pair<std::string, std::string>> stack_undo_, stack_redu_;
    public:
        void add(const std::string& str1);
        std::string del(int n);
        void undu();
        void redu();
        void print() const;
    private:
        void add_base(const std::string& str1);
        std::string del_base(int n);
};

#endif