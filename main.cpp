#include "functions.h"

int main()
{
    // <-------------------- open a file with a specific name ------------------->

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
        return 0;
    }

    while (input.good())
    {
        string line = "";
        getline(input, line);
        cout
            << line << endl<<endl;
    }

    // <-------------------- END  ------------------->

    input.close();
    // string account, password;
    //  loginSection(account, password);
    //  bool ok = checkAccAndPass(account, password);
}