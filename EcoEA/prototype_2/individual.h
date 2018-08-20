// Class defining one individual in the EA's population. Currently just a string wrapper.
// 8/20/18
// Austin Ferguson

#pragma once

#include <string>
#include <iostream>

#include "constants.h"

class Individual{
public:
    Individual(std::string);
    ~Individual();
    std::string getString() const;
    Individual getMutation();
    Individual getCrossover(Individual other);
protected:
    std::string mData;

};

inline std::ostream& operator<<(std::ostream& f, const Individual& ind){
    f << ind.getString();
}
