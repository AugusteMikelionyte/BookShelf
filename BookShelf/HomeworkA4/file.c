#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//define failo varda
//unit testai
typedef struct Book {
    char *bookAuthor;
    char *bookName;
    int pages;
    int year;
} Book;

typedef struct BookShelf{
    int capacity;
    Book *books;
}BookShelf;

void loadFromFile(BookShelf *bookshelf){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("test.bin", "rb");
    if (fp == NULL){
        printf("No file found\n");
        return;
    }
    if (NULL != fp) {
        fseek (fp, 0, SEEK_END);
        long size = ftell(fp);
        if (0 == size) {
            fclose(fp);
            return;
        }
        rewind(fp);
    }
    int i=0;
    while ((read = getline(&line, &len, fp)) != -1) {
        struct Book newBook;
        if(i==0){
            newBook.bookAuthor = malloc(20*(sizeof(char)));
            strcpy(newBook.bookAuthor, line);
            strtok(newBook.bookAuthor, "\n");
        }
        else if(i==1){
            newBook.bookName = malloc(20*(sizeof(char)));
            strcpy(newBook.bookName, line);
            strtok(newBook.bookName, "\n");
        }
        else if(i==2){
            newBook.pages = atoi(line);
        }
        else if(i==3){
            newBook.year = atoi(line);
        }
        i++;
        if(i == 4){
            addBookToShelf(bookshelf, newBook);
            i = 0;
        }
//free 
    }

    fclose(fp);
    if (line)
        free(line);
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
void saveToFile2(BookShelf *bookshelf){
    FILE *fp;
    fp = fopen("test.bin", "wb");
    if (fp == NULL) { //fwrite i binarini vietoj printf, skaitymui - fread
        printf("Failed to open file");
        return;
    }
    for(int i = 0; i < bookshelf->capacity; i++){
        fputs((const char *)concat(bookshelf->books[i].bookAuthor, "\n"),fp);
        fputs((const char *)concat(bookshelf->books[i].bookName, "\n"),fp);
        fprintf(fp, "%d\n", bookshelf->books[i].pages);
        fprintf(fp, "%d\n", bookshelf->books[i].year);
    }
    fclose(fp);
}

