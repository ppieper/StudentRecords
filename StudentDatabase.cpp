#include <StudentDatabase.h>
#include <string>
#include <set>
#include <iostream>

using namespace std;

/**
 * @brief inRange - Checks that the given id is within the valid range of ids.
 * @param id
 * @return true if id is within range, false if not
 */
bool StudentDatabase::inRange(long id)
{
    // check that the provided id is within range
    return !(id < 0 || id >= m_sys_id);
}

/**
 * @brief findRecord - Search for a student record given an id and return a
 *                     pointer to it.
 * @param id
 * @return StudentRecord* if successful, nullptr
 */
const StudentRecord* StudentDatabase::findRecord(long id)
{
     if (inRange(id))
     {
         set<StudentRecord>::iterator it = m_records.find(StudentRecord(id));
         if(it == m_records.end())
             return nullptr; // failure
         else
            return &(*it); // success
     }
     return nullptr; // failure

}

/**
 * @brief updateRecord - Update an existing record given an id
 * @param id
 * @param firstName
 * @param lastName
 * @param year
 * @param gender
 * @return 0 if successful, 1 if failure
 */
int StudentDatabase::updateRecord(long id, string firstName, string lastName, Year year, Gender gender)
{
     if(deleteRecord(id))
         return 1; // failure
     if(addRecord(id, firstName,lastName,year,gender))
        return 1; //failure
     return 0; // success
}

/**
 * @brief addRecord - Add a student record to the database, auto increments the PK (id)
 * @param firstName
 * @param lastName
 * @param year
 * @param gender
 * @returns 0 if successful, 1 if not
 */
int StudentDatabase::addRecord(string firstName, string lastName, Year year, Gender gender)
{
    auto result = m_records.insert(StudentRecord(m_sys_id, firstName,lastName,year,gender));
    if(result.second == false)
        return 1; // failure
    m_sys_id++; // increment the current system id
    return 0; // success

}

/**
 * @brief addRecord - Add a student record to the database --* this version is to be
 *                    called by updateRecord
 * @param id
 * @param firstName
 * @param lastName
 * @param year
 * @param gender
 * @returns 0 if successful, 1 if not
 */
int StudentDatabase::addRecord(long id, string firstName, string lastName, Year year, Gender gender)
{
    auto result = m_records.insert(StudentRecord(id,firstName,lastName,year,gender));
    if(result.second == false)
        return 1; // failure
    return 0; // success

}

/**
 * @brief deleteRecord
 * @param id
 * @return 0 if successful, 1 if failure
 */
int StudentDatabase::deleteRecord(long id)
{
    if (inRange(id))
    {
        if(m_records.erase(StudentRecord(id)))
            return 0; // success
    }
    return 1; // failure
}

/**
 * @brief StudentDatabase::printRecord - Print a single student record, given a
 *                                       pointer to the record
 * @param record
 */
void StudentDatabase::printRecord(const StudentRecord* record)
{
    cout << "Id: " << record->getId() << endl;
    cout << "Name: " << record->getFirstName() << " " << record->getLastName() << endl;
    cout << "Year: " << getYearString(record->getYear()) << endl;
    cout << "Gender: " << (record->getGender() == male ? "male" : "female") << endl;
}

/**
 * @brief StudentDatabase::printAllRecords - Print all student records
 * @param id
 */
void StudentDatabase::printAllRecords()
{
    set<StudentRecord>::iterator it = m_records.begin();
    for(; it != m_records.end(); it++)
    {
        printRecord(&(*it));
    }
}

/**
 * @brief printAllInYear - Print all of the students that belong to a given year of
 *                         graduation.
 * @param year
 */
void StudentDatabase::printAllInYear(Year year)
{
    set<StudentRecord>::iterator it = m_records.begin();
    for(; it != m_records.end(); it++)
    {
        if(it->getYear() == year)
        {
            printRecord(&(*it));
        }
    }
}
