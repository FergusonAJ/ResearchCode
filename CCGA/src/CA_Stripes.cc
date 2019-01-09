//  Evolutionary Computing Term Project
//  Investigating Cooperative Co-Evolution Modularity Using Cellular Automata
//  Austin J. Ferguson
//  11/9/2018

//  Main program for stripes runs 

//  This file uses parts of Empirical, https://github.com/devosoft/Empirical
//  Copyright (C) Michigan State University, 2016-2017.
//  Released under the MIT Software license; see doc/LICENSE

#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <sstream>

#include "Evolve/World.h"
#include "tools/Random.h"
#include "tools/string_utils.h"

#include "./Constants.h"
#include "./Stripes.h"
#include "./config/ConfigLoader.h"
#include "./util.h"

int main(int argc, char ** argv)
{
    //Load Configuration
    if(argc < 2){
        std::cerr << "This program requires exactly one command line argument: ";
        std::cerr << "the configuration filename!" << std::endl;
        return 1;
    }
    std::string configFilename = std::string(argv[1]);
    ConfigLoader config;
    ConfigInit(config); 
    if(config.Load(configFilename) != 0){
        std::cerr << "Error in opening config file: " << argv[1] << "!" << std::endl;
        return 1;
    }
    std::cout << "Using config file: " << configFilename << std::endl;
     
    //Initialize organism variables
    emp::Random random;
    Initialize(&random);
    
    //Variable initialization
    std::vector<unsigned char> endState;
    size_t popSize = GetConfig().Fetch<int>("POP_SIZE"); 
    size_t numGens = GetConfig().Fetch<int>("NUM_GENS"); 
    size_t tourneySize= GetConfig().Fetch<int>("TOURNEY_SIZE"); 
    size_t tourneyCount = GetConfig().Fetch<int>("TOURNEY_COUNT"); 
    size_t eliteCount = GetConfig().Fetch<int>("ELITE_COUNT"); 
    size_t eliteCopies = GetConfig().Fetch<int>("ELITE_COPIES");
    std::string fitFunStr = GetConfig().Fetch<std::string>("FIT_FUN");
    std::string outputDir = GetConfig().Fetch<std::string>("OUTPUT_DIR");
    std::ostringstream oss;
    std::string idStr;

    oss.str("");
    if(argc > 2){
        for(int i = 2; i < argc; i++){
            oss << "_" << argv[i];
        }
    }
    else
        oss << "_" << rand();
    idStr = oss.str();
    oss.str("");
    std::cout << "ID string for this run: " << idStr << std::endl;

    std::vector<emp::World<emp::vector<bool>>*> worldICs; 
    emp::World<emp::vector<bool>> worldICs1(random);
    worldICs.push_back(&worldICs1); 
    emp::World<emp::vector<bool>> worldICs2(random); 
    worldICs.push_back(&worldICs2); 
    emp::World<emp::vector<bool>> worldICs3(random); 
    worldICs.push_back(&worldICs3); 
    emp::World<emp::vector<bool>> worldICs4(random); 
    worldICs.push_back(&worldICs4); 
    //IC World Setup
    for(size_t ic = 0; ic < 4; ic++){
        worldICs[ic]->SetPopStruct_Mixed(false);
        worldICs[ic]->SetPrintFun(print_fun_stripe_ic);
        worldICs[ic]->SetMutFun(mutate_fun_all);
        worldICs[ic]->SetCache(true);
    }
    std::function<double(std::vector<bool> &)> fit_fun_ic_1 = fit_fun_match_stripe_ic_1;
    std::function<double(std::vector<bool> &)> fit_fun_ic_2 = fit_fun_match_stripe_ic_2;
    std::function<double(std::vector<bool> &)> fit_fun_ic_3 = fit_fun_match_stripe_ic_3;
    std::function<double(std::vector<bool> &)> fit_fun_ic_4 = fit_fun_match_stripe_ic_4;
    
    if(fitFunStr.compare("STATIC_REP") == 0){
        fit_fun_ic_1 = fit_fun_static_rep_stripe_ic_1;
        fit_fun_ic_2 = fit_fun_static_rep_stripe_ic_2;
        fit_fun_ic_3 = fit_fun_static_rep_stripe_ic_3;
        fit_fun_ic_4 = fit_fun_static_rep_stripe_ic_4;
        std::cout << "Using static and repeating structures for fitness." << std::endl;
    }
    else {   
        std::cout << "Using end state matching for fitness." << std::endl;
    }
    worldICs[0]->SetFitFun(fit_fun_ic_1);
    worldICs[1]->SetFitFun(fit_fun_ic_2);
    worldICs[2]->SetFitFun(fit_fun_ic_3);
    worldICs[3]->SetFitFun(fit_fun_ic_4);

    //Fill the worlds with random orgs
    for(size_t ic = 0; ic < 4; ic++){
        for(size_t i = 0; i < popSize; i++){
            worldICs[ic]->Inject(GetRandomOrg_Quad_IC(random));
        }
        worldICs[ic]->Update();
        SetICQuadPtr(worldICs[ic], ic);
    }
    
    //Ruleset World Setup
    emp::World<emp::vector<bool>> worldRuleset(random);
    worldRuleset.SetPopStruct_Mixed(false);
    worldRuleset.SetPrintFun(print_fun_classic_ruleset);
    worldRuleset.SetMutFun(mutate_fun_all);
    std::function<double(std::vector<bool> &)> fit_fun_ruleset = fit_fun_match_stripe_ruleset;
    
    if(fitFunStr.compare("STATIC_REP") == 0){
        fit_fun_ruleset = fit_fun_static_rep_stripe_ruleset;
    }
    worldRuleset.SetFitFun(fit_fun_ruleset);
    worldRuleset.SetCache(true);

    //Fill the world with random orgs
    for(size_t i = 0; i < popSize; i++){
        worldRuleset.Inject(GetRandomOrg_Classic_Ruleset(random));
    }
    worldRuleset.Update();
    SetRulesetWorldPtr(&worldRuleset);

    std::multimap<double, size_t>rulesetFitnessMap;
    std::vector<std::multimap<double, size_t>> icFitnessMaps(4);
    SetRulesetFitnessMapPtr(&rulesetFitnessMap);
    SetICQuadFitnessMapPtr(&icFitnessMaps[0], 0);
    SetICQuadFitnessMapPtr(&icFitnessMaps[1], 1);
    SetICQuadFitnessMapPtr(&icFitnessMaps[2], 2);
    SetICQuadFitnessMapPtr(&icFitnessMaps[3], 3);
    
    std::fstream icFP;
    std::fstream rulesetFP;
    //Main Loop
    for(size_t i = 0; i < numGens; i++){
        worldRuleset.ClearCache();
        std::cout << "Generation #" << i << std::endl;
        for(size_t ic = 0; ic < 4; ic++){
            worldICs[ic]->ClearCache();
            if(eliteCount > 0 && eliteCopies > 0)
                EliteSelect(*worldICs[ic], eliteCount, eliteCopies);
            TournamentSelect(*worldICs[ic], tourneySize, tourneyCount);
        }
        SetMaxFitIC(0);//fit_map.rbegin()->second);
        if(eliteCount > 0 && eliteCopies > 0)
            EliteSelect(worldRuleset, eliteCount, eliteCopies);
        TournamentSelect(worldRuleset, tourneySize, tourneyCount);
       
        //Stripes 
        for(size_t ic = 0; ic < 4; ic++){
            //Save off members of both populations to check convergence
            oss.str("");
            oss << outputDir << "/STRIPES_IC_" << ic << "_Gen_" << i << idStr << ".txt";
            icFP.open(oss.str(), std::ios::out | std::ios::trunc);
            for (size_t id = 0; id < worldICs[ic]->GetSize(); id++) {
                icFP << "IC ID: " << id << std::endl;
                icFP << "Fitness: " << worldICs[ic]->GetCache(id) << std::endl;
                icFP << std::endl;
            }
            icFP.close(); 
            //Mutate & Update
            worldICs[ic]->DoMutations();
            worldICs[ic]->Update();
        } 
        //Ruleset
        oss.str("");
        oss << outputDir << "/STRIPES_Ruleset_Gen_" << i << idStr << ".txt";
        rulesetFP.open(oss.str(), std::ios::out | std::ios::trunc);
        for (size_t id = 0; id < worldRuleset.GetSize(); id++) {
            rulesetFP << "Ruleset ID: " << id << std::endl;
            rulesetFP << "Fitness: " << worldRuleset.GetCache(id) << std::endl;
            rulesetFP << std::endl;
        }
        //Update fitness maps
        rulesetFitnessMap.clear();
        for (size_t id = 0; id < worldRuleset.GetSize(); id++) {
            rulesetFitnessMap.insert(std::make_pair(worldRuleset.GetCache(id), id));
        }
        for(size_t ic = 0; ic < 4; ic++){
            icFitnessMaps[ic].clear();
            for (size_t id = 0; id < worldICs[ic]->GetSize(); id++) {
                icFitnessMaps[ic].insert(std::make_pair(worldICs[ic]->GetCache(id), id));
            }
        }
        rulesetFP.close(); 
        worldRuleset.DoMutations();
        worldRuleset.Update();
    }

    // Last generation image generation
    std::cout << "Last generation finished! Finishing up..." << std::endl; 
    
    for(size_t ic = 0; ic < 4; ic++){ 
        oss.str(""); 
        oss << outputDir << "/STRIPES_IC_" << ic << "_Last_Gen" << idStr << ".txt";
        icFP.open(oss.str(), std::ios::out | std::ios::trunc);
        for (size_t id = 0; id < worldICs[ic]->GetSize(); id++) {
            icFP << "IC ID: " << id << std::endl;
            icFP << "Fitness: " << worldICs[ic]->GetCache(id) << std::endl;
            print_fun_stripe_ic(worldICs[ic]->GetOrg(id), icFP);
            icFP << std::endl;
        }
        icFP.close(); 
    }
    oss.str("");
    oss << outputDir << "/STRIPES_Ruleset_Last_Gen" << idStr << ".txt";
    rulesetFP.open(oss.str(), std::ios::out | std::ios::trunc);
    for (size_t id = 0; id < worldRuleset.GetSize(); id++) {
        rulesetFP << "Ruleset ID: " << id << std::endl;
        rulesetFP << "Fitness: " << worldRuleset.GetCache(id) << std::endl;
        print_fun_classic_ruleset(worldRuleset.GetOrg(id), rulesetFP);
        rulesetFP << std::endl;
    }
    //Finished! 
    std::cout << "Done!" << std::endl;
}
