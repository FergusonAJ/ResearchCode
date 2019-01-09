#pragma once
#include <functional>
#include <string>

#include "../source/base/vector.h"
#include "../source/base/Ptr.h"
#include "../source/tools/Random.h"
#include "../source/base/assert.h"
#include "../source/base/macros.h"

namespace empCA{
    template <class CELL> 
    struct CAFunctionStruct{
        std::string id;
        std::function<CELL(CELL&, const emp::vector<emp::Ptr<CELL>> &)> func_update;
        std::function<CELL(emp::Random &)> func_spawn;
        std::function<std::string(CELL&)> func_print;
        std::function<bool(CELL&, CELL&)> func_cmp;
        std::function<bool(CELL&)> func_alive;
        std::function<CELL(char)> func_from_char;
        std::function<CELL()> func_get_base;
        std::function<CELL(size_t, size_t, size_t)> func_from_color; 
        std::function<uint32_t(CELL)> func_get_color; 
        std::function<CELL()> func_mouse_left; 
        std::function<CELL()> func_mouse_right; 
        std::function<CELL()> func_mouse_middle; 
    };
    
}
