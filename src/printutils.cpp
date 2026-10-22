#include <iostream>
#include "main.h"
#include "printutils.h"

void print_line(string msg)
{
	cout << msg << endl;
}

void print_title(string title)
{
	string line = "-----------------------------------";

	cout << line << endl
		<< title << endl
		<< line << endl;
}

void fatal_error(string msg)
{
	cout << "KLAIDA: " << msg << endl;
	g_quit = true;
}