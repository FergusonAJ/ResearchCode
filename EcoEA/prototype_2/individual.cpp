// Class defining one individual in the EA's population. Currently just a string wrapper.
// 8/20/18
// Austin Ferguson

#include "individual.h"

Individual::Individual(std::string data){
    mData = data;
}

Individual::~Individual(){

}

std::string Individual::getString() const{
    return mData;
}

Individual Individual::getMutation(){
    std::string newS("");
    int range = ALPHABET_END - ALPHABET_START + 1;
    for(int i = 0; i < mData.length(); i++)
    {
        if((double)rand() / RAND_MAX < MUT_RATE){
            char c = rand() % range + ALPHABET_START;
            newS += c;
        }
        else
            newS += mData[i];
    }
    return Individual(newS);
}

Individual Individual::getCrossover(Individual other){
    std::string newS("");
    std::string otherData = other.getString();
    for(int i = 0; i < mData.length(); i++)
    {
        if((double)rand() / RAND_MAX < 0.5){
            newS += otherData[i];
        }
        else
            newS += mData[i];
    }
    return Individual(newS);
}
