#include "../CellularAutomaton.h"
#include "../Definitions.h"

//Update
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)> conway_update_func = 
    [](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
        unsigned char alive_neighbors = 0;
        for(unsigned char i = 0; i < neighbors.size(); i++){
            if(*neighbors[i] == 1)
                alive_neighbors++;
        }
        if(alive_neighbors == 3)
            return (unsigned char)1;
        else if (alive_neighbors == 2)
            return cell;
        return (unsigned char)0;
};

//Spawn
std::function<unsigned char(emp::Random &)> conway_spawn_func = 
    [](emp::Random & rand){
        if(rand.GetDouble() < 0.2)
            return 1;
        return 0;
};

//Print
std::function<std::string(unsigned char &)> conway_print_func = 
    [](unsigned char & cell){
        if(cell == 1) return "X";
        return ".";
};

//Compare
std::function<bool(unsigned char &, unsigned char &)> conway_cmp_func = 
    [](unsigned char & A, unsigned char & B){
        if(A == 1 && B == 1)
            return true;
        return false;
};

//Alive
std::function<bool(unsigned char &)> conway_alive_func = 
    [](unsigned char & A){
        return (A != 0);
};

//From char
std::function<unsigned char(char)> conway_from_char_func = 
    [](char c){
        if (c == '#')
            return 1;
        return 0;
};

//Basic cell
std::function<unsigned char()> conway_get_base_func = 
    [](){
    return 0;
};

//Get value from a color
std::function<unsigned char(size_t, size_t, size_t)> conway_from_color_func = 
    [](size_t r, size_t g, size_t b){
    if(r == 255 && g == 255 && b == 255)
        return (unsigned char)1;
    return (unsigned char)0;  
};

//Get color from a value
std::function<uint32_t(unsigned char)> conway_get_color_func = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(255 << 24 | 255 << 16 | 255 << 8 | 255);
    return (uint32_t)255;
};  

//Fun
std::function<uint32_t(unsigned char)> conway_get_color_func_alt = 
    [](unsigned char c){
    if(c == 1)
        return (uint32_t)(0 << 24 | 175 << 16 | 250 << 8 | 255);
    return (uint32_t)(0 << 24 | 50 << 16 | 200 << 8 | 255);
};  
std::function<unsigned char(size_t, size_t, size_t)> conway_from_color_func_alt = 
    [](size_t r, size_t g, size_t b){
    if(r == 0 && g == 175 && b == 250)
        return (unsigned char)1;
    return (unsigned char)0;  
};

//Get value for left click
std::function<unsigned char()> conway_mouse_left_func =
    [](){ return 1; };
//Get value for right click
std::function<unsigned char()> conway_mouse_right_func =
    [](){ return 0; };
//Get value for middle click
std::function<unsigned char()> conway_mouse_middle_func =
    [](){ return 1; }; 

empCA::CAFunctionStruct<unsigned char> conwayStruct = {
        "CONWAY",
        conway_update_func,
        conway_spawn_func,
        conway_print_func,
        conway_cmp_func,
        conway_alive_func,
        conway_from_char_func,
        conway_get_base_func,
        conway_from_color_func,
        conway_get_color_func,
        conway_mouse_left_func,
        conway_mouse_right_func,
        conway_mouse_middle_func
}; 
