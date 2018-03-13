#include <StudentApp.h>
#include <iostream>

using namespace std;

/**
 * @brief StudentApp::run - Run the program until the user
 *                          inputs that they want to quit
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
    {
        cout << "There was a problem saving " << saveFile << '\n';
        promptContinue();
        return;
    }
    cout << "Successfully saved " << saveFile << '\n';
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
            if (loadFile == "q")
                return;
            if(m_database.loadSaveFile(loadFile)) // attempt to load the file
            {
                std::cout << "Could not find file: " << loadFile << "\n";
                promptContinue();
                return;
            }
            std::cout << "Successfully loaded the file: " << loadFile << "\n";
            promptContinue();
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
    } while (choice !="q" && !isIdValid(choice));

    if(choice == "q")
        return;

    int id;
    id = stoi(choice);
    const StudentRecord* record = m_database.findRecord(id);
    if(!record)
    {
        cout << "Lookup failed:" << endl << "--No record exists with student id "
             << padIdWithZeroes(id) << endl << '\n';
    }
    else
    {
        cout << "Lookup Successful:\n" << endl;
        m_database.printRecord(record);
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
    choice = tolower(choice);
    do
    {
        cout << "\n====== PRINT STUDENTS IN YEAR ======\n";
        cout << "1. (F)reshman\n";
        cout << "2. Sophomor(e)\n";
        cout << "3. (J)unior\n";
        cout << "4. (S)enior\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
        switch (choice)
        {
            case '1': case 'f': year = freshman; m_database.printAllInYear(year); promptContinue(); break;
            case '2': case 'e': year = sophomore; m_database.printAllInYear(year); promptContinue(); break;
            case '3': case 'j': year = junior; m_database.printAllInYear(year); promptContinue(); break;
            case '4': case 's': year = senior; m_database.printAllInYear(year); promptContinue(); break;
            case 'q': return; break;
            default: break;
        }
    } while (choice !='q' && (choice > 4 || choice < 1));
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
 * @brief StudentApp::promptAddStudent - Prompt user to add a student
 *
 *                                       User inputs the name, year, gender
 *                                       and a new StudentRecord is constructed
 *                                       and added to the db
 */
void StudentApp::promptAddStudent()
{
    string firstName = "Jane";
    string lastName = "Doe";
    Year year = freshman;
    Gender gender = male;
    char choice;
    do
    {
        cout << "\n====== ADD STUDENT RECORD ======\n";
        cout << "========= # " << padIdWithZeroes(m_database.getCurrentId()) << " ==========\n";
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
        cout << "\n";
        switch (choice)
        {
            case '1': case 'f': firstName = promptFirstName(firstName); break;
            case '2': case 'l': lastName = promptLastName(lastName); break;
            case '3': case 'y': year = promptYear(); break;
            case '4': case 'g': gender = promptGender(); break;
            case '5': case 's': if(firstName.length() < 2 || lastName.length() < 2)
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

    if(m_database.addRecord(firstName,lastName,year,gender))
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
    } while (idChoice !="q" && !isIdValid(idChoice));

    // quit to menu
    if(idChoice == "q")
        return;

    // display the record to be deleted first
    int id = stoi(idChoice);
    const StudentRecord* record = m_database.findRecord(id);
    if(!record)
    {
        cout << "\nNo record of student " << padIdWithZeroes(id) << " in database\n";
        promptContinue();
        return;
    }
    m_database.printRecord(record);

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
            if (m_database.deleteRecord(id))
            {
                cout << "Deletion failed:" << endl << "--No record exists with student id "
                     << padIdWithZeroes(id) << endl << "\n";
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
    } while (idChoice !="q" && !isIdValid(idChoice));

    // quit to menu
    if(idChoice == "q")
        return;

    // otherwise, get the record to be modified
    int id = stoi(idChoice);
    const StudentRecord* record = m_database.findRecord(id);
    if(!record)
    {
        cout << "\nNo record of student " << padIdWithZeroes(id) << " in database\n";
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
        cout << "=========== # " << padIdWithZeroes(id) << " ===========\n";
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
        cout << "\n";

        switch (choice)
        {
            case '1': case 'f': firstName = promptFirstName(firstName); break;
            case '2': case 'l': lastName = promptLastName(lastName); break;
            case '3': case 'y': year = promptYear(); break;
            case '4': case 'g': gender = promptGender(); break;
            case '5': case 's': if(firstName.length() < 2 || lastName.length() < 2)
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

    if(m_database.updateRecord(id,firstName,lastName,year,gender))
    {
        cout << "Update failed:" << endl << "--No record exists with student id "
             << padIdWithZeroes(id) << endl << '\n';
    }
    else
        cout << "Update Successful\n";

    promptContinue();
}

/**
 * @brief StudentApp::promptFirstName - Prompt user for a first name string input
 * @return
 */
string StudentApp::promptFirstName(string original)
{
    string choice;
    do
    {
        cout << "\nPress 'q' to return to menu\n";
        cout << "\nEnter a first name (mininum 2 chars):=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (choice !="q" && choice.length() < 2);

    if (choice == "q")
        return original;
    else
        return choice;
}

/**
 * @brief StudentApp::promptLastName - Prompt user for a last name string input
 * @return
 */
string StudentApp::promptLastName(string original)
{
    string choice;
    do
    {
        cout << "\nPress 'q' to return to menu\n";
        cout << "\nEnter a last name (minimun 2 chars):=> ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (choice !="q" && choice.length() < 2);

    if (choice == "q")
        return original;
    else
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
        cout << "1. (F)reshman\n";
        cout << "2. Sophomor(e)\n";
        cout << "3. (J)unior\n";
        cout << "4. (S)enior\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        cout << "\n";
        switch (choice)
        {
            case '1': case 'f': year = freshman; return year; break;
            case '2': case 'e': year = sophomore; return year; break;
            case '3': case 'j': year = junior; return year; break;
            case '4': case 's': year = senior; return year; break;
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
        cout << "1. (M)ale\n";
        cout << "2. (F)emale\n";
        cout << "Press 'q' to return to menu\n";
        cout << "\nSelect your choice :=> ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice);
        cout << "\n";
        switch (choice)
        {
            case '1': case 'm': gender = male; return gender; break;
            case '2': case 'f': gender = female; return gender; break;
            case 'q': return male; break;
            default: break;
        }
    } while (choice !='q' && (choice > 2 || choice < 1));
    return gender;
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
    cout << "\n";
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
