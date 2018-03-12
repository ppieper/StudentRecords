#ifndef STUDENTDATABASE_H
#define STUDENTDATABASE_H

#include <set>
#include <string>
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
        m_sys_id = 0;
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

private:
    std::set<StudentRecord, StudentRecordCompare> m_records;
    long m_sys_id;
};

#endif // STUDENTDATABASE_H
