#ifndef TERMINALUTILS_H
#define TERMINALUTILS_H

#include <string>
using namespace std;

extern int padding;

int getTerminalWidth();
void printCentered(const string& text);
void addVerticalPadding(int lines);

#endif
