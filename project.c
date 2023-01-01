#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void initialise_points(StudentList* students){
    /*Function to set a new students points to 0*/
    int i = students->num;

    students->students[i].round1 = 0;
    students->students[i].round2 = 0;
    students->students[i].round3 = 0;
    students->students[i].round4 = 0;
    students->students[i].round5 = 0;
    students->students[i].round6 = 0;
    students->students[i].total = 0;
}

int check_command(const char* command_str){
    unsigned int i;
    int count = 0, str_len = 0;

    for (i = 0; i <strlen(command_str); i++){
        if (isspace(command_str[i]) && str_len > 0){
            count++;
            str_len = 0;
        }
        else
            str_len++;
    }
    return count;
}

int add_student(const char* user_cmd, StudentList *students){
    int str_len = 0;
    int current = 0;
    int i = students->num;

    char *number, *surname, *name;
    
    // loop to allocate memory for 
    students->students = realloc(students->students, (i+1)*sizeof(Student));
    if (students->students == NULL)
        return 1;    

    if (check_command(user_cmd) != 4){
        printf("Invalid number of inputs entered\n");
        return 1;
    }
    
    for (unsigned int j = 0; j < strlen(user_cmd); j++){
        if (isalpha(user_cmd[j]) || isdigit(user_cmd[j])){
            str_len++;
        }
        else if (isspace(user_cmd[j])){
            if (current == 1)
                if (str_len < 6){
                    printf("Student number must contain at least 6 characters\n");
                    return 1;
                }
                else
                    number = calloc(str_len + 1, sizeof(char));
            else if (current == 2)
                surname = calloc(str_len + 1, sizeof(char));
            else if (current == 3)
                name = calloc(str_len + 1, sizeof(char));
            
            str_len = 0;
            current++;
        }
    }

    sscanf(user_cmd, "A %s %s %s", number, surname, name);
    
    for (int j = 0; j < students->num; j++){
        if (strcmp(students->students[j].number, number) == 0){
            printf("Student already in database\n");
            free(number);
            free(surname);
            free(name);
            return 1;
        }
    }

    /* setting data values for student */
    students->students[i].number = calloc(sizeof(char), strlen(number)+1);
    strcpy(students->students[i].number, number);
    students->students[i].number[strlen(number)] = '\0';
    students->students[i].surname = calloc(sizeof(char), strlen(surname)+1);
    strcpy(students->students[i].surname, surname);
    students->students[i].surname[strlen(surname)] = '\0';
    students->students[i].name = calloc(sizeof(char), strlen(name)+1);
    strcpy(students->students[i].name, name);
    students->students[i].name[strlen(name)] = '\0';

    initialise_points(students);
    free(number);
    free(surname);
    free(name);

    // i++;
    students->num++;
    return 0;
}

int update_points(const char* user_cmd, StudentList* students){
    char *number;
    int round;
    unsigned int points;
    int str_len = 0;
    int current = 0;
    int flag = 0;

    if (check_command(user_cmd) != 4){
        printf("Invalid number of inputs entered\n");
        return 1;
    }
    
    for (unsigned int i = 0; i < strlen(user_cmd); i++){
        if (isalpha(user_cmd[i]) || isdigit(user_cmd[i])){
            str_len++;
        }
        else if (isspace(user_cmd[i])){
            if (current == 1) {
                if (str_len < 6){
                    printf("Student number must contain at least 6 characters\n");
                    return 1;
                }
                else
                    number = calloc(str_len + 1, sizeof(char));
            }
            str_len = 0;
            current++;
        }
    }
    sscanf(user_cmd, "U %s %d %u", number, &round, &points);


    for (int j = 0; j < students->num; j++){
        if (strcmp(students->students[j].number, number) == 0){
            switch (round){
                case 1:
                    students->students[j].round1 = points;
                    break;
                case 2: 
                    students->students[j].round2 = points;
                    break;
                case 3:
                    students->students[j].round3 = points;
                    break;
                case 4:
                    students->students[j].round4 = points;
                    break;
                case 5:
                    students->students[j].round5 = points;
                    break;
                case 6:
                    students->students[j].round6 = points;
                    break;
            }
            students->students[j].total = students->students[j].total + points;
            flag = 1;
        }
    }

    free(number);

    if (flag == 0){
        printf("Student not in database\n");
        return 1;
    }  

    return 0;
}

