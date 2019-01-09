
#pragma once
#include "../Definitions.h"


//Update
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)> fredkin_update_func = 
    [](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
        unsigned char alive_neighbors = 0;
        for(unsigned char i = 0; i < neighbors.size(); i++){
            if(*neighbors[i] == 1)
                alive_neighbors++;
        }
        if(cell == 1)
            alive_neighbors++;
        if(alive_neighbors % 2 == 1)
            return (unsigned char)1;
        return cell;
};

//Spawn
std::function<unsigned char(emp::Random &)> fredkin_spawn_func = 
    [](emp::Random & rand){
        if(rand.GetDouble() < 0.04)
            return 1;
        return 0;
};

//Print
std::function<std::string(unsigned char &)> fredkin_print_func = 
    [](unsigned char & cell){
        if(cell == 1) return "X";
        return ".";
};

//Compare
std::function<bool(unsigned char &, unsigned char &)> fredkin_cmp_func = 
    [](unsigned char & A, unsigned char & B){
        if(A == 1 && B == 1)
            return true;
        return false;
};

//Alive
std::function<bool(unsigned char &)> fredkin_alive_func = 
    [](unsigned char & A){
        return (A != 0);
};

//From char
std::function<unsigned char(char)> fredkin_from_char_func = 
    [](char c){
        if (c == '#')
            return 1;
        return 0;
};

std::function<unsigned char()> fredkin_get_base_func = 
    [](){
    return 0;
};

std::function<unsigned char(size_t, size_t, size_t)> fredkin_from_color_func = 
    [](size_t r, size_t g, size_t b){
    if(r == 255 && g == 255 && b == 255)
        return (unsigned char)1;
    return (unsigned char)0;  
};

std::function<uint32_t(unsigned char)> fredkin_get_color_func = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(255 << 24 | 255 << 16 | 255 << 8 | 255);
    return (uint32_t)255;
}; 

//Get value for left click
std::function<unsigned char()> fredkin_mouse_left_func =
    [](){ return 1; }; 
//Get value for right click
std::function<unsigned char()> fredkin_mouse_right_func =
    [](){ return 0; }; 
//Get value for middle click
std::function<unsigned char()> fredkin_mouse_middle_func =
    [](){ return 1; }; 

empCA::CAFunctionStruct<unsigned char> fredkinStruct = {
        "FREDKIN",
        fredkin_update_func,
        fredkin_spawn_func,
        fredkin_print_func,
        fredkin_cmp_func,
        fredkin_alive_func,
        fredkin_from_char_func,
        fredkin_get_base_func,
        fredkin_from_color_func,
        fredkin_get_color_func,
        fredkin_mouse_left_func,
        fredkin_mouse_right_func,
        fredkin_mouse_middle_func
}; 
