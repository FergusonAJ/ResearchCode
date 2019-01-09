#pragma once

#include <string>
#include <fstream>


//Quick and dirty loader for end state .txt files

void LoadFile(std::vector<unsigned char>& vec, std::string filename, size_t w, size_t h){
    std::ifstream fp;
    fp.open(filename, std::ios::in);
    std::string line;
    vec.resize(w * h, 0);
    size_t j = 0;
    while(std::getline(fp, line)){
        for(size_t i = 0; i < w; i++){
            if(line[i] == '#' || line[i] == '1')
                vec[i + j * w] = 1;
            else
                vec[i + j * w] = 0;
        }
        j++;
    }
}
