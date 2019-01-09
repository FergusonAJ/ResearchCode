
//  DEPRECATED
//  This file has been superceded by individual header files for the different treatments
//  See ./OrganismShared.h for code shared amongst the different treatments
//  For ./Control.h ./Classic.h ./Quads.h ./Stripes.h for code unique to each treatment


#include <functional>

#include "tools/string_utils.h"
#include "base/vector.h"

#include "../../../CellularAutomata/CellularAutomaton.h"
#include "../../../CellularAutomata/AllCAs.h"

#include "./Constants.h"
#include "./endLoader.h"
#include "./DefinitionDecoder.h"

empCA::CellularAutomaton<unsigned char> ca;
empCA::Visualizer<unsigned char> viz;
std::function<unsigned char(emp::Random &)> spawnFunc;
int width, height, subWidth, subHeight, subX, subY, numSteps, checkSteps;
bool canMove, mustMove;
std::string name;
float mutRate;
std::vector<unsigned char> endState;
int max = 0;


void Initialize(){
    width = GetConfig().Fetch<int>("WIDTH");
    height = GetConfig().Fetch<int>("HEIGHT");
    subWidth = GetConfig().Fetch<int>("SUB_WIDTH");
    subHeight = GetConfig().Fetch<int>("SUB_HEIGHT");
    subX = GetConfig().Fetch<int>("SUB_X");
    subY = GetConfig().Fetch<int>("SUB_Y");
    numSteps = GetConfig().Fetch<int>("NUM_STEPS");
    mutRate = (1.0f / GetConfig().Fetch<float>("MUT_RATE_RECIPROCAL"));
    name = GetConfig().Fetch<std::string>("AUTOMATON");
    checkSteps = GetConfig().Fetch<int>("CHECK_STEPS");
    canMove = GetConfig().Fetch<bool>("CAN_MOVE");
    mustMove = GetConfig().Fetch<bool>("MUST_MOVE");
    LoadFile(endState, GetConfig().Fetch<std::string>("END_STATE"), width, height);
    ca.Resize(width, height);
    bool isValidAutomata = false;
    for(size_t i = 0; i < automataStructs.size(); i++){
        if(name.compare(automataStructs[i].id) == 0){
            ca.SetFunctions(automataStructs[i]);
            spawnFunc = automataStructs[i].func_spawn;
            isValidAutomata = true;
            break;
        }
    }
    if(!isValidAutomata){
        std::cout << "Using customized automaton." << std::endl;
        std::vector<unsigned char> B;
        std::vector<unsigned char> S;
        LoadBSVectors(name, B, S);
        auto update_func = GetUpdateFunc(B, S);
        ca.SetFunctions(conwayStruct);
        spawnFunc = conwayStruct.func_spawn;
        ca.SetUpdateFunc(update_func);////LoadCustomAutomaton(name));
    }
}

void VisualizerInit(empCA::Visualizer<unsigned char>& v){
    for(size_t i = 0; i < automataStructs.size(); i++){
        if(name.compare(automataStructs[i].id) == 0){
            viz.SetFunctions(automataStructs[i]);
            break;
        }
    }
}

emp::vector<unsigned char> GetRandomOrg(emp::Random& rand){
    emp::vector<unsigned char> vec;
    vec.resize(subWidth * subHeight,0);
    for(size_t i = 0; i < vec.size(); i++){
        vec[i] = spawnFunc(rand);
    }
    return vec;
}

empCA::Visualizer<unsigned char>* GetVisualizer(size_t width, size_t height){
    viz.Init(width, height, &ca);
    VisualizerInit(viz);
    return &viz;
}


std::function<size_t(emp::vector<unsigned char> &, emp::Random &)> mutate_fun = [](emp::vector<unsigned char> & org, emp::Random & rand) {
    size_t count = 0;
    for(size_t i = 0; i < org.size(); i++){
        if(rand.GetDouble() < mutRate){
            org[i] = (org[i] == 0) ? 1 : 0;
            count++;
        } 
    }  
    return count;
};

std::function<void(emp::vector<unsigned char> &, std::ostream &)> print_fun = [](emp::vector<unsigned char> & org, std::ostream & os) {
    for(int y = 0; y < subHeight; y++){
        for(int x = 0; x < subWidth; x++){
            os << (char)('0' + org[x + y * subWidth]) << " ";
        }
        os << std::endl;
    }
    os << std::endl;
};

auto fit_fun_match = [](emp::vector<unsigned char> & org){
    ca.Reset();
    ca.AddSubsurface(org, subX, subY, subWidth);
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
};

auto fit_fun_static_rep = [](emp::vector<unsigned char> & org){
    ca.Reset();
    ca.AddSubsurface(org, subX, subY, subWidth);
    for(int i = 0; i < numSteps; i++){
        ca.Update();
    } 
    ca.GroupStart();
    std::vector<size_t> validStructures = ca.CheckAllRepeating(checkSteps,canMove,mustMove);
    double score = (double)validStructures.size(); 
    if(score > max){
        max = score;
        ca.GroupStart();
        ca.PrintGroupFlat(std::cout);
        for(size_t val : validStructures){
            std::cout << val << " ";
        }
        std::cout << std::endl;
        std::cout << score << std::endl;
    }
    return score;
};
