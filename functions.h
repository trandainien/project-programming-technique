#pragma once
#include <iostream>
#include <fstream>
#include <string>
//#include <stdlib.h>
#include <conio.h> //take getCh() from this library

#include <direct.h>

using namespace std;
    
struct Course
{
    string StartDate, EndDate, ID, Name, TeacherName, Day1, Day2, Time1, Time2;
    int NumberOfCredits, MaxNumOfStudent;
};

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
void loginSection();
bool validateUser(string username, string password, Node *pHead, Student &curStudent);
void ExtractStudentInfoFromCSVFileAndTurnToSLL(Node *&pHead);
void StudentLoginSection(Node *pStudentSLL);
void AcademicStaffLoginSection();
void start();
void displayStudentInfo(Student curStudent, Node *pStudentSLL);
void writeCSVFile(Node *pStudentSLL);
void updatePasswordChangeToCSVFile(Student curStudent, Node *&pStudentSLL);
void changePassword(Student &curStudent);
void createNewDirectory();