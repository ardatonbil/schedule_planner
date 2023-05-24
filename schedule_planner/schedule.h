#include <iostream>
using namespace std;
enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
#ifndef HW4_SCHEDULE_H
#define HW4_SCHEDULE_H



class Schedule{
private:
    int time_slots;
    string ** data;
public:
    Schedule();
    Schedule(int c);
    Schedule (const Schedule & copy);
    ~Schedule();
    string ** data_pointer_copy() const;
    Schedule & operator=(const Schedule & schedule1);
    const Schedule operator*(const Schedule & rhs) const;
    Schedule operator+(Days day);
    Schedule operator+ (int z);
    string * operator[](Days day) const;
    bool operator<(const Schedule & rhs);
    int time_slot_count() const;
    string ** get_data() const;
};

ostream & operator<<(ostream &output, const Schedule & rhs);
ostream & operator<<(ostream & output, Days day);

Schedule operator+ (const Schedule & schedule1, const Schedule & schedule2);

#endif //HW4_SCHEDULE_H