#include <stdio.h>
#include <string.h>

#define LIMIT 200

struct Date {
    int day, month, year;
};

struct Employee {
    int id;
    char name[50];
    char dept[20];
    char role[20];
    float salary;
    struct Date join;
    char phone[20];
    char email[50];
};

int getExperience(struct Date j, struct Date t) {
    int y = t.year - j.year;
    if (t.month < j.month || (t.month == j.month && t.day < j.day))
        y--;
    return y;
}

int rankOf(char r[]) {
    if (!strcmp(r, "Intern")) return 1;
    if (!strcmp(r, "Junior")) return 2;
    if (!strcmp(r, "Senior")) return 3;
    if (!strcmp(r, "Manager")) return 4;
    return 5;
}

void promote(struct Employee *p) {
    int r = rankOf(p->role);
    if (r >= 5) return;

    if (r == 1) strcpy(p->role, "Junior");
    else if (r == 2) strcpy(p->role, "Senior");
    else if (r == 3) strcpy(p->role, "Manager");
    else if (r == 4) strcpy(p->role, "Director");
}

int main() {
    struct Employee list[LIMIT];
    int count = 0, ch;

    struct Date today = {1, 1, 2026};

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Add Employee\n");
        printf("2. View All\n");
        printf("3. Find by Department\n");
        printf("4. Find by Role\n");
        printf("5. Filter by Experience\n");
        printf("6. Salary Stats\n");
        printf("7. Appraisal\n");
        printf("8. Promotions\n");
        printf("9. Exit\n");
        printf("Select: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("ID: ");
            scanf("%d", &list[count].id);

            printf("Name: ");
            scanf("%s", list[count].name);

            printf("Department: ");
            scanf("%s", list[count].dept);

            printf("Role: ");
            scanf("%s", list[count].role);

            printf("Salary: ");
            scanf("%f", &list[count].salary);

            printf("Join Date (d m y): ");
            scanf("%d %d %d",
                  &list[count].join.day,
                  &list[count].join.month,
                  &list[count].join.year);

            printf("Phone: ");
            scanf("%s", list[count].phone);

            printf("Email: ");
            scanf("%s", list[count].email);

            printf("Employee added.\n");
            count++;
        }

        else if (ch == 2) {
            printf("\n---- EMPLOYEES ----\n");
            for (int i = 0; i < count; i++) {
                int exp = getExperience(list[i].join, today);
                printf("\nID: %d\nName: %s\nDept: %s\nRole: %s\nSalary: %.2f\nExp: %d yrs\nContact: %s | %s\n",
                       list[i].id, list[i].name, list[i].dept, list[i].role,
                       list[i].salary, exp, list[i].phone, list[i].email);
            }
        }

        else if (ch == 3) {
            char d[20];
            printf("Enter dept: ");
            scanf("%s", d);

            for (int i = 0; i < count; i++)
                if (!strcmp(list[i].dept, d))
                    printf("%s (ID %d)\n", list[i].name, list[i].id);
        }

        else if (ch == 4) {
            char r[20];
            printf("Enter role: ");
            scanf("%s", r);

            for (int i = 0; i < count; i++)
                if (!strcmp(list[i].role, r))
                    printf("%s (ID %d)\n", list[i].name, list[i].id);
        }

        else if (ch == 5) {
            int ex;
            printf("Minimum experience: ");
            scanf("%d", &ex);

            for (int i = 0; i < count; i++) {
                int calc = getExperience(list[i].join, today);
                if (calc >= ex)
                    printf("%s (ID %d, %d yrs)\n", list[i].name, list[i].id, calc);
            }
        }

        else if (ch == 6) {
            char d[20];
            printf("Dept: ");
            scanf("%s", d);

            float sum = 0;
            int c = 0;

            for (int i = 0; i < count; i++) {
                if (!strcmp(list[i].dept, d)) {
                    sum += list[i].salary;
                    c++;
                }
            }

            if (!c) printf("No data.\n");
            else printf("Total: %.2f\nAverage: %.2f\n", sum, sum / c);
        }

        else if (ch == 7) {
            int id;
            float pct;

            printf("Employee ID: ");
            scanf("%d", &id);

            printf("Percent (5-15): ");
            scanf("%f", &pct);

            for (int i = 0; i < count; i++) {
                if (list[i].id == id) {
                    list[i].salary += list[i].salary * (pct / 100);
                    printf("Updated salary: %.2f\n", list[i].salary);
                }
            }
        }

        else if (ch == 8) {
            for (int i = 0; i < count; i++) {
                int exp = getExperience(list[i].join, today);
                if (exp >= 3) {
                    printf("%s (ID %d) promoted from %s to ",
                           list[i].name, list[i].id, list[i].role);
                    promote(&list[i]);
                    printf("%s\n", list[i].role);
                }
            }
        }

        else if (ch == 9) {
            break;
        }

        else {
            printf("Invalid option!\n");
        }
    }

    return 0;
}
