#include <StudentDatabase.h>
#include <iostream>

using namespace std;

/**
 * @brief inRange - Checks that the given id is within the valid range of ids
 * @param id
 * @returns true if id is within range, false if it is not
 */
bool StudentDatabase::inRange(int id)
{
    return !(id < 0 || id >= m_sys_id);
}

/**
 * @brief findRecord - Search for a student record given an id and return a
 *                     pointer to it
 * @param id
 * @returns StudentRecord* if successful, nullptr if failure
 */
const StudentRecord* StudentDatabase::findRecord(int id)
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
int StudentDatabase::updateRecord(int id, string firstName, string lastName, Year year, Gender gender)
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
int StudentDatabase::deleteRecord(int id)
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
    cout << "Id: " << padIdWithZeroes(record->getId()) << endl;
    cout << "Name: " << record->getFirstName() << " " << record->getLastName() << endl;
    cout << "Year: " << getYearString(record->getYear()) << endl;
    cout << "Gender: " << (record->getGender() == male ? "male" : "female") << endl;
    cout << '\n';
}

/**
 * @brief StudentDatabase::printAllRecords - Print all student records
 */
void StudentDatabase::printAllRecords()
{
    cout << "Printing all student records...\n\n";
    set<StudentRecord>::iterator it = m_records.begin();
    for(; it != m_records.end(); it++)
    {
        printRecord(&(*it));
    }
}

/**
 * @brief printStudentsInYear - Print all of the students that belong to a given year of
 *                              graduation in '#id - firstname lastname' format
 * @param year
 */
void StudentDatabase::printStudentsInYear(Year year)
{
    set<StudentRecord>::iterator it = m_records.begin();
    cout << "\nPrinting all " << getYearString(year) << " students...\n" << endl;
    bool found = false;
    for(; it != m_records.end(); it++)
    {
        if(it->getYear() == year)
        {
            cout << "# "<< padIdWithZeroes(it->getId()) << " - "
                 << it->getFirstName() << " " << it->getLastName() << endl;
            found = true;
        }
    }
    if(!found)
        cout << "(No " <<getYearString(year) << " students found)\n";

    cout << endl;
}

/**
 * @brief StudentDatabase::saveAllRecords - Save all student records to a file
 *                                          specified by user
 * @param filename
 * @returns 0 if success, 1 if failure
 */
int StudentDatabase::saveAllRecords(string filePath)
{
    if(filePath.empty())
        return ERR_NOT_FOUND; // failure
    ofstream file (filePath);
    if(!file)
        return ERR_NOT_FOUND; // failure
    set<StudentRecord>::iterator it = m_records.begin();
    for(; it != m_records.end(); it++)
    {
        file << " " << it->getId() << " " << it->getFirstName() << " " << it->getLastName()
              << " " << it->getYear() << " " << it->getGender();
    }
    file.close();
    return SUCCESS; // success
}

/**
 * @brief StudentApp::padWithZeroes - Take a numeric student id, convert to string,
 *                                    and pad it with zeroes so that it is 9 digits int
 * @param id
 * @return padded_id the string of 9 digits padded with leading 0's
 */
std::string padIdWithZeroes(int id)
{
    std::string original_id = std::to_string(id);
    std::string padded_id = std::string(9-original_id.length(), '0') + original_id;
    return padded_id;
}
