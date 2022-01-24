//fish.h
//Declares functions in the fish class
//Written by Auguste Brown

#ifndef Fish_H
#define Fish_H

#include "fishtank.h"
#include <iostream>

class Fish
{
public:
    Fish();
    bool read_fish(std::istream &input);
    std::string get_name();
    void set_name(std::string n);
    void set_pos(int row, int col);
    int get_height();
    int get_width();
    int lifetime();
    void move(int tank_hgt, int tank_wid);
    void draw(FishTank *tank);
    void print();
private:
    static const int MAX_HGT = 30;
    static const int MAX_WID = 60;

    //variables to define fish movement
    float y_speed, x_speed, current_row, current_col;
    int height, width, life_left;
    std::string name; //name of fish
    char picture[MAX_HGT][MAX_WID]; //2D array to store the fish picture
    float adjust_row(float index, int hgt);
    float adjust_col(float index, int wid);
    void clear_picture();
};

#endif