#pragma once
#include "../Definitions.h"


//Update
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)> replicator_update_func = 
    [](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
        unsigned char alive_neighbors = 0;
        for(unsigned char i = 0; i < neighbors.size(); i++){
            if(*neighbors[i] == 1)
                alive_neighbors++;
        }
        if(alive_neighbors % 2 == 1)
            return (unsigned char)1;
        return (unsigned char)0;
};

//Spawn
std::function<unsigned char(emp::Random &)> replicator_spawn_func = 
    [](emp::Random & rand){
        if(rand.GetDouble() < 0.04)
            return 1;
        return 0;
};

//Print
std::function<std::string(unsigned char &)> replicator_print_func = 
    [](unsigned char & cell){
        if(cell == 1) return "X";
        return ".";
};

//Compare
std::function<bool(unsigned char &, unsigned char &)> replicator_cmp_func = 
    [](unsigned char & A, unsigned char & B){
        if(A == 1 && B == 1)
            return true;
        return false;
};

//Alive
std::function<bool(unsigned char &)> replicator_alive_func = 
    [](unsigned char & A){
        return (A != 0);
};

//From char
std::function<unsigned char(char)> replicator_from_char_func = 
    [](char c){
        if (c == '#')
            return 1;
        return 0;
};

std::function<unsigned char()> replicator_get_base_func = 
    [](){
    return 0;
};

std::function<unsigned char(size_t, size_t, size_t)> replicator_from_color_func = 
    [](size_t r, size_t g, size_t b){
    if(r == 255 && g == 255 && b == 255)
        return (unsigned char)1;
    return (unsigned char)0;  
};

std::function<uint32_t(unsigned char)> replicator_get_color_func = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(255 << 24 | 255 << 16 | 255 << 8 | 255);
    return (uint32_t)255;
}; 

//Get value for left click
std::function<unsigned char()> replicator_mouse_left_func =
    [](){ return 1; }; 
//Get value for right click
std::function<unsigned char()> replicator_mouse_right_func =
    [](){ return 0; }; 
//Get value for middle click
std::function<unsigned char()> replicator_mouse_middle_func =
    [](){ return 1; }; 

empCA::CAFunctionStruct<unsigned char> replicatorStruct = {
        "REPLICATOR",
        replicator_update_func,
        replicator_spawn_func,
        replicator_print_func,
        replicator_cmp_func,
        replicator_alive_func,
        replicator_from_char_func,
        replicator_get_base_func,
        replicator_from_color_func,
        replicator_get_color_func,
        replicator_mouse_left_func,
        replicator_mouse_right_func,
        replicator_mouse_middle_func
}; 
