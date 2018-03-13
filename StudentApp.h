#ifndef STUDENTAPP_H
#define STUDENTAPP_H

#include <StudentDatabase.h>

/**
 * @brief The StudentApp class
 */
class StudentApp
{
public:
    StudentApp(StudentDatabase database)
    {
        m_database = database;
    }

    void run();
    void displayMainMenu();
    void printAllRecords();
    bool isIdValid(std::string);
    const StudentRecord* findRecord(int);

    void promptAddStudent();
    void promptRemoveStudent();
    void promptModifyStudent();
    void promptLoad();
    void promptSave();
    void promptContinue();
    int promptEditRecordFields(const StudentRecord*);

    int promptStudentId();
    std::string promptFirstName(std::string);
    std::string promptLastName(std::string);
    Year promptYear(Year);
    Gender promptGender(Gender);

    void promptPrintStudent();
    void promptPrintStudentsInYear();

private:
    StudentDatabase m_database;
};



#endif // STUDENTAPP_H
