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

bool findStudentWithID(string ID, Student &student, Node *&pHead, string &classAddress, string password)
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

            pHead = nullptr;
            classAddress = address + "\\" + className + ".csv";
            // cout << classAddress << endl;
            findStudentInAClass(pHead, ID, classAddress, isStudentExist, student, password);

            if (isStudentExist)
            {

                return true;
            }
        }
    }

    return false;

    // return the info of that student, and the address of that class, and SLL of that class
}

void findStudentInAClass(Node *&pHead, string curID, string address, bool &isStudentExist, Student &student, string password)
{
    bool isFind = false;
    ifstream input;
    address = ".\\inputs\\" + address;
    input.open(address);

    Node *pCur = pHead;

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

    bool ok = findStudentWithID(username, student, studentListHead, classAddress, password);

    if (ok)
    {
        displayStudentInfo(student, studentListHead, classAddress);
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
    cout << num + 2 << ". Log out" << endl;
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
            loginSection();
        }
    }
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
void ExtractStudentInfoFromCSVFileAndTurnToSLL(Node *&pHead)
{
    ifstream input;
    input.open("./inputs/Students List.csv");
    string temp;
    getline(input, temp); // ignore the first row of the sheet(title row)

    Node *pCur = pHead;

    while (!input.eof())
    {
        string no, ID, LastName, FirstName, Password, Gender;
        getline(input, no, ',');
        getline(input, ID, ',');
        getline(input, LastName, ',');
        getline(input, FirstName, ',');
        getline(input, Password, ',');
        getline(input, Gender);

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

            pCur->next = nullptr;
        }
    }
    input.close();
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

void displayStudentInfo(Student curStudent, Node *pStudentSLL, string classAddress)
{
    system("CLS");
    int n;

    cout << "No: " << curStudent.no << endl;
    cout << "ID: " << curStudent.ID << endl;
    cout << "Fullname: " << curStudent.LastName << ' ' << curStudent.FirstName << ' ' << endl;
    cout << "Date Of Birth: " << curStudent.DateOfBirth << endl;
    cout << "Gender: " << curStudent.Gender << endl;
    cout << "Social ID: " << curStudent.SocialID << endl;
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
        updatePasswordChangeToCSVFile(curStudent, pStudentSLL, classAddress);
        cout << "Successfully Updated!!!" << endl;
        cout << "Hit any key to see the change.";
        getch(); // hit any key and then execute then below function
        displayStudentInfo(curStudent, pStudentSLL, classAddress);
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

void updatePasswordChangeToCSVFile(Student curStudent, Node *&pStudentSLL, string classAddress)
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
    writeCSVFile(pStudentSLL, classAddress);
}

void writeCSVFile(Node *pStudentSLL, string classAddress)
{
    ofstream output;
    classAddress = ".\\inputs\\" + classAddress;
    cout << classAddress << endl;
    output.open(classAddress);
    output << "No ,ID,Lastname,Firstname,Gender,Date Of Birth,Social ID,Password" << endl;

    while (pStudentSLL)
    {
        output << pStudentSLL->student.no << ',';
        output << pStudentSLL->student.ID << ',';
        output << pStudentSLL->student.LastName << ',';
        output << pStudentSLL->student.FirstName << ',';
        output << pStudentSLL->student.Gender << ',';
        output << pStudentSLL->student.DateOfBirth << ',';
        output << pStudentSLL->student.SocialID << ',';
        output << pStudentSLL->student.Password << endl;
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

void createNewDirectory(string url)
{
    string s;
    cout << "Your new File name: ";
    getline(cin, s);
    // string url = "./inputs/School years/";
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

void createNewSchoolYear()
{
}