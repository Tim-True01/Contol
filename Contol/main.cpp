#include <iostream>
#include "file.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, ".UTF-8");
    const char* filePath = R"(C:\Users\Тимофей\Desktop\Controlinay.txt)";
    int bookCount;
    Book* books = LoadBooks(filePath, bookCount);
    PrintAllBooks(books, bookCount);
    PrintNabokovBooks(books, bookCount);
    delete[] books;
    return 0;
}