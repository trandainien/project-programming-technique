#include "functions.h"

// global var
StaffList *staffListHead = nullptr;
Staff newStaff;
Staff staff;

Node *studentListHead = nullptr;
Student student;
Student newStudent;

void start()
{
    loginSection();
}

void loginSection()
{
    int n;

    system("CLS"); // used for clearing the console
    cout << "***----------------------      Welcome to Student Management System    -----------------***" << endl;
    cout << "Please choose whether you are student or teacher: " << endl;
    cout << "1. Student" << endl;
    cout << "2. Academic Staff" << endl;
    cout << "3. End process" << endl;
    cout << "Your choice: ";
    cin >> n;

    if (n == 1)
    {

        StudentLoginSection();
        delete[] studentListHead;
    }
    else if (n == 2)
    {
        AcademicStaffLoginSection();
        delete[] staffListHead;
    }
    else
    {
        cout << "Have a nice day ^-^ ";
    }
}

bool findStudentWithID(string ID, string &classAddress, string password)
{
    string address = "School years\\"; // final goal is to find the class where this student are in

    string schoolYears[1000];
    int num;
    bool isStudentExist = false;
    // find school years folder
    ListAllFileNames("School years", false, schoolYears, num);

    for (int i = 0; i < num; i++)
    {
        // check
        string schoolYear = schoolYears[i];

        bool ok = true;
        for (int j = 2; j < 4; j++)
        {
            if (schoolYear[j] != ID[j - 2])
            {
                ok = false;
            }
        }
        if (ok)
        {
            address += schoolYear;
            isStudentExist = true;

            break;
        }
    }
    // find all the class in the school year folder which student are
    if (isStudentExist)
    {
        isStudentExist = false;
        string classNames[1000];
        int num1;

        ListAllFileNames(address, true, classNames, num1);

        for (int i = 0; i < num1; i++)
        {
            string className = classNames[i];

            studentListHead = nullptr;
            classAddress = address + "\\" + className + ".csv";
            // cout << classAddress << endl;
            findStudentInAClass(ID, classAddress, isStudentExist, password);

            if (isStudentExist)
            {

                return true;
            }
        }
    }

    return false;

    // return the info of that student, and the address of that class, and SLL of that class
}

void findStudentInAClass(string curID, string address, bool &isStudentExist, string password)
{
    bool isFind = false;
    ifstream input;
    address = ".\\inputs\\" + address;
    input.open(address);

    Node *pCur = studentListHead;

    string temp;
    getline(input, temp);

    while (!input.eof())
    {
        string no, ID, LastName, FirstName, Gender, DateOfBirth, SocialID, Password;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');
        getline(input, Gender, ',');
        getline(input, DateOfBirth, ',');
        getline(input, SocialID, ',');
        getline(input, Password);

        if (no == "")
        {
            return;
        }

        if (ID == curID && password == Password)
        {
            isStudentExist = true;
        }

        if (!studentListHead)
        {
            studentListHead = new Node;
            studentListHead->student.no = no;
            studentListHead->student.ID = ID;
            studentListHead->student.LastName = LastName;
            studentListHead->student.FirstName = FirstName;
            studentListHead->student.Gender = Gender;
            studentListHead->student.DateOfBirth = DateOfBirth;
            studentListHead->student.SocialID = SocialID;
            studentListHead->student.Password = Password;
            studentListHead->next = nullptr;
            pCur = studentListHead;
        }
        else
        {
            pCur->next = new Node;
            pCur = pCur->next;
            pCur->student.no = no;
            pCur->student.ID = ID;
            pCur->student.LastName = LastName;
            pCur->student.FirstName = FirstName;
            pCur->student.Gender = Gender;
            pCur->student.DateOfBirth = DateOfBirth;
            pCur->student.SocialID = SocialID;
            pCur->student.Password = Password;
            pCur->next = nullptr;
        }

        if (isStudentExist && !isFind)
        {
            isFind = true;
            student = pCur->student;
        }
    }
    input.close();
}

void StudentLoginSection()
{
    system("CLS");
    cout << "***-------------        Welcome to Student Login Section        --------------***" << endl;

    string username;
    string password;
    studentListHead = nullptr;
    student = newStudent; // the student who is logging in
    string classAddress;

    cout << "Enter Your Account: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    bool ok = findStudentWithID(username, classAddress, password);

    if (ok)
    {
        displayStudentInfo(classAddress);
    }
    else
    {
        int n;

        cout << "Your password is incorrect!!!" << endl;
        cout << endl;
        cout << "1. Enter username and password again" << endl;
        cout << "2. Back to the login section" << endl;
        cout << "Your option: ";
        cin >> n;
        if (n == 1)
        {
            StudentLoginSection();
        }
        else
        {
            loginSection();
        }
    }
}

