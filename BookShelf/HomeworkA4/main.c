//
//  main.c
//  HomeworkA4
//
//  Created by Auguste Mikelionyte on 01/12/2019.
//  Copyright � 2019 Auguste Mikelionyte. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "file.h"
#include "sorting.h"
#include "constants.h"


time_t start, end;
char *LOG_FILE = "/Users/augustemikelionyte/Desktop/HomeworkA4/HomeworkA4/log.txt";

int showMenu();
void initBookShelf(struct BookShelf *bookshelf);


void addBookToShelf(BookShelf *bookshelf, Book book);
Book createBook();
char *getAndValidateBookName();
char *getAndValidateAuthor();
int getAndValidateBookYear();
int getAndValidateNumberOfPages();

char *getAndValidateAuthor2();

void printBookShelf(BookShelf *bookshelf);

void deleteBookorBookshelf(BookShelf *bookshelf);

void editBookInfo(BookShelf *bookshelf);

void findBooks(BookShelf *bookshelf);
void findbyAuthor(BookShelf *bookshelf);
void findbyName(BookShelf *bookshelf);
void findbyPages(BookShelf *bookshelf);
void findbyYears(BookShelf *bookshelf);

void saveToFile(BookShelf *bookshelf);
void logFileCloses();
void logFileOpens();

int main(){
    
    printf("\n\tWelcome to program -Bookshelf-\t\n\n");
    BookShelf bookShelf;
    initBookShelf(&bookShelf);
    loadFromFile(&bookShelf);
    logFileOpens();
    atexit(logFileCloses);
    while(1){
        int choice = showMenu();
        if(choice == 7){
            printf("You chose : 7)Exit the program\n");
            break;
        }
        else{
            switch(choice)
            {
                case 1:
                    printf("\n    You chose: 1)Add a new book \n");
                    addBookToShelf(&bookShelf, createBook());
                    break;
                case 2:
                    printf("\n    You chose: 2)View added books list \n");
                    printf("\n");
                    printBookShelf(&bookShelf);
                    printf("\n");
                    break;
                case 3:
                    printf("\n    You chose: 3)Delete a book from the list \n");
                    deleteBookorBookshelf(&bookShelf);
                    break;
                case 4:
                    printf("\n    You chose: 4)Edit book`s info \n");
                    editBookInfo(&bookShelf);
                    break;
                case 5:
                    printf("\n    You chose: 5)Sort books \n");
                    sortBooks(&bookShelf);
                    break;
                case 6:
                    printf("\n    You chose: 6)Find books \n");
                    findBooks(&bookShelf);
                    break;
                default:
                    printf("\n    Your choice was invalid\n");
                    break;
            }
        }
    }
    saveToFile(&bookShelf);
    
    
    return 0;
}

void logFileOpens(){
    
    FILE *log = fopen(LOG_FILE, "a");
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    fprintf(log, "Program opened: %s", asctime(info));
    
    start = time(NULL);
    fclose(log);
}

void logFileCloses(){
    
    FILE *log = fopen(LOG_FILE, "a");
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    fprintf(log, "Program closed: %s", asctime(info));
    
    end = time(NULL);
    fprintf(log, "Time taken:  %.2f seconds\n",
            difftime(end, start));
    
    fclose(log);
}

int showMenu(){
    int choice;
    printf("1)Add a new book\n");
    printf("2)View added books list\n");
    printf("3)Delete a book from the list\n");
    printf("4)Edit book`s info\n");
    printf("5)Sort books\n");
    printf("6)Find Books\n");
    printf("7)Exit the program\n");
    while(1){
        printf("\nEnter your option :");
        if(scanf("%d", &choice) == 1 && getchar() == '\n'){
            while(choice > 7 && choice < 1){
                printf("Invalid choice\n");
                continue;
            }
            if(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7){
                break;
            }
        }
        else{
            while(getchar() != '\n')
                ;
        }
        
    }
    return choice;
}

