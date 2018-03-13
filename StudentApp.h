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
    void promptLoad();
    void promptSave();
    void promptContinue();
    void displayMainMenu();
    void printAllRecords();
    bool isIdValid(std::string);

    void promptAddStudent();
    void promptRemoveStudent();
    void promptModifyStudent();

    std::string promptFirstName(std::string);
    std::string promptLastName(std::string);
    Year promptYear();
    Gender promptGender();

    void promptPrintStudent();
    void promptPrintStudentsInYear();

private:
    StudentDatabase m_database;
};



#endif // STUDENTAPP_H