void StaffMenu()
{
    int n;

    system("CLS");

    cout << "***------------------      Welcome to Academic Staff Menu    ----------------***" << endl;
    cout << "1. View personal information" << endl;
    cout << "2. View School year" << endl;
    cout << "3. Log out" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n == 1)
    {
        viewStaffPersonalInfo(staff, staffListHead);
    }
    else
    {
        if (n == 2)
        {
            viewSchoolYear();
        }
        else
        {
            loginSection();
        }
    }
}

void viewStaffPersonalInfo(Staff staff, StaffList *&pHead)
{
    int n;

    system("CLS");

    cout << "***------------------      Welcome to Academic Staff Personal Info    ----------------***" << endl;
    cout << "ID: " << staff.ID << endl;
    cout << "Fullname: " << staff.LastName << ' ' << staff.FirstName << endl;
    cout << "Gender: " << staff.Gender << endl;
    cout << "Password: " << staff.Password << endl;
    cout << endl;
    cout << "1. Change Password" << endl;
    cout << "2. Log out" << endl;
    cout << "3. Back to Staff Menu" << endl;
    cout << "Your Option: ";
    cin >> n;

    if (n == 1)
    {
        changeStaffPassword(staff, pHead);
    }
    else
    {
        if (n == 2)
        {
            loginSection();
        }
        else
        {
            StaffMenu();
        }
    }
}

void changeStaffPassword(Staff &staff, StaffList *&pHead)
{
    string newPass;
    cout << "New password: ";
    cin >> newPass;

    staff.Password = newPass;

    StaffList *pCur = pHead;
    while (pCur)
    {
        if (pCur->staff.ID == staff.ID)
        {
            pCur->staff.Password = staff.Password;
            break;
        }
        pCur = pCur->next;
    }

    writeChangesToStaffCSV(pHead);

    cout << "Your password has been updated. Click anything to see the changes...";
    getch();
    viewStaffPersonalInfo(staff, pHead);
}

void writeChangesToStaffCSV(StaffList *pHead)
{
    ofstream output;
    output.open("./inputs/Staff List.csv");
    output << "No ,ID,Lastname,Firstname,Gender,Email,Password" << endl;

    while (pHead)
    {

        output << pHead->staff.no << ',';
        output << pHead->staff.ID << ',';
        output << pHead->staff.LastName << ',';
        output << pHead->staff.FirstName << ',';
        output << pHead->staff.Gender << ',';
        output << pHead->staff.Email << ',';
        output << pHead->staff.Password << endl;

        pHead = pHead->next;
    }

    output.close();
}

void AcademicStaffLoginSection()
{
    system("CLS");
    cout << "***------------------      Welcome to Academic Staff Login Section     ----------------***" << endl;
    string username;
    string password;

    cout << "Enter Your Account: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    staffListHead = nullptr;
    staff = newStaff;
    ExtractStaffInfoAndTurnToSLL(staffListHead);

    if (validateStaff(username, password, staffListHead, staff))
    {
        cout << "Login successful!!!" << endl;
        cout << "Press any key to continue...";
        getch();
        StaffMenu();
    }
    else
    {
        int n;
        cout << "Login Unsuccessful!!! Please Try agian" << endl;
        cout << "1. Login again" << endl;
        cout << "2. Back to Homepage" << endl;
        cout << "Your option: ";
        cin >> n;

        if (n == 1)
        {
            AcademicStaffLoginSection();
        }
        else
        {
            loginSection();
        }
    }
}

bool validateStaff(string username, string password, StaffList *pHead, Staff &staff)
{

    while (pHead)
    {
        if (username == pHead->staff.ID && password == pHead->staff.Password)
        {
            staff = pHead->staff;
            return true;
        }
        pHead = pHead->next;
    }
    return false;
}

void ExtractStaffInfoAndTurnToSLL(StaffList *&pHead)
{
    ifstream input;
    input.open("./inputs/Staff List.csv");

    StaffList *pCur = pHead;

    string temp = "";
    getline(input, temp);

    while (!input.eof())
    {
        string no, ID, LastName, FirstName, Gender, Email, Password;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');

        getline(input, Gender, ',');
        getline(input, Email, ',');
        getline(input, Password);

        if (no == "")
            return;

        if (!pHead)
        {
            pHead = new StaffList;
            pHead->staff.no = no;
            pHead->staff.ID = ID;
            pHead->staff.LastName = LastName;
            pHead->staff.FirstName = FirstName;
            pHead->staff.Gender = Gender;
            pHead->staff.Email = Email;
            pHead->staff.Password = Password;
            pHead->next = nullptr;
            pCur = pHead;
        }
        else
        {
            pCur->next = new StaffList;
            pCur = pCur->next;
            pCur->staff.no = no;
            pCur->staff.ID = ID;
            pCur->staff.LastName = LastName;
            pCur->staff.FirstName = FirstName;
            pCur->staff.Gender = Gender;
            pCur->staff.Email = Email;
            pCur->staff.Password = Password;
            pCur->next = nullptr;
        }
    }

    input.close();
}

