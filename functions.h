#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sys\stat.h>
#include <dirent.h>
#include <conio.h> //take getCh() from this library
#include <stdio.h>
#include <iomanip> //format into table data
using namespace std;

struct Course
{
    string StartDate, EndDate, ID, Name, TeacherName, Day1, Day2, Time1, Time2;
    int NumberOfCredits, MaxNumOfStudent;
};

struct Student
{
    string no, ID, LastName, FirstName, Gender, DateOfBirth, SocialID, Password;
};

struct Node
{
    Student student;
    Node *next;
};

struct Staff
{
    string no, ID, LastName, FirstName, Gender, Email, Password;
};

struct StaffList
{
    Staff staff;
    StaffList *next;
};

void start();
void loginSection();
void openCSVFileFromUserInput();

// student
void ExtractStudentInfoFromCSVFileAndTurnToSLL(Node *&pHead);
bool validateUser(string username, string password, Node *pHead, Student &curStudent);
void StudentLoginSection();
void displayStudentInfo(Student curStudent, Node *pStudentSLL, string classAddress);
void changePassword(Student &curStudent);
void updatePasswordChangeToCSVFile(Student curStudent, Node *&pStudentSLL, string classAddress);
void ExtractStudentInClass(Node *&pHead, string schoolYear, string className);
void writeCSVFile(Node *pStudentSLL, string classAddress);

void findStudentInAClass(Node *&pHead, string curID, string address, bool &isStudentExist, Student &student, string password);
bool findStudentWithID(string ID, Student &student, Node *&pHead, string &classAddress,string password);

// staff
void AcademicStaffLoginSection();
void StaffMenu();
void viewStaffPersonalInfo(Staff staff, StaffList *&pHead);
bool validateStaff(string username, string password, StaffList *pHead, Staff &staff);
void ExtractStaffInfoAndTurnToSLL(StaffList *&pHead);
void writeChangesToStaffCSV(StaffList *pHead);
void changeStaffPassword(Staff &staff, StaffList *&pHead);
void viewSchoolYear();
void viewClassesInSchoolYear(string address, string schoolYear);
void viewStudentInClass(string address, string className, string schoolYear);
void createNewSchoolYear();

// Files
void createNewDirectory(string url);
void ListAllFileNames(string address, bool isFile, string arr[], int &num);
string removeType(string s);

// format
template <class T>
void printElement(T t, const int &width);