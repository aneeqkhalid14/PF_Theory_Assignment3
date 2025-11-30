#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "members.dat"

typedef struct {
    int id;
    char name[100];
    char batch[30];
    char membership[10];
    char reg_date[20];
    char dob[20];
    char interest[10];
} Student;

Student *db = NULL;
int db_count = 0;

void load_db(const char *fname);
void save_db(const char *fname);
void add_student(Student s, const char *fname);
void update_student(int id);
void delete_student(int id);
void show_all();
int id_exists(int id);
void batch_report(const char *batch, const char *membership);
void clear_input_buffer();
int validate_batch(const char *batch);
int validate_membership(const char *membership);
int validate_interest(const char *interest);
int validate_date(const char *date);

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validate_batch(const char *batch) {
    return (strcmp(batch, "CS") == 0 || strcmp(batch, "SE") == 0 || 
            strcmp(batch, "Cyber Security") == 0 || strcmp(batch, "AI") == 0);
}

int validate_membership(const char *membership) {
    return (strcmp(membership, "IEEE") == 0 || strcmp(membership, "ACM") == 0);
}

int validate_interest(const char *interest) {
    return (strcmp(interest, "IEEE") == 0 || strcmp(interest, "ACM") == 0 || 
            strcmp(interest, "Both") == 0);
}

int validate_date(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    return 1;
}

void load_db(const char *fname) {
    FILE *fp = fopen(fname, "rb");
    if (!fp) {
        db = NULL;
        db_count = 0;
        return;
    }

    int cap = 10;
    db = malloc(cap * sizeof(Student));
    if (!db) {
        fclose(fp);
        db_count = 0;
        return;
    }

    Student temp;
    int cnt = 0;

    while (fread(&temp, sizeof(Student), 1, fp) == 1) {
        if (cnt >= cap) {
            cap *= 2;
            Student *tmp = realloc(db, cap * sizeof(Student));
            if (!tmp) {
                free(db);
                fclose(fp);
                db_count = 0;
                return;
            }
            db = tmp;
        }
        db[cnt++] = temp;
    }

    db_count = cnt;
    fclose(fp);
}

void save_db(const char *fname) {
    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        return;
    }
    fwrite(db, sizeof(Student), db_count, fp);
    fclose(fp);
}

void add_student(Student s, const char *fname) {
    if (id_exists(s.id)) {
        printf("Error: Student ID already exists\n");
        return;
    }

    if (!validate_batch(s.batch)) {
        printf("Error: Batch must be CS, SE, Cyber Security, or AI\n");
        return;
    }

    if (!validate_membership(s.membership)) {
        printf("Error: Membership must be IEEE or ACM\n");
        return;
    }

    if (!validate_interest(s.interest)) {
        printf("Error: Interest must be IEEE, ACM, or Both\n");
        return;
    }

    if (!validate_date(s.reg_date)) {
        printf("Error: Registration date must be in YYYY-MM-DD format\n");
        return;
    }

    if (!validate_date(s.dob)) {
        printf("Error: Date of birth must be in YYYY-MM-DD format\n");
        return;
    }

    if (db_count == 0) {
        db = malloc(sizeof(Student));
    } else {
        Student *tmp = realloc(db, (db_count + 1) * sizeof(Student));
        if (!tmp) {
            return;
        }
        db = tmp;
    }

    db[db_count++] = s;
    save_db(fname);
    printf("Student added successfully!\n");
}