// coi nguon address
void viewSchoolYear()
{
    system("CLS");

    cout << "***------------------      Welcome to School Year section    ----------------***" << endl;
    // add school year to array to easy to access
    string schoolYears[1000];
    int num;
    int n;

    ListAllFileNames("School years", false, schoolYears, num);
    for (int i = 0; i < num; i++)
    {
        cout << i + 1 << ". " << schoolYears[i] << endl;
    }
    cout << endl;
    cout << num + 1 << ". Create new school year" << endl;
    cout << num + 2 << ". Back to Staff Menu" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n >= 1 && n <= num)
    {
        string address = "School years/" + schoolYears[n - 1];
        viewClassesInSchoolYear(address, schoolYears[n - 1]);
    }
    else
    {
        if (n == num + 1)
        {
            createNewSchoolYear();
        }
        else
        {
            StaffMenu();
        }
    }
}

void viewClassesInSchoolYear(string address, string schoolYear)
{
    system("CLS");

    cout << "***------------------   Classes in " << schoolYear << " ----------------***" << endl;
    string classNames[1000];
    int num;
    int n;

    ListAllFileNames("School years/" + schoolYear, true, classNames, num);
    for (int i = 0; i < num; i++)
    {
        cout << i + 1 << ". " << classNames[i] << endl;
    }
    cout << endl;

    cout << num + 1 << ". Back to the School Years" << endl;
    cout << num + 2 << ". Semesters" << endl;
    cout << num + 3 << ". Log out" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n >= 1 && n <= num)
    {
        viewStudentInClass("School years/" + schoolYear, classNames[n - 1], schoolYear);
    }
    else
    {
        if (n == num + 1)
        {
            viewSchoolYear();
        }
        else
        {
            if (n == num + 3)
            {
                loginSection();
            }
            else
            {
                viewSemesters(address, schoolYear);
            }
        }
    }
}

void viewSemesters(string address, string schoolYear)
{
    system("CLS");

    cout << "***------------------   Semesters in " << schoolYear << " ----------------***" << endl;

    string semesters[100];
    int num = 0;
    int n;

    ListAllFileNames("School years/" + schoolYear + "/Semesters", false, semesters, num);
    for (int i = 0; i < num; i++)
    {
        cout << i + 1 << ". " << semesters[i] << endl;
    }
    cout << endl;
    if (num >= 3)
    {
        cout << num + 1 << ". Back to School years " << endl;
        cout << num + 2 << ". Log out" << endl;
        cout << "Your option: ";
        cin >> n;
    }
    else
    {
        cout << num + 1 << ". Create new Semester" << endl;
        cout << num + 2 << ". Back to School years " << endl;
        cout << num + 3 << ". Log out" << endl;
        cout << "Your option: ";
        cin >> n;
    }

    if (n >= 1 && n <= num)
    {
        switch (n)
        {
        case 1:
            viewCourse("School years/" + schoolYear + +"/Semesters/1", schoolYear, "1");
            break;
        case 2:
            viewCourse("School years/" + schoolYear + +"/Semesters/2", schoolYear, "2");
            break;
        case 3:
            viewCourse("School years/" + schoolYear + +"/Semesters/3", schoolYear, "3");
            break;
        }
    }
    else
    {
        if (num >= 3)
        {
            if (n == num + 1)
            {
                viewSchoolYear();
            }
            else
            {
                loginSection();
            }
        }
        else
        {
            if (n == num + 1)
            {
                CreateSemester(address, schoolYear);
            }
            else
            {
                if (n == num + 2)
                {
                    viewSchoolYear();
                }
                else
                {
                    loginSection();
                }
            }
        }
    }
}

void viewCourse(string address, string schoolYear, string term)
{
    system("CLS");
    string fullTerm = "";
    if (term == "1")
    {
        fullTerm = "First Term";
    }
    else if (term == "2")
    {
        fullTerm = "Second Term";
    }
    else
    {
        fullTerm = "Third Term";
    }
    cout << "***------------------   Courses in " << fullTerm << " of " << schoolYear << " ----------------***" << endl;
    string nameCourses[100];
    int num = 0;
    int n;

    ListAllFileNames("School years/" + schoolYear + "/Semesters/" + term, false, nameCourses, num);

    for (int i = 0; i < num; i++)
    {
        cout << i + 1 << ". " << nameCourses[i] << endl;
    }
    cout << endl;

    cout << num + 1 << ". Create new Course" << endl; // write another csv file for info.
    cout << num + 2 << ". Back to the semesters section" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n >= 1 && n <= num)
    {
        viewCourseInfo(address, schoolYear, term, nameCourses[n - 1]);
    }
    else
    {
        if (n == num + 1)
        {
            createNewCourse(address, schoolYear, term);
        }
        else
        {
            viewSemesters("School years/" + schoolYear, schoolYear);
        }
    }
}

