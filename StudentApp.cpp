#include <StudentDatabase.h>
#include <StudentApp.h>
#include <string>
#include <set>
#include <iostream>

using namespace std;

StudentApp::StudentApp()
{

}

void StudentApp::run()
{
    m_records = StudentDatabase(); // get our blank database
    char choice;
    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
            case '1': promptAddStudent(); break;
            case '2': promptRemoveStudent(); break;
            case '3': promptModifyStudent(); break;
            case '4': promptPrintStudent(); break;
            case '5': promptPrintStudentsInYear(); break;
            case '6': promptSave(); break;
            case '7': promptLoad(); break;
            case 'q': return; break;
            default: break;
        }
    } while(choice != 'q' && (choice > 7 || choice < 1));

}

void StudentApp::displayMenu()
{
    cout << "====== STUDENT DATABASE MANAGEMENT SYSTEM ======\n\n\n";
    cout << "1. Add\n";
    cout << "2. Remove\n";
    cout << "3. Modify\n";
    cout << "4. Print\n";
    cout << "5. Print in year\n";
    cout << "6. Save\n";
    cout << "7. Load\n";
    cout << "Press 'q' to Quit\n";
    cout << "\nSelect your choice :=> ";
}

/**
 * @brief StudentApp::promptSave - Prompt user to save db to file
 *
 *                                 User inputs a filename and a new
 *                                 file is created with the db data
 */
void StudentApp::promptSave()
{
    char choice;
    do
    {
        cout << "Save to a file? (y/n) :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        if(choice == 'n')
            return;
        else if(choice == 'y')
        {
            string saveFile;
            cout << "Enter filename to save :=> ";
            cin >> saveFile;
            m_records.saveAllRecords(saveFile);
            return;
        }
    } while (choice !='n' && choice != 'y');
}

/**
 * @brief StudentApp::promptLoad - Prompt the user to load a file
 *
 *                                 User inputs a filename and the
 *                                 new db is constructed
 */
void StudentApp::promptLoad()
{
    string loadFile;
    char choice;
    do
    {
        cout << "Load from a file? Current db will be lost (y/n) :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        if(choice == 'n')
            return;
        else if(choice == 'y')
        {
            cout << "Enter filename to load :=> ";
            cin >> loadFile;
            cin.ignore();
            m_records.loadSaveFile(loadFile); // attempt to load the file
            return;
        }
    } while (choice !='n' && choice != 'y');
}

/**
 * @brief StudentApp::promptPrintStudent - Prompt the user to print out a student record
 *
 *                                         User inputs an id and the corresponding db
 *                                         function is called
 */
