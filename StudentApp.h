#ifndef STUDENTAPP_H
#define STUDENTAPP_H

#include <string>
#include <StudentRecord.h>
#include <StudentDatabase.h>

/**
 * @brief The StudentApp class
 */
class StudentApp
{
public:
    StudentApp();

    void run();
    void promptLoad();
    void promptSave();
    void promptContinue();
    void displayMenu();

    void promptAddStudent();
    void promptRemoveStudent();
    void promptModifyStudent();

    std::string promptFirstName();
    std::string promptLastName();
    Year promptYear();
    Gender promptGender();

    void promptPrintStudent();
    void promptPrintStudentsInYear();

private:
    StudentDatabase m_records;
};



#endif // STUDENTAPP_H
