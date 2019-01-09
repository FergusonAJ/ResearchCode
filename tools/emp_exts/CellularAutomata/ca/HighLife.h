#include "../CellularAutomaton.h"
#include "../Definitions.h"

//Update
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)> highlife_update_func = 
    [](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
        unsigned char alive_neighbors = 0;
        for(unsigned char i = 0; i < neighbors.size(); i++){
            if(*neighbors[i] == 1)
                alive_neighbors++;
        }
        if(cell == 0 && (alive_neighbors == 3 || alive_neighbors == 6))
            return (unsigned char)1;
        else if (cell == 1 && (alive_neighbors == 2 || alive_neighbors == 3))
            return (unsigned char)1;
        return (unsigned char)0;
};

//Spawn
std::function<unsigned char(emp::Random &)> highlife_spawn_func = 
    [](emp::Random & rand){
        if(rand.GetDouble() < 0.2)
            return 1;
        return 0;
};

//Print
std::function<std::string(unsigned char &)> highlife_print_func = 
    [](unsigned char & cell){
        if(cell == 1) return "X";
        return ".";
};

//Compare
std::function<bool(unsigned char &, unsigned char &)> highlife_cmp_func = 
    [](unsigned char & A, unsigned char & B){
        if(A == 1 && B == 1)
            return true;
        return false;
};

//Alive
std::function<bool(unsigned char &)> highlife_alive_func = 
    [](unsigned char & A){
        return (A != 0);
};

//From char
std::function<unsigned char(char)> highlife_from_char_func = 
    [](char c){
        if (c == '#')
            return 1;
        return 0;
};

//Basic cell
std::function<unsigned char()> highlife_get_base_func = 
    [](){
    return 0;
};

//Get value from a color
std::function<unsigned char(size_t, size_t, size_t)> highlife_from_color_func = 
    [](size_t r, size_t g, size_t b){
    if(r == 255 && g == 255 && b == 255)
        return (unsigned char)1;
    return (unsigned char)0;  
};

//Get color from a value
std::function<uint32_t(unsigned char)> highlife_get_color_func = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(255 << 24 | 255 << 16 | 255 << 8 | 255);
    return (uint32_t)255;
};  

//Fun
std::function<uint32_t(unsigned char)> highlife_get_color_func_alt = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(0 << 24 | 175 << 16 | 250 << 8 | 255);
    return (uint32_t)(0 << 24 | 50 << 16 | 200 << 8 | 255);
};  

//Get value for left click
std::function<unsigned char()> highlife_mouse_left_func =
    [](){ return 1; };
//Get value for right click
std::function<unsigned char()> highlife_mouse_right_func =
    [](){ return 0; };
//Get value for middle click
std::function<unsigned char()> highlife_mouse_middle_func =
    [](){ return 1; }; 

empCA::CAFunctionStruct<unsigned char> highlifeStruct = {
        "HIGHLIFE",
        highlife_update_func,
        highlife_spawn_func,
        highlife_print_func,
        highlife_cmp_func,
        highlife_alive_func,
        highlife_from_char_func,
        highlife_get_base_func,
        highlife_from_color_func,
        highlife_get_color_func,
        highlife_mouse_left_func,
        highlife_mouse_right_func,
        highlife_mouse_middle_func
}; 
