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

void AcademicStaffLoginSection()
{
    system("CLS");
    cout << "***------------------      Welcome to Academic Staff Login Section     ----------------***" << endl;
}

void ExtractStudentInfoFromCSVFileAndTurnToSLL(Node *&pHead)
{
    ifstream input;
    input.open("./inputs/Students List.csv");
    string temp;
    getline(input, temp); // ignore the first row of the sheet(title row)

    Node *pCur = pHead;

    while (input.good())
    {
        string no, ID, LastName, FirstName, Username, Password, Gender, Email, Class;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');
        getline(input, Username, ',');
        getline(input, Password, ',');
        getline(input, Gender, ',');
        getline(input, Email, ',');
        getline(input, Class);

        if (!pHead)
        {
            pHead = new Node;
            pHead->student.no = no;
            pHead->student.ID = ID;
            pHead->student.LastName = LastName;
            pHead->student.FirstName = FirstName;
            pHead->student.Username = Username;
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
            pCur->student.ID = ID;
            pCur->student.LastName = LastName;
            pCur->student.FirstName = FirstName;
            pCur->student.Username = Username;
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
    while (pHead)
    {
        if (pHead->student.Username == username && pHead->student.Password == password)
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

    cout << "Username: " << curStudent.Username << endl;
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
        getch(); //hit any key and then execute then below function
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
            break;
        }
        pCur = pCur->next;
    }

    writeCSVFile(pStudentSLL);
}

void writeCSVFile(Node *pStudentSLL)
{
    ofstream output;
    output.open("./inputs/Students List.csv");
    output << "No ,ID,Last name,Full name,Username,Password,Gender,Email,class" << endl;

    while (pStudentSLL)
    {
        output << pStudentSLL->student.no << ',';
        output << pStudentSLL->student.ID << ',';
        output << pStudentSLL->student.LastName << ',';
        output << pStudentSLL->student.FirstName << ',';
        output << pStudentSLL->student.Username << ',';
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
