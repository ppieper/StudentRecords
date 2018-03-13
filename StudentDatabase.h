#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <StudentRecord.h>

const int SUCCESS          = 0;
const int ERR_NOT_FOUND    = 1;
const int ERR_OUT_OF_RANGE = 2;
const int ERR_DUPLICATE_ID = 3;

/**
 * @brief The StudentDatabase class
 */
class StudentDatabase
{
public:
    StudentDatabase(std::string filePath){
        m_sys_id = 0;

        // no file given
        if(filePath.empty())
            return;

        std::ifstream inFile(filePath);

        // file given is not valid
        if(!inFile)
        {
            std::cout << "Could not find file: " << filePath << "\n";
            return;
        }

        // else load file
        long id = 0;
        std::string firstName, lastName;
        int year;
        int gender;
        while (inFile.good())
        {
            inFile >> id; inFile >> firstName >> lastName >> year >> gender;
            m_records.insert(StudentRecord(id,firstName,lastName,(Year)year,(Gender)gender));
            m_sys_id = id + 1;
        }
        inFile.close();
    }

    std::set<StudentRecord, StudentRecordCompare> getDatabase() const {return m_records;}
    const char* getYearString(Year year) const {return yearStrings[year];}

    int addRecord(std::string,std::string,Year,Gender);
    int addRecord(long,std::string,std::string,Year,Gender);
    int deleteRecord(long);
    int updateRecord(long,std::string,std::string,Year,Gender);
    const StudentRecord* findRecord(long);

    bool inRange(long);

    void printAllInYear(Year);
    void printAllRecords();
    void printRecord(const StudentRecord*);
    void saveAllRecords(std::string);

private:
    std::set<StudentRecord, StudentRecordCompare> m_records;
    long m_sys_id;
};

#endif // STUDENTDATABASE_H
