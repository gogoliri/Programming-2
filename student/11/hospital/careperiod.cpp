#include "careperiod.hh"
#include "utils.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
    // Destructing the person information
    delete patient_;
    patient_ = nullptr;
}

// Close the period
void CarePeriod::closed(const Date& date)
{
    end_ = date;
}

// Check if the period have been closed
bool CarePeriod::is_closed() const
{
    if(end_.is_default()){
        return false;
    }
    return true;
}

// Assign a staff to this period
void CarePeriod::assign(const std::string& staff)
{
    staff_list_.insert(staff);
}

// Return the staff list
std::set<std::string> CarePeriod::get_staff_list() const
{
    return staff_list_;
}

// Print the staff list
// The staff list is only a set
void CarePeriod::print_staff() const
{
    std::cout<<"  - Staff:";
    if(staff_list_.size() != 0){
        for(auto& name: staff_list_){
            std::cout<<" "<<name;
        }}else{
        std::cout<<" None";
    }
    std::cout<<std::endl;
}

//Print infor of this period
// There is a boolen variable to decide whether
// to print the staff of this period
void CarePeriod::print_period() const
{

    start_.print();
    std::cout<<" - ";

    // Check if the period is closed
    // if so, print end date
    if(is_closed()){
        end_.print();
    }
    std::cout<<std::endl;

}








