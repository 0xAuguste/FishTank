//simulation.cpp
//Defines functions in the Simulation class
//Written by Auguste Brown

#include "simulation.h"
#include "fishtank.cpp"
#include "termfuncs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>

using namespace std;

// Simulation constructor
// Creates empty Fish linked list
// Assigns other data members to appropraite start values
Simulation::Simulation(){
    p_first_fish = nullptr;
    num_fish = 0;
    num_cycles = 0;
}

// Simulation destructor
// Recycles the memory used in the fish linked list
Simulation::~Simulation(){
    recycle_fish(p_first_fish);
}

// bool setup(std::string filename)
// gets data from input file and reads creates appropriate tank and fish
// Parameters: string filename
// Returns: True if data was read successfully, false otherwise
bool Simulation::setup(std::string filename){
    ifstream infile;
    infile.open(filename);

    if (not infile.is_open())
        return false; //file failed to open

    setup_tank(infile);
    setup_fish(infile);

    infile.close();
    return true;
}

// void setup_tank(ifstream &infile)
// helper function for setup() that reads in the tank data and makes the
//      appropriate changes to the tank data members
// Parameters: ifstream &infile
// Returns: None
void Simulation::setup_tank(ifstream &infile){
    string line, temp;
    int tank_hgt, tank_wid;

    getline(infile, line); //get first line of file
    stringstream ss = stringstream(line); //convert to stringstream
    ss >> temp >> tank_hgt >> tank_wid; //read data into variables
    
    //assign tank data members to appropriate values
    tank.set_height(tank_hgt);
    tank.set_width(tank_wid);
}

// void setup_fish(ifstream &infile)
// helper function for setup() that creates the fish linked list and calls
//      read_fish to populate each fish's data members
// Parameters: ifstream &infile
// Returns: None
void Simulation::setup_fish(ifstream &infile){
    string line, temp; //variables to store file data

    while(true){
        infile >> temp; //get first word of line
        if (infile.eof()) //check for end of file after getting temp
            return;
        if (temp == "fish"){
            //create a node in the linked list
            Linked_Fish *new_node = new Linked_Fish;
            Fish *new_fish = new Fish(); //create a new fish on the heap
            new_node->fish = *new_fish;
            num_fish++;

            //put new node in front of the list
            Linked_Fish *holder = p_first_fish;
            p_first_fish = new_node;
            new_node->next = holder;
            new_node->fish.read_fish(infile); //fill fish data members

            //cerr << endl;
        }
    }

}

// void run(bool single_step, int fps)
// determines the run method for the animation and
//      calls the appropriate function
// Parameters: bool single_step, int fps
// Returns: None
void Simulation::run(bool single_step, int fps){
    if (single_step)
        run_step();
    else
        run_fps(1000000 / fps);
}

// void draw_all_fish(Linked_Fish *first)
// draws each fish
// if the number of cycles passed is beyond a fish's lifetime, the fish is
//      removed from the list
// Parameters: Linked_Fish *first
// Returns: None
void Simulation::draw_all_fish(Linked_Fish *first){
    // removing first fish is special case
    if (first->fish.lifetime() < num_cycles and first->fish.lifetime() != -1){
        Linked_Fish *second_fish = first->next;
        delete first;
        p_first_fish = second_fish;
        first = second_fish; //the front of the list is reassigned
        num_fish--;

    }

    for (int i = 0; i < num_fish; i++){
        //if a fish needs to be removed
        if (first->next != nullptr and first->next->fish.lifetime() < num_cycles
            and first->next->fish.lifetime() != -1){
            remove_next(first);
            i++; //to avoid loop out of bounds
        }
        else {
            first->fish.draw(&tank); //draw the fish into the tank
            first = first->next; //get the next fish
        }
    }
}

// void move_all_fish(Linked_Fish *first)
// loops through the list of fish and moves each one
// Parameters: Linked_Fish *first
// Returns: None
void Simulation::move_all_fish(Linked_Fish *first){
    for (int i = 0; i < num_fish; i++){
        first->fish.move(tank.get_height(), tank.get_width());
        first = first->next;
    }
}

// run_fps(int pause_length)
// runs the animation with the given fps
// Parameters: int pause_length
// Returns: None
void Simulation::run_fps(int pause_length){
    char c = ' ';
    while (c != 'q' and p_first_fish != nullptr) {
        screen_home(); //home the cursor
        screen_clear();
        tank.clear_tank(); //fill tank with spaces
        
        draw_all_fish(p_first_fish); //draw the fish into the tank
        tank.show_tank(); //print out the tank with fish in it
        cout.flush(); //force print
        screen_home(); //home the cursor
        move_all_fish(p_first_fish); //make necessary changes to fish location
        num_cycles++; //one cycle has passed

        usleep(pause_length); //pause for the correct amount of time
        
        c = getacharnow(0);  // see if user wants to quit
    }
    screen_clear(); //clear the screen when the animation is over
}

// run_fps(int pause_length)
// runs the animation in single step mode
// Parameters: None
// Returns: None
void Simulation::run_step(){
    char c = ' ';
    screen_clear();
    cout << "Type n to go to the next frame and q to quit" << endl;
    while (c != 'q') {
        c = getachar();  // try to get a character
        if (c == 'n'){
            screen_home();
            tank.clear_tank();
            
            draw_all_fish(p_first_fish);
            tank.show_tank();
            cout.flush();
            move_all_fish(p_first_fish);
            num_cycles++;
        }
    }
}

// void remove_next(Linked_Fish *fish)
// removes the fish in the linked list after the input fish
// Parameters: Linked_Fish *fish
// Returns: None
void Simulation::remove_next(Linked_Fish *fish){
    Linked_Fish *removed_fish = fish->next; //find fish to remove
    fish->next = fish->next->next; //reassign previous fish's next address
    delete removed_fish; //delete appropriate fish
    num_fish--; //increment number of fish
}

// void recycle_fish(Linked_Fish *first)
// recycles the memory used for the linked list of fish
// Parameters: Linked_Fish *first
// Returns: None
void Simulation::recycle_fish(Linked_Fish *first){
    if (first == nullptr) //reached end of list
        return;
    recycle_fish(first->next); //go to the next fish
    delete first;
}
