#include "functions.h"

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
        Node *pStudentSLL = nullptr;
        ExtractStudentInfoFromCSVFileAndTurnToSLL(pStudentSLL);
        StudentLoginSection(pStudentSLL);
        delete[] pStudentSLL;
    }
    else if (n == 2)
    {
        AcademicStaffLoginSection();
    }
    else
    {
        cout << "Have a nice day ^-^ ";
    }
}

void StudentLoginSection(Node *pStudentSLL)
{
    system("CLS");
    cout << "***-------------        Welcome to Student Login Section        --------------***" << endl;

    Student curStudent; // the student who is logging in
    string username;
    string password;

    cout << "Enter Your Account: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    bool ok = validateUser(username, password, pStudentSLL, curStudent);

    if (ok)
    {
        displayStudentInfo(curStudent, pStudentSLL);
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
            StudentLoginSection(pStudentSLL);
        }
        else
        {
            loginSection();
        }
    }
}

void StaffMenu(Staff staff, StaffList *&pHead)
{
    int n;

    system("CLS");

    cout << "***------------------      Welcome to Academic Staff Menu    ----------------***" << endl;
    cout << "1. View personal information" << endl;
    cout << "2. Create new School year" << endl;
    cout << "3. Log out" << endl;
    cout << "Your option: ";
    cin >> n;

    if (n == 1)
    {
        viewStaffPersonalInfo(staff, pHead);
    }
    else
    {
        if (n == 2)
        {
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
            StaffMenu(staff, pHead);
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

    StaffList *pHead = nullptr;
    Staff staff;
    ExtractStaffInfoAndTurnToSLL(pHead);

    if (validateStaff(username, password, pHead, staff))
    {
        cout << "Login successful!!!" << endl;
        cout << "Press any key to continue...";
        getch();
        StaffMenu(staff, pHead);
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

void ExtractStudentInfoFromCSVFileAndTurnToSLL(Node *&pHead)
{
    ifstream input;
    input.open("./inputs/Students List.csv");
    string temp;
    getline(input, temp); // ignore the first row of the sheet(title row)

    Node *pCur = pHead;

    while (!input.eof())
    {
        string no, ID, LastName, FirstName, Password, Gender, Email, Class;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');

        getline(input, Password, ',');
        getline(input, Gender, ',');
        getline(input, Email, ',');
        getline(input, Class);

        if (no == "")
            return;

        if (!pHead)
        {
            pHead = new Node;
            pHead->student.no = no;
            pHead->student.ID = ID;
            pHead->student.LastName = LastName;
            pHead->student.FirstName = FirstName;

            pHead->student.Password = Password;
            pHead->student.Gender = Gender;
            pHead->student.Email = Email;
            pHead->student.Class = Class;
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

            pCur->student.Password = Password;
            pCur->student.Gender = Gender;
            pCur->student.Email = Email;
            pCur->student.Class = Class;
            pCur->next = nullptr;
        }
    }
}

bool validateUser(string username, string password, Node *pHead, Student &curStudent)
{
    // send list of user in here and take the username and password of each node
    while (pHead)
    {
        if (pHead->student.ID == username && pHead->student.Password == password)
        {
            curStudent = pHead->student;
            return true;
        }
        pHead = pHead->next;
    }
    return false;
}

void displayStudentInfo(Student curStudent, Node *pStudentSLL)
{
    system("CLS");
    int n;

    cout << "No: " << curStudent.no << endl;
    cout << "ID: " << curStudent.ID << endl;
    cout << "Full name: " << curStudent.LastName << ' ' << curStudent.FirstName << ' ' << endl;
    cout << "Class: " << curStudent.Class << ' ' << endl;
    cout << "--------------------------------------------------------------------" << endl;

    cout << "Username: " << curStudent.ID << endl;
    cout << "Password: " << curStudent.Password << endl;

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
        changePassword(curStudent);
        updatePasswordChangeToCSVFile(curStudent, pStudentSLL);
        cout << "Successfully Updated!!!" << endl;
        cout << "Hit any key to see the change.";
        getch(); // hit any key and then execute then below function
        displayStudentInfo(curStudent, pStudentSLL);
    }
    // change password option.
    // log out option
}

void changePassword(Student &curStudent)
{
    string newPass;
    cout << "Your new Password: ";
    cin >> newPass;
    curStudent.Password = newPass;
}

void updatePasswordChangeToCSVFile(Student curStudent, Node *&pStudentSLL)
{

    Node *pCur = pStudentSLL;
    while (pCur)
    {
        if (pCur->student.ID == curStudent.ID)
        {
            pCur->student.Password = curStudent.Password;
        }
        pCur = pCur->next;
    }

    // while (pCur->next)
    // {

    //     pCur = pCur->next;
    // }

    // delete pCur->next;
    // pCur->next = nullptr;
    writeCSVFile(pStudentSLL);
}

void writeCSVFile(Node *pStudentSLL)
{
    ofstream output;
    output.open("./inputs/Students List.csv");
    output << "No ,ID,Lastname,Firstname,Password,Gender,Email,class" << endl;

    while (pStudentSLL)
    {

        output << pStudentSLL->student.no << ',';
        output << pStudentSLL->student.ID << ',';
        output << pStudentSLL->student.LastName << ',';
        output << pStudentSLL->student.FirstName << ',';

        output << pStudentSLL->student.Password << ',';
        output << pStudentSLL->student.Gender << ',';
        output << pStudentSLL->student.Email << ',';
        output << pStudentSLL->student.Class << endl;
        pStudentSLL = pStudentSLL->next;
    }

    output.close();
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

void createNewDirectory()
{
    string s;
    cout << "Your new File name: ";
    getline(cin, s);
    string url = "./inputs/School years/";
    url += s;
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

void ListAllFileNames(string address, bool isFile)
{

    // libraries:  sys\stat.h, dirent.h, conio.h
    struct dirent *d;
    struct stat dst;

    DIR *dr;

    string path = ".\\inputs\\School years\\" + address + "\\";

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
                        cout << name << endl;
                    }
                }
                else
                {
                    if (dst.st_mode & S_IFDIR)
                    {
                        string name = removeType(d->d_name);
                        if (name != "")
                            cout << name << endl;
                    }
                }
            }
        }
        closedir(dr);
    }
}

void CreateSemester() 
{
    struct stat dst;
    string s1, s2;
    cout << "Your new semester: ";
    getline(cin, s1);
    cout << "School year to create: ";
    getline (cin , s2);
    string url = "./inputs/School years/" + s2 + "/" + s1 + "/";
    if (stat(url.c_str(), &dst) == 0)
    {
        cout << "Semester existed, please try again \n";
        CreateSemester();
    }
    else 
    {
        mkdir(url.c_str());
        cout << "Semester has been created. \n";
    }
}

void inputCourse() {}