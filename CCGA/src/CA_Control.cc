//  Evolutionary Computing Term Project
//  Investigating Cooperative Co-Evolution Modularity Using Cellular Automata
//  Austin J. Ferguson
//  11/9/2018

//  Main program for control runs 

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
#include "./Control.h"
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
 
    //World Setup
    emp::World<emp::vector<bool>> world(random);
    world.SetPopStruct_Mixed(false);
    world.SetPrintFun(print_fun_control);
    world.SetMutFun(mutate_fun_all);
    std::function<double(std::vector<bool> &)> fit_fun = fit_fun_match_control;
    if(fitFunStr.compare("STATIC_REP") == 0){
        fit_fun = fit_fun_static_rep_control;
        std::cout << "Using static and repeating structures for fitness." << std::endl;
    }
    else {   
        fit_fun = fit_fun_match_control;
        std::cout << "Using end state matching for fitness." << std::endl;
    }
    world.SetFitFun(fit_fun);
    oss.str("");
    oss << outputDir << "/CONTROL_fitness" <<  idStr << ".csv";
    world.SetupFitnessFile(oss.str(), true);
    //world.SetupPopulationFile("./output/pop.csv", true);
    world.SetCache(true);

    //Fill the world with random orgs
    for(size_t i = 0; i < popSize; i++){
        world.Inject(GetRandomOrg_Control(random));
    }
    world.Update();
    


    //Main Loop
    for(size_t i = 0; i < numGens; i++){
        std::cout << "Generation #" << i << std::endl;
        if(eliteCount > 0 && eliteCopies > 0)
            EliteSelect(world, eliteCount, eliteCopies);
        TournamentSelect(world, tourneySize, tourneyCount);
        for(size_t j = 0; j < world.GetSize(); j++){
            std::cout << "\t" << j << " - > " << world.GetCache(j) << std::endl;
        }
        world.DoMutations();
        world.Update();
    }

    // Last generation image generation
    std::cout << "Last generation finished! Finishing up..." << std::endl; 
    std::fstream lastGenFP;
    oss.str("");
    oss << outputDir << "/CONTROL_Last_Gen" <<  idStr << ".txt";
    lastGenFP.open(oss.str(), std::ios::out | std::ios::trunc);
    for (size_t id = 0; id < world.GetSize(); id++) {
        lastGenFP << "ID: " << id << std::endl;
        lastGenFP << "Fitness: " << world.GetCache(id) << std::endl;
        print_fun_control(world.GetOrg(id), lastGenFP);
        lastGenFP << std::endl;
    }
   
    //Finished! 
    std::cout << "Done!" << std::endl;
}