void viewCourseInfo(string address, string schoolYear, string term, string nameCourse)
{
    // open specific file with path

    cout << address;
    ifstream input;
    input.open("./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + nameCourse + "/Course Info.csv");

    Course course;
    string temp = "";
    cin.ignore();
    getline(input, temp, ',');
    getline(input, course.id);
    getline(input, temp, ',');
    getline(input, course.name);
    getline(input, temp, ',');
    getline(input, course.teacherName);
    getline(input, temp, ',');
    getline(input, course.numberOfCredits);
    getline(input, temp, ',');
    getline(input, course.max);
    getline(input, temp, ',');
    getline(input, course.s1Time);
    getline(input, temp, ',');
    getline(input, course.s1Date);
    getline(input, temp, ',');
    getline(input, course.s2Time);
    getline(input, temp, ',');
    getline(input, course.s2Date);
    getline(input, temp, ',');
    getline(input, temp, ',');
    TurnDate(temp, course.startDate.year, course.startDate.month, course.startDate.day);
    getline(input, temp);
    TurnDate(temp, course.endDate.year, course.endDate.month, course.endDate.day);
    input.close();

    system("CLS");
    int n;
    // cout << ".\\inputs\\" + address + "\\" + nameCourse + "\\Course Info " << endl;
    cout << "***------------------   " + nameCourse + " Course Info ----------------***" << endl;
    cout << "Course Registration Date: " << course.startDate.day << "/" << course.startDate.month << "/" << course.startDate.year << " - " << course.endDate.day << "/" << course.endDate.month << "/" << course.endDate.year << endl;
    cout << endl;
    cout << "ID: " << course.id << endl;
    cout << "Name: " << course.name << endl;
    cout << "Teacher name: " << course.teacherName << endl;
    cout << "Number of Credits: " << course.numberOfCredits << endl;
    cout << "Max student in this course: " << course.max << endl;
    cout << "Session 1: " << endl;
    cout << "Time: " << getTime(course.s1Time) << endl;
    cout << "Day: " << getDay(course.s1Date) << endl;
    cout << "Session 2: " << endl;
    cout << "Time: " << getTime(course.s2Time) << endl;
    cout << "Day: " << getDay(course.s2Date) << endl;
    cout << endl;

    cout << "1. Update Course" << endl;
    cout << "2. Delete Course" << endl;
    cout << "3. Back to the view Course section" << endl;
    cout << "Your option: ";
    cin >> n;

    string url = "";
    string file1, file2;
    switch (n)
    {
    case 1:
        updateCourse(course, address, schoolYear, term, nameCourse);
    case 2:
        url = "./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + nameCourse;

        file1 = url + "/Course Info.csv";
        file2 = url + "/Student Score Board.csv";
        cout << file1 << ' ' << file2 << endl;
        DeleteFile(file1);

        DeleteFile(file2);

        DeleteFolder(url);

        viewCourse(address, schoolYear, term);
    case 3:
        viewCourse(address, schoolYear, term);
    }
    // update course
    // delete course
    // back to the view course
}

void updateCourse(Course &course, string address, string schoolYear, string term, string nameCourse)
{

    string isFinish = "";

    while (isFinish != "NO")
    {
        int n;
        system("CLS");
        cout << "***------------------   Update Course  ----------------***" << endl;
        cout << "1. Course Registration Date: " << course.startDate.day << "/" << course.startDate.month << "/" << course.startDate.year << " - " << course.endDate.day << "/" << course.endDate.month << "/" << course.endDate.year << endl;
        cout << endl;
        cout << "2. ID: " << course.id << endl;
        cout << "3. Name: " << course.name << endl;
        cout << "4. Teacher name: " << course.teacherName << endl;
        cout << "5. Number of Credits: " << course.numberOfCredits << endl;
        cout << "6. Max student in this course: " << course.max << endl;
        cout << "Session 1: " << endl;
        cout << "7. Time: " << getTime(course.s1Time) << endl;
        cout << "8. Day: " << getDay(course.s1Date) << endl;
        cout << "Session 2: " << endl;
        cout << "9. Time: " << getTime(course.s2Time) << endl;
        cout << "10. Day: " << getDay(course.s2Date) << endl;
        cout << endl;
        cout << "Your option: ";
        cin >> n;

        string oldname;
        string path, newPath;
        bool tmp;
        switch (n)
        {
        case 1:
            int d, m, y;
            cout << endl;
            cout << "Registration Date: " << endl;
            cout << "Start date: " << endl;
            cout << "Day: ";
            cin >> d;
            cout << "Month: ";
            cin >> m;
            cout << "Year: ";
            cin >> y;

            while (!checkdate(d, m, y))
            {
                cout << "Your input is invalid. Please type again!!!" << endl;
                cout << "Day: ";
                cin >> d;
                cout << "Month: ";
                cin >> m;
                cout << "Year: ";
                cin >> y;
                cout << endl;
            }

            course.startDate.day = d;
            course.startDate.month = m;
            course.startDate.year = y;
            cout << "End date: " << endl;
            cout << "Day: ";
            cin >> d;
            cout << "Month: ";
            cin >> m;
            cout << "Year: ";
            cin >> y;
            while (!checkdate(d, m, y))
            {
                cout << "Your input is invalid. Please type again!!!" << endl;
                cout << "Day: ";
                cin >> d;
                cout << "Month: ";
                cin >> m;
                cout << "Year: ";
                cin >> y;
                cout << endl;
            }

            course.endDate.day = d;
            course.endDate.month = m;
            course.endDate.year = y;
            break;
        case 2:
            cout << endl;
            cout << "Course ID: ";
            cin >> course.id;
            break;
        case 3:
        {
            oldname = course.name;
            cout << endl;
            cout << "Course name: ";
            cin.ignore();
            getline(cin, course.name);

            // change directory name too.
            // if (term == "First Term")
            // {
            //     path = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\1\\" + oldname;
            //     newPath = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\1\\" + course.name;
            // }
            // else
            // {
            //     if (term == "Second Term")
            //     {
            //         path = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\2\\" + oldname;
            //         newPath = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\2\\" + course.name;
            //     }
            //     else
            //     {
            //         path = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\3\\" + oldname;
            //         newPath = ".\\inputs\\School years\\" + schoolYear + "\\Semesters\\3\\" + course.name;
            //     }
            // }

            // path = ".\\inputs\\" + address.c_str() + oldname.c_str();
            path = "./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + oldname;
            newPath = "./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + course.name;
            char p[path.length() + 1];
            char p1[newPath.length() + 1];

            strcpy(p, path.c_str());
            strcpy(p1, newPath.c_str());
            // cout << p << endl;
            // cout << p1 << endl;
            //  newPath = ".\\inputs\\" + address.c_str() + course.name.c_str();
            if (rename(p, p1) != 0)
                perror("Error renaming file");
            else
                cout << "Course renamed successfully";
            break;
        }
        case 4:
            cout << endl;
            cout << "Course teacher name: ";
            cin.ignore();
            getline(cin, course.teacherName);
            break;
        case 5:
            cout << endl;
            cout << "Number of Credits: ";
            cin >> course.numberOfCredits;
            break;

        case 6:
            cout << endl;
            cout << "6. Max student in this course: ";
            cin >> course.max;
            break;
        case 7:
            cout << endl;
            cout << "Time(S1,S2,S3,S4): ";
            cin >> course.s1Time;
            while (!checkTime(course.s1Time))
            {
                cout << "Your input is invalid. Please type again, example: S1" << endl;
                cout << "Your input : ";
                cin >> course.s1Time;

                cout << endl;
            }
            break;
        case 8:
            cout << endl;
            cout << "Date(MON/TUE/WED...): ";
            cin >> course.s1Date;
            while (!checkDay(course.s1Date))
            {
                cout << "Your input is invalid. Please type again, example: MON." << endl;
                cout << "Your input: ";
                cin >> course.s1Date;
                cout << endl;
            }
            break;

        case 9:
            cout << endl;
            cout << "Time(S1,S2,S3,S4): ";
            cin >> course.s2Time;
            while (!checkTime(course.s2Time))
            {
                cout << "Your input is invalid. Please type again, example: S1" << endl;
                cout << "Your input : ";
                cin >> course.s2Time;

                cout << endl;
            }
            break;
        case 10:
            cout << endl;
            cout << "Date(MON/TUE/WED...): ";
            cin >> course.s2Date;
            while (!checkDay(course.s2Date))
            {
                cout << "Your input is invalid. Please type again, example: MON." << endl;
                cout << "Your input: ";
                cin >> course.s2Date;
                cout << endl;
            }
            break;
        }

        cout << endl;
        cout << "Do you want to continue?(YES/NO): ";
        cin >> isFinish;
    }

    // write new course info to csv file
    string path = ".\\inputs\\" + address + "\\" + course.name + "\\Course Info.csv";
    // cout << path << endl;
    writeCourseToFile(path, course);

    cout << "Successfully updated!!! type anything to continue";
    getch();
    viewCourseInfo(address, schoolYear, term, course.name);
}

string getTime(string time)
{

    if (time == "S1")
        return "7:30";
    if (time == "S2")
        return "9:30";
    if (time == "S3")
        return "13:30";
    if (time == "S4")
        return "15:30";
    return "";
}
string getDay(string day)
{
    if (day == "MON")
        return "Monday";
    if (day == "TUE")
        return "Tuesday";
    if (day == "WED")
        return "Wednesday";
    if (day == "THU")
        return "Thursday";
    if (day == "FRI")
        return "Friday";
    if (day == "SAT")
        return "Saturday";
    return "";
}

int turnToInt(char c)
{
    return (int)c - 48;
}

void TurnDate(string date, int &y, int &m, int &d)
{
    int count = 1;
    int dem = 0;
    int tmp = 0;

    for (int i = date.length() - 1; i >= 0; i--)
    {
        if (date[i] == '/')
        {

            if (dem == 0)
            {
                y = tmp;
            }
            else
            {
                if (dem == 1)
                {
                    m = tmp;
                }
                else
                {
                    d = tmp;
                }
            }
            dem++;
            tmp = 0;
            count = 1;
            continue;
        }
        tmp += count * turnToInt(date[i]);

        count *= 10;
    }
    d = tmp;
}

void createNewCourse(string address, string schoolYear, string term)
{
    // create new folder with a new of a course
    // user input course info, we write in in course info.csv file
    // create student score file csv then write title first and
    Course newCourse;
    int d, m, y;
    system("CLS");

    cout << "***------------------  Create new course ----------------***" << endl;

    cout << "Registration Date: " << endl;
    cout << "Start date: " << endl;
    cout << "Day: ";
    cin >> d;
    cout << "Month: ";
    cin >> m;
    cout << "Year: ";
    cin >> y;

    while (!checkdate(d, m, y))
    {
        cout << "Your input is invalid. Please type again!!!" << endl;
        cout << "Day: ";
        cin >> d;
        cout << "Month: ";
        cin >> m;
        cout << "Year: ";
        cin >> y;
        cout << endl;
    }

    newCourse.startDate.day = d;
    newCourse.startDate.month = m;
    newCourse.startDate.year = y;
    cout << "End date: " << endl;
    cout << "Day: ";
    cin >> d;
    cout << "Month: ";
    cin >> m;
    cout << "Year: ";
    cin >> y;
    while (!checkdate(d, m, y))
    {
        cout << "Your input is invalid. Please type again!!!" << endl;
        cout << "Day: ";
        cin >> d;
        cout << "Month: ";
        cin >> m;
        cout << "Year: ";
        cin >> y;
        cout << endl;
    }

    newCourse.endDate.day = d;
    newCourse.endDate.month = m;
    newCourse.endDate.year = y;

    cout << endl;
    cout << "Course ID: ";
    cin >> newCourse.id;
    cout << "Course name: ";
    cin.ignore();
    getline(cin, newCourse.name);
    cout << "Course teacher name: ";

    getline(cin, newCourse.teacherName);
    cout << "Number of Credits: ";

    cin >> newCourse.numberOfCredits;
    cout << "Max student in a course: ";
    cin >> newCourse.max;

    cout << "Session 1: " << endl;
    cout << "Date(MON/TUE/WED...): ";
    cin >> newCourse.s1Date;
    while (!checkDay(newCourse.s1Date))
    {
        cout << "Your input is invalid. Please type again, example: MON." << endl;
        cout << "Your input: ";
        cin >> newCourse.s1Date;
        cout << endl;
    }
    cout << "Time(S1,S2,S3,S4): ";
    cin >> newCourse.s1Time;
    while (!checkTime(newCourse.s1Time))
    {
        cout << "Your input is invalid. Please type again, example: S1" << endl;
        cout << "Your input : ";
        cin >> newCourse.s1Time;

        cout << endl;
    }
    cout << "Session 2: " << endl;
    cout << "Date(MON/TUE/WED...): ";
    cin >> newCourse.s2Date;
    while (!checkDay(newCourse.s2Date))
    {
        cout << "Your input is invalid. Please type again, example: MON." << endl;
        cout << "Your input: ";
        cin >> newCourse.s2Date;
        cout << endl;
    }
    cout << "Time(S1,S2,S3,S4): ";
    cin >> newCourse.s2Time;
    while (!checkTime(newCourse.s2Time))
    {
        cout << "Your input is invalid. Please type again, example: S1" << endl;
        cout << "Your input : ";
        cin >> newCourse.s2Time;

        cout << endl;
    }
    createNewDirectory("./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + newCourse.name);

    string path = "./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + newCourse.name + "/Course Info.csv";
    writeCourseToFile(path, newCourse);

    path = "./inputs/School years/" + schoolYear + "/Semesters/" + term + "/" + newCourse.name + "/Student Score Board.csv";
    ofstream file1(path);

    file1 << "No,Student ID,Lastname,Firstname, Homework, Midterm Mark, Final Mark, TotalMark" << endl;
    file1.close();
    cout << endl;
    cout << "Please check the info again and hit any key to continue...";
    getch();

    viewCourse(address, schoolYear, term);
}

void writeCourseToFile(string path, Course newCourse)
{
    ofstream file(path);
    // write title in csv fileName
    file << "ID"
         << "," << newCourse.id << endl;
    file << "Name"
         << "," << newCourse.name << endl;
    file << "Teacher Name"
         << "," << newCourse.teacherName << endl;
    file << "Number of Credits"
         << "," << newCourse.numberOfCredits << endl;
    file << "Max"
         << "," << newCourse.max << endl;
    file << "S1 time"
         << "," << newCourse.s1Time << endl;
    file << "S1 date"
         << "," << newCourse.s1Date << endl;
    file << "S2 time"
         << "," << newCourse.s2Time << endl;
    file << "S2 date"
         << "," << newCourse.s2Date << endl;
    file << "Registration Date"
         << "," << newCourse.startDate.day << "/" << newCourse.startDate.month << "/" << newCourse.startDate.year << "," << newCourse.endDate.day << "/" << newCourse.endDate.month << "/" << newCourse.endDate.year << endl;

    file.close();
}

bool checkDay(string day)
{
    if (day == "MON" || day == "TUE" || day == "WED" || day == "THU" || day == "FRI" || day == "SAT")
        return true;
    return false;
}

bool checkTime(string time)
{
    if (time == "S1" || time == "S2" || time == "S3" || time == "S4")
        return true;
    return false;
}

bool checkdate(int m, int d, int y)
{
    if (!(1 <= m && m <= 12))
        return false;
    if (!(1 <= d && d <= 31))
        return false;
    if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
        return false;
    if ((d == 30) && (m == 2))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 != 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 400 == 0))
        return true;
    if ((m == 2) && (d == 29) && (y % 100 == 0))
        return false;
    if ((m == 2) && (d == 29) && (y % 4 == 0))
        return true;

    return true;
}

