#pragma once
class Book
{
private:
    int* cardNumber;
    char* authorName;
    char* bookTitle;
    double* bookPrice;

public:
    Book();
    Book(int number, const char* author, const char* title, double price);
    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book();
    void PrintInfo() const;
    bool IsNabokov() const;
};

Book* LoadBooks(const char* path, int& bookCount);
void PrintAllBooks(const Book* books, int bookCount);
void PrintNabokovBooks(const Book* books, int bookCount);