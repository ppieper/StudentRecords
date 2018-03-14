#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include <set>
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
    StudentDatabase(){
        m_sys_id = 1;
    }

    StudentDatabase(std::string filePath){
        m_sys_id = 1;
        loadSaveFile(filePath);
    }
    std::set<StudentRecord, StudentRecordCompare> getDatabase() const {return m_records;}
    const char* getYearString(Year year) const {return yearStrings[year];}

    int addRecord(std::string,std::string,Year,Gender);
    int addRecord(int,std::string,std::string,Year,Gender);
    int deleteRecord(int);
    int updateRecord(int,std::string,std::string,Year,Gender);
    const StudentRecord* findRecord(int);

    bool inRange(int);
    int getCurrentId() const {return m_sys_id;}

    void printStudentsInYear(Year);
    void printAllRecords();
    void printRecord(const StudentRecord*);
    int saveAllRecords(std::string);

    /**
     * @brief loadSaveFile - Attempt to load a file given its path
     * @param filePath
     * @returns 0 if success, 1 if failure
     */
    int loadSaveFile(std::string filePath)
    {
        // no file given
        if(filePath.empty())
            return ERR_NOT_FOUND; // failure

        std::ifstream inFile(filePath);

        // file given is not valid
        if(!inFile)
        {
            return ERR_NOT_FOUND; // failure
        }

        // else load file
        m_records.clear(); // in case of loading a new db from the user app

        int id = 0;
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
        return SUCCESS; // success
    }

private:
    std::set<StudentRecord, StudentRecordCompare> m_records;
    int m_sys_id;
};

#endif // STUDENTDATABASE_H
