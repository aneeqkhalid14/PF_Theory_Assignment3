#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char fullName[50];
    int rollNo;
    int sub1, sub2, sub3;
    float scorePercent;
    char gradeLetter[3];
};

void evaluate(struct Student *s) {
    s->scorePercent = (s->sub1 + s->sub2 + s->sub3) / 3.0;

    if (s->scorePercent >= 90) strcpy(s->gradeLetter, "A+");
    else if (s->scorePercent >= 80) strcpy(s->gradeLetter, "A");
    else if (s->scorePercent >= 70) strcpy(s->gradeLetter, "B+");
    else if (s->scorePercent >= 60) strcpy(s->gradeLetter, "B");
    else if (s->scorePercent >= 50) strcpy(s->gradeLetter, "C");
    else strcpy(s->gradeLetter, "F");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int total, i;

    printf("Enter number of students: ");
    scanf("%d", &total);

    for (i = 0; i < total; i++) {
        printf("\nEnter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].fullName);
        printf("Roll Number: ");
        scanf("%d", &students[i].rollNo);

        do {
            printf("Enter 3 subject marks (0-100): ");
            scanf("%d %d %d", &students[i].sub1, &students[i].sub2, &students[i].sub3);

            if (students[i].sub1 < 0 || students[i].sub1 > 100 ||
                students[i].sub2 < 0 || students[i].sub2 > 100 ||
                students[i].sub3 < 0 || students[i].sub3 > 100)
                printf("Invalid marks! Enter between 0-100.\n");
        } while (students[i].sub1 < 0 || students[i].sub1 > 100 ||
                 students[i].sub2 < 0 || students[i].sub2 > 100 ||
                 students[i].sub3 < 0 || students[i].sub3 > 100);

        evaluate(&students[i]);
    }

    float avgScore = 0;
    for (i = 0; i < total; i++)
        avgScore += students[i].scorePercent;
    avgScore /= total;

    for (i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (students[j].scorePercent > students[i].scorePercent) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n===== STUDENT RECORDS =====\n");
    printf("Rank\tName\tRoll\t%%\tGrade\n");
    for (i = 0; i < total; i++) {
        printf("%d\t%s\t%d\t%.2f\t%s\n",
               i + 1, students[i].fullName, students[i].rollNo,
               students[i].scorePercent, students[i].gradeLetter);
    }

    printf("\nClass Average = %.2f\n", avgScore);

    printf("\nStudents ABOVE average:\n");
    for (i = 0; i < total; i++)
        if (students[i].scorePercent > avgScore)
            printf("%s (%.2f)\n", students[i].fullName, students[i].scorePercent);

    printf("\nStudents BELOW average:\n");
    for (i = 0; i < total; i++)
        if (students[i].scorePercent < avgScore)
            printf("%s (%.2f)\n", students[i].fullName, students[i].scorePercent);

    int choice;
    char searchName[50];
    int searchRoll;
    char searchGrade[3];

    while (1) {
        printf("\n===== SEARCH MENU =====\n");
        printf("1. Search by Roll Number\n");
        printf("2. Search by Name\n");
        printf("3. Find all students with a Grade\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter roll number: ");
            scanf("%d", &searchRoll);
            int found = 0;
            for (i = 0; i < total; i++) {
                if (students[i].rollNo == searchRoll) {
                    printf("Found: %s %.2f %s\n",
                           students[i].fullName, students[i].scorePercent, students[i].gradeLetter);
                    found = 1;
                    break;
                }
            }
            if (!found) printf("No student found.\n");
        }

        else if (choice == 2) {
            printf("Enter name: ");
            scanf("%s", searchName);
            int found = 0;
            for (i = 0; i < total; i++) {
                if (strcmp(students[i].fullName, searchName) == 0) {
                    printf("Found: Roll %d, %% %.2f, Grade %s\n",
                           students[i].rollNo, students[i].scorePercent, students[i].gradeLetter);
                    found = 1;
                }
            }
            if (!found) printf("No student found.\n");
        }

        else if (choice == 3) {
            printf("Enter grade (A+, A, B+, B, C, F): ");
            scanf("%s", searchGrade);
            int found = 0;
            for (i = 0; i < total; i++) {
                if (strcmp(students[i].gradeLetter, searchGrade) == 0) {
                    printf("%s (Roll %d) - %.2f%%\n",
                           students[i].fullName, students[i].rollNo, students[i].scorePercent);
                    found = 1;
                }
            }
            if (!found) printf("No matching students.\n");
        }

        else if (choice == 4) break;
        else printf("Invalid choice!\n");
    }

    return 0;
}
