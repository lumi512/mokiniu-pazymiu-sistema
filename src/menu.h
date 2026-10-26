#pragma once

#include <string>
#include <vector>
#include "main.h"

enum MenuAction
{
	MENU_INVALID = -1,

	MENU_MAIN,

	MENU_ADDSTUDENT,
	MENU_VIEWALL,
	MENU_VIEWSTUDENT,
	MENU_UPDATE,
	MENU_CALCAVG,
	MENU_DELETESTUDENT,
	MENU_QUIT,

	MENU_ACTIONEND,

	MENU_MAX,
};

extern MenuAction g_currentAction;
extern MenuAction g_lastAction;

void menu_set_action(MenuAction act);
bool menu_perform_action(int studentIndex = -1);

void menu_print_list(vector<string> list);
int menu_list(string title, vector<string> list);

extern int g_inputResult;
extern string g_inputString;

void menu_clear_input();
bool menu_get_string();
bool menu_get_input(int minval = -1, int maxval = -1);