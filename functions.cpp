#include "functions.h"

void loginSection()
{
    string username;
    string password;
    cout << "Login Section" << endl
         << endl;
    cout << "Enter Your Account: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    bool ok = validateUser(username, password);

    if (ok)
    {
        
    }
    else
    {
        cout<<"Your password is incorrect!!!";
    }
}

bool validateUser(string username, string password)
{
    ifstream input;
    input.open("./inputs/Students List.csv");
    string temp;
    getline(input, temp);

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
        getline(input, Class, ',');

        if (username == Username && password == Password)
        {
            return true;
        }
    }
    return false;
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