void viewStudentInClass(string address, string className, string schoolYear)
{
    system("CLS");

    cout << "***------------------   Students in " << className << " ----------------***" << endl;

    Node *pHead = nullptr;
    int n;
    ExtractStudentInClass(pHead, schoolYear, className);
    printElement("ID", 10);
    printElement("FullName", 20);
    printElement("Gender", 8);
    printElement("Date Of Birth", 15);
    printElement("Social ID", 8);
    cout << endl;
    while (pHead)
    {
        printElement(pHead->student.ID, 10);
        printElement(pHead->student.LastName + " " + pHead->student.FirstName, 20);
        printElement(pHead->student.Gender, 8);
        printElement(pHead->student.DateOfBirth, 15);
        printElement(pHead->student.SocialID, 8);
        cout << endl;
        pHead = pHead->next;
    }
    cout << endl;
    cout << "1. Back to the Class List" << endl;
    cout << "2. Log out" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n == 1)
    {
        viewClassesInSchoolYear(address, schoolYear);
    }
    else
    {
        loginSection();
    }
}

void ExtractStudentInClass(Node *&pHead, string schoolYear, string className)
{
    string url = ".\\inputs\\School years\\" + schoolYear + "\\" + className + ".csv";

    ifstream input;
    input.open(url);
    string temp;
    getline(input, temp); // ignore the first row of the sheet(title row)

    Node *pCur = pHead;

    while (!input.eof())
    {
        string no, ID, LastName, FirstName, Gender, DateOfBirth, SocialID, Password;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');
        getline(input, Gender, ',');
        getline(input, DateOfBirth, ',');
        getline(input, SocialID, ',');
        getline(input, Password);

        if (no == "")
            return;

        if (!pHead)
        {
            pHead = new Node;
            pHead->student.no = no;
            pHead->student.ID = ID;
            pHead->student.LastName = LastName;
            pHead->student.FirstName = FirstName;
            pHead->student.Gender = Gender;
            pHead->student.DateOfBirth = DateOfBirth;
            pHead->student.SocialID = SocialID;
            pHead->student.Password = Password;

            pHead->next = nullptr;
            pCur = pHead;
        }
        else
        {
            pCur->next = new Node;
            pCur = pCur->next;
            pCur->student.no = no;
            pCur->student.ID = ID;
            pCur->student.LastName = LastName;
            pCur->student.FirstName = FirstName;
            pCur->student.Gender = Gender;
            pCur->student.DateOfBirth = DateOfBirth;
            pCur->student.SocialID = SocialID;
            pCur->student.Password = Password;
            pCur->next = nullptr;
        }
    }
    input.close();
}

