//simft.cpp
//Auguste Brown

#include "simulation.h"

using namespace std;

const int FPS = 24;              // frames per sec
const bool STEP = false;  // running mode

int main(int argc, char *argv[])
{
    Simulation sim;

    if (argc == 1) {
        cout << "Filename needed\n";
        return 1;
    }
    if (not sim.setup(string(argv[1])))
        return 1;

    sim.run(STEP, FPS);

    return 0;
}