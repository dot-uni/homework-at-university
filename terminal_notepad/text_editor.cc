#include <iostream>
#include "text_editor.h"


void TextEditor::add(const std::string& str1) {
    str_ += str1;
    auto pr = std::make_pair("add", str1);
    stack_undo_.push(pr);
    stack_redu_.clear();
}

std::string TextEditor::del(int n) {
    std::string tail = del_base(n);

    auto pr = std::make_pair("del", tail);
    stack_undo_.push(pr);
    stack_redu_.clear();
    return tail;
}

void TextEditor::undo() {
    if (!stack_undo_.empty()) {
        auto pr = stack_undo_.pop();
        std::pair<std::string, std::string> pr_redu;
        if (pr.first == "add") { 
            del_base(pr.second.length());
            pr_redu = {"del", pr.second};
        }
        else if (pr.first == "del") { 
            add_base(pr.second);
            pr_redu = {"add", pr.second};
        }
        stack_redu_.push(pr_redu);
    }
}

void TextEditor::redu() {
    if (!stack_redu_.empty()) {
        auto pr = stack_redu_.pop();
        std::pair<std::string, std::string> pr_undo;
        if (pr.first == "add") { 
            del_base(pr.second.length());
            pr_undo = {"del", pr.second};
        }
        else if (pr.first == "del") { 
            add_base(pr.second);
            pr_undo = {"add", pr.second};
        }
        stack_undo_.push(pr_undo);
    }
}

void TextEditor::print() const {
    std::cout << "text_editor:: "<< str_ << "\n";
}

void TextEditor::add_base(const std::string& str1) {
    str_ += str1;
}

std::string TextEditor::del_base(int n) {
    if (n <= 0) throw std::runtime_error("Значение переменной n должно быть натуральным числом.\n");
    size_t len = str_.length();
    std::string tail = str_.substr(len - n, len);
    str_.resize(len - n);
    return tail;
}