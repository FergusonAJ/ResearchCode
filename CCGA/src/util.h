#pragma once

#include <bitset>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <locale>


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