int sort_database(StudentList* students){
    int i, j, num;
    Student temp;
    num = students->num;
    for (i = 0; i < num; i++) {     
        for (j = i+1; j < num; j++) {     
            if (students->students[i].total < students->students[j].total) {    
                temp = students->students[i];    
                students->students[i] = students->students[j];    
                students->students[j] = temp;    
            }
        }     
    }
    return 0;
}

void print_database(StudentList *students, FILE* out){
    sort_database(students);
    int num_students = students->num;
    for (int i = 0; i < num_students; i++){
    fprintf(out,"%s %s %s ", students->students[i].number, students->students[i].surname, students->students[i].name);
    fprintf(out,"%d %d %d %d %d %d %d\n", students->students[i].round1, students->students[i].round2, students->students[i].round3, students->students[i].round4, students->students[i].round5, students->students[i].round6, students->students[i].total);
    }
}

int write_to_file (const char* user_cmd, StudentList *students) {
    char *filename;
    int str_len = 0, current = 0;

    for (unsigned int j = 0; j < strlen(user_cmd); j++){
        if (isalpha(user_cmd[j]) || isdigit(user_cmd[j])){
            str_len++;
        }
        else if (isspace(user_cmd[j])){
            if (current == 1)
                filename = calloc(str_len + 1, sizeof(char));
            
            str_len = 0;
            current++;
        }
    }

    sscanf(user_cmd, "W %s", filename);
    // strcat(filename, ".txt");
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot write to file %s.\n", filename);
        fclose(file);
        free(filename);
        return 1;
    }
    
    print_database(students, file);
    fclose(file);
    free(filename);
    return 0;
}

int read_file (const char *user_cmd, StudentList *students){
    char *filename;
    char line[MAXLENGTH], number[20], surname[25], name[25];
    int str_len = 0, current = 0, i = 0;

    for (unsigned int j = 0; j < strlen(user_cmd); j++){
        if (isalpha(user_cmd[j]) || isdigit(user_cmd[j])){
            str_len++;
        }
        else if (isspace(user_cmd[j])){
            if (current == 1)
                filename = calloc(str_len + 1, sizeof(char));
            
            str_len = 0;
            current++;
        }
    }

    sscanf(user_cmd, "O %s", filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot read file %s.\n", filename);
        fclose(file);
        free(filename);
        return 1;
    }

    fgets(line, MAXLENGTH-1, file);
    while (!feof(file)) {
        if (sscanf(line, "%s %s %s", number, surname, name) != 3){
            printf("Error loading file\n");
            fclose(file);
            free(filename);
            return 1;
        }
        /* setting data values for student */
        students->students[i].number = calloc(sizeof(char), strlen(number)+1);
        strcpy(students->students[i].number, number);
        students->students[i].number[strlen(number)] = '\0';
        students->students[i].surname = calloc(sizeof(char), strlen(surname)+1);
        strcpy(students->students[i].surname, surname);
        students->students[i].surname[strlen(surname)] = '\0';
        students->students[i].name = calloc(sizeof(char), strlen(name)+1);
        strcpy(students->students[i].name, name);
        students->students[i].name[strlen(name)] = '\0';

        initialise_points(students);
        fgets(line, MAXLENGTH-1, file);
        i++;
    }

    fclose(file);
    free(filename);
    return 0;
}

int main(void){
    // char command;
    char command_str[MAXLENGTH];

    StudentList students;
    
    students.num = 0;
    students.students = calloc(sizeof(Student), 1);

    while (1){
        fgets(command_str, MAXLENGTH-1, stdin);
        if (command_str[0] == 'A'){
            if (!add_student(command_str, &students))
                printf("SUCCESS\n");
            else
                printf("error\n");
        }
        else if (command_str[0] == 'U'){
            if (!update_points(command_str, &students))
                printf("SUCCESS\n");
            else
                printf("error\n");
        }
        else if (command_str[0] == 'L'){
            print_database(&students, stdout);
        }
        else if (command_str[0] == 'W'){
            if (!write_to_file(command_str, &students))
                printf("SUCCESS\n");
            else
                printf("error\n");
        }
        else if (command_str[0] == 'O'){
            if (!read_file(command_str, &students))
                printf("SUCCESS\n");
            else 
                printf("error\n");
        }
        else if (command_str[0] == 'Q') {
                for (int i = 0; i < students.num; i++){
                    free(students.students[i].number);
                    free(students.students[i].surname);
                    free(students.students[i].name);
                }
                free(students.students);
                return 0;
        }
        else{
            printf("Invalid command %c", command_str[0]);
        }
        command_str[0] = '\0';
    }
    return 0;
}