void editBookInfo(BookShelf *bookshelf){
    printBookShelf(bookshelf);
    printf("    Please enter number of book you wish to edit:\n");
    int choice;
    scanf("%d", &choice);
    
    printf("    You chose to edit book number %d\n", choice);
    choice = choice - 1;
    printf("    1) Change Author\n");
    printf("    2) Change Book title\n");
    printf("    3) Change Book pages\n");
    printf("    4) Change Book year\n");
    int propertyToChange;
    scanf("%d", &propertyToChange);
    
    printf("    You chose to edit property number %d\n", propertyToChange);
    
    if(propertyToChange == 1){
        bookshelf->books[choice].bookAuthor = getAndValidateAuthor();
    }
    else if(propertyToChange == 2){
        bookshelf->books[choice].bookName = getAndValidateBookName();
    }
    else if(propertyToChange == 3){
        bookshelf->books[choice].pages = getAndValidateNumberOfPages();
    }
    else if(propertyToChange == 4){
        bookshelf->books[choice].year = getAndValidateBookYear();
    }
}

char *getAndValidateAuthor(){
    char *bookAuthor = malloc(MAX_AUTHOR_NAME*sizeof(char));
    while(1){
        char *p;
        printf("\nPlease enter the author: \n");
        if(fgets(bookAuthor, 20, stdin)){
            if( isupper(*bookAuthor)){
                if ((p = strchr(bookAuthor, '\n')) != NULL){
                    *p = '\0';
                }
                assert(bookAuthor != "");
                //assert(bookAuthor < "");
                return bookAuthor;
            }
            else{
                while(getchar() != '\n')
                    ;
            }
        }
    }
}

char *getAndValidateBookName(){
    char *bookName = malloc(MAX_BOOK_TITLE*sizeof(char));
    char *p;
    while(1){
        printf("Please enter the book title: \n");
        
        if(fgets(bookName, 20, stdin)){
            if( isupper(*bookName)){
                if ((p = strchr(bookName, '\n')) != NULL){
                    *p = '\0';
                }
                assert(bookName != "");
                return bookName;
            }
            else{
                while(getchar() != '\n')
                    ;
            }
        }
    }
}

Book createBook(){
    struct Book newBook;
    newBook.bookAuthor = getAndValidateAuthor();
    newBook.bookName = getAndValidateBookName();
    newBook.pages = getAndValidateNumberOfPages();
    newBook.year = getAndValidateBookYear();
    return newBook;
}

void addBookToShelf(BookShelf *bookshelf, Book book){
    if(bookshelf->capacity == 0){
        bookshelf->books = malloc(sizeof(Book));
        if(bookshelf->books == NULL){
            printf("Memory allocation failed");
            return;
        }
        bookshelf->capacity = bookshelf->capacity+1;
        bookshelf->books[0]=book;
    }
    else{
        bookshelf->books = realloc(bookshelf->books, sizeof(Book)*bookshelf->capacity+sizeof(Book));
        if(bookshelf->books == NULL){
            printf("Memory allocation failed");
            return;
        }
        bookshelf->capacity=bookshelf->capacity+1;
        bookshelf->books[bookshelf->capacity-1]= book;
    }
    assert(bookshelf->capacity > 0);
}

void printBookShelf(BookShelf *bookshelf){
    
    for(int i = 0; i < bookshelf->capacity; i++){
        printf(" %d - Author: %s, Book title: %s, Book pages: %d, Book year: %d\n",
               (i+1),
               bookshelf->books[i].bookAuthor, bookshelf->books[i].bookName,
               bookshelf->books[i].pages, bookshelf->books[i].year);
    }
}

void initBookShelf(struct BookShelf *bookshelf){
    bookshelf->capacity = 0;
    bookshelf->books = NULL;
}

int getAndValidateNumberOfPages(){
    int numberPages;
    while(1){
        printf("Enter number of pages: \n");
        if(scanf("%d", &numberPages) == 1 && getchar() == '\n'){
            if(numberPages > 0)
                return numberPages;
        }
        else{
            while(getchar() != '\n')
                ;
        }
    }
}

int getAndValidateBookYear(){
    int bookYear;
    while(1)
    {
        printf("Enter the year of publication: \n");
        if(scanf("%d", &bookYear) == 1 && getchar() == '\n')
        {
            if(bookYear >= 868 && bookYear < 2020)
                return bookYear;
        }
        else
        {
            while(getchar() != '\n')
                ;
        }
    }
    
}

