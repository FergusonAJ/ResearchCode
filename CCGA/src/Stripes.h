#pragma once
#include "OrganismShared.h"
#include "Evolve/World.h"
#include "./Quads.h"


//Note: Stripes treatment does reuse code from quads and classic


//Print functions
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_stripe_ic = [](std::vector<bool> & org, std::ostream & os) {
    for(int y = 0; y < height / 4; y++){
        for(int x = 0; x < width; x++){
            os << (org[x + y * width]? "1" : "0") << " ";
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
void AssembleParts_Stripes(size_t idx, std::vector<bool>& org, bool best, size_t iter){
    std::vector<unsigned char> tmp = BitstringToVec(org);
    switch(idx){
        case 0:
            ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
            break;
        case 1:
            ca.AddSubsurface(tmp, 0, 0, width);
            break;
        case 2:
            ca.AddSubsurface(tmp, 0, height / 4, width);
        break;
        case 3:
            ca.AddSubsurface(tmp, 0, height / 2, width);
            break;
        case 4:
            ca.AddSubsurface(tmp, 0, 3 * height / 4, width);
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
        ca.AddSubsurface(tmp, 0, 0, width);
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
        ca.AddSubsurface(tmp, 0, height / 4, width);
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
        ca.AddSubsurface(tmp, 0, height / 2, width);
    }
    if(idx != 4){
        auto iter4 = icFitnessMapPtrs[3]->rbegin();
        if(best && icFitnessMapPtrs[3]->size() > iter){
            for(size_t n = 1; n <= iter; n++){ 
                iter4++;
            }
            idx = iter4->second;
        }
        else{
            idx = randPtr->GetUInt(0, rulesetWorldPtr->GetSize());    
        }
        tmp = BitstringToVec(icWorldPtrs[3]->GetOrg(idx));
        ca.AddSubsurface(tmp, 0, 3 * height / 4,  width);
    }
}

//org - The organim whose fitness we want to calculate
//idx - 0 for ruleset, 1-4 for ICs 1-4
//func - After assembling the CA, this is the fitness function that will be called. 
double GenericFitnessCalc_Stripes(std::vector<bool>& org, size_t idx, double (*func) ()){
    ca.Reset();
    double max = 0;
    double score = 0;
    for(size_t i = 0; i < numBestCollaborators; i++){
        ca.Reset();
        AssembleParts_Stripes(idx, org, true, i);
        score = func();
        if(score > max)
            max = score;
    }
    for(size_t i = 0; i < numRandCollaborators; i++){
        ca.Reset();
        AssembleParts_Stripes(idx, org, false, i);
        score = func();
        if(score > max)
            max = score;
    }
    ca.Reset();
    return max;
}

//IC Fitness Functions - End State Matching
auto fit_fun_match_stripe_ic_1 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 1, GetMatchFitness);
};
auto fit_fun_match_stripe_ic_2 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 2, GetMatchFitness);
};
auto fit_fun_match_stripe_ic_3 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 3, GetMatchFitness);
};
auto fit_fun_match_stripe_ic_4 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 4, GetMatchFitness);
};

//IC Fitness Functions - Statis/Repeating Structures
auto fit_fun_static_rep_stripe_ic_1 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 1, GetStaticRepFitness);
};
auto fit_fun_static_rep_stripe_ic_2 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 2, GetStaticRepFitness);
};
auto fit_fun_static_rep_stripe_ic_3 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 3, GetStaticRepFitness);
};
auto fit_fun_static_rep_stripe_ic_4 = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 4, GetStaticRepFitness);
};

//Ruleset Fitness Functions
auto fit_fun_match_stripe_ruleset = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 0, GetMatchFitness);
};
auto fit_fun_static_rep_stripe_ruleset = [](std::vector<bool> & org){
    return GenericFitnessCalc_Stripes(org, 0, GetStaticRepFitness);
};
