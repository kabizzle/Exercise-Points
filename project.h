#ifndef _PROJECT__H_
#define _PROJECT__H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* declaring struct to store data of one student*/
typedef struct {
    char* number;
    char* surname;
    char* name;
    int round1;
    int round2;
    int round3;
    int round4;
    int round5;
    int round6;  
    int total;
} Student;

/* declaring struct to store student structs and point structs*/
typedef struct{
    int num;
    Student* students;
}  StudentList;

#define MAXLENGTH 1000

/* function definitions*/

void initialise_points(StudentList* students);
int check_command(const char* command_str);
int add_student(const char* user_cmd, StudentList *students);
int update_points(const char* user_cmd, StudentList* students);
int sort_database(StudentList* students);
void print_database(StudentList *students, FILE* out);
int write_to_file (const char* user_cmd, StudentList *students);
int main(void);

#endif //! _PROJECT__H_