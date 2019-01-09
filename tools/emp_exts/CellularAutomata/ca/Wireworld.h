#include "../CellularAutomaton.h"
#define WW_EMPTY 0
#define WW_WIRE 1
#define WW_HEAD 2
#define WW_TAIL 3

//Update
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)> wireworld_update_func = 
    [](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
        unsigned char active_neighbors = 0;
        switch(cell){
            case WW_HEAD:
                return (unsigned char) WW_TAIL;
            break;
            case WW_TAIL:
                return (unsigned char) WW_WIRE;
            break;
            case WW_WIRE:
                for(unsigned char i = 0; i < neighbors.size(); i++){
                    if(*neighbors[i] == WW_HEAD)
                        active_neighbors++;
                }
                if(active_neighbors == 1 || active_neighbors == 2)
                    return (unsigned char)WW_HEAD;
                return (unsigned char)WW_WIRE;
            break;
            case WW_EMPTY:
            default:
                return (unsigned char)WW_EMPTY;
            break;
            
        }
};

//Spawn
std::function<unsigned char(emp::Random &)> wireworld_spawn_func = 
    [](emp::Random & rand){
        if(rand.GetDouble() < 0.1)
            return WW_HEAD;
        if(rand.GetDouble() < 0.2)
            return WW_WIRE;
        return WW_EMPTY;
};

//Print
std::function<std::string(unsigned char &)> wireworld_print_func = 
    [](unsigned char & cell){
        switch(cell){
            case WW_HEAD:
                return "O";
            break;
            case WW_TAIL:
                return "!";
            break;
            case WW_WIRE:
                return "X";
            break;
            case WW_EMPTY:
            default:
                return ".";
            break;
        }
};

//Compare
std::function<bool(unsigned char &, unsigned char &)> wireworld_cmp_func = 
    [](unsigned char & A, unsigned char & B){
        if(A == WW_WIRE && B == WW_WIRE)
            return true;
        if(A == WW_HEAD && B == WW_HEAD)
            return true;
        return false;
};

//Alive
std::function<bool(unsigned char &)> wireworld_alive_func = 
    [](unsigned char & A){
        return (A == WW_HEAD);
};

//From char
std::function<unsigned char(char)> wireworld_from_char_func = 
    [](char c){
        switch(c){
            case '#':
                return WW_WIRE;
            case 'O':
                return WW_HEAD;
            case '!':
                return WW_TAIL;
        }
        return WW_EMPTY;
};

std::function<unsigned char()> wireworld_get_base_func = 
    [](){
    return WW_EMPTY;
};

std::function<unsigned char(size_t, size_t, size_t)> wireworld_from_color_func = 
    [](size_t r, size_t g, size_t b){
    if(r == 255 && g == 255 && b == 0)
        return (unsigned char)WW_WIRE;
    else if(r == 255 && g == 0 && b == 0)
        return (unsigned char)WW_HEAD;
    else if(r == 0 && g == 0 && b == 255)
        return (unsigned char)WW_TAIL;
    return (unsigned char)WW_EMPTY;  
};

std::function<uint32_t(unsigned char)> wireworld_get_color_func = 
    [](unsigned char c){
    if(c == WW_WIRE)
        return (uint32_t)(255 << 24 | 255 << 16 | 0 << 8 | 255);
    else if(c == WW_HEAD)
        return (uint32_t)(255 << 24 | 0 << 16 | 0 << 8 | 255);
    else if(c == WW_TAIL)
        return (uint32_t)(0 << 24 | 0 << 16 | 255 << 8 | 255);
    return (uint32_t)255;
};  

std::function<uint32_t(unsigned char)> wireworld_get_color_func_alt = 
    [](unsigned char c){
    if(c == WW_WIRE)
        return (uint32_t)(100 << 24 | 100 << 16 | 100 << 8 | 255);
    else if(c == WW_HEAD)
        return (uint32_t)(200 << 24 | 200 << 16 | 0 << 8 | 255);
    else if(c == WW_TAIL)
        return (uint32_t)(150 << 24 | 150 << 16 | 0 << 8 | 255);
    return (uint32_t)255;
};

//Get value for left click
std::function<unsigned char()> wireworld_mouse_left_func =
    [](){ return WW_WIRE; }; 
//Get value for right click
std::function<unsigned char()> wireworld_mouse_right_func =
    [](){ return WW_EMPTY; }; 
//Get value for middle click
std::function<unsigned char()> wireworld_mouse_middle_func =
    [](){ return WW_HEAD; };
  
empCA::CAFunctionStruct<unsigned char> wireworldStruct = {
        "WIREWORLD",
        wireworld_update_func,
        wireworld_spawn_func,
        wireworld_print_func,
        wireworld_cmp_func,
        wireworld_alive_func,
        wireworld_from_char_func,
        wireworld_get_base_func,
        wireworld_from_color_func,
        wireworld_get_color_func,
        wireworld_mouse_left_func,
        wireworld_mouse_right_func,
        wireworld_mouse_middle_func
}; 
