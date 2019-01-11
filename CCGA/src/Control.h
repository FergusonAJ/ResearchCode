#include "OrganismShared.h"

//Generate a new bit string
std::vector<bool> GetRandomOrg_Control(emp::Random& rand){
    return GenerateRandomBitstring(rand, width * height + 18);
}

//Print function, dump ruleset and initial configuration
std::function<void(std::vector<bool> &, std::ostream &)> print_fun_control = [](std::vector<bool> & org, std::ostream & os) {
    os << "B";
    unsigned int a = 1;
    for(int i = 0; i < 9; i++){
        if(org[i] && (bBlackMask & a) == 0)
            os << i;
        a *= 2;
    }
    os << "/S";
    a = 1;
    for(int i = 0; i < 9; i++){
        if(org[i+9] && (sBlackMask & a) == 0)
            os << i;
        a *= 2;
    }
    os << "\n";
    for(int y = 0; y < subHeight; y++){
        for(int x = 0; x < subWidth; x++){
            os << (org[x + y * subWidth + 18]? "1" : "0") << " ";
        }
        os << std::endl;
    }
    os << std::endl;
};

//Fitness function - matching
auto fit_fun_match_control = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    std::vector<unsigned char> tmp = BitstringToVec(org, 18);
    ca.AddSubsurface(tmp, subX, subY, subWidth);
    return GetMatchFitness();
};

//Fitness function - Static/Repeating & Gliders
auto fit_fun_static_rep_control = [](std::vector<bool> & org){
    ca.Reset();
    ca.SetUpdateFunc(GetUpdateFunc(org, bBlackMask, sBlackMask));
    std::vector<unsigned char> tmp = BitstringToVec(org, 18);
    ca.AddSubsurface(tmp, subX, subY, subWidth);
    double score = GetStaticRepFitness(); 
    return score;
};
