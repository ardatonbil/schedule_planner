#include "schedule.h"

Schedule::Schedule() {   //default constructor
    data = new string * [7];     // array of 7 pointers to string
    for (int i = 0; i < 7; i++){
        data[i] = nullptr;
    }
    time_slots = 0;
}

Schedule::Schedule(int c) {  //c is for specific amount of columns
    data = new string * [7];
    for (int i = 0; i < 7; i++){
        data[i] = new string [c];
        for (int x = 0; x < c; x++){
            data[i][x] = "free"; //each column is filled with free
        }
    }
    time_slots = c;
}

Schedule::~Schedule() {   //destructor
    for (int i = 0; i < 7; i++){
        string * ptr_main_array = data[i];
        ptr_main_array = nullptr;    //deallocation part
        delete ptr_main_array;

    }
}

string ** Schedule::data_pointer_copy() const {   //copying the array part of schedule
    string ** newcopy = new string * [7];   //copy array
    if (this->time_slots == 0){
        for (int i = 0; i < 7; i++){
            newcopy[i] = nullptr;
        }
    }

    else{
        for (int i = 0; i < 7; i++){
            newcopy[i] = new string [time_slots];
            for (int x = 0; x < this->time_slots; x++){
                newcopy[i][x] = data[i][x];
            }
        }
    }

    return newcopy;
}

int Schedule::time_slot_count() const { //time getter
    return this->time_slots;
}

string ** Schedule::get_data() const{  //data getter (data = 2d array)
    return this->data;
}

Schedule::Schedule(const Schedule & copy) {   //copy constructor
    data = copy.data_pointer_copy();
    time_slots = copy.time_slot_count();
}

Schedule & Schedule::operator=(const Schedule & schedule1) {     //this = schedule1
    this->data = schedule1.data_pointer_copy();
    this->time_slots = schedule1.time_slot_count();
    return *this;
}

const Schedule Schedule::operator*(const Schedule & rhs) const{   //intersection of operators's busy slots
    Schedule newestschedule(rhs.time_slot_count());
    for (int i = 0; i < 7; i++){
        for (int x = 0; x < this->time_slots; x++){
            if (this->data[i][x] == "busy" && rhs.get_data()[i][x] == "busy"){
                newestschedule.get_data()[i][x] = "busy";
            }
        }
    }
    return newestschedule;
}

string * Schedule::operator[](Days day) const{
    return this->data[day];
}

bool Schedule::operator<(const Schedule & rhs){  //which operator is busier
    int lhs_busy_count = 0;
    int rhs_busy_count = 0;
    for (int i = 0; i < 7; i++){
        for (int x = 0; x < this->time_slots; x++){
            if (this->data[i][x] == "busy"){
                lhs_busy_count++;
            }
        }
    }

    for (int i = 0; i < 7; i++){
        for (int x = 0; x < rhs.time_slots; x++){
            if (rhs.data[i][x] == "busy"){
                rhs_busy_count++;
            }
        }
    }

    if (lhs_busy_count < rhs_busy_count){
        return true;
    }
    else{
        return false;
    }
}

Schedule Schedule::operator+(Days day){   //the day is busy
    Schedule newschedule(this->time_slots);
    for (int x = 0; x < 7; x++){
        for (int y = 0; y < this->time_slots; y++){
            newschedule.get_data()[x][y] = this->data[x][y];
        }
    }
    int m = day;
    for (int i = 0; i < this->time_slots; i++){
        newschedule.get_data()[m][i] = "busy";
    }
    return newschedule;
}

Schedule Schedule::operator+ (int z){   //adding a busy column
    Schedule newschedule(*this);
    for (int i = 0; i < 7; i++){
        newschedule.data[i][z] = "busy";
    }
    return newschedule;
}

Schedule operator+ (const Schedule& schedule1, const Schedule & schedule2){  //if same slot of both schedules are free then it is free
    Schedule newschedule(schedule1.time_slot_count());
    for (int x = 0; x < 7; x++){
        for (int y = 0; y < schedule1.time_slot_count(); y++){
            newschedule.get_data()[x][y] = schedule1.get_data()[x][y];
        }
    }

    for (int x = 0; x < 7; x++){
        for (int y = 0; y < schedule1.time_slot_count(); y++){
            if (schedule1.get_data()[x][y] == "free" && schedule2.get_data()[x][y] == "free"){
                newschedule.get_data()[x][y] = "free";
            }
            else{
                newschedule.get_data()[x][y] = "busy";
            }
        }
    }
    return newschedule;
}

ostream & operator<<(ostream &output, const Schedule & rhs){  //printing the schedule
    for (int i = 0; i < 7; i++){
        if (i == 0){
            output << "Mo: ";
        }
        else if (i == 1){
            output << "Tu: ";
        }
        else if (i == 2){
            output << "We: ";
        }
        else if (i == 3){
            output << "Th: ";
        }
        else if (i == 4){
            output << "Fr: ";
        }
        else if (i == 5){
            output << "Sa: ";
        }
        else if (i == 6){
            output << "Su: ";
        }
        if (rhs.time_slot_count() > 0){
            for (int x = 0; x < rhs.time_slot_count(); x++){
                output << rhs.get_data()[i][x] << ' ';
            }
        }
        output << "\n";
    }
    return output;
}

ostream & operator<<(ostream & output, Days day){   // printing the day
    if (day == 0){
        output << "Monday";
    }
    else if (day == 1){
        output << "Tuesday";
    }
    else if (day == 2){
        output << "Wednesday";
    }
    else if (day == 3){
        output << "Thursday";
    }
    else if (day == 4){
        output << "Friday";
    }
    else if (day == 5){
        output << "Saturday";
    }
    else if (day == 6){
        output << "Sunday";
    }
    return output;
}