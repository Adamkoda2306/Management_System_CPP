// Terminalutils.h Header file
#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

#include <string>//for strings
using namespace std;

extern int padding;

// functions for this Header files
int getTerminalWidth();
void printCentered(const string& text);
void addVerticalPadding(int lines);

#endif
