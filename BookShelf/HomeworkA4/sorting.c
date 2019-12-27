//
//  sorting.c
//  Namu Darbas A4
//
//  Created by Auguste Mikelionyte on 15/12/2019.
//  Copyright © 2019 Auguste Mikelionyte. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "file.h"
#include "sorting.h"

void sortBooks(BookShelf *bookshelf){
    
    printf("    1) Sort by Author (A-Z)\n");
    printf("    2) Sort by title (A-Z)\n");
    printf("    3) Sort by pages\n");
    printf("    4) Sort by year\n");
    
    printf("    Please enter your choice of sorting:\n");
    
    int sortingType;
    scanf("%d", &sortingType);
    
    if(sortingType == 1){
        printf("    You chose to sort books by author's name:\n");
        sortbyAuthor(bookshelf);
    }
    else if(sortingType == 2){
        printf("    You chose to sort books by book's title:\n");
        sortbyName(bookshelf);
    }
    else if(sortingType == 3){
        printf("    You chose to sort books by pages:\n");
        sortbyPages(bookshelf);
    }
    else if(sortingType == 4){
        printf("    You chose to sort books by years:\n");
        sortbyYears(bookshelf);
    }
}

void sortbyAuthor(BookShelf *bookshelf){
    int i, j;
    char temp[25];
    int temp1, temp2;
    for(i=0;i < bookshelf->capacity; i++){
        for(j=i+1;j < bookshelf -> capacity - 1;j++){
            if(strcmp(bookshelf->books[i].bookAuthor, bookshelf->books[j].bookAuthor)>0){
                strcpy(temp, bookshelf->books[i].bookAuthor);
                strcpy(bookshelf->books[i].bookAuthor,bookshelf->books[j].bookAuthor);
                strcpy(bookshelf->books[j].bookAuthor,temp);
                strcpy(temp, bookshelf->books[i].bookName);
                strcpy(bookshelf->books[i].bookName,bookshelf->books[j].bookName);
                strcpy(bookshelf->books[j].bookName,temp);
                temp1 = bookshelf->books[j+1].pages;
                bookshelf->books[j+1].pages = bookshelf->books[j].pages;
                bookshelf->books[j].pages = temp1;
                temp2 = bookshelf->books[j+1].year;
                bookshelf->books[j+1].year = bookshelf->books[j].year;
                bookshelf->books[j].year = temp2;
            }
        }
    }
    printBookShelf(bookshelf);
}

void sortbyName(BookShelf *bookshelf){
    int i, j;
    char temp[25];
    int temp1, temp2;
    for(i=0;i < bookshelf->capacity; i++){
        for(j=i+1;j < bookshelf -> capacity - 1;j++){
            if(strcmp(bookshelf->books[i].bookName, bookshelf->books[j].bookName) >0){
                strcpy(temp, bookshelf->books[i].bookAuthor);
                strcpy(bookshelf->books[i].bookAuthor,bookshelf->books[j].bookAuthor);
                strcpy(bookshelf->books[j].bookAuthor,temp);
                strcpy(temp, bookshelf->books[i].bookName);
                strcpy(bookshelf->books[i].bookName,bookshelf->books[j].bookName);
                strcpy(bookshelf->books[j].bookName,temp);
                temp1 = bookshelf->books[j+1].pages;
                bookshelf->books[j+1].pages = bookshelf->books[j].pages;
                bookshelf->books[j].pages = temp1;
                temp2 = bookshelf->books[j+1].year;
                bookshelf->books[j+1].year = bookshelf->books[j].year;
                bookshelf->books[j].year = temp2;
            }
        }
    }
    printBookShelf(bookshelf);
}

void sortbyPages(BookShelf *bookshelf){
    int i, j;
    for (i = 0; i < bookshelf->capacity; i++){
        for (j = 0; j < bookshelf->capacity - 1; j++){
            if (bookshelf->books[j].pages > bookshelf->books[j+1].pages){
                Book temp = bookshelf->books[j+1];
                bookshelf->books[j+1] = bookshelf->books[j];
                bookshelf->books[j] = temp;
            }
        }
    }
    printBookShelf(bookshelf);
}

void sortbyYears(BookShelf *bookshelf){
    int i, j;
    for (i = 0; i < bookshelf->capacity; i++){
        for (j = 0; j < bookshelf->capacity - 1; j++){
            if (bookshelf->books[j].year > bookshelf->books[j+1].year){
                Book temp = bookshelf->books[j+1];
                bookshelf->books[j+1] = bookshelf->books[j];
                bookshelf->books[j] = temp;
            }
        }
    }
    printBookShelf(bookshelf);
}
