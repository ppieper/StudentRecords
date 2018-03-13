#include <StudentDatabase.h>
#include <string>
#include <set>
#include <iostream>

using namespace std;

/**
 * @brief inRange - Checks that the given id is within the valid range of ids
 * @param id
 * @returns true if id is within range, false if it is not
 */
bool StudentDatabase::inRange(long id)
{
    return !(id < 0 || id >= m_sys_id);
}

/**
 * @brief findRecord - Search for a student record given an id and return a
 *                     pointer to it
 * @param id
 * @returns StudentRecord* if successful, nullptr if failure
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
 * @returns 0 if successful, 1 (id not found) or 2 (id already in database) if failure
 */
int StudentDatabase::updateRecord(long id, string firstName, string lastName, Year year, Gender gender)
{
     if(deleteRecord(id))
         return ERR_NOT_FOUND; // failure
     auto result = m_records.insert(StudentRecord(id, firstName,lastName,year,gender));
     if(result.second == false)
         return ERR_DUPLICATE_ID; // failure
     return SUCCESS; // success
}

/**
 * @brief addRecord - Add a student record to the database, auto increments the PK (id)
 * @param firstName
 * @param lastName
 * @param year
 * @param gender
 * @returns 0 if successful, 1 if failure (id already in database)
 */
int StudentDatabase::addRecord(string firstName, string lastName, Year year, Gender gender)
{
    auto result = m_records.insert(StudentRecord(m_sys_id, firstName,lastName,year,gender));
    if(result.second == false)
        return ERR_DUPLICATE_ID; // failure
    m_sys_id++; // increment the current system id
    return SUCCESS; // success
}

/**
 * @brief deleteRecord
 * @param id
 * @returns 0 if successful, 1 (id not found) or 2 (id out of range) if failure
 */
int StudentDatabase::deleteRecord(long id)
{
    if (inRange(id))
    {
        if(m_records.erase(StudentRecord(id)))
            return SUCCESS; // success
        else
            return ERR_NOT_FOUND; // failure
    }
    return ERR_OUT_OF_RANGE; // failure
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
            printRecord(&(*it));
    }
}

/**
 * @brief StudentDatabase::saveAllRecords - Save all student records to a file
 *                                          specified by user.
 * @param filename
 */
void StudentDatabase::saveAllRecords(string filePath)
{
    ofstream file (filePath);
    set<StudentRecord>::iterator it = m_records.begin();
    for(; it != m_records.end(); it++)
    {
        file << " " << it->getId() << " " << it->getFirstName() << " " << it->getLastName()
              << " " << it->getYear() << " " << it->getGender();
    }
    file.close();
}
