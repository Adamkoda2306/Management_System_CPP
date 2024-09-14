#include<iostream>
#include<cstdlib>

#define Red "\033[31m"
#define Default "\033[0m"
#define Green "\033[38;5;28m"
#define lightGreen "\033[32m"
#define Blue "\033[34m"

#include "TerminalUtils.h"
#include "Librarian_MainMenu.h"
using namespace std;

void Librarian_Menu::wish(){
    cout<<"**********Hello**************"<<endl;
}