#include <StudentApp.h>
#include <iostream>

using namespace std;

/**
 * @brief StudentApp::run - Run the program until the user
 *                          inputs that they want to Quit
 */
void StudentApp::run()
{
    char choice;
    do
    {
        displayMainMenu();
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        switch (choice)
        {
            case '1': case 'a': promptAddStudent(); break;
            case '2': case 'r': promptRemoveStudent(); break;
            case '3': case 'm': promptModifyStudent(); break;
            case '4': case 'p': promptPrintStudent(); break;
            case '5': case 'y': promptPrintStudentsInYear(); break;
            case '6': case 't': printAllRecords(); break;
            case '7': case 's': promptSave(); break;
            case '8': case 'l': promptLoad(); break;
            case 'q': return;
            default: break;
        }
    } while(choice != 'q' && (choice > 8 || choice < 1));

}

/**
 * @brief StudentApp::displayMenu - Display the main menu
 */
void StudentApp::displayMainMenu()
{
    cout << "====== STUDENT DATABASE MANAGEMENT SYSTEM ======\n\n\n";
    cout << "1. (A)dd              Record\n";
    cout << "2. (R)emove           Record\n";
    cout << "3. (M)odify           Record\n";
    cout << "4. (P)rint            Record\n";
    cout << "5. Print in (y)ear    Records\n";
    cout << "6. Prin(t) all        Records\n";
    cout << "7. (S)ave             Database\n";
    cout << "8. (L)oad             Database\n";
    cout << "Press 'q' to Quit\n";
    cout << "\nSelect your choice :=> ";
}

/**
 * @brief StudentApp::promptPrintStudent - Prompt the user to print out a student record
 *
 *                                         User inputs an id and the corresponding db
 *                                         function is called
 */
void StudentApp::promptPrintStudent()
{
    cout << "\n====== PRINT STUDENTS RECORD ======\n";
    int id = promptStudentId();

    // Quit to menu
    if(!id)
        return;

    // else look up the record
    const StudentRecord* record = findRecord(id);
    if(!record)
        return;

    // print the record
    m_database.printRecord(record);

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
    cout << "\n====== PRINT STUDENTS IN YEAR ======\n";
    Year year = promptYear(no_year);
    switch (year)
    {
        case freshman: m_database.printAllInYear(year); promptContinue(); break;
        case sophomore: m_database.printAllInYear(year); promptContinue(); break;
        case junior: m_database.printAllInYear(year); promptContinue(); break;
        case senior: m_database.printAllInYear(year); promptContinue(); break;
        case no_year: return; break;
        default: break;
    }
}

/**
 * @brief StudentApp::promptPrintAllRecords - Prints all records in the db
 */
void StudentApp::printAllRecords()
{
    cout << "\n====== PRINT ALL RECORDS ======\n";
    m_database.printAllRecords();
    promptContinue();
}

/**
 * @brief StudentApp::promptStudentId - Prompt user for a 9-digit student id input
 * @returns int id - a valid student id or 0 if user Quit
 */
int StudentApp::promptStudentId()
{
    string choice;
    do
    {
        cout << "Press 'q' to return to menu\n";
        cout << "\nEnter a 9-digit student id :=> ";
        cin >> choice;
        cin.ignore();
        cout << endl;
    } while (choice !="q" && choice != "Q" && !isIdValid(choice));

    if (choice == "q" || choice == "Q")
        return 0;
    else
        return stoi(choice);
}

/**
 * @brief StudentApp::promptFirstName - Prompt user for a first name string input
 * @return string firstName - the chosen firstName or the original by default
 */
string StudentApp::promptFirstName(string original)
{
    string choice;
    do
    {
        cout << "\nEnter a first name (minimum 2 chars)\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nEnter your choice :=> ";
        cin >> choice;
        cin.ignore();
    } while (choice !="q" && choice != "Q" && choice.length() < 2);

    if (choice == "q" || choice == "Q")
        return original;
    else
        return choice;
}

/**
 * @brief StudentApp::promptLastName - Prompt user for a last name string input
 * @return string lastName - the chosen lastName or the original by default
 */
