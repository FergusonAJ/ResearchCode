//  Evolutionary Computing Term Project
//  Investigating Cooperative Co-Evolution Modularity Using Cellular Automata
//  Austin J. Ferguson
//  11/9/2018

//  Main program for classic runs 

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
#include "./Classic.h"
#include "./config/ConfigLoader.h"
#include "./util.h"

int main(int argc, char ** argv)
{
    //Load Configuration
    srand(time(NULL));
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

 
    //IC World Setup
    emp::World<emp::vector<bool>> worldIC(random);
    worldIC.SetPopStruct_Mixed(false);
    worldIC.SetPrintFun(print_fun_classic_ic);
    worldIC.SetMutFun(mutate_fun_all);
    std::function<double(std::vector<bool> &)> fit_fun_ic = fit_fun_match_classic_ic;
    
    if(fitFunStr.compare("STATIC_REP") == 0){
        fit_fun_ic = fit_fun_static_rep_classic_ic;
        std::cout << "Using static and repeating structures for fitness." << std::endl;
    }
    else {   
        fit_fun_ic = fit_fun_match_classic_ic;
        std::cout << "Using end state matching for fitness." << std::endl;
    }
    worldIC.SetFitFun(fit_fun_ic);
    worldIC.SetCache(true);

    //Fill the world with random orgs
    for(size_t i = 0; i < popSize; i++){
        worldIC.Inject(GetRandomOrg_Classic_IC(random));
    }
    worldIC.Update();
    SetICWorldPtr(&worldIC);
    
    //Ruleset World Setup
    emp::World<emp::vector<bool>> worldRuleset(random);
    worldRuleset.SetPopStruct_Mixed(false);
    worldRuleset.SetPrintFun(print_fun_classic_ruleset);
    worldRuleset.SetMutFun(mutate_fun_all);
    std::function<double(std::vector<bool> &)> fit_fun_ruleset = fit_fun_match_classic_ruleset;
    
    if(fitFunStr.compare("STATIC_REP") == 0){
        fit_fun_ruleset = fit_fun_static_rep_classic_ruleset;
    }
    else {   
        fit_fun_ruleset = fit_fun_match_classic_ruleset;
    }
    worldRuleset.SetFitFun(fit_fun_ruleset);
    worldRuleset.SetCache(true);

    //Fill the world with random orgs
    for(size_t i = 0; i < popSize; i++){
        worldRuleset.Inject(GetRandomOrg_Classic_Ruleset(random));
    }
    worldRuleset.Update();
    SetRulesetWorldPtr(&worldRuleset);

    //worldIC.SetupFitnessFile("./output/fitness_ic.csv", true);
    //worldRuleset.SetupFitnessFile("./output/fitness_ruleset.csv", true);
    //worldIC.SetupPopulationFile("./output/pop_ic.csv", true);
    //worldRuleset.SetupPopulationFile("./output/pop_ruleset.csv", true);
    std::fstream icFP;
    std::fstream rulesetFP;
    std::multimap<double, size_t> icFitnessMap, rulesetFitnessMap;
    SetICFitnessMapPtr(&icFitnessMap);
    SetRulesetFitnessMapPtr(&rulesetFitnessMap);
    //Main Loop
    for(size_t i = 0; i < numGens; i++){
        worldRuleset.ClearCache();
        worldIC.ClearCache();
        std::cout << "Generation #" << i << std::endl;
        if(eliteCount > 0 && eliteCopies > 0)
            EliteSelect(worldIC, eliteCount, eliteCopies);
        TournamentSelect(worldIC, tourneySize, tourneyCount);
        if(eliteCount > 0 && eliteCopies > 0)
            EliteSelect(worldRuleset, eliteCount, eliteCopies);
        TournamentSelect(worldRuleset, tourneySize, tourneyCount);
        //Save off members of both populations to check convergence
        oss.str("");
        oss << outputDir << "/CLASSIC_IC_Gen_" << i << idStr << ".txt";
        icFP.open(oss.str(), std::ios::out | std::ios::trunc);
        for (size_t id = 0; id < worldIC.GetSize(); id++) {
            icFP << "IC ID: " << id << std::endl;
            icFP << "Fitness: " << worldIC.GetCache(id) << std::endl;
            icFP << std::endl;
        }
        icFP.close(); 
        
        oss.str("");
        oss << outputDir << "/CLASSIC_Ruleset_Gen_" << i << idStr<< ".txt";
        rulesetFP.open(oss.str(), std::ios::out | std::ios::trunc);
        for (size_t id = 0; id < worldRuleset.GetSize(); id++) {
            rulesetFP << "Ruleset ID: " << id << std::endl;
            rulesetFP << "Fitness: " << worldRuleset.GetCache(id) << std::endl;
            rulesetFP << std::endl;
        }
        icFitnessMap.clear();
        rulesetFitnessMap.clear();
        for (size_t id = 0; id < worldIC.GetSize(); id++) {
            icFitnessMap.insert(std::make_pair(worldIC.GetCache(id), id));
        }
        for (size_t id = 0; id < worldRuleset.GetSize(); id++) {
            rulesetFitnessMap.insert(std::make_pair(worldRuleset.GetCache(id), id));
        }
        rulesetFP.close(); 
        worldIC.DoMutations();
        worldIC.Update();
        worldRuleset.DoMutations();
        worldRuleset.Update();
    }

    // Last generation image generation
    std::cout << "Last generation finished! Finishing up..." << std::endl; 
   
    oss.str(""); 
    oss << outputDir << "/CLASSIC_IC_Last_Gen" << idStr << ".txt";
    icFP.open(oss.str(), std::ios::out | std::ios::trunc);
    for (size_t id = 0; id < worldIC.GetSize(); id++) {
        icFP << "IC ID: " << id << std::endl;
        icFP << "Fitness: " << worldIC.GetCache(id) << std::endl;
        print_fun_classic_ic(worldIC.GetOrg(id), icFP);
        icFP << std::endl;
    }
    icFP.close(); 
        
    oss.str("");
    oss << outputDir << "/CLASSIC_Ruleset_Last_Gen" << idStr << ".txt";
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
