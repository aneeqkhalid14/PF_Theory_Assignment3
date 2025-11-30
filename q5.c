#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define startcapacity 2
#define maxlinelength 1024

typedef struct {
    char **lines;
    int count;
    int capacity;
} textbuffer;

textbuffer createbuffer();
void addline(textbuffer *buffer, int position, const char *text);
void removeline(textbuffer *buffer, int position);
void showlines(textbuffer buffer);
void freebuffer(textbuffer buffer);
void shrinkbuffer(textbuffer *buffer);
void savetofile(textbuffer buffer, const char *filename);
void loadfromfile(textbuffer *buffer, const char *filename);

textbuffer createbuffer() {
    textbuffer newbuffer;
    newbuffer.lines = (char**)malloc(startcapacity * sizeof(char*));
    if (!newbuffer.lines) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newbuffer.count = 0;
    newbuffer.capacity = startcapacity;
    return newbuffer;
}

void addline(textbuffer *buffer, int position, const char *text) {
    if (position < 0 || position > buffer->count) return;

    if (buffer->count == buffer->capacity) {
        int newcapacity = buffer->capacity * 2;
        char **temp = (char**)realloc(buffer->lines, newcapacity * sizeof(char*));
        if (!temp) {
            printf("Failed to expand buffer.\n");
            return;
        }
        buffer->lines = temp;
        buffer->capacity = newcapacity;
    }

    for (int i = buffer->count; i > position; i--) {
        buffer->lines[i] = buffer->lines[i-1];
    }

    buffer->lines[position] = (char*)malloc(strlen(text) + 1);
    if (!buffer->lines[position]) {
        printf("Failed to allocate memory for line.\n");
        return;
    }
    strcpy(buffer->lines[position], text);
    buffer->count++;
}

void removeline(textbuffer *buffer, int position) {
    if (position < 0 || position >= buffer->count) return;

    free(buffer->lines[position]);

    for (int i = position; i < buffer->count - 1; i++) {
        buffer->lines[i] = buffer->lines[i+1];
    }
    buffer->count--;
}

void showlines(textbuffer buffer) {
    for (int i = 0; i < buffer.count; i++) {
        printf("%d: %s\n", i, buffer.lines[i]);
    }
}

void freebuffer(textbuffer buffer) {
    for (int i = 0; i < buffer.count; i++) {
        free(buffer.lines[i]);
    }
    free(buffer.lines);
}

void shrinkbuffer(textbuffer *buffer) {
    if (buffer->count == 0) return;
    char **temp = (char**)realloc(buffer->lines, buffer->count * sizeof(char*));
    if (temp) {
        buffer->lines = temp;
        buffer->capacity = buffer->count;
    }
}

void savetofile(textbuffer buffer, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    for (int i = 0; i < buffer.count; i++) {
        fprintf(file, "%s\n", buffer.lines[i]);
    }
    fclose(file);
}

void loadfromfile(textbuffer *buffer, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    for (int i = 0; i < buffer->count; i++) free(buffer->lines[i]);
    buffer->count = 0;

    char line[maxlinelength];
    while (fgets(line, maxlinelength, file)) {
        line[strcspn(line, "\n")] = '\0';
        addline(buffer, buffer->count, line);
    }
    fclose(file);
}

int main() {
    textbuffer mytext = createbuffer();

    addline(&mytext, 0, "Hello world");
    addline(&mytext, 1, "This is a test");
    addline(&mytext, 1, "Inserted line");

    printf("All lines:\n");
    showlines(mytext);

    printf("\nAfter deleting line 1:\n");
    removeline(&mytext, 1);
    showlines(mytext);

    printf("\nShrinking buffer...\n");
    shrinkbuffer(&mytext);

    printf("\nSaving to file...\n");
    savetofile(mytext, "output.txt");

    freebuffer(mytext);
    return 0;
}