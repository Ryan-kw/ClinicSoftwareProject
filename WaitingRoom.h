#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <iostream>
#include <deque>
#include <iomanip>
#include <limits>
#include "Patient.h"

using namespace std;

class WaitingRoom
{
    private:
        deque<Patient *> q;
        
    public:
        WaitingRoom();
        ~WaitingRoom();
        void enqueue(string, int);
        int getsize();
        void examine();
        void displayQueue();
        
};

#endif
