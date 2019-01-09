//  OrganismShared.h
//  For code shared across all treatments

#pragma once

#include <functional>
#include <map>

#include "tools/string_utils.h"
#include "base/vector.h"

#include "CellularAutomata/CellularAutomaton.h"
#include "CellularAutomata/AllCAs.h"

#include "./Constants.h"
#include "./endLoader.h"
#include "./DefinitionDecoder.h"
#include "./util.h"


//Variables
empCA::CellularAutomaton<unsigned char> ca;
std::function<unsigned char(emp::Random &)> spawnFunc;
int width, height, subWidth, subHeight, subX, subY, numSteps, checkSteps;
size_t numCollaborators;
bool canMove, mustMove;
std::string name;
float mutRateFactor;
unsigned int bBlackMask, sBlackMask;
std::vector<unsigned char> endState;
int max = 0;
emp::Random* randPtr;

//Set up cellulat automaton and load in configuration variables
void Initialize(emp::Random* ptr){
    width = GetConfig().Fetch<int>("WIDTH");
    height = GetConfig().Fetch<int>("HEIGHT");
    subWidth = GetConfig().Fetch<int>("SUB_WIDTH");
    subHeight = GetConfig().Fetch<int>("SUB_HEIGHT");
    subX = GetConfig().Fetch<int>("SUB_X");
    subY = GetConfig().Fetch<int>("SUB_Y");
    numSteps = GetConfig().Fetch<int>("NUM_STEPS");
    mutRateFactor = GetConfig().Fetch<float>("MUT_RATE_SCALE");
    name = GetConfig().Fetch<std::string>("AUTOMATON");
    checkSteps = GetConfig().Fetch<int>("CHECK_STEPS");
    numCollaborators = (size_t)GetConfig().Fetch<int>("NUM_COLLABORATORS");
    canMove = GetConfig().Fetch<bool>("CAN_MOVE");
    mustMove = GetConfig().Fetch<bool>("MUST_MOVE");
    bBlackMask = (unsigned int)(GetConfig().Fetch<int>("B_BLACK_MASK"));
    sBlackMask = (unsigned int)(GetConfig().Fetch<int>("S_BLACK_MASK"));
    LoadFile(endState, GetConfig().Fetch<std::string>("END_STATE"), width, height);
    ca.Resize(width, height);
    ca.SetFunctions(conwayStruct);
    spawnFunc = conwayStruct.func_spawn;
    randPtr = ptr;
}


//Once ca has been set with the right properties, calculate fitness using end state matching
double GetMatchFitness(){
    for(int i = 0; i < numSteps; i++){
        ca.Update();
    } 
    emp::vector<emp::Ptr<unsigned char>> vec = ca.GetField();
    
    double score = 0;
    int w = width;
    int h = height;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(*vec[x + y * w] == endState[x + y * w])
                score++;
        }
    }
    return score / (width * height);
}

//Once ca has been set with the right properties, calculate fitness for static/repeating and glider functions
double GetStaticRepFitness(){
    for(int i = 0; i < numSteps; i++){
        ca.Update();
    } 
    ca.GroupStart();
    std::vector<size_t> validStructures = ca.CheckAllRepeating(checkSteps,canMove,mustMove);
    return (double)validStructures.size(); 
}

//Universal mutation function
//Potentially swap each bit with probability 1/length of org * mutRateFactor (A configuration var)
std::function<size_t(std::vector<bool> &, emp::Random &)> mutate_fun_all = [](std::vector<bool> & org, emp::Random & rand) {
    size_t count = 0;
    float mutRate = 1.0f / org.size() * mutRateFactor;
    for(size_t i = 0; i < org.size(); i++){
        if(rand.GetDouble() < mutRate){
            org[i] = !org[i];
            count++;
        } 
    }  
    return count;
};
