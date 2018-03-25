#ifndef STUDENTRECORD_H
#define STUDENTRECORD_H

#include <string>

enum Gender {male, female, no_gender};
enum Year {freshman, sophomore, junior, senior, no_year};
static const char* yearStrings[] = {"freshman", "sophomore", "junior", "senior", ""};

/**
 * @brief The StudentRecord class
 */
class StudentRecord
{
public:
    StudentRecord(int id, std::string firstName, std::string lastName, Year year, Gender gender)
    {
        m_id = id;
        m_firstName = firstName;
        m_lastName = lastName;
        m_year = year;
        m_gender = gender;
    }
    StudentRecord(int id)
    {
        m_id = id; // constructor for performing lookups
    }

    int getId() const {return m_id;}
    std::string getFirstName() const {return m_firstName;}
    std::string getLastName() const {return m_lastName;}
    Year getYear() const {return m_year;}
    Gender getGender() const {return m_gender;}

private:
    int m_id;
    std::string m_firstName;
    std::string m_lastName;
    Year m_year;
    Gender m_gender;
};

/**
 * @brief StudentRecordCompare - value comparison for std::set
 */
struct StudentRecordCompare
{
    bool operator() (const StudentRecord& record1, const StudentRecord& record2) const
    {
        return (record1.getId() < record2.getId());
    }
};
extern std::string padIdWithZeroes(int); // defined in StudentDatabase.cpp

#endif // STUDENTRECORD_H
