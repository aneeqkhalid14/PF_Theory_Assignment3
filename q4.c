#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int bookID;
    int score;
    int lastUsed;
} LibraryBook;

int findBookIndex(LibraryBook shelf[], int total, int id) {
    for(int i = 0; i < total; i++) {
        if(shelf[i].bookID == id) return i;
    }
    return -1;
}

int main() {
    int maxBooks, operations;
    scanf("%d %d", &maxBooks, &operations);

    LibraryBook *shelf = (LibraryBook*)malloc(maxBooks * sizeof(LibraryBook));
    int bookCount = 0;
    int currentTime = 0;

    for(int i = 0; i < operations; i++) {
        char command[10];
        scanf("%s", command);

        if(strcmp(command, "ADD") == 0) {
            int id, pop;
            scanf("%d %d", &id, &pop);

            int index = findBookIndex(shelf, bookCount, id);

            if(index != -1) {
                shelf[index].score = pop;
                shelf[index].lastUsed = ++currentTime;
            } else {
                if(bookCount < maxBooks) {
                    shelf[bookCount].bookID = id;
                    shelf[bookCount].score = pop;
                    shelf[bookCount].lastUsed = ++currentTime;
                    bookCount++;
                } else {
                    int lraIndex = 0;
                    for(int j = 1; j < bookCount; j++) {
                        if(shelf[j].lastUsed < shelf[lraIndex].lastUsed) {
                            lraIndex = j;
                        }
                    }
                    shelf[lraIndex].bookID = id;
                    shelf[lraIndex].score = pop;
                    shelf[lraIndex].lastUsed = ++currentTime;
                }
            }

        } else if(strcmp(command, "ACCESS") == 0) {
            int id;
            scanf("%d", &id);
            int idx = findBookIndex(shelf, bookCount, id);
            if(idx != -1) {
                printf("%d\n", shelf[idx].score);
                shelf[idx].lastUsed = ++currentTime;
            } else {
                printf("-1\n");
            }
        }
    }

    free(shelf);
    return 0;
}