void deleteBookorBookshelf(BookShelf *bookshelf){
    int choice;
    printf("Please enter 1 to delete one book or enter 2 to delete all bookshelf:\n");
    scanf("%d", &choice);
    
    if(choice == 1){
        int position;
        printf("Enter the number of the book that you wish to delete:\n");
        scanf("%d", &position);
        
        if (position >= bookshelf->capacity + 1)
            printf("Deletion not possible.\n");
        else{
            int i = 0;
            for (i = position - 1; i < bookshelf->capacity-1; ++i){
                bookshelf->books[i] = bookshelf->books[i+1];
            }
            bookshelf->capacity = bookshelf->capacity-1;
            printf("Resultant bookshelf:\n");
            printBookShelf(bookshelf);
        }
    }
    else if(choice == 2){
        free(bookshelf->books);
        initBookShelf(bookshelf);
        printf("The list is empty now.\n");
    }
}


void findBooks(BookShelf *bookshelf){
    
    printf("    1) Find by Author ()\n");
    printf("    2) Find by title ()\n");
    printf("    3) Find by pages\n");
    printf("    4) Find by year\n");
    
    printf("    Please enter your choice:\n");
    
    int findingType;
    scanf("%d", &findingType);
    
    if(findingType == 1){
        printf("    You chose to find books by author (starts with vowel):\n");
        findbyAuthor(bookshelf);
    }
    else if(findingType == 2){
        printf("    You chose to find books by name (starts with vowel):\n");
        findbyName(bookshelf);
    }
    else if(findingType == 3){
        printf("    You chose to find books which has less than 500 pages:\n");
        findbyPages(bookshelf);
    }
    else if(findingType == 4){
        printf("    You chose to find books which were published later than 2000:\n");
        findbyYears(bookshelf);
    }
}

void findbyAuthor(BookShelf *bookshelf){
    
    for(int i = 0; i < bookshelf->capacity; i++){
        if (bookshelf->books[i].bookAuthor[0] == 'A' || bookshelf->books[i].bookAuthor[0] == 'E' || bookshelf->books[i].bookAuthor[0] == 'I' || bookshelf->books[i].bookAuthor[0] == 'U' || bookshelf->books[i].bookAuthor[0] == 'O'){
            printf(" %d - Author: %s, Book title: %s, Book pages: %d, Book year: %d\n",
                   (i+1),
                   bookshelf->books[i].bookAuthor, bookshelf->books[i].bookName,
                   bookshelf->books[i].pages, bookshelf->books[i].year);
        }
    }
}

void findbyName(BookShelf *bookshelf){
    
    for(int i = 0; i < bookshelf->capacity; i++){
        if (bookshelf->books[i].bookName[0] == 'A' || bookshelf->books[i].bookName[0] == 'E' || bookshelf->books[i].bookName[0] == 'I' || bookshelf->books[i].bookName[0] == 'U' || bookshelf->books[i].bookName[0] == 'O'){
            printf(" %d - Author: %s, Book title: %s, Book pages: %d, Book year: %d\n",
                   (i+1),
                   bookshelf->books[i].bookAuthor, bookshelf->books[i].bookName,
                   bookshelf->books[i].pages, bookshelf->books[i].year);
        }
    }
}


void findbyPages(BookShelf *bookshelf){
    for(int i = 0; i < bookshelf->capacity; i++){
        if (bookshelf->books[i].pages < 500){
            printf(" %d - Author: %s, Book title: %s, Book pages: %d, Book year: %d\n",
                   (i+1),
                   bookshelf->books[i].bookAuthor, bookshelf->books[i].bookName,
                   bookshelf->books[i].pages, bookshelf->books[i].year);
        }
    }
}

void findbyYears(BookShelf *bookshelf){
    for(int i = 0; i < bookshelf->capacity; i++){
        if (bookshelf->books[i].year > 2000){
            printf(" %d - Author: %s, Book title: %s, Book pages: %d, Book year: %d\n",
                   (i+1),
                   bookshelf->books[i].bookAuthor, bookshelf->books[i].bookName,
                   bookshelf->books[i].pages, bookshelf->books[i].year);
        }
    }
}


void saveToFile(BookShelf *bookshelf){
    FILE *fp;
    fp = fopen("test.bin", "wb");
    if (fp == NULL) {
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


