// Collection of helper functions for evolutionary algorithms
// 8/20/18
// Austin Ferguson

#include "ea_utils.h"
#include "constants.h"

std::vector<std::string> genRandomStrings(int numStrings){
    std::vector<std::string> vec;
    int range = ALPHABET_END - ALPHABET_START + 1;
    for(int i = 0; i < numStrings; i++){
        std::string s("");
        for(int j = 0; j < STRING_LENGTH; j++){
            s += (char)(rand() % range + ALPHABET_START);
        }
        vec.push_back(s);
    }
    return vec;
}