// need to fix

void displayStudentInfo(string classAddress)
{
    system("CLS");
    int n;

    cout << "No: " << student.no << endl;
    cout << "ID: " << student.ID << endl;
    cout << "Fullname: " << student.LastName << ' ' << student.FirstName << ' ' << endl;
    cout << "Date Of Birth: " << student.DateOfBirth << endl;
    cout << "Gender: " << student.Gender << endl;
    cout << "Social ID: " << student.SocialID << endl;
    cout << "--------------------------------------------------------------------" << endl;

    cout << "Username: " << student.ID << endl;
    cout << "Password: " << student.Password << endl;

    cout << endl;
    cout << "1. Log out" << endl;
    cout << "2. Change Password" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n == 1)
    {
        loginSection();
    }
    else
    {
        changePassword();
        updatePasswordChangeToCSVFile(classAddress);
        cout << "Successfully Updated!!!" << endl;
        cout << "Hit any key to see the change.";
        getch(); // hit any key and then execute then below function
        displayStudentInfo(classAddress);
    }
    // change password option.
    // log out option
}

void changePassword()
{
    string newPass;
    cout << "Your new Password: ";
    cin >> newPass;
    student.Password = newPass;
}

void updatePasswordChangeToCSVFile(string classAddress)
{

    Node *pCur = studentListHead;
    while (pCur)
    {
        if (pCur->student.ID == student.ID)
        {
            pCur->student.Password = student.Password;
        }
        pCur = pCur->next;
    }

    // while (pCur->next)
    // {

    //     pCur = pCur->next;
    // }

    // delete pCur->next;
    // pCur->next = nullptr;
    writeCSVFile(classAddress);
}

