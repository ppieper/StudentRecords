#include <StudentApp.h>

int main()
{
    // get our app with a blank database
    StudentApp app = StudentApp(StudentDatabase());
    // run it
    app.run();

    return 0;
}
