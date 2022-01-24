//fishtank.cpp
//Defines functions in the FishTank class
//Written by Auguste Brown

#include <iostream>
#include "fish.h"

using namespace std;

//Default constructor
//Sets tank height and width to 0
//Fills tank with spaces
FishTank::FishTank(){
    set_height(0);
    set_width(0);
    clear_tank();
}

//Constructor
//Sets tank height and width to specified values
//Fills tank with spaces
FishTank::FishTank(int hgt, int wid){
    set_height(hgt);
    set_width(wid);
    clear_tank();
}

// bool set_height(int hgt)
// Assigns the tank width data member to the specified value if it is valid
// Parameters: int hgt
// Returns: true if was successful, false otherwise
bool FishTank::set_height(int hgt){
    if (hgt > 0 and hgt <= MAX_HGT){
        height = hgt; //assign data member
        return true; //function succeeded
    }

    return false; //function failed
}

// bool set_width(int wid)
// Assigns the tank width data member to the specified value if it is valid
// Parameters: int wid
// Returns: true if was successful, false otherwise
bool FishTank::set_width(int wid){
    if (wid > 0 and wid <= MAX_WID){
        width = wid; //assign data member
        return true; //function succeeded
    }

    return false; //function failed
}

//returns the integer data member, height
int FishTank::get_height(){
    return height;
}

//returns the integer data member, width
int FishTank::get_width(){
    return width;
}

// bool set_width(int wid)
// Sets all characters in the tank array to a space
// Parameters: None
// Returns: None
void FishTank::clear_tank(){
    for (int row = 0; row < MAX_HGT; row++){
        for (int col = 0; col < MAX_WID; col++){
            tank[row][col] = ' ';
        }
    }
}

// bool set_width(int wid)
// Sets the tank value at the specified row and column to the input character
// Parameters: int row, int col, char c
// Returns: None
void FishTank::update_at(int row, int col, char c){
    tank[row][col] = c;
}

// bool set_width(int wid)
//Prints out the tank array in rows.
//      -Only prints out the values within the bounds of the
//       height and width data members
// Parameters: None
// Returns: None
void FishTank::show_tank(){
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            cout << tank[row][col];
        }

        cout << endl;
    }
}
