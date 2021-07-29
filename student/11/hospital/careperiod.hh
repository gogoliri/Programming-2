/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include "utils.hh"
#include <string>
#include <vector>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    // Close the care period
    void closed(const Date& date);

    // Check if the period is closed
    bool is_closed() const;

    // Assign staff to the period
    void assign(const std::string& staff);

    // get the staff list
    std::set<std::string> get_staff_list() const;

    // Print infomation about the period
    void print_period() const;

    // Disable default copy constructor and asignment operation
    CarePeriod(const CarePeriod& initial_value) = delete;
    CarePeriod& operator=(const CarePeriod& assignable_value) = delete;

    void print_staff() const;
private:
    Person* patient_;
    Date start_;
    Date end_;

    // More attributes and methods
    // Establishing the staff list
    std::set<std::string>  staff_list_={};

};

#endif // CAREPERIOD_HH
