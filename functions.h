#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    string no, ID, LastName, FirstName, Username, Password, Gender, Email, Class;
};

struct Node
{
    Student student;
    Node *next;
};

void openCSVFileFromUserInput();
void loginSection(Node *pHead);
bool validateUser(string username, string password, Node *pHead);
void ExtractInfoFromCSVFileAndTurnToSLL(Node *&pHead);