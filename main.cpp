#include <StudentRecord.h>
#include <StudentDatabase.h>
#include <set>

using namespace std;

int main()
{
    string loadFile;
    char choice;
    do
    {
        cout << "Load from a file? (y/n) :=> ";
        cin >> choice;
        choice = tolower(choice);
        if(choice == 'n')
            break;
        else if(choice == 'y')
        {
                cout << "Enter filename to load :=> ";
                cin >> loadFile;
                break;
        }
    } while (choice !='n' && choice != 'y');

    StudentDatabase records = StudentDatabase(loadFile); // get our database

    // testing database functions for now

    // populate the database
    records.addRecord("Alaska","T",freshman,female);
    records.addRecord("Detox","S",sophomore,male);
    records.addRecord("Roxxxy","Andrews",junior,female);
    records.addRecord("Paul","Pieper",senior, male);

    // print all sophomores
    cout << endl << "Listing sophomores:" << endl;
    records.printAllInYear(sophomore);

    // search
    cout << endl << "Testing search on student id 4:" << endl;
    long findId = 4;
    const StudentRecord* record = records.findRecord(findId);
    if(record == nullptr)
        cout << "Lookup failed:" << endl << "--No record exists with student id " << findId << endl;
    else
    {
        cout << "Lookup Successful:" << endl;
        records.printRecord(record);
    }

    // search
    cout << endl << "Testing search on student id 2:" << endl;
    findId = 2;
    record = records.findRecord(findId);
    if(record == nullptr)
        cout << "Lookup failed:" << endl << "--No record exists with student id " << findId << endl;
    else
    {
        cout << "Lookup Successful:" << endl;
        records.printRecord(record);
    }

    // update
    long updateId = 3;
    cout << endl << "Testing update on student id 3:" << endl;
    if(records.updateRecord(updateId,"Bianca","Delrio",sophomore,female))
        cout << "Update failed:" << endl << "--No record exists with student id " << updateId << endl;
    else
        cout << "Update Successful:" << endl;

    // delete
    cout << endl << "Testing delete on student id 2:" << endl;
    long deleteId = 2;
    if (records.deleteRecord(deleteId))
        cout << "Deletion failed:" << endl << "--No record exists with student id " << deleteId << endl;
    else
        cout << "--Successfully deleted student id " << deleteId << endl;

    records.addRecord("Paul","Pieper",senior,male);

    // search again
    cout << endl << "Testing search on student id 2:" << endl;
    findId = 2;
    record = records.findRecord(findId);
    if(record == nullptr)
        cout << "Lookup failed:" << endl << "--No record exists with student id " << findId << endl;
    else
    {
        cout << "Lookup Successful:" << endl;
        records.printRecord(record);
    }

    // print all
    cout << endl << "Listing all students:" << endl;
    records.printAllRecords();

    // save record
    cout << "Enter a name for the savefile :=> ";
    string saveFile;
    cin >> saveFile;
    records.saveAllRecords(saveFile);
    return 0;
}
