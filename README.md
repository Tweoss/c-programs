This README is available as HTML with syntax highlighting at [this link](https://valour.vision/c-programs/) or [themed](https://valour.vision/c-programs/README.html). 


The program runs with verification of a password input. It displays a menu with the options to interact with the array of students. The array's length of valid inputs is kept in a variable in order to ensure that only valid values from the array are used and not outdated, deleted values. 

Here is the source code with comments:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ------------ PREPROCESSOR DIRECTIVES ------------

// The array size
#define ARRAY_SIZE 100
// Password is abcdefgacdebfg. Hashing means the password should not be inspectable from the executable.
#define PASSWORD_HASH 1362678140;

// -------------- STRUCTURES --------------

// The structure student consists of a name (character array of size 20), midterm and final scores (integer).
typedef struct
{
    char name[20];
    int midterm;
    int final;
} Student;

// -------------- UTILITY FUNCTIONS --------------

// simple hash algorithm (sdbm) to check password while hiding pswd from executable (from http://www.cse.yorku.ca/~oz/hash.html)
// Note: this is not a cryptographically secure hash at all.
// shows bit mixing: subtraction and addition with shifting
int hash(char *word)
{
    int hash = 0;
    // exclude the last character from the hash (since it would be the newline character)
    for (int counter = 0; word[counter + 1] != '\0'; counter++)
    {
        hash = word[counter] + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

// comparator function for qsort
int compare_students_name(const void *a, const void *b)
{
    // alphabetical ascending (a, b, c)
    // compare the name of the students
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

// comparator function for qsort
int compare_students_midterm(const void *a, const void *b)
{
    // numerical descending (3, 2, 1)
    // compare the midterm of the students
    return -((Student *)a)->midterm + ((Student *)b)->midterm;
}

// comparator function for qsort
int compare_students_final(const void *a, const void *b)
{
    // numerical descending (3, 2, 1)
    // compare the final of the students
    return -((Student *)a)->final + ((Student *)b)->final;
}

// -------------- USER INTERACTION FUNCTIONS --------------

// Request the password from the user and return whether or not it is correct.
bool request_password()
{
    char password[20];
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    return hash(password) == PASSWORD_HASH;
}

// Showing menu and selecting option
// ------------
// 1. Add a student
// 2. Remove a student
// 3. Enter grades for students
// 4. Display Name and midterm and final grades in a table format
// 5. Sort based on names and list the name, midterm and final
// 6. Sort based on midterm and list the name, midterm and final
// 7. Sort based on final exam and list the name, midterm and final
// 8. Find class mean and average for final exam
int menu_selection(void)
{
    int selection = -1;
    // menu array
    char *menu[] = {
        "Add a student",
        "Remove a student",
        "Enter grades for students",
        "Display Name and midterm and final grades in a table format",
        "Sort based on names and list the name, midterm and final",
        "Sort based on midterm and list the name, midterm and final",
        "Sort based on final exam and list the name, midterm and final",
        "Find class mean and average for final exam"};
    int menu_size = sizeof(menu) / sizeof(char *);
    printf("=====================================================================\n");
    // print menu and read input while input is not valid
    while (selection < 0 || selection > menu_size)
    {
        // print the menu
        for (int i = 0; i < menu_size; i++)
        {
            printf("%d-\t%s\n", i + 1, menu[i]);
        }
        // print the prompt
        printf("\nEnter choice: ");
        // read input
        scanf("%d", &selection);
        // input validation
        if (selection < 0 || selection > menu_size)
        {
            printf("Invalid selection.\n");
        }
        // flush the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
    printf("=====================================================================\n");
    return selection;
}

bool add_student(Student *student)
{
    printf("Enter a name: ");
    scanf("%s", student->name);
    printf("Enter a midterm score: ");
    scanf("%d", &(student->midterm));
    printf("Enter a final score: ");
    scanf("%d", &(student->final));
    return true;
}

bool remove_student(Student students[], int *currentSize)
{
    char name[20];
    printf("Enter the name of the student to be removed (removes the first instance of this name): ");
    scanf("%s", name);
    bool found = false;
    for (size_t i = 0; i < *currentSize; i++)
    {
        // if the names are equivalent, remove the student
        if (strcmp(name, students[i].name) == 0)
        {
            found = true;
            currentSize--;
        }
        if (found && i < ARRAY_SIZE - 1)
        {
            students[i] = students[i + 1];
        }
        // because we have reduced the counter, we do not need to set the last student to null values
    }
    return found;
}

bool enter_grades(Student students[], int currentSize)
{
    printf("Enter the name of the student to enter grades for: ");
    char name[20];
    scanf("%s", name);
    bool found = false;
    for (size_t i = 0; i < currentSize; i++)
    {
        // if the names are equivalent, enter grades
        if (strcmp(name, students[i].name) == 0)
        {
            found = true;
            printf("Enter a midterm score: ");
            scanf("%d", &(students[i].midterm));
            printf("Enter a final score: ");
            scanf("%d", &(students[i].final));
            break;
        }
    }
    return found;
}

bool display_students(Student students[], int currentSize)
{
    // print the header
    printf("Name\tMidterm\tFinal\n");
    // print the student
    for (int i = 0; i < currentSize; i++)
    {
        printf("%s\t%d\t%d\n", students[i].name, students[i].midterm, students[i].final);
    }
    return true;
}

bool sort_students_name(Student students[], int currentSize)
{
    // sort the array based on the name, using quicksort provided by c header file
    qsort(students, currentSize, sizeof(Student), compare_students_name);
    return true;
}

bool sort_students_midterm(Student students[], int currentSize)
{
    // sort the array based on the midterm, using quicksort provided by c header file
    qsort(students, currentSize, sizeof(Student), compare_students_midterm);
    return true;
}

bool sort_students_final(Student students[], int currentSize)
{
    // sort the array based on the final, using quicksort provided by c header file
    qsort(students, currentSize, sizeof(Student), compare_students_final);
    return true;
    return true;
}

float find_class_mean(Student students[], int currentSize)
{
    // find the class mean
    float class_mean = 0;
    for (int i = 0; i < currentSize; i++)
    {
        class_mean += students[i].final;
    }
    class_mean /= currentSize;
    return class_mean;
}

int find_class_median(Student students[], int currentSize)
{
    // find the class median
    int class_median = 0;
    sort_students_final(students, currentSize);
    return (currentSize % 2 == 0) ? (students[currentSize / 2 - 1].final + students[currentSize / 2].final) / 2 : students[currentSize / 2].final;
}

// ------------ MAIN FUNCTION ------------

// An array of student structures of size 100 (write #define for defining the size).
// A variable called currentSize. When no students are added currentSize is zero. As students are added or removed currentSize is updated.
int main(int argc, char *argv[])
{
    // the array of students
    Student students[ARRAY_SIZE];
    int currentSize = 0;
    // if failed the password is incorrect, exit
    if (!request_password())
    {
        printf("Incorrect password.\n");
        exit(1);
    }
    // if the password is correct, continue
    printf("Welcome to the student database.\nEnter 0 to exit from menu selection.\n");
    // loop until the user wants to exit
    while (true)
    {
        // execute each function depending on the input
        switch (menu_selection())
        {
        case 0:
            exit(0);
        case 1:
            // use pointer addition to set the new student
            add_student(students + currentSize) ? printf("Added.\n") && currentSize++ : printf("Failed.\n");
            break;
        case 2:
            // pass pointer so that currentSize can be decremented if a student is successfully removed
            remove_student(students, &currentSize);
            currentSize--;
            printf("Removed.\n");
            break;
        case 3:
            // pass currentSize so know how many to search in
            enter_grades(students, currentSize);
            printf("Updated grades.\n");
            break;
        case 4:
            // currentSize to know how many to display
            display_students(students, currentSize);
            break;
        case 5:
            // pass currentSize to qsort to avoid using deleted elements
            sort_students_name(students, currentSize);
            printf("Sorted.\n");
            display_students(students, currentSize);
            break;
        case 6:
            // pass currentSize to qsort to avoid using deleted elements
            sort_students_midterm(students, currentSize);
            printf("Sorted.\n");
            display_students(students, currentSize);
            break;
        case 7:
            // pass currentSize to qsort to avoid using deleted elements
            sort_students_final(students, currentSize);
            printf("Sorted.\n");
            display_students(students, currentSize);
            break;
        case 8:
            // pass currentSize to avoid using deleted elements
            printf("The class mean for the final was: %f.\n", find_class_mean(students, currentSize));
            printf("The class median for the final was: %d.\n", find_class_median(students, currentSize));
            break;
        }
    }
}

```

First, there are the include headers and the preprocessor directives, as alternatives to const variables. Second, there is the struct definition for the Student type. 

Then, there are the utility functions. Because the program does not use function prototyping, the functions must be defined before they are used. Thus, the utility functions come first. The first function is a hash function described at [this link](http://www.cse.yorku.ca/~oz/hash.html). It is a simple hash function meant to obscure the password from the compiled executable. The password is `abcdefgacdebfg`, and its hash is part of the preprocessor directives. Then the comparator functions are defined. These are used later to sort the array of students via the quick sort provided by stdlib. 

After the utility functions are the user interaction functions, which have output and input from the user and provide their results, primarily whether or not they succeed, to main. Request_password requests a password and returns whether or not it matches with the hash. Menu_selection displays a menu and requests a selection, stopping only when there is a valid input. The choice is relayed to main, where other functions are called. Exiting on a `0` is done by main, since it is an important part of control flow and should be very visible instead of being obscured inside a function. Next come the functions to add students, remove students, enter grades, display names and grades, sort, and find the mean and median for the final grade. Notably, `remove_student` receives a pointer to `currentSize`, as the function may not succeed, so it needs to be able to modify `currentSize`. An alternate approach is shown with `add_student`, which returns a boolean to main, which then increments on success. 

After these definitions comes main, which initializes the array `students` and the `currentSize` variable. It then requests a password, exiting with an unsuccessful code if it is incorrect. It begins the main loop with a menu request and then resulting actions encased in a switch statement. If the selection is `0`, the program exits with the successful 0 code. 

Possible improvements to the program would be persistent data via file IO, more robust error handling, and visual analysis of the data instead of mere numbers. 