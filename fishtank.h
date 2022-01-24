//fishtank.h
//Declares functions in the FishTank class
//Written by Auguste Brown

#ifndef FishTank_H
#define FishTank_H

class FishTank
{
public:
    FishTank();
    FishTank(int hgt, int wid);
    bool set_height(int hgt);
    bool set_width(int wid);
    int get_height();
    int get_width();
    void clear_tank();
    void update_at(int row, int col, char c);
    void show_tank();
private:
    static const int MAX_HGT = 50;
    static const int MAX_WID = 200;
    int height, width; //actual height and width of tank object
    char tank[MAX_HGT][MAX_WID]; //array to hold tank data
};

#endif