void update_student(int id) {
    for (int i = 0; i < db_count; i++) {
        if (db[i].id == id) {
            char new_batch[30], new_membership[10], new_interest[10];
            
            printf("New batch (CS/SE/Cyber Security/AI): ");
            scanf("%[^\n]", new_batch);
            clear_input_buffer();
            
            printf("New membership (IEEE/ACM): ");
            scanf("%[^\n]", new_membership);
            clear_input_buffer();
            
            printf("New interest (IEEE/ACM/Both): ");
            scanf("%[^\n]", new_interest);
            clear_input_buffer();
            
            if (!validate_batch(new_batch)) {
                printf("Error: Invalid batch\n");
                return;
            }
            if (!validate_membership(new_membership)) {
                printf("Error: Invalid membership\n");
                return;
            }
            if (!validate_interest(new_interest)) {
                printf("Error: Invalid interest\n");
                return;
            }
            
            strcpy(db[i].batch, new_batch);
            strcpy(db[i].membership, new_membership);
            strcpy(db[i].interest, new_interest);
            
            save_db(FILE_NAME);
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Error: Student not found\n");
}

void delete_student(int id) {
    int idx = -1;
    for (int i = 0; i < db_count; i++) {
        if (db[i].id == id) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Error: Student not found\n");
        return;
    }

    for (int i = idx; i < db_count - 1; i++)
        db[i] = db[i + 1];

    db_count--;
    if (db_count > 0) {
        db = realloc(db, db_count * sizeof(Student));
    } else {
        free(db);
        db = NULL;
    }
    save_db(FILE_NAME);
    printf("Student deleted successfully!\n");
}

int id_exists(int id) {
    for (int i = 0; i < db_count; i++)
        if (db[i].id == id) return 1;
    return 0;
}

void show_all() {
    if (db_count == 0) {
        printf("No records found\n");
        return;
    }

    printf("\n%-8s %-20s %-15s %-12s %-12s %-12s %s\n", 
           "ID", "Name", "Batch", "Membership", "Reg Date", "DOB", "Interest");
    printf("-------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < db_count; i++) {
        printf("%-8d %-20s %-15s %-12s %-12s %-12s %s\n",
               db[i].id, db[i].name, db[i].batch,
               db[i].membership, db[i].reg_date,
               db[i].dob, db[i].interest);
    }
}

void batch_report(const char *batch, const char *membership) {
    int found = 0;
    printf("\n--- %s Students (%s) ---\n", batch, membership);
    for (int i = 0; i < db_count; i++) {
        if (strcmp(db[i].batch, batch) == 0 &&
            strcmp(db[i].membership, membership) == 0)
        {
            printf("%d | %s | %s\n", db[i].id, db[i].name, db[i].membership);
            found = 1;
        }
    }
    if (!found) printf("No records found\n");
}

int main() {
    load_db(FILE_NAME);

    int choice;
    while (1) {
        printf("\n=== IEEE/ACM Membership Registration System ===\n");
        printf("1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Registrations\n");
        printf("5. Batch Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        if (choice == 1) {
            Student s;
            printf("\n1) Student ID: ");
            scanf("%d", &s.id);
            clear_input_buffer();
            
            printf("2) Full Name: ");
            scanf("%[^\n]", s.name);
            clear_input_buffer();
            
            printf("3) Batch (CS/SE/Cyber Security/AI): ");
            scanf("%[^\n]", s.batch);
            clear_input_buffer();
            
            printf("4) Membership Type (IEEE/ACM): ");
            scanf("%[^\n]", s.membership);
            clear_input_buffer();
            
            printf("5) Registration Date (YYYY-MM-DD): ");
            scanf("%[^\n]", s.reg_date);
            clear_input_buffer();
            
            printf("6) Date of Birth (YYYY-MM-DD): ");
            scanf("%[^\n]", s.dob);
            clear_input_buffer();
            
            printf("7) Interest in (IEEE/ACM/Both): ");
            scanf("%[^\n]", s.interest);
            clear_input_buffer();
            
            add_student(s, FILE_NAME);
        }
        else if (choice == 2) {
            int id;
            printf("Enter Student ID to update: ");
            scanf("%d", &id);
            clear_input_buffer();
            update_student(id);
        }
        else if (choice == 3) {
            int id;
            printf("Enter Student ID to delete: ");
            scanf("%d", &id);
            clear_input_buffer();
            delete_student(id);
        }
        else if (choice == 4) {
            show_all();
        }
        else if (choice == 5) {
            char batch[30], mem[10];
            printf("Enter Batch: ");
            scanf("%[^\n]", batch);
            clear_input_buffer();
            printf("Enter Membership Type: ");
            scanf("%[^\n]", mem);
            clear_input_buffer();
            batch_report(batch, mem);
        }
        else if (choice == 6) {
            save_db(FILE_NAME);
            if (db) free(db);
            printf("Exiting... Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}