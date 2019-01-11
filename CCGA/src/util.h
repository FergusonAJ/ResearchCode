#pragma once

#include <bitset>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <locale>
#include <fstream>
#include "tools/Random.h"

//A sad function because the CA is still using unsigned char while the individuals use bools
std::vector<unsigned char> BitstringToVec(std::vector<bool> bs, size_t offset = 0){
    std::vector<unsigned char> vec;
    vec.resize(bs.size() - offset);
    for(size_t i = 0; i < vec.size(); i++){
        vec[i] = bs[i + offset] ? 1 : 0;
    }
    return vec;
}

//Grabs a timestamp to create unique filenames
std::string GetTimestamp(){
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buff[100];
    std::strftime(buff, sizeof(buff), "%Y_%m_%d_%H_%M_%S", std::localtime(&t));
    return std::string(buff);
}

std::vector<bool> GenerateRandomBitstring(emp::Random& rand, size_t len){
    std::vector<bool> vec(len);
    for(size_t i = 0; i < vec.size(); i++){
        vec[i] = (rand.GetDouble() >= 0.5);
    }
    return vec;
}

//Dumps all organism and their fitnesses to the specified file
void WriteLastGenToFile(std::string filename, emp::World<std::vector<bool>>& world,
        std::function<void(std::vector<bool> &, std::ostream &)> print_func){
    std::fstream fp;
    fp.open(filename, std::ios::out | std::ios::trunc);
    for (size_t id = 0; id < world.GetSize(); id++) {
        fp << "ID: " << id << std::endl;
        fp << "Fitness: " << world.GetCache(id) << std::endl;
        print_func(world.GetOrg(id), fp);
        fp << std::endl;
    }
    fp.close(); 
}
