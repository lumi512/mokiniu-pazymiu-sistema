#pragma once

#include "main.h"
#include <string>

#define GRADE_MIN 1
#define GRADE_MAX 10

#define MAX_STUDENTS 100
#define MAX_GRADES 10

extern string g_studentList[MAX_STUDENTS];
extern int g_gradesList[MAX_STUDENTS][MAX_GRADES];

int student_count();
int student_grade_count(int idx);
int student_grade_count(string name);

int student_get_free_space();
bool student_has_free_space();

int student_get_index(string name);
bool student_is_valid(int idx);

void student_rearrange();

int student_add(string name);
void student_delete(int idx);
void student_delete(string name);

void student_set_grade(int idx, int grade, int num);
void student_set_grade(string name, int grade, int num);