void writeCSVFile(string classAddress)
{
    ofstream output;
    classAddress = ".\\inputs\\" + classAddress;
    cout << classAddress << endl;
    output.open(classAddress);
    output << "No ,ID,Lastname,Firstname,Gender,Date Of Birth,Social ID,Password" << endl;

    Node *pCur = studentListHead;
    while (pCur)
    {
        output << pCur->student.no << ',';
        output << pCur->student.ID << ',';
        output << pCur->student.LastName << ',';
        output << pCur->student.FirstName << ',';
        output << pCur->student.Gender << ',';
        output << pCur->student.DateOfBirth << ',';
        output << pCur->student.SocialID << ',';
        output << pCur->student.Password << endl;
        pCur = pCur->next;
    }

    output.close();
}

void createNewSchoolYear()
{
    string s;
    cout << endl;
    cout << "Create new school year(Year1 - Year2):" << endl;
    cin.ignore();
    getline(cin, s);

    createNewDirectory("./inputs/School years/" + s);
    cout << "Create successfully..." << endl;
    getch();
    viewSchoolYear();
}

void CreateSemester(string address, string schoolYear)
{
    struct stat dst, dst2;
    string s1, s2, st, ed;
    cout << "Your new semester: ";
    //cin.ignore();
    getline(cin, s1);

    cout << "School year to create(Year1 - Year2): ";
    getline(cin, s2);

    string url = "./inputs/School years/" + s2 + "/Semesters/" + s1;

    // createNewDirectory(url.c_str());
    if (stat(url.c_str(), &dst) == 0)
    {
        cout << "Semester existed, please try again \n";
        CreateSemester(address, schoolYear);
    }
    else
    {
        string url2 = "./inputs/School years/" + s2 + "/Semesters/";
        if (stat(url2.c_str(), &dst2) != 0)
        {
            mkdir(url2.c_str());
            url2 += s1;
            mkdir(url2.c_str());
        }
        else {
            mkdir(url.c_str());
        }
        cout << "Semester has been created. \n";
    }
    cout << "Create successfully..." << endl;
    getch();
    viewSemesters(address, schoolYear);
}

