#include "WaitingRoom.h"
#include "Patient.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <deque>

using namespace std;

bool checkint(string input)
{
    if(input.size()==0)
        return false;
 
    for(int i=0;i<input.size();i++)
    {
        if(!isdigit(input[i]))
            return false;
    }
    return true;
}

Patient::Patient(string thename, int cardnum)
{
    cout << "Calling Patient() ctor, " << endl;
    this -> name = thename;
    this -> healthcard = cardnum;
    this -> condition = UNKNOWN;
    this -> systolic = -1; //Set the default BP to -1 to represent an unknown value.
    this -> diastolic = -1;
}

int Patient::examinepat()
{
    cout << "=============\n[Examine Patient]\n";
    cout << "Name: " << this->name;
    cout << "\nHealth Card Number: " << this->healthcard;
    
    cout << "\nEnter Systolic number in mm/Hg: ";
    string systolic;
    cin >> systolic;

    while (!checkint(systolic))
    {
        cin.clear();
        cout << "\nPlease enter a valid input: ";
        cin >> systolic;
    }

    this->systolic = stoi(systolic);

    cout << "Enter Diastolic Pressure in mm/Hg: ";
    string diastolic;
    cin >> diastolic;

    bool diastoliccheck = false;
    while (!diastoliccheck)
    {
        while (!checkint(diastolic))
        {
            cin.clear();
            cout << "\nPlease enter a valid input: ";
            cin >> diastolic;
        }

        if (stoi(diastolic) > this->systolic)
        {
            cin.clear();
            cout << "\nDiastolic Pressure should be LESS THAN Systolic. Enter again: ";
            cin >> diastolic;
        }
        
        else
            diastoliccheck = true;
    }
    
    this->diastolic = stoi(diastolic);

    if ((this->systolic <= 120 && this->systolic >= 90) && (this->diastolic >= 60 && this->diastolic <= 80))
    {
        this -> condition = SAFE;
    }
    
    else if ((this->systolic < 90 && this->systolic > 0) || (this->diastolic < 60 && this->diastolic > 0))
    {
        this -> condition = LOW;
    }

    else if (this->systolic > 180 || this->diastolic > 110)
    {
        this -> condition = CRITICAL;
    }

    else if ((this->systolic > 120 && this->systolic <= 180) || (this->diastolic > 80 && this->diastolic <= 110))
    {
        this -> condition = HIGH;
    }

    else if (this->systolic <= 0 || this->diastolic <= 0)
    {
        this -> condition = DECEASED;
    }

    return this->condition;
}

const string& Patient::getname()
{
    return name;
}

const int Patient::getcard()
{
    return this->healthcard;
}

int Patient::getsystolic()
{
    return this->systolic;
}

int Patient::getdiastolic()
{
    return this->diastolic;
}

string Patient::getcondition()
{
    if (this -> condition == UNKNOWN)
        return "UNKNOWN";
    else if (this -> condition == SAFE)
        return "SAFE";
    else if (this -> condition == LOW)
        return "LOW";
    else if (this -> condition == HIGH)
        return "HIGH";
    else if (this -> condition == CRITICAL)
        return "CRITICAL";
    else if (this -> condition == DECEASED)
        return "DECEASED";
    else
        return "None";
}

Patient::~Patient()
{
    cout << "Calling Patient destructor, " << endl;
}

// --------------------------

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
                << left << setw(10) << "DECEASED\n";
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
// --------------------

int main()
{
    string option;
    WaitingRoom patReg;

    while(option != "1" || option != "2" || option != "3" || option != "4")
    {
        int patcount = patReg.getsize();
        cout << "=======================\n";
        cout << "There are currently " << patcount << " patients in the waiting room.\n";
        cout << "\nPlease select an option:\n";
        cout << "1. Register Patient\n";
        cout << "2. Examine Patient\n";
        cout << "3. Display Patients\n";
        cout << "4. Quit\n";
        cin >> option;
        
        if (option == "1")
        {
            string name = "";
            string hcard;

            cout << "=============\n[Register Patient]\n";
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name, '\n');
            cout << "Enter Health Card Number: ";
            
            cin >> hcard;
            
            while(!checkint(hcard))
            {
                cin.clear();
                cout << "\nCan not register with non numeric health card.\n";
                cout << "Enter Health Card Number: ";
                cin >> hcard;
            }

            cout << "\n.. [Registering]\n\n";
            int healthcard;
            healthcard = stoi(hcard);
            patReg.enqueue(name, healthcard);          
        }

        else if (option == "2")
        {
            patReg.examine();
        }

        else if (option =="3")
        {
            patReg.displayQueue();
        }

        else if (option == "4")
        {
            cout << "\n.. [Quitting]\n";
            break;
        }

        else
        {
            cout << "\nPlease enter a valid input.\n";
        }
        
    }

    return 0;
}