string StudentApp::promptLastName(string original)
{
    string choice;
    do
    {
        cout << "\nEnter a last name (minimum 2 chars)\n";
        cout << "\nPress 'q' to return to menu\n";
        cout << "\nEnter your choice :=> ";
        cin >> choice;
        cin.ignore();
    } while (choice !="q" && choice != "Q" && choice.length() < 2);

    if (choice == "q" || choice == "Q")
        return original;
    else
        return choice;
}

/**
 * @brief StudentApp::promptYear - Prompt user to make a year selection
 * @return Year year - the selected year or 'freshman' by default
 */
Year StudentApp::promptYear(Year original)
{
    Year year = freshman;
    char choice;
    do
    {
        cout << "1. (F)reshman\n";
        cout << "2. Sophomor(e)\n";
        cout << "3. (J)unior\n";
        cout << "4. (S)enior\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        switch (choice)
        {
            case '1': case 'f': year = freshman; goto Done; break;
            case '2': case 'e': year = sophomore; goto Done; break;
            case '3': case 'j': year = junior; goto Done; break;
            case '4': case 's': year = senior; goto Done; break;
            case 'q': return original; break;
            default: break;
        }
    } while (choice !='q' && (choice > 4 || choice < 1));
    Done:
    return year;
}

/**
 * @brief StudentApp::promptGender - Prompt user to make a gender selection
 * @return Gender gender - the chosen gender or 'male' by default
 */
Gender StudentApp::promptGender(Gender original)
{
    Gender gender = male;
    char choice;
    do
    {
        cout << "1. (M)ale\n";
        cout << "2. (F)emale\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        switch (choice)
        {
            case '1': case 'm': gender = male; return gender; break;
            case '2': case 'f': gender = female; return gender; break;
            case 'q': return original; break;
            default: break;
        }
    } while (choice !='q' && (choice > 2 || choice < 1));
    return gender;
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
    cout << "\n====== ADD STUDENT RECORD ======\n";
    int exitCode = promptEditRecordFields(nullptr);

    // Quit to menu
    if(exitCode == -1)
        return;

    if(exitCode)
        cout << "Unable to add student to the database" << endl;
    else
        cout << "Successfully added student to the database" << endl;
    promptContinue();
}

/**
 * @brief StudentApp::promptRemoveStudent - Prompt user to remove a student
 */
