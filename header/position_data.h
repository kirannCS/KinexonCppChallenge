
//
// Created by kiran on 17.2.2023.
//

#ifndef POSITION_DATA_H
#define POSITION_DATA_H

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <zmq.hpp>
#include "position.pb.h"


#define SIMULATION_COUNT		120 // Number of times (secs) the radom positions generated for each player
#define TOTAL_NO_OF_SENSORS 		10
#define MAX_DIST_IN_ONE_SEC 		2.9 // In meters, (assumption: average human velocity = 12kmph)
#define PI				3.14
#define XLIM				100
#define YLIM				100
#define ZLIM				8.0
#define NOISE_THRESHOLD			30
#define MAX_STEP_COUNT			20 // Maximum time (in secs) a player runs in a direction and then changes the direction 
#define MIN_STEP_COUNT			0

class PositionData {
private:
    float x, y, z;
    float radius;
    unsigned short step_count;

public:
    PositionData();

    float getX() const { return x;}

    float getY() const { return y;}

    float getZ() const { return z;}

    void addNoise();

    float uniform();

    float getRandomFloatNumber (float, float);

    int getRandomIntNumber (int, int);

    void generateRandPointInCircle();

    void printCurPosition(unsigned short) const;

    ~PositionData() {}
};

#endif //POSITION_DATA_H
