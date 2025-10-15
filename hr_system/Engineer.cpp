#include "Engineer.h"
#include <iostream>
#include <string>
#include <string_view>


Engineer::Engineer(std::string_view name, std::string_view speciality, int id, double salary, int exp, int overtime, float overtimeRate): Employee(name, id, salary) {
    this->speciality = speciality;
    this->exp = exp;
    this->overtime = overtime;
    this->overtimeRate = overtimeRate;
}

void Engineer::setOvertimeHours(int hours) {
    overtime = hours;
}

void Engineer::setOvertimeHourRate(float rate) {
    overtimeRate = rate;
}

double Engineer::getTotalSalary() const {
    return salary + (overtime * overtimeRate);
}

void Engineer::print() const {
    Employee::print();
    std::cout << "Speciality: " << speciality << "\nYears of Experience: " << exp << "\nOvertime Hours: " << overtime << "\nOvertime Hours Rate: " << overtimeRate << "\n";
}

