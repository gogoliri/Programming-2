#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
        iter->second = nullptr;
    }

    // Remember to deallocate patients also

    // Deallocating all patients
    // we don't need to do it for current patients since they are included
    for(std::map<std::string, Person*>::iterator
        iter = all_patients_.begin();
        iter != all_patients_.end();
        ++iter){
        delete iter->second;
        iter->second = nullptr;
    }

    // Delocate care_periods_
    for(std::vector<std::pair<std::string, CarePeriod*>>::iterator
        iter = care_periods_.begin();
        iter != care_periods_.end();
        iter++){
        delete iter->second;
        iter->second = nullptr;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

// Notice if the person already exist in a list
bool Hospital::already_exists(const std::string &id, const std::map<std::string, Person *>&list)
{
    if( list.find(id) != list.end()){
        std::cout<< ALREADY_EXISTS << id<<std::endl;
        return true;
    }
    return false;
}

// Notice if the person cant be found in a list
bool Hospital::cant_find(const std::string &id, const std::map<std::string, Person *> &list)
{
    if( list.find(id) == list.end()){
        std::cout<< CANT_FIND << id<<std::endl;
        return true;
    }
    return false;
}

// New patient enter
void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);

    if(already_exists(patient_id, current_patients_)){
        return;
    }

    // If the new_patient was initialized later,
    // the if structure will prevent us to create new care period
    Person* new_patient = nullptr;

    // Create new care period with patient id
    CarePeriod* new_careperiod = new CarePeriod(utils::today, new_patient);
    care_periods_.push_back({patient_id, new_careperiod});

    // If patient had not been here before, add a new person
    // if they had been here before, just point to the same person
    if( all_patients_.find(patient_id) == all_patients_.end()){
        new_patient = new Person(patient_id);
        current_patients_.insert({patient_id, new_patient});
        all_patients_.insert({patient_id, new_patient});
    }else{
        new_patient = all_patients_.at(patient_id);
        current_patients_.insert({patient_id, new_patient});
    }

    std::cout<<PATIENT_ENTERED<<std::endl;

}

// A patient leave the hospital
void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    if(cant_find(patient_id,current_patients_)){
        return;
    }

    // Remove patient from current list
    for(std::vector<std::pair<std::string, CarePeriod*>>::iterator
        iter = care_periods_.begin();
        iter != care_periods_.end();
        iter++){
        if(iter->first == patient_id and !iter->second->is_closed()){
            iter->second->closed(utils::today);
        }
    }

    // The patient removed from current list
    current_patients_[patient_id] = nullptr;
    current_patients_.erase(patient_id);

    std::cout<<PATIENT_LEFT<<std::endl;


}

// Assign a staff to a care period of a patient
void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    // Check if staff and patient exist
    if(cant_find(staff_id,staff_)){
        return;
    }else if(cant_find(patient_id,current_patients_)){
        return;
    }

    // Go through the list of all record care period
    // Find the care period that of the patient and is not closed
    // we know in advance there is only one period that satisfies both
    // conditions
    for(std::vector<std::pair<std::string, CarePeriod*>>::iterator
        iter = care_periods_.begin();
        iter != care_periods_.end();
        iter++){
        if(iter->first == patient_id and !iter->second->is_closed()){
            iter->second->assign(staff_id);
        }
    }
    std::cout<<STAFF_ASSIGNED<<patient_id<<std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
            not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

// Print information of a patient
void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);

    if(cant_find(patient_id,all_patients_)){
        return;
    }

    Person* patient = all_patients_.at(patient_id);
    for(std::vector<std::pair<std::string, CarePeriod*>>::iterator
        iter = care_periods_.begin();
        iter != care_periods_.end();
        iter++){
        if(iter->first == patient_id){
            std::cout<<"* Care period: ";
            iter->second->print_period();
            iter->second->print_staff();
        }
    }
    std::cout<<"* Medicines:";
    patient->print_medicines("  - ");
}

// Print the care periods of a staff in question
void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);

    if(cant_find(staff_id,staff_)){
        return;
    }

    // Flag to make sure that there is at least 1 period
    bool is_period = false;

    // Go through all the periods and acces their staff list to find staff
    for(std::vector<std::pair<std::string, CarePeriod*>>::iterator
        iter = care_periods_.begin();
        iter != care_periods_.end();
        iter++){
        std::set<std::string> staff_list = iter->second->get_staff_list();

        if(staff_list.find(staff_id) != staff_list.end()){
            iter->second->print_period();
            is_period = true;
            std::cout<<"* Patient: "<<iter->first<<std::endl;
        }
    }

    // Print if no period is found
    utils::print_none(is_period);
}

// Print a given medicine list
void Hospital::print_medicine_list(std::map<std::string, std::set<std::string> > medicines)
{
    if(!medicines.empty()){
        for(std::map<std::string, std::set<std::string>>::iterator
            iter = medicines.begin();
            iter!= medicines.end();
            iter++){
            std::cout<<iter->first<<" prescribed for"<<std::endl;
            for(std::set<std::string>::iterator
                iter_2 = iter->second.begin();
                iter_2 != iter->second.end();
                iter_2++){
                std::cout<<"* "<<*iter_2<<std::endl;
            }
        }
    }else{
        bool is_any_medicine = false;
        utils::print_none(is_any_medicine);
    }
}

// Make a medicines list and then print it
void Hospital::print_all_medicines(Params)
{
    std::map<std::string, std::set<std::string>> medicines;

    //Go throughh all patient
    for(std::map<std::string, Person*>::iterator
        iter = all_patients_.begin();
        iter != all_patients_.end();
        iter++){
        // This is only a vector of strings, for the sack of simplicity
        // we just use for instead of pointer
        for(auto& medicines_of_patient: (iter->second->get_medicines())){
            if(medicines.find(medicines_of_patient)==medicines.end()){
                medicines.insert(std::pair<std::string,std::set<std::string>>
                                 (medicines_of_patient, {iter->first}));
            }else{
                medicines.at(medicines_of_patient).insert(iter->first);
            }
        }
    }

    print_medicine_list(medicines);
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

// Take a list of patients and print it
void Hospital::print_a_patient_list(const std::map<std::string, Person*>& list)
{
    // A boolen variable to make sure there is at least one element
    bool is_anyone = false;

    // Go through the patien list and then call print_patient_info for each of them
    for(auto& patient: list){
        std::cout<<patient.first<<std::endl;

        // Change the id to a vector of 1 element to put it in the print_patient_info
        std::vector<std::string> id_vector = utils::string_to_vector(patient.first);
        print_patient_info(id_vector);
        is_anyone = true;
    }

    // print none if no element found
    utils::print_none(is_anyone);
}

// Print all patients
void Hospital::print_all_patients(Params)
{
    print_a_patient_list(all_patients_);
}

// Print all current patients
void Hospital::print_current_patients(Params)
{
    print_a_patient_list(current_patients_);
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
            not utils::is_numeric(month, false) or
            not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}


