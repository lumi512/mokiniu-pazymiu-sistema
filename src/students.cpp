#include "students.h"

string g_studentList[MAX_STUDENTS] {};
int g_gradesList[MAX_STUDENTS][MAX_GRADES] {};

int student_count()
{
	int count = 0;
	for (int i = 0; i < MAX_STUDENTS; i++)
	{
		string str = g_studentList[i];
		if (str != "")
			count++;
	}

	return count;
}

int student_grade_count(int idx)
{
	int *grades = g_gradesList[idx];
	if (grades == nullptr)
		return 0;

	int count = 0;
	for (int i = 0; i < MAX_GRADES; i++)
	{
		if (grades[i] != 0)
			count++;
	}

	return count;
}

int student_grade_count(string name)
{
	int idx = student_get_index(name);
	if (idx != -1)
		return student_grade_count(idx);
}

int student_get_free_space()
{
	for (int i = 0; i < MAX_STUDENTS; i++)
	{
		if (g_studentList[i] == "")
			return i;
	}

	return -1;
}

bool student_has_free_space() { return student_get_free_space() != -1; }

bool student_empty_space_check()
{
	string prevstr = "";
	for (int i = MAX_STUDENTS - 1; i >= 0; i--)
	{
		string str = g_studentList[i];
		if (prevstr != "" && str == "")
			return false;

		prevstr = str;
	}

	return true;
}

int student_get_index(string name)
{
	int idx = -1;
	for (int i = 0; i < MAX_STUDENTS; i++)
	{
		if (g_studentList[i] == name)
		{
			idx = i;
			break;
		}
	}

	return idx;
}

string student_get_name(int idx)
{
	if (student_is_valid(idx))
		return g_studentList[idx];
	return "";
}

bool student_is_valid(int idx) { return idx >= 0 && idx < MAX_STUDENTS && g_studentList[idx] != ""; }

void student_rearrange()
{
	while (!student_empty_space_check())
	{
		string prevstr = "";
		int previdx = -1;
		int *prevgrades = nullptr;

		for (int i = MAX_STUDENTS - 1; i >= 0; i--)
		{
			string str = g_studentList[i];
			if (prevstr != "" && str == "" && previdx != -1)
			{
				g_studentList[i] = prevstr;
				g_studentList[previdx] = "";

				if (prevgrades != nullptr)
				{
					for (int j = 0; j < MAX_GRADES; j++)
						g_gradesList[i][j] = prevgrades[j];
				}
			}

			prevstr = str;
			previdx = i;
			prevgrades = g_gradesList[i];
		}
	}
}

int student_add(string name)
{
	student_rearrange();

	int idx = student_get_free_space();
	if (idx == -1)
		return idx;

	g_studentList[idx] = name;
	return idx;
}

void student_delete(int idx)
{
	if (student_is_valid(idx))
	{
		g_studentList[idx] = "";

		int *grades = g_gradesList[idx];
		for (int i = 0; i < MAX_GRADES; i++)
			grades[i] = 0;

		student_rearrange();
	}
}

void student_delete(string name)
{
	int idx = student_get_index(name);
	if (idx != -1)
		student_delete(idx);
}

void student_set_grade(int idx, int grade, int num)
{
	if (student_is_valid(idx) && grade >= 0 && grade < MAX_GRADES)
		g_gradesList[idx][grade] = num;
}

void student_set_grade(string name, int grade, int num)
{
	int idx = student_get_index(name);
	if (idx != -1)
		student_set_grade(idx, grade, num);
}