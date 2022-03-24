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
        string address = "School years\\" + schoolYears[n - 1];
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

    ListAllFileNames(address, true, classNames, num);
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
        viewStudentInClass(address, classNames[n - 1], schoolYear);
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

    ListAllFileNames(address + "/Semesters", false, semesters, num);
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
            viewCourse(address + "/Semesters/1", schoolYear, "First Term");
            break;
        case 2:
            viewCourse(address + "/Semesters/2", schoolYear, "Second Term");
            break;
        case 3:
            viewCourse(address + "/Semesters/3", schoolYear, "Third Term");
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
    cout << "***------------------   Courses in " << term << " of " << schoolYear << " ----------------***" << endl;
    string nameCourses[100];
    int num = 0;
    int n;

    ListAllFileNames(address, false, nameCourses, num);

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
    input.open(".\\inputs\\" + address + "\\" + nameCourse + "\\Course Info.csv");

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

    system("CLS");
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

    // update course
    // delete course
    // back to the view course
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
    cin >> newCourse.name;
    cout << "Course teacher name: ";
    cin.ignore();
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
    createNewDirectory(".\\inputs\\" + address + "\\" + newCourse.name);

    string path = ".\\inputs\\" + address + "\\" + newCourse.name + "\\Course Info.csv";
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
    path = ".\\inputs\\" + address + "\\" + newCourse.name + "\\Student Score Board.csv";
    ofstream file1(path);

    file1 << "No,Student ID,Lastname,Firstname, Homework, Midterm Mark, Final Mark, TotalMark" << endl;

    cout << endl;
    cout << "Please check the info again and hit any key to continue...";
    getch();

    viewCourse(address, schoolYear, term);
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
    cin.ignore();
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
        if (stat(url.c_str(), &dst2) != 0)
        {
            mkdir(url2.c_str());
        }
        mkdir(url.c_str());
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
