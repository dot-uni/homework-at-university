#include <iostream>
#include "text_editor.h"

int main() {
    TextEditor text_editor;
    std::string mess;
    while(true) {
        std::getline(std::cin, mess);
        if (mess.empty()) continue;
        
        size_t pos = mess.find(' ');
        std::string command = mess.substr(0, pos);
        std::string text = mess.substr(pos+1);

        if (command == "exit") break;
        else if (command == "add") text_editor.add(text);
        else if (command == "del") text_editor.del(std::stoi(text));
        else if (command == "undo") text_editor.undo();
        else if (command == "redu") text_editor.redu();
        else if (command == "print") text_editor.print();
        else throw std::runtime_error(std::string("Такой команды не существует '") + mess + "'\n");
    }
    return 0;
}