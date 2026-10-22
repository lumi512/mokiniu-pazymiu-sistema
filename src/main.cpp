#include "main.h"
#include "menu.h"

bool g_quit = false;

int main()
{
	while (!g_quit)
	{
		if (!menu_perform_action())
			break;
	}

	return 0;
}