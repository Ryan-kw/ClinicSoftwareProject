#include "Patient.h"

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