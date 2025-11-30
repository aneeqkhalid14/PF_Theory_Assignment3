#include <stdio.h>
#include <string.h>

#define LIMIT_TR 50
#define LIMIT_ACC 100

struct LogEntry {
    char dt[20];
    char kind[20];
    float val;
};

struct UserAcc {
    char holder[50];
    int id;
    char cat[20];
    float bal;
    char openDt[20];
    char lastDt[20];
    struct LogEntry logs[LIMIT_TR];
    int logCnt;
};

float minReq(char t[]) {
    if (strcmp(t, "Savings") == 0) return 1000;
    if (strcmp(t, "Current") == 0) return 5000;
    return 10000;
}

float rateOf(char t[]) {
    if (strcmp(t, "Savings") == 0) return 4;
    if (strcmp(t, "Fixed") == 0) return 7;
    return 0;
}

void addLog(struct UserAcc *x, char d[], char k[], float v) {
    int p = x->logCnt;
    strcpy(x->logs[p].dt, d);
    strcpy(x->logs[p].kind, k);
    x->logs[p].val = v;
    x->logCnt++;
    strcpy(x->lastDt, d);
}

void addFunds(struct UserAcc *x, float amt, char d[]) {
    x->bal += amt;
    addLog(x, d, "Deposit", amt);
}

void takeFunds(struct UserAcc *x, float amt, char d[]) {
    float req = minReq(x->cat);
    if (x->bal - amt < req) {
        printf("Cannot withdraw! Minimum balance requirement did not meet.\n");
        return;
    }
    x->bal -= amt;
    addLog(x, d, "Withdrawal", amt);
}

int main() {
    struct UserAcc bank[LIMIT_ACC];
    int total = 0, opt;

    while (1) {
        printf("\n===== BANK MENU =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Show Account Details\n");
        printf("5. Show Transaction History\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &opt);

        if (opt == 1) {
            printf("\nEnter name: ");
            scanf("%s", bank[total].holder);

            printf("Enter account number: ");
            scanf("%d", &bank[total].id);

            printf("Enter type (Savings/Current/Fixed): ");
            scanf("%s", bank[total].cat);

            printf("Enter initial deposit: ");
            scanf("%f", &bank[total].bal);

            printf("Enter creation date: ");
            scanf("%s", bank[total].openDt);

            strcpy(bank[total].lastDt, bank[total].openDt);
            bank[total].logCnt = 0;

            float req = minReq(bank[total].cat);

            if (bank[total].bal < req) {
                printf("Initial deposit must be at least %.2f\n", req);
                continue;
            }

            printf("Account created successfully!\n");
            total++;
        }

        else if (opt == 2) {
            int num, pos = -1;
            float amt;
            char d[20];

            printf("Enter account number: ");
            scanf("%d", &num);

            for (int i = 0; i < total; i++)
                if (bank[i].id == num) pos = i;

            if (pos == -1) {
                printf("Account not found.\n");
                continue;
            }

            printf("Enter deposit amount: ");
            scanf("%f", &amt);

            printf("Enter date: ");
            scanf("%s", d);

            addFunds(&bank[pos], amt, d);
            printf("Deposit successful!\n");
        }

        else if (opt == 3) {
            int num, pos = -1;
            float amt;
            char d[20];

            printf("Enter account number: ");
            scanf("%d", &num);

            for (int i = 0; i < total; i++)
                if (bank[i].id == num) pos = i;

            if (pos == -1) {
                printf("Account not found.\n");
                continue;
            }

            printf("Enter withdrawal amount: ");
            scanf("%f", &amt);

            printf("Enter date: ");
            scanf("%s", d);

            takeFunds(&bank[pos], amt, d);
        }

        else if (opt == 4) {
            int num, pos = -1;
            printf("Enter account number: ");
            scanf("%d", &num);

            for (int i = 0; i < total; i++)
                if (bank[i].id == num) pos = i;

            if (pos == -1) {
                printf("Account not found.\n");
                continue;
            }

            struct UserAcc u = bank[pos];
            printf("\n===== ACCOUNT DETAILS =====\n");
            printf("Name: %s\n", u.holder);
            printf("Acc No: %d\n", u.id);
            printf("Type: %s\n", u.cat);
            printf("Balance: %.2f\n", u.bal);
            printf("Interest Rate: %.2f%%\n", rateOf(u.cat));
            printf("Created On: %s\n", u.openDt);
            printf("Last Transaction: %s\n", u.lastDt);
        }

        else if (opt == 5) {
            int num, pos = -1;
            printf("Enter account number: ");
            scanf("%d", &num);

            for (int i = 0; i < total; i++)
                if (bank[i].id == num) pos = i;

            if (pos == -1) {
                printf("Account not found.\n");
                continue;
            }

            struct UserAcc *u = &bank[pos];

            printf("\n===== TRANSACTION HISTORY =====\n");
            for (int i = 0; i < u->logCnt; i++) {
                printf("%s - %s: %.2f\n",
                       u->logs[i].dt,
                       u->logs[i].kind,
                       u->logs[i].val);
            }
        }

        else if (opt == 6) {
            break;
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
