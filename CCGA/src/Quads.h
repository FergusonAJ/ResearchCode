#pragma once
#include "OrganismShared.h"
#include "Evolve/World.h"
#include "./Classic.h"


//Note: Quads treatment uses some code from the classic treatment


//Variables
emp::World<emp::vector<bool>>* icWorldPtrs[4];
std::vector<std::multimap<double, size_t>*> icFitnessMapPtrs(4);

//Utility functions
void SetICQuadPtr(emp::World<emp::vector<bool>>* ptr, size_t idx){
    icWorldPtrs[idx] = ptr;
}
void SetICQuadFitnessMapPtr(std::multimap<double, size_t>* ptr, size_t idx){
    icFitnessMapPtrs[idx] = ptr;
}
//Get random organism functions
std::vector<bool> GetRandomOrg_Quad_IC(emp::Random& rand){
    return GenerateRandomBitstring(rand, width * height / 4);
}

//Print functions
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_quad_ic = [](std::vector<bool> & org, std::ostream & os) {
    for(int y = 0; y < subHeight / 2; y++){
        for(int x = 0; x < subWidth / 2; x++){
            os << (org[x + y * subWidth]? "1" : "0") << " ";
        }
        os << std::endl;
    }
    os << std::endl;
};


//idx - 0 for ruleset, 1-4 for ICs 1-4
//org - bitstring we are testing
//best - Are we using the highest fitness collaborators? Otherwise pick at random
//iter - If we are using highest fitness, this says to get the nth highest. 
//          This way we aren't always using the absolute highest fitness collaborator. 
void AssembleParts_Quads(size_t idx, std::vector<bool>& org, bool best, size_t iter){
    std::vector<unsigned char> tmp = BitstringToVec(org);
    switch(idx){
        case 0:
            ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
            break;
        case 1:
            ca.AddSubsurface(tmp, 0, 0, subWidth/2);
            break;
        case 2:
            ca.AddSubsurface(tmp, subWidth / 2, 0, subWidth/2);
        break;
        case 3:
            ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth/2);
            break;
        case 4:
            ca.AddSubsurface(tmp, subWidth / 2, subHeight / 2, subWidth/2);
            break;
    }   
    if(idx != 0){
        auto iterR = rulesetFitnessMapPtr->rbegin();
        if(best && rulesetFitnessMapPtr->size() > iter){
            for(size_t n = 1; n <= iter; n++){ 
                iterR++;
            }
            idx = iterR->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        ca.SetUpdateFunc(GetUpdateFunc(rulesetWorldPtr->GetOrg(idx), bBlackMask, sBlackMask));
    }
    if(idx != 1){
        auto iter1 = icFitnessMapPtrs[0]->rbegin();
        if(best && icFitnessMapPtrs[0]->size() > iter){
            for(size_t n = 1; n <= iter; n++){ 
                iter1++;
            }
            idx = iter1->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        tmp = BitstringToVec(icWorldPtrs[0]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 0, subWidth / 2);
    }
    if(idx != 2){
        auto iter2 = icFitnessMapPtrs[1]->rbegin();
        if(best && icFitnessMapPtrs[1]->size() > iter){
            for(size_t n = 1; n <= iter; n++){ 
                iter2++;
            }
            idx = iter2->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        tmp = BitstringToVec(icWorldPtrs[1]->GetOrg(idx));
        ca.AddSubsurface(tmp, subWidth / 2, 0, subWidth / 2);
    }
    if(idx != 3){
        auto iter3 = icFitnessMapPtrs[2]->rbegin();
        if(best && icFitnessMapPtrs[2]->size() > iter){
            for(size_t n = 1; n <= iter; n++){ 
                iter3++;
            }
            idx = iter3->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        tmp = BitstringToVec(icWorldPtrs[2]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, subHeight / 2, subWidth / 2);
    }
    if(idx != 4){
        auto iter4 = icFitnessMapPtrs[3]->rbegin();
        if(best && icFitnessMapPtrs[3]->size() > iter){
            for(size_t n = 1; n < iter; n++){ 
                iter4++;
            }
            idx = iter4->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        tmp = BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, subWidth / 2, subHeight / 2,  subWidth / 2);
    }
}

//org - The organim whose fitness we want to calculate
//idx - 0 for ruleset, 1-4 for ICs 1-4
//func - After assembling the CA, this is the fitness function that will be called. 
double GenericFitnessCalc_Quad(std::vector<bool>& org, size_t idx, double (*func) ()){
    ca.Reset();
    double max = 0;
    double score = 0;
    for(size_t i = 0; i < numBestCollaborators; i++){
        ca.Reset();
        AssembleParts_Quads(idx, org, true, i);
        score = func();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){
        ca.Reset();
        AssembleParts_Quads(idx, org, false, i);
        score = func();
        if(score > max)
            max = score;
    }
    ca.Reset();
    return max;
}

//IC Fitness Functions - End State Matching
auto fit_fun_match_quad_ic_1 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 1, GetMatchFitness);
};
auto fit_fun_match_quad_ic_2 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 2, GetMatchFitness);
};
auto fit_fun_match_quad_ic_3 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 3, GetMatchFitness);
};
auto fit_fun_match_quad_ic_4 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 4, GetMatchFitness);
};

//IC Fitness Functions - Static/Repeating Structures
auto fit_fun_static_rep_quad_ic_1 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 1, GetStaticRepFitness);
};
auto fit_fun_static_rep_quad_ic_2 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 2, GetStaticRepFitness);
};
auto fit_fun_static_rep_quad_ic_3 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 3, GetStaticRepFitness);
};
auto fit_fun_static_rep_quad_ic_4 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 4, GetStaticRepFitness);
};

//Ruleset Fitness Functions
auto fit_fun_match_quad_ruleset = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 0, GetMatchFitness);
};
auto fit_fun_static_rep_quad_ruleset = [](std::vector<bool> & org){
    return GenericFitnessCalc_Quad(org, 0, GetStaticRepFitness);
};
