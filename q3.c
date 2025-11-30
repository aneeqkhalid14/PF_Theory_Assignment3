#include <stdio.h>
#include <string.h>

struct Employee {
    int empID;
    char empName[50];
    char role[50];
    float salary;
};

void showEmployees(struct Employee staff[], int total) {
    printf("\nID\tName\t\tRole\t\tSalary\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%d\t%-10s\t%-12s\t%.2f\n", staff[i].empID, staff[i].empName, staff[i].role, staff[i].salary);
    }
}

void highestPaid(struct Employee staff[], int total) {
    int idx = 0;
    for (int i = 1; i < total; i++) {
        if (staff[i].salary > staff[idx].salary)
            idx = i;
    }
    printf("\nHighest Salary Employee:\n");
    printf("ID: %d, Name: %s, Role: %s, Salary: %.2f\n", 
           staff[idx].empID, staff[idx].empName, staff[idx].role, staff[idx].salary);
}

void findEmployee(struct Employee staff[], int total) {
    int option;
    printf("\nSearch Employee By:\n1. ID\n2. Name\nChoice: ");
    scanf("%d", &option);

    if(option == 1) {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        for(int i = 0; i < total; i++) {
            if(staff[i].empID == id) {
                printf("\nFound Employee:\nID: %d, Name: %s, Role: %s, Salary: %.2f\n", 
                       staff[i].empID, staff[i].empName, staff[i].role, staff[i].salary);
                return;
            }
        }
        printf("No employee found with ID %d.\n", id);
    } else if(option == 2) {
        char name[50];
        printf("Enter Employee Name: ");
        scanf("%s", name);
        for(int i = 0; i < total; i++) {
            if(strcmp(staff[i].empName, name) == 0) {
                printf("\nFound Employee:\nID: %d, Name: %s, Role: %s, Salary: %.2f\n", 
                       staff[i].empID, staff[i].empName, staff[i].role, staff[i].salary);
                return;
            }
        }
        printf("No employee found with name '%s'.\n", name);
    } else {
        printf("Invalid choice!\n");
    }
}

void applyBonus(struct Employee staff[], int total, float threshold) {
    int count = 0;
    for(int i = 0; i < total; i++) {
        if(staff[i].salary < threshold) {
            staff[i].salary *= 1.10;
            count++;
        }
    }
    printf("\n10%% bonus applied to %d employees earning below %.2f\n", count, threshold);
}

int main() {
    int n;
    printf("How many employees will you enter? ");
    scanf("%d", &n);

    struct Employee staff[n];

    for(int i = 0; i < n; i++) {
        printf("\n--- Employee %d ---\n", i + 1);
        printf("ID: ");
        scanf("%d", &staff[i].empID);
        printf("Name: ");
        scanf("%s", staff[i].empName);
        printf("Role: ");
        scanf("%s", staff[i].role);
        printf("Salary: ");
        scanf("%f", &staff[i].salary);
    }

    printf("\n=== Employee Records ===\n");
    showEmployees(staff, n);

    highestPaid(staff, n);
    findEmployee(staff, n);

    printf("\n--- Salary Review ---\n");
    printf("Applying 10%% bonus to all employees earning less than 50000...\n");
    applyBonus(staff, n, 50000.0);

    printf("\n=== Updated Records ===\n");
    showEmployees(staff, n);

    printf("\nThanks for using ABC Technologies HR System!\n");
    return 0;
}