void StudentApp::promptPrintStudent()
{
    string choice;
    do
    {
        cout << "\n====== PRINT STUDENTS RECORD ======\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nEnter a 9-digit student id :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (choice !="q" && choice.length()!= 1);

    if(choice == "q")
        return;

    long id;
    id = stol(choice);
    const StudentRecord* record = m_records.findRecord(id);
    if(!record)
    {
        cout << "Lookup failed:" << endl << "--No record exists with student id " << id
             << endl << '\n';
    }
    else
    {
        cout << "Lookup Successful:\n" << endl;
        m_records.printRecord(record);
    }
    promptContinue();
}

/**
 * @brief StudentApp::promptPrintStudentsInYear - Prompt user to print students in a year
 *
 *                                                User makes a year selection and the
 *                                                corresponding db function is called
 */
void StudentApp::promptPrintStudentsInYear()
{
    Year year;
    char choice;
    do
    {
        cout << "\n====== PRINT STUDENTS IN YEAR ======\n";
        cout << "1. Freshman\n";
        cout << "2. Sophomore\n";
        cout << "3. Junior\n";
        cout << "4. Senior\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
        switch (choice)
        {
            case '1': year = freshman; m_records.printAllInYear(year); goto PrintStudents; break;
            case '2': year = sophomore; m_records.printAllInYear(year); goto PrintStudents; break;
            case '3': year = junior; m_records.printAllInYear(year); goto PrintStudents; break;
            case '4': year = senior; m_records.printAllInYear(year); goto PrintStudents; break;
            case 'q': return; break;
            default: break;
        }
    } while (choice !='q' && (choice > 4 || choice < 1));
    PrintStudents:
    promptContinue();
}

/**
 * @brief StudentApp::promptAddStudent - Prompt user to add a student
 *
 *                                       User inputs the name, year, gender
 *                                       and a new StudentRecord is constructed
 *                                       and added to the db
 */
void StudentApp::promptAddStudent()
{
    string firstName, lastName ="";
    Year year = freshman;
    Gender gender = male;
    char choice;
    do
    {
        cout << "\n====== ADD STUDENT RECORD ======\n";
        cout << "1. First name - " << firstName << "\n";
        cout << "2. Last name - " << lastName << "\n";
        cout << "3. Year - " << m_records.getYearString(year) << "\n";
        cout << "4. Gender - " << (gender == male ? "male" : "female") << "\n";
        cout << "5. Save Record\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
        switch (choice)
        {
            case '1': firstName = promptFirstName(); break;
            case '2': lastName = promptLastName(); break;
            case '3': year = promptYear(); break;
            case '4': gender = promptGender(); break;
            case '5': if(firstName.length() < 2 || lastName.length() < 2)
                      {
                          cout << "Failure--Please be sure to enter a first & last name\n";
                          promptContinue();
                      }
                      else
                          goto Saving;
                      break;
            case 'q': return; break;
            default: break;
        }
    } while (choice !='q' && (choice > 5 || choice < 1));
    Saving:

    if(m_records.addRecord(firstName,lastName,year,gender))
        cout << "Unable to add student to the database";
    else
        cout << "Successfully added student to the database\n";
    promptContinue();
}

/**
 * @brief StudentApp::promptRemoveStudent - Prompt user to remove a student
 */
void StudentApp::promptRemoveStudent()
{
    string idChoice;
    do
    {
        cout << "\n====== REMOVE STUDENTS RECORD ======\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nEnter a 9-digit student id :=> ";
        cin >> idChoice;
        cin.ignore();
        cout << "\n";
    } while (idChoice !="q" && idChoice.length()!= 1);

    if(idChoice == "q")
        return;

    // display the record to be deleted first
    long id = stol(idChoice);
    const StudentRecord* record = m_records.findRecord(id);
    if(!record)
    {
        cout << "\nNo record of student " << id << " in database\n";
        promptContinue();
        return;
    }
    m_records.printRecord(record);

    // make sure the user really wants to delete this record
    char choice;
    do
    {
        cout << "Delete this record? (y/n) :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        if(choice == 'n')
            return;
        else if(choice == 'y')
        {
            if (m_records.deleteRecord(id))
            {
                cout << "Deletion failed:" << endl << "--No record exists with student id " << id
                     << endl << "\n";
            }
            else
            {
                cout << "--Successfully deleted student id " << id << endl << '\n';
            }

            promptContinue();
            return;
        }
    } while (choice !='n' && choice != 'y');
}

/**
 * @brief StudentApp::promptModifyStudent - Prompt user to modify a student record
 *
 *                                          User inputs the name, year, gender
 *                                          and the record is updated in the db
 */
void StudentApp::promptModifyStudent()
{
    string idChoice;
    do
    {
        cout << "\n====== MODIFY STUDENT RECORD ======\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nEnter a 9-digit student id :=> ";
        cin >> idChoice;
        cin.ignore();
        cout << "\n";
    } while (idChoice !="q" && idChoice.length()!= 1);

    // quit to menu
    if(idChoice == "q")
        return;

    // otherwise, get the record to be modified
    long id = stol(idChoice);
    const StudentRecord* record = m_records.findRecord(id);
    if(!record)
    {
        cout << "\nNo record of student " << id << " in database\n";
        promptContinue();
        return;
    }

    string firstName = record->getFirstName();
    string lastName = record->getLastName();
    Year year = record->getYear();
    Gender gender = record->getGender();

    // display modification menu
    char choice;
    do
    {
        cout << "\n====== MODIFY STUDENT RECORD ======\n";
        cout << "1. First name - " << firstName << "\n";
        cout << "2. Last name - " << lastName << "\n";
        cout << "3. Year - " << m_records.getYearString(year) << "\n";
        cout << "4. Gender - " << (gender == male ? "male" : "female") << "\n";
        cout << "5. Save Record\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice)
        {
            case '1': firstName = promptFirstName(); break;
            case '2': lastName = promptLastName(); break;
            case '3': year = promptYear(); break;
            case '4': gender = promptGender(); break;
            case '5': if(firstName.length() < 2 || lastName.length() < 2)
                      {
                          cout << "Failure--Please be sure to enter a first & last name\n";
                          promptContinue();
                      }
                      else
                          goto Modifying;
                      break;
            case 'q': return; break;
            default: break;
        }
    } while (choice !='q' && (choice > 5 || choice < 1));
    Modifying:

    if(choice == 'q')
        return;

    if(m_records.updateRecord(id,firstName,lastName,year,gender))
    {
        cout << "Update failed:" << endl << "--No record exists with student id " << id
             << endl << '\n';
    }
    else
        cout << "Update Successful\n";

    promptContinue();
}

/**
 * @brief StudentApp::promptFirstName - Prompt user for a first name string input
 * @return
 */
string StudentApp::promptFirstName()
{
    string choice;
    do
    {
        cout << "\nPress 'q' to return to menu\n";
        cout << "\nEnter a first name :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (choice !="q" && choice.length() < 2);

    return choice;
}

/**
 * @brief StudentApp::promptLastName - Prompt user for a last name string input
 * @return
 */
string StudentApp::promptLastName()
{
    string choice;
    do
    {
        cout << "\nPress 'q' to return to menu\n";
        cout << "\nEnter a last name :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (choice !="q" && choice.length() < 2);

    return choice;
}

/**
 * @brief StudentApp::promptYear - Prompt user to make a year selection
 * @return
 */
Year StudentApp::promptYear()
{
    Year year = freshman;
    char choice;
    do
    {
        cout << "1. Freshman\n";
        cout << "2. Sophomore\n";
        cout << "3. Junior\n";
        cout << "4. Senior\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
        switch (choice)
        {
            case '1': year = freshman; return year; break;
            case '2': year = sophomore; return year; break;
            case '3': year = junior; return year; break;
            case '4': year = senior; return year; break;
            case 'q': return freshman; break;
            default: break;
        }
    } while (choice !='q' && (choice > 4 || choice < 1));

    return year;
}

/**
 * @brief StudentApp::promptGender - Prompt user to make a gender selection
 * @return
 */
Gender StudentApp::promptGender()
{
    Gender gender = male;
    char choice;
    do
    {
        cout << "1. Male\n";
        cout << "2. Female\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
        switch (choice)
        {
            case '1': gender = male; return gender; break;
            case '2': gender = female; return gender; break;
            case 'q': return male; break;
            default: break;
        }
    } while (choice !='q' && (choice > 2 || choice < 1));
    return gender;
}

void StudentApp::promptContinue()
{
    cout << "Press enter to continue :=> ";
    cin.ignore();
    cout << "\n";
}
