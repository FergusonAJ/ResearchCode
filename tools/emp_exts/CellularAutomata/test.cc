#include <string>
#include <fstream>

#include "./CellularAutomaton.h"
#include "./Wireworld.h"
#include "./Conway.h"

#define WIDTH 64
#define HEIGHT 64
#define NUM_GENS 10

int main(){
    emp::Random random; 
    empCA::CellularAutomaton<unsigned char> ca(random, WIDTH, HEIGHT);
    ca.SetUpdateFunc(conway_update_func);
    ca.SetSpawnFunc(conway_spawn_func);
    ca.SetPrintFunc(conway_print_func);
    ca.SetCompareFunc(conway_cmp_func);
    ca.SetAliveFunc(conway_alive_func);
    ca.SetFromCharFunc(conway_from_char_func);
    ca.SetDoGrouping(true);
    /*
    ca.SetUpdateFunc(wireworld_update_func);
    ca.SetSpawnFunc(wireworld_spawn_func);
    ca.SetPrintFunc(wireworld_print_func);
    */
   
     
    /*
    emp::vector<unsigned char> data;
    data.resize(WIDTH * HEIGHT, 0);
    std::ifstream inFP;
    inFP.open("./Archive/symmetry1.txt");
    ca.LoadFromFile(inFP, data);
    inFP.close();
    ca.Populate(data);
    */

    
    emp::vector<unsigned char> data;
    data.resize(WIDTH * HEIGHT, 0);
    emp::vector<unsigned char> tmp;
    tmp.resize(9, 0);
    tmp[0] = 1;
    tmp[1] = 1;
    tmp[2] = 0;
    tmp[3] = 0;
    tmp[4] = 0;
    tmp[5] = 1;
    tmp[6] = 1;
    tmp[7] = 1;
    tmp[8] = 0;
    for(int x = 5; x < 10; x += 5)
        ca.AddSubsurface(data, tmp, WIDTH/2, HEIGHT/2,3);
    ca.Populate(data);
    
    
    //ca.Populate();
   
    std::ofstream groupFP, fieldFP, centroidFP;
    groupFP.open("groups.txt", std::ios::out | std::ios::trunc);
    fieldFP.open("field.txt", std::ios::out | std::ios::trunc);
    centroidFP.open("centroids.txt", std::ios::out | std::ios::trunc);
    for(int i = 0; i < NUM_GENS; i++)
    {
        std::cout << "Step #" << i << std::endl;
        fieldFP << "Step #" << i << "\n\n";
        groupFP << "Step #" << i << "\n";
        centroidFP << "Step #" << i << "\n";
        ca.Print(fieldFP);
        ca.PrintGroup(groupFP);
        ca.CalculateGroupCentroids(centroidFP);
        ca.Update();
    }
    groupFP.close();
    fieldFP.close();
    centroidFP.close();
}

