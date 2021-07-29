/* Program author
* Name: Khoa Pham Dinh
* Student number: 050359620
* UserID: gmkhph
* E-Mail: khoa.phamdinh@tuni.fi
*
* Description
* This program simulates a hospital with patients, staff and care periods
* There are 6 modules beside the main function:
* careperiod: defines class CarePeriod, which define a care period
* with patient, staff and date record
*
* cli: the module establishes the user interface for the program
*
* date: define class Date, which represent date
* the class also define some important action with date
*
* person: defines class Person, which are staff and patient
* an object of this class store information about medicines of
* a person, name and define some action
*
* hospital: defines class Hospital, the main class of the program
* an object hospital represent a hospital and manapulate person objects there
* it also record about the care periods
*
* utils: define some miscellanous functions which use as tools for the program
*
* In this program, there are 17 commands, 9 of them were written
* the other 8 commands are given as tasks:
* Written commands:
* QUIT: quit the program
* HELP: print instructions
* READ_FROM: read an input file
* SET_DATE: set the date
* ADVANCE_DATE: increase date by a given number
* RECRUIT: recruit a staff
* PRINT_ALL_STAFF: print all the staff
* ADD_MEDICINE: add medicine for a patient
* REMOVE_MEDICINE: remove medicine for a patient
*
* Task commands:
* ENTER: a new patient enter
* LEAVE: a patient leave
* ASSIGN_STAFF: assign a staff to a patient
* PRINT_PATIENT_INFOR: print infor of a patient
* PRINT_CARE_PERIODS: print record of all care period in the past
* PRINT_ALL_MEDICINES: print the medicines of all patient in past and now
* PRINT_CURRENT_PATIENTS: Print the information of all current patients
* PRINT_ALL_PATIENTS: Print the information of all patients of all time
*
*/
#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
