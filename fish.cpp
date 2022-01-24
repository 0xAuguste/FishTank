//fish.cpp
//Defines functions in the Fish class
//Written by Auguste Brown

#include "fish.h"

#include "simulation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

//Constructor
//Fills fish picture with spaces, sets all data meembers to default values
Fish::Fish(){
    clear_picture();
    height = 0;
    width = 0;
    x_speed = 0;
    y_speed = 0;
    name = "";
    life_left = -1;
}

// void clear_picture()
// Fills fish picture with spaces
// Parameters: None
// Returns: None
void Fish::clear_picture(){
    for (int row = 0; row < MAX_HGT; row++){
        for (int col = 0; col < MAX_WID; col++){
            picture[row][col] = ' ';
        }
    }
}

// bool read_fish(std::istream &input)
// read_fish is called by the Simulation function, setup_fish()
// Reads in fish data into its data members
// Parameters: input stream
// Returns: true if succeeded, false otherwise
bool Fish::read_fish(std::istream &input){
    string temp, line;

    input >> height >> width >> current_row >> current_col >> y_speed >> x_speed
          >> life_left >> name;

    getline(input, temp); //go to first row of fish picture
    if (input.fail())
        return false;
    for (int row = 0; row < height; row++){
        getline(input, line);
        for (int col = 0; col < width; col++){
            picture[row][col] = line.at(col);
        }
    }

    return true;
}

//returns fish name data member
std::string Fish::get_name(){
    return name;
}

//sets the fish name data member to the input string, n
void Fish::set_name(std::string n){
    name = n;
}

//sets the fish's position to the input row and column
void Fish::set_pos(int row, int col){
    current_row = row;
    current_col = col;
}

//returns fish height data member
int Fish::get_height(){
    return height;
}

//returns fish width data member
int Fish::get_width(){
    return width;
}

//returns fish life_left data member
int Fish::lifetime(){
    return life_left;
}

// float adjust_row(float index, int hgt)
// returns an adjusted value of the fish's row, depending on if it
//      is out of bounds or not
// Parameters: float row index, int tank height
// Returns: New row
float Fish::adjust_row(float index, int hgt){
    if (index >= hgt)
        return index - hgt;
    else if (index < 0)
        return index + hgt;
    else
        return index;
}

// float adjust_col(float index, int wid)
// returns an adjusted value of the fish's column, depending on if it
//      is out of bounds or not
// Parameters: float column index, int tank width
// Returns: New column
float Fish::adjust_col(float index, int wid){
    if (index >= wid)
        return index - wid;
    else if (index < 0)
        return index + wid;
    else
        return index;
}

// void move(int tank_hgt, int tank_wid)
// correctly assigns fish row and column values based on its speed
// includes wrap-around functionality
// Parameters: int tank_hgt, int tank_wid
// Returns: None
void Fish::move(int tank_hgt, int tank_wid){
    current_row = adjust_row(current_row += y_speed, tank_hgt);
    current_col = adjust_col(current_col += x_speed, tank_wid);
}

// void draw(FishTank *tank)
// draws the fish's picture onto the tank 2D array in the correct spot
// includes wrap-around functionality
// Parameters: FishTank *tank
// Returns: None
void Fish::draw(FishTank *tank){
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            char symbol = picture[r][c];
            if (symbol != ' '){
                //adjust fish to travel over tank bounds
                int row = adjust_row(current_row + r, tank->get_height());
                int col = adjust_col(current_col + c, tank->get_width());

                if (symbol == '$')
                    symbol = ' ';
                //update tank
                tank->update_at(row, col, symbol);
            }
        }
    }
}

// void print()
// prints the fish's picture onto the console for debugging purposes
// Parameters: None
// Returns: None
void Fish::print(){
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            cout << picture[row][col];
        }
        cout << endl;
    }
}