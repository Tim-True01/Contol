#include "file.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void CopyString(char* destination, const char* source)
{
    int i = 0;
    while (source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

Book::Book()
{
    cardNumber = new int(0);
    authorName = new char[1] { '\0' };
    bookTitle = new char[1] { '\0' };
    bookPrice = new double(0);
}

Book::Book(int number, const char* author,
    const char* title, double price)
{
    cardNumber = new int(number);
    authorName = new char[strlen(author) + 1];
    CopyString(authorName, author);
    bookTitle = new char[strlen(title) + 1];
    CopyString(bookTitle, title);
    bookPrice = new double(price);
}

Book::Book(const Book& other)
{
    cardNumber = new int(*other.cardNumber);
    authorName = new char[strlen(other.authorName) + 1];
    CopyString(authorName, other.authorName);
    bookTitle = new char[strlen(other.bookTitle) + 1];
    CopyString(bookTitle, other.bookTitle);
    bookPrice = new double(*other.bookPrice);
}

Book& Book::operator=(const Book& other)
{
    if (this != &other)
    {
        int* newNumber = new int(*other.cardNumber);
        char* newAuthor = new char[strlen(other.authorName) + 1];
        char* newTitle = new char[strlen(other.bookTitle) + 1];
        double* newPrice = new double(*other.bookPrice);
        CopyString(newAuthor, other.authorName);
        CopyString(newTitle, other.bookTitle);
        delete cardNumber;
        delete[] authorName;
        delete[] bookTitle;
        delete bookPrice;
        cardNumber = newNumber;
        authorName = newAuthor;
        bookTitle = newTitle;
        bookPrice = newPrice;
    }
    return *this;
}

Book::~Book()
{
    delete cardNumber;
    delete[] authorName;
    delete[] bookTitle;
    delete bookPrice;
}

void Book::PrintInfo() const
{
    cout << "Номер читательского билета: " <<(*cardNumber) << '\n';
    cout << "Автор: " << authorName << '\n';
    cout << "Название: " << bookTitle << '\n';
    cout << "Стоимость: " << *bookPrice << " руб.\n";
    cout << "---------------------------------------\n";
}
bool Book::IsNabokov() const
{
    return strstr(authorName, "Набоков") != nullptr ||
        strstr(authorName, "Nabokov") != nullptr;
}

Book* LoadBooks(const char* path, int& bookCount)
{
    ifstream file(path);
    bookCount = 0;
    int number;
    double price;
    char author[100];
    char title[200];

    while (file >> number)
    {
        file.ignore(1000, '\n');
        file.getline(author, 100);
        file.getline(title, 200);
        file >> price;
        file.ignore(1000, '\n');
        bookCount++;
    }

    file.clear();
    file.seekg(0);

    Book* books = new Book[bookCount];

    for (int i = 0; i < bookCount; i++)
    {
        file >> number;
        file.ignore(1000, '\n');
        file.getline(author, 100);
        file.getline(title, 200);
        file >> price;
        file.ignore(1000, '\n');
        Book currentBook(number, author, title, price);
        books[i] = currentBook;
    }

    file.close();
    return books;
}

void PrintAllBooks(const Book* books, int bookCount)
{
    cout << "\nВсе выданные книги:\n\n";
    for (int i = 0; i < bookCount; i++)
        books[i].PrintInfo();
}

void PrintNabokovBooks(const Book* books, int bookCount)
{
    cout << "\nКниги автора Набокова:\n\n";
    bool found = false;
    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].IsNabokov())
        {
            books[i].PrintInfo();
            found = true;
        }
    }

    if (!found)
        cout << "Книги Набокова не найдены.\n";
}