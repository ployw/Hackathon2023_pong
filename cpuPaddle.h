#ifndef CPUPADDLE_H
#define CPUPADDLE_H

//#include "paddle.cpp"
#include "paddle.h"

class cpuPaddle: public Paddle
{
    public:
    void update(int);
};
#endif