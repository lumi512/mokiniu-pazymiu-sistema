#include "main.h"
#include "menu.h"
#include "students.h"
#include "printutils.h"

bool g_quit = false;

int main()
{
	while (!g_quit)
	{
		int index = -1;
		if (g_currentAction == MENU_DELETESTUDENT	||
			g_currentAction == MENU_VIEWSTUDENT		||
			g_currentAction == MENU_UPDATE			||
			g_currentAction == MENU_CALCAVG)
		{
			if (student_count() <= 0)
			{
				print_line("Nera jokiu ivestu mokiniu duomenys.");
				menu_set_action(MENU_MAIN);
				continue;
			}

			print_title("Iveskite mokinio varda arba numeri");
			if (menu_get_string())
			{
				int idx = atoi(g_inputString.c_str());
				if (idx != 0)
				{
					index = idx - 1;
					if (!student_is_valid(index))
					{
						print_line("Mokinio su numeriu " + to_string(idx) + " nera.");
						menu_set_action(MENU_ACTIONEND);
					}
				}
				else
				{
					index = student_get_index(g_inputString);
					if (index == -1)
					{
						print_line("Mokinio su vardu " + g_inputString + " nera.");
						menu_set_action(MENU_ACTIONEND);
					}
				}
			}
		}

		if (g_currentAction == MENU_UPDATE			||
			g_currentAction == MENU_VIEWSTUDENT		||
			g_currentAction == MENU_CALCAVG)
		{
			if (student_grade_count(index) <= 0)
			{
				print_line("Mokinys " + student_get_name(index) + " neturi pazymiu.");
				menu_set_action(MENU_ACTIONEND);
				continue;
			}
		}

		menu_perform_action(index);
	}

	return 0;
}