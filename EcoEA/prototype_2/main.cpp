// Slighlty improved comparison of a naive EA approach against a rough EcoEA approach
// 8/20/18
// Austin Ferguson

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "constants.h"
#include "basic_ea.h"
#include "eco_ea.h"

int main(int argc, char** argv){
    if(argc < 2){
        std::cerr << "Error! You must pass the number of generations as a command line argument!" << std::endl;
        return -1;
    }
    int numTrials = std::stoi(argv[1]);
    std::cout << "Running " << numTrials << " trials!" <<  std::endl;
    srand(time(NULL));
    for(int i = 0; i < numTrials; i++){
        std::cout << "Starting EcoEA trial #" << i << "!" << std::endl;
        EcoEAHandler eco(i);
        eco.run(NUM_GENS);
        std::cout << "Finished EcoEA trial #" << i << "!" << std::endl;
        std::cout << "Starting naive trial #" << i << "!" << std::endl;
        BasicEAHandler basic(i);
        basic.run(NUM_GENS);
        std::cout << "Finished naive trial #" << i << "!" << std::endl;
    }
    std::cout << "Done!" << std::endl;
    return 0;
}
