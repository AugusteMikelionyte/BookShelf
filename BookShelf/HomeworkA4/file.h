#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

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

void loadFromFile(BookShelf *bookshelf);
void saveToFile2(BookShelf *bookshelf);
char* concat(const char *s1, const char *s2);

#endif // FILE_H_INCLUDED
