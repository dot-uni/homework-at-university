#include <cerrno>
#include <iostream>
#include <fstream>

// По условию максимально вяжут руки, так что многое нельзя использовать.

#define STR2(x) #x      // делает строку
#define STR1(x) STR2(x) // чтобы подставился макрос
#define MAKE_ERROR(mess)  std::string("[") + __FILE__ + ':' + STR1(__LINE__) + std::string("] ") + mess

enum ExitCode {
    SUCCESS=0, 
    NOT_FOUND, 
    NOT_ENGH_ARG
};

void set(char** buffer, size_t& idx, std::string str) {
    buffer[idx] = new char[str.length()];
    for (size_t i = 0; i < str.length(); ++i)
        buffer[idx][i] = str[i];
    idx++;
}

void clear(char** buffer, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == nullptr) break;
        delete[] buffer[i];
        buffer[i] = nullptr;
    }
}

void print(char** buffer, const size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == nullptr) break;
        std::cout << buffer[i];
    }
}

size_t fill_template_buffer(const char* file_templ, char** buffer, const size_t buf_size, std::streampos& point) {
    std::ifstream file(file_templ, std::ios::in);
    if (!file.is_open()) {
        std::string mess = MAKE_ERROR(strerror(errno) + " '" + file_templ + "'");
        throw std::runtime_error(mess);
    }
    file.seekg(point);
    size_t idx = 0;
    std::string line;
    std::string line_beg="", line_end = "";
    while(std::getline(file, line)) {
        size_t beg = 0, star = 0;
        while (star != std::string::npos || beg < line.length()) {
            star = line.find('*', beg);
            if (star != std::string::npos) line_beg = line.substr(beg, star-beg);
            else line_beg = line.substr(beg);

            // ...........
            if (star == std::string::npos) {
                point = file.tellg();
                line_end += line_beg + "\n";
                break;
            }
            
            // ..........*
            if (star+1 >= line.length()) {
                point += star;
                line_end += line_beg;     
                set(buffer, idx, line_end);
                line_end = "\n";
                if (idx >= buf_size) { 
                    return idx;
                }
                break;
            }

            // *.........
            if (star == 0) {
                point += 1;
                if (line_end.length() != 0) {
                    set(buffer, idx, line_end);
                    line_end = "";
                }
                if (idx >= buf_size) { 
                    return idx;
                }
                beg += 1;
                continue;         
            }

            // .....*.....
            point += star;
            if (line_end.length() != 0) {
                line_end += line_beg;
                set(buffer, idx, line_end);
                line_end = "";
                if (idx >= buf_size) { 
                    return idx;
                }
                beg = star+1;
                continue;
            }
            set(buffer, idx, line_beg);
            if (idx >= buf_size) { 
                return idx;
            }
            beg = star+1;
        }
    }
    if (line_end.length() != 0 && idx != buf_size) {
        set(buffer, idx, line_end);
        point = file.tellg();
    }
    if (file.tellg() == -1) point = file.tellg();
    file.close();
    return idx;
}

void write_in_file(std::string* array_names, const size_t size_names, char** buffer_templ, const size_t size_templ, std::streampos& point, char& flag) {
    std::string path = "./cpp_code/hw/results/";
    for (size_t i = 0; i < size_names; ++i) {
        std::string name = array_names[i];
        if (name.length() == 0) break;
        std::string file_name =  path + name + ".txt";
        std::ofstream file;
        if (flag != 0) {
            file.open(file_name, std::ios::app);
            if(!file.is_open()) {
                std::string mess = MAKE_ERROR(strerror(errno) + " '" + file_name + "'");
                throw std::runtime_error(mess);
            }
            for (size_t j = 0; j < size_templ; ++j) {
                if (buffer_templ[j][-1] == '\n') {
                    j++; continue;
                }
                file << buffer_templ[j];
                if (j != (size_templ-1) || point != -1) file << name;
            }
        }
        else {
            file.open(file_name, std::ios::out);
            if(!file.is_open()) {
                std::string mess = MAKE_ERROR(strerror(errno) + " '" + file_name + "'");
                throw std::runtime_error(mess);
            }
            for (size_t j = 0; j < size_templ; ++j) {
                if (buffer_templ[j][-1] == '\n') {
                    j++; continue;
                }
                file << buffer_templ[j];
                if (j != (size_templ-1) || point != -1) file << name;
            }
        }
        file.close();
    }
    if (flag == 0) flag = 1;
}

std::string* extention(std::string* array, size_t& arr_size) {
    size_t new_size = arr_size*2;
    std::string* new_array = new std::string[new_size];
    for (size_t i = 0; i < arr_size; ++i) {
        new_array[i] = array[i];
    }
    arr_size = new_size;
    delete[] array;
    return new_array;
}

size_t fill_names_array(const char* file_names, std::string*& array_names, size_t arr_size) {
    std::ifstream file(file_names, std::ios::in);
    if(!file.is_open()) {
        std::string mess = MAKE_ERROR(strerror(errno) + " '" + file_names + "'");
        throw std::runtime_error(mess);
    }
    size_t idx = 0;
    array_names = new std::string[arr_size];
    std::string line;
    while(std::getline(file, line)) {
        if (idx == arr_size) {
            array_names = extention(array_names, arr_size);
        }
        array_names[idx++] = line;
    }
    file.close();
    return arr_size;
}

ExitCode insert_template(const char* file_templ, const char* file_names) {
    try {
        std::streampos point_templ = 0;
        size_t idx_templ = 0;
        size_t idx_names = 0;
        const size_t size_templ = 100; 
        const size_t size_names = 100; 
        char* buffer_templ[size_templ];
        char flag = 0;
        std::string* array_names;
        idx_names = fill_names_array(file_names, array_names, size_names);
        while (point_templ != -1) {
            idx_templ = fill_template_buffer(file_templ, buffer_templ, size_templ, point_templ);
            write_in_file(array_names, idx_names, buffer_templ, idx_templ, point_templ, flag);
            clear(buffer_templ, idx_templ);
            idx_templ = 0;
        }
        delete[] array_names;
    } catch(std::runtime_error& mess) {
        std::cerr << mess.what() << "\n";
        return NOT_FOUND;
    }
    return SUCCESS;
}


int main(int argc, char** argv) {
    ExitCode code;
    if (argc != 1) {
        code = insert_template(argv[1], argv[2]);
    }
    else {
        std::cerr << MAKE_ERROR("Not enough input data") << "\n";
        return NOT_ENGH_ARG;
    }
    return code;
}
