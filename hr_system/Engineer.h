#ifndef ENGINEER_H
#define ENGINEER_H


#include "Employee.h"
#include <string>
#include <string_view>


class Engineer : public Employee {
private:
    std::string speciality;
    int exp;
    int overtime;
    float overtimeRate;

public:
    Engineer(std::string_view name, std::string_view speciality, int id, double salary, int exp, int overtime, float overtimeRate);

    void setOvertimeHours(int hours);

    void setOvertimeHourRate(float rate);

    double getTotalSalary() const;

    void print() const;
};

#endif

