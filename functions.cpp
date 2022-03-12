#include "functions.h"

void loginSection(Node *pHead)
{
    string username;
    string password;
    cout << "Login Section" << endl
         << endl;
    cout << "Enter Your Account: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    bool ok = validateUser(username, password, pHead);

    if (ok)
    {
        cout << "login successfully" << endl;
    }
    else
    {
        cout << "Your password is incorrect!!!";
    }
}

void ExtractInfoFromCSVFileAndTurnToSLL(Node *&pHead)
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

bool validateUser(string username, string password, Node *pHead)
{
    while (pHead)
    {
        if (pHead->student.Username == username && pHead->student.Password == password)
            return true;
        pHead = pHead->next;
    }
    return false;
}

// void displayStudentInfo(string No, string ID, string FirstName, string LastName, string Username, string Password, string Class)
// {
//     cout << "Your number in Students List: " << No << endl;
//     cout << "ID: " << ID << endl;
//     cout << "Full name: " << LastName << ' ' << FirstName << ' ' << endl;
//     cout << "Class: " << Class << endl;
//     cout << "--------------------------------------------------------------------" << endl;

//     cout << "Username: " << Username << endl;
//     cout << "Password: " << Password << endl;

//     // change password option.
//     // log out option
// }

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
