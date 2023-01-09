#include "WaitingRoom.h"
#include "Patient.h"
#include <deque>
#include <climits>
#include <iomanip>

WaitingRoom::WaitingRoom()
{
    cout << "Calling WaitingRoom() constructor, " << endl;
}

WaitingRoom::~WaitingRoom()
{
    cout << "Calling WaitingRoom() destructor, " << endl;

    int qSize = q.size();
    for(int i=0;i<qSize;++i) 
    {
        delete q[i];
        q[i] = 0;
    }
}

void WaitingRoom::enqueue(string patname, int hcard)
{
    Patient *patient = new Patient(patname, hcard);
    q.push_back(patient);
}

int WaitingRoom::getsize()
{
    if (q.empty())
        return 0;
    else
        return q.size();
}

void WaitingRoom::examine()
{
    if (q.empty())
        return;
    else
    {
        Patient *p = q[0];
        q.pop_front();
        int condition = p->examinepat();
        
        if (condition == 4 || condition == 5)
        {
            cout << "\n.. [Admitting]\n\n";
            
            cout << left << setw(15) << "Patient Name"
            << left << setw(15) << "Health Card #"
            << left << setw(21) << "BP (mm/HG)"
            << left << setw(10) << "Condition\n";

            cout << "==============================================================\n";
            if (condition == 4)
            {
                cout << left << setw(15) << p->getname() 
                << left << setw(15) << p->getcard() 
                << setw(3) << p->getsystolic() << "/" << left << setw(17) << p->getdiastolic()
                << left << setw(10) << "CRITICAL\n";
            }
            else if(condition == 5)
            {
                cout << left << setw(15) << p->getname() 
                << left << setw(15) << p->getcard() 
                << setw(21) << "0/0"
                << left << setw(10) << "DISEASED\n";
            }
            
            delete p; p=0;
        }

        else
        {
            cout << "\n.. [Going back to queue]\n";
            q.push_back(p);
        }
    }
}

void WaitingRoom::displayQueue()
{
    if (q.empty())
    {
        cout << "\nNo patients in the register.\n";
        return;
    }

    cout << "\n=============\n\n[Display Patients]\n";
    cout << left << setw(15) << "Patient Name"
            << left << setw(15) << "Health Card #"
            << left << setw(21) << "BP (mm/HG)"
            << left << setw(10) << "Condition\n";        
    cout << "==============================================================\n";

    int qsize = q.size();
    for(int i=0;i<qsize;++i)
    {
        cout << left << setw(15) << q[i]->getname() 
            << left << setw(15) << q[i]->getcard() 
            << setw(3) << q[i]->getsystolic() << "/" << left << setw(17) << q[i]->getdiastolic()
            << left << setw(10) << q[i]->getcondition() << endl;
    }
    cout << endl;
}