void StudentApp::promptRemoveStudent()
{
    cout << "\n====== REMOVE STUDENTS RECORD ======\n";
    int id = promptStudentId();

    // Quit to menu
    if(!id)
        return;

    // otherwise, get the record to be removed
    const StudentRecord* record = findRecord(id);
    if(!record)
        return;

    // print it
    m_database.printRecord(record);

    // make sure the user really wants to delete this record
    char choice;
    do
    {
        cout << "Delete this record? (y/n) :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        cout << endl;
        if(choice == 'n')
            return;
        else if(choice == 'y')
        {
            if (m_database.deleteRecord(id))
            {
                cout << "\nDeletion failed\n--No record of student  "
                     << padIdWithZeroes(id) << " in database\n" << endl;
            }
            else
            {
                cout << "\nSuccessfully deleted student id " << id << '\n' << endl;
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
    cout << "\n====== MODIFY STUDENT RECORD ======\n";
    int id = promptStudentId();

    // Quit to menu
    if(!id)
        return;

    // otherwise, get the record to be modified
    const StudentRecord* record = findRecord(id);
    if(!record)
        return;

    cout << "\n====== MODIFY STUDENT RECORD ======\n";
    int exitCode = promptEditRecordFields(record);

    // Quit to menu
    if(exitCode == -1)
        return;

    if(exitCode)
    {
        cout << "Update failed:\n--No record exists with student id "
             << padIdWithZeroes(id) << '\n' << endl;
    }
    else
        cout << "Update Successful" << endl;
    promptContinue();
}

/**
 * @brief StudentApp::promptSave - Prompt user to save db to file
 *
 *                                 User inputs a filename and a new
 *                                 file is created with the db data
 */
void StudentApp::promptSave()
{
    string saveFile;
    cout << "Enter filename to save or 'q' to return to menu :=> ";
    cin >> saveFile;
    cin.ignore();
    if (saveFile == "q")
        return;
    if(m_database.saveAllRecords(saveFile))
        cout << "There was a problem saving " << saveFile << endl;
    else
        cout << "Successfully saved " << saveFile << endl;
    promptContinue();
    return;
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
            cout << "Enter filename to load or 'q' to return to menu :=> ";
            cin >> loadFile;
            cin.ignore();
            cout << endl;
            if (loadFile == "q")
                return;
            if(m_database.loadSaveFile(loadFile)) // attempt to load the file
                cout << "Could not find file: " << loadFile << endl;
            else
                cout << "Successfully loaded the file: " << loadFile << endl;
            promptContinue();
            return;
        }
    } while (choice !='n' && choice != 'y');
}

/**
 * @brief StudentApp::promptEditRecordFields - Prompt user to edit record fields
 * @param record
 * @returns 0 if successful, 1 or 2 if failure, -1 if quit
 */
int StudentApp::promptEditRecordFields(const StudentRecord* record)
{
    // default values
    string firstName = "Jane";
    string lastName = "Doe";
    Year year = freshman;
    Gender gender = male;

    // if we are given a record, use its values
    if(record)
    {
        firstName = record->getFirstName();
        lastName = record->getLastName();
        year = record->getYear();
        gender = record->getGender();
    }
    // present the user with a menu & wait for input
    char choice;
    do
    {
        cout << "========= # " << padIdWithZeroes(record ? record->getId() : m_database.getCurrentId())
             << " ==========\n";
        cout << "1. (F)irst name - " << firstName << "\n";
        cout << "2. (L)ast name - " << lastName << "\n";
        cout << "3. (Y)ear - " << m_database.getYearString(year) << "\n";
        cout << "4. (G)ender - " << (gender == male ? "male" : "female") << "\n";
        cout << "5. (S)ave Record\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        cout << endl;
        switch (choice)
        {
            case '1': case 'f': firstName = promptFirstName(firstName); break;
            case '2': case 'l': lastName = promptLastName(lastName); break;
            case '3': case 'y': year = promptYear(year); break;
            case '4': case 'g': gender = promptGender(gender); break;
            case '5': case 's': if(firstName.length() < 2 || lastName.length() < 2)
                                {
                                    cout << "--Failed to save record; please be sure to "
                                            "enter a valid first & last name" << endl;
                                    promptContinue();
                                }
                                else
                                    return (record ? m_database.updateRecord(record->getId(), firstName,
                                                                             lastName, year, gender)
                                                   : m_database.addRecord(firstName,lastName,year,gender));
                                break;
            case 'q': return -1; break;
            default: break;
        }
    } while (choice !='q' && (choice > 5 || choice < 1));
    return -1;
}

/**
 * @brief StudentApp::promptContinue -- Prompts the user to continue -- useful for when
 *                                      you need to hold some display on the screen e.g.
 *                                      viewing a record or error message
 */
void StudentApp::promptContinue()
{
    cout << "Press enter to continue :=> ";
    cin.ignore();
    cout << endl;
}

/**
 * @brief StudentApp::isIdValid - Return true if the id is valid aka 9 digits non-negative
 *                                (ids < 9 digits are allowed, since they get padded with 0's)
 * @param id
 */
bool StudentApp::isIdValid(string id)
{
    return (id.length() < 10 && stoi(id) > 0);
}

/**
 * @brief StudentApp::findRecord - Search for a record in the database given an id
 * @param id
 * @returns a record pointer if successful, nullptr if not
 */
const StudentRecord* StudentApp::findRecord(int id)
{
    const StudentRecord* record = m_database.findRecord(id);
    if(!record)
    {
        cout << "\nLookup failed:\n--No record of student "
             << padIdWithZeroes(id) << " in database\n" << endl;
        promptContinue();
        return nullptr;
    }
    return record;
}
