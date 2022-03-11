#pragma once
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

void loginSection(string &account, string &password);
bool checkAccAndPass(string account, string password);
void displayCSVFile();