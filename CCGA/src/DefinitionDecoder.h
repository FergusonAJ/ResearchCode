#pragma once
#include <vector>
#include <string>

#include "./config/BasicLoaders.h"

//From https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

//Generate the update function for a CA given B and S values
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)>
        GetUpdateFunc(std::vector<unsigned char>& B, std::vector<unsigned char>& S){ 
    return [B, S](unsigned char & cell, const emp::vector<emp::Ptr<unsigned char>> & neighbors){
            unsigned char alive_neighbors = 0;
            for(unsigned char i = 0; i < neighbors.size(); i++){
                if(*neighbors[i] == 1)
                    alive_neighbors++;
            }
            if(cell == 0){
                for(int b : B){
                    if(alive_neighbors == b)
                        return (unsigned char)1;
                }
            }
            if(cell == 1){
                for(int s : S){
                    if(alive_neighbors == s)
                        return (unsigned char)1;
                }
            }
            return (unsigned char)0;
    };
    
}

//Load B and S vectors from a string
void LoadBSVectors(const std::string& s, 
        std::vector<unsigned char> &B, std::vector<unsigned char> &S){
    bool bFirst = s[0] == 'B';
    size_t splitPos = s.find("/");
    
    if(splitPos !=  std::string::npos){
        std::string first = s.substr(0, splitPos);
        std::string second = s.substr(splitPos+1);
        trim(first);
        trim(second);
        for(char f : first){
            if(f >= '0' && f <= '9')
                (bFirst ? B : S).push_back(f - '0');
        }
        for(char f : second){
            if(f >= '0' && f <= '9')
                (bFirst ? S : B).push_back(f - '0');
        }
    }
}

//Load B and S vectors from a bitstring
void LoadBSVectors(const std::vector<bool>& v, 
std::vector<unsigned char> &B, std::vector<unsigned char> &S, 
     unsigned int bBlackMask, unsigned int sBlackMask){
    unsigned int a = 1;
    for(int i = 0; i < 9; i++){
        if(v[i] && (bBlackMask & a) == 0)
            B.push_back(i);
        a *= 2;
    }
    a = 1;
    for(int i = 0; i < 9; i++){
        if(v[i+9] && (sBlackMask & a) == 0)
            S.push_back(i);
        a *= 2;
    }
}

//Generate the update function for a CA given a bitstring
std::function<unsigned char(unsigned char &, const emp::vector<emp::Ptr<unsigned char>> &)>
GetUpdateFunc(const std::vector<bool>& v, unsigned int bBlackMask = 0, unsigned int sBlackMask = 0){
    std::vector<unsigned char> B, S;
    LoadBSVectors(v, B, S, bBlackMask, sBlackMask);
    return GetUpdateFunc(B, S); 
}