void openCSVFileFromUserInput()
{
    string fileName = "./inputs/";
    string name;
    ifstream input;
    cout << "Your file name: ";
    getline(cin, name);
    fileName += name;
    input.open(fileName.c_str());
    if (input.fail())
    {
        cout << "Your file name is invalid" << endl;
        return;
    }

    while (input.good())
    {
        string line = "";
        getline(input, line);
        cout
            << line << endl
            << endl;
    }

    input.close();
}

void createNewDirectory(string url)
{

    // string url = "./inputs/School years/";

    mkdir(url.c_str());
}

string removeType(string s)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
            break;
        ans += s[i];
    }
    return ans;
}

void ListAllFileNames(string address, bool isFile, string arr[], int &num)
{

    // libraries:  sys\stat.h, dirent.h, conio.h
    struct dirent *d;
    struct stat dst;

    DIR *dr;

    string path = ".\\inputs\\" + address + "\\";

    dr = opendir(path.c_str());

    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            string type = d->d_name;
            type = path + type;
            if (stat(type.c_str(), &dst) == 0)
            {
                if (isFile)
                {
                    if (dst.st_mode & S_IFREG)
                    {
                        string name = removeType(d->d_name);
                        // cout << name << endl;
                        arr[num] = name;
                        num++;
                    }
                }
                else
                {
                    if (dst.st_mode & S_IFDIR)
                    {
                        string name = removeType(d->d_name);
                        if (name != "")
                        {
                            // cout << name << endl;
                            arr[num] = name;
                            num++;
                        }
                    }
                }
            }
        }
        closedir(dr);
    }
}

template <typename T>
void printElement(T t, const int &width)
{
    cout << left << setw(width) << setfill(' ') << t;
}

// fix later
void DeleteFile(string path)
{

    while (remove(path.c_str()) != 0)
    {
        perror("Error deleting file: ");
        cout << endl;
    }
    cout << "Successfully deleted..." << endl;
    getch();
}

void DeleteFolder(string path)
{

    while (rmdir(path.c_str()) != 0)
    {
        perror("Error deleting folder: ");
        cout << endl;
    }
    cout << "Successfully deleted..." << endl;
    getch();
}