//simulation.h
//Declares functions in the Simulation class
//Written by Auguste Brown

#ifndef Simulation_H
#define Simulation_H

#include "fish.h"
#include <iostream>

class Simulation
{
public:
    Simulation();
    ~Simulation();
    bool setup(std::string filename);
    void run(bool single_step, int fps);
private:
    FishTank tank;
    int num_fish; //total number of fish
    int num_cycles;
    struct Linked_Fish{
        Fish fish;
        Linked_Fish *next;
    };
    Linked_Fish *p_first_fish; //pointer to first fish in the linked list
    
    //helper functions
    void setup_tank(std::ifstream &infile);
    void setup_fish(std::ifstream &infile);
    void draw_all_fish(Linked_Fish *first);
    void move_all_fish(Linked_Fish *first);
    void run_fps(int pause_length);
    void run_step();
    void remove_next(Linked_Fish *fish);
    void recycle_fish(Linked_Fish *first);
    void recycle_tank();
};

#endif