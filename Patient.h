#ifndef PATIENT_H_
#define PATIENT_H_

#include <iostream>

using namespace std;

class Patient
{
    enum Condition{UNKNOWN, SAFE, LOW, HIGH, CRITICAL, DECEASED};

    private:
        string name;
        int healthcard;
        int systolic;
        int diastolic;
        Condition condition;

    public:
        Patient(string, int); //Constructor which requires a patient name and healthcard
        ~Patient(); //Destructor which must be called when deleting a Patient object.
        int examinepat();
        const string& getname(); //Set the name and card to be constant so they can not be changed.
        const int getcard();
        int getsystolic();
        int getdiastolic();
        string getcondition();
};

#endif /* PATIENT_H */
