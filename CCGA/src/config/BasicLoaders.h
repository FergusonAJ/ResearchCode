#pragma once
#include <string>

//Integers
std::function<void *(std::string&)> loader_int =
    [](std::string& s){
        int* tmp = new int;
        *tmp = std::stoi(s);
        return (void*)tmp;
};
std::function<void(void*)> delete_int = 
    [](void* p){
       delete (int*) p;
};

//Floats
std::function<void *(std::string&)> loader_float =
    [](std::string& s){
        float* tmp = new float;
        *tmp = std::stof(s);
        return (void*)tmp;
};
std::function<void(void*)> delete_float = 
    [](void* p){
       delete (float*) p;
};

//Chars
std::function<void *(std::string&)> loader_char =
    [](std::string& s){
        char* tmp = new char;
        *tmp = s[0];
        return (void*)tmp;
};
std::function<void(void*)> delete_char = 
    [](void* p){
       delete (char*) p;
};

//Strings
std::function<void *(std::string&)> loader_string =
    [](std::string& s){
        std::string* newS = new std::string(s);
        return (void*)newS;
};
std::function<void(void*)> delete_string = 
    [](void* p){
       delete (std::string*) p;
};

//Bools
std::function<void *(std::string&)> loader_bool =
    [](std::string& s){
        bool* b = new bool;
        *b = false;
        if(s.compare("TRUE") == 0 || s.compare("T") == 0)
            *b = true;
        return (void*)b;
};
std::function<void(void*)> delete_bool = 
    [](void* p){
       delete (bool*) p;
};
