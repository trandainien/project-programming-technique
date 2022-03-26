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
#include <cstdio>
#include <bits/stdc++.h>
#include <unistd.h>
#include <filesystem>

using namespace std;

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

struct Date
{
    int day;
    int month;
    int year;
};

struct Course
{
    string id, teacherName, s1Time, s1Date, s2Time, s2Date;
    string name;
    Date startDate, endDate;
    string max = "50";
    string numberOfCredits;
};

struct CourseList
{
    Course course;
    CourseList *next;
};

struct CourseDate {
    int start_day, start_month, start_year, end_day, end_month, end_year;
};

void start();
void loginSection();
void openCSVFileFromUserInput();

// student
void StudentLoginSection();
void displayStudentInfo(string classAddress);
void changePassword();
void updatePasswordChangeToCSVFile(string classAddress);
void ExtractStudentInClass(Node *&pHead, string schoolYear, string className);
void writeCSVFile(string classAddress);

void findStudentInAClass(string curID, string address, bool &isStudentExist, string password);
bool findStudentWithID(string ID, string &classAddress, string password);

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
void viewSemesters(string address, string schoolYear);
void viewCourse(string address, string schoolYear, string term);
void CreateSemester(string address, string schoolYear);
void createNewCourse(string address, string schoolYear, string term);
void writeCourseToFile(string path, Course newCourse);
bool checkDay(string day);
bool checkTime(string time);
bool checkdate(int d, int m, int y);
void viewCourseInfo(string address, string schoolYear, string term, string nameCourse);
void updateCourse(Course &course, string address, string schoolYear, string term, string nameCourse);
int turnToInt(char c);
void TurnDate(string date, int &y, int &m, int &d);
string getTime(string time);
string getDay(string day);
void RegistrationDateCourse(CourseDate &Date);
int LeapYears(int year, int month);
int CountDays(tm* y,CourseDate x);
void CheckDate(CourseDate Date);
// Files
void createNewDirectory(string url);
void ListAllFileNames(string address, bool isFile, string arr[], int &num);
string removeType(string s);
void DeleteFile(string path);
void DeleteFolder(string path);
// format
template <class T>
void printElement(T t, const int &width);