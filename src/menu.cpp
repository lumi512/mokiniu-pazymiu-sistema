#include <iostream>
#include "menu.h"
#include "students.h"
#include "printutils.h"
#include "random.h"

MenuAction g_currentAction = MENU_MAIN;
MenuAction g_lastAction = MENU_INVALID;

void menu_set_action(MenuAction act)
{
	g_lastAction = g_currentAction;
	g_currentAction = act;
}

bool menu_perform_action()
{
	int result;
	switch (g_currentAction)
	{
		case MENU_MAIN:
			result = menu_list("Meniu", {
				"Ivesti mokini",
				"Perziureti visu mokiniu pazymius",
				"Perziureti mokinio pazymi",
				"Atnaujinti pazymi",
				"Apskaiciuoti mokinio vidurki",
				"Pasalinti mokini",
				"Iseiti"
			});

			if (result != -1)
				menu_set_action((MenuAction)result);
			break;

		case MENU_ADDSTUDENT:
			if (!student_has_free_space())
			{
				print_line("Pasiektas mokiniu limitas. Kad ivesti nauja mokini, pasalinkite kita mokini.");
				menu_set_action(MENU_MAIN);
				break;
			}

			print_title("Iveskite mokinio varda");
			print_line("Mokiniu skaicius: " + to_string(student_count()));

			if (menu_get_string())
			{
				if (g_inputString == "AUTO")
				{
					g_inputResult = -1;
					print_title("AUTOMATINIS REZIMAS: Iveskite mokiniu skaiciu");

					do menu_get_input(1, MAX_STUDENTS);
					while (g_inputResult == -1);


					for (int i = 0; i < g_inputResult; i++)
					{
						if (student_add("Petriukas (" + to_string(i) + ")") == -1)
						{
							print_line("Pasiektas mokiniu limitas, ivestas mokiniu skaicius: " + to_string(i));
							break;
						}
						else
						{
							for (int j = 0; j < MAX_GRADES; j++)
								student_set_grade(i, j, generate_int(GRADE_MIN, GRADE_MAX));
						}
					}
				}
				else
				{
					int index = student_add(g_inputString);

					int gradeCount = 0;
					do
					{
						print_title("Iveskite pazymi " + to_string(gradeCount + 1) + " mokiniui " + g_inputString);

						do
						{
							menu_get_input(GRADE_MIN, GRADE_MAX);
							if (g_inputResult == -1)
								print_line("Iveskite skaiciu nuo " + to_string(GRADE_MIN) + " iki " + to_string(GRADE_MAX) + ".");
						}
						while (g_inputResult == -1);

						student_set_grade(index, gradeCount, g_inputResult);
						gradeCount++;


						int gradeResult = menu_list("Ivesti dar viena pazymi?", {
							"Taip",
							"Ne"
						});

						if (gradeResult == 2)
							break;
					}
					while (gradeCount < 10);
				}

				menu_set_action(MENU_ACTIONEND);
			}
			break;

		case MENU_DELETESTUDENT:
			if (student_count() <= 0)
			{
				print_line("Nera jokiu ivestu mokiniu duomenys.");
				menu_set_action(MENU_MAIN);
				break;
			}

			print_title("Iveskite mokinio varda");
			if (menu_get_string())
			{
				int studentIndex = student_get_index(g_inputString);
				if (studentIndex != -1)
					student_delete(studentIndex);
				else
					print_line("Mokinio su vardu " + g_inputString + " nera.");

				menu_set_action(MENU_ACTIONEND);
			}
			break;

		case MENU_QUIT:
			g_quit = true;
			break;

		case MENU_ACTIONEND:
			result = menu_list("Ka dabar?", {
				"Is naujo vykdyti veiksma",
				"Grizti i meniu",
				"Iseiti"
			});

			switch (result)
			{
				case 1:
					menu_set_action(g_lastAction);
					break;
				case 2:
					menu_set_action(MENU_MAIN);
					break;
				case 3:
					menu_set_action(MENU_QUIT);
					break;
			}
			break;

		default:
			fatal_error("Nezinomas veiksmas - " + to_string(g_currentAction));
			return false;
	}

	return true;
}

void menu_print_list(vector<string> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		string str = list[i];
		print_line(to_string(i + 1) + ". " + str);
	}
}

int menu_list(string title, vector<string> list)
{
	print_title(title);
	menu_print_list(list);

	do menu_get_input(1, list.size());
	while (g_inputResult == -1);

	return g_inputResult;
}

int g_inputResult = -1;
string g_inputString = "";

void menu_clear_input()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool menu_get_string()
{
	cout << "> ";

	string str;
	cin >> str;

	if (cin.fail())
	{
		print_line("Neteisingas ivedimas.");
		menu_clear_input();

		g_inputString = "";
		return false;
	}

	g_inputString = str;
	return true;
}

bool menu_get_input(int minval, int maxval)
{
	cout << "> ";

	string str;
	cin >> str;

	int val = atoi(str.c_str());
	if (cin.fail() || (minval != -1 && val < minval) || (maxval != -1 && val > maxval))
	{
		print_line("Neteisingas pasirinkimas.");
		menu_clear_input();

		g_inputResult = -1;
		return false;
	}

	g_inputResult = val;
	return true;
}