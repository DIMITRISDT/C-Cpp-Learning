#include <stdio.h>      //Used for main command
#include <stdlib.h>     //Memory management + system("cls")
#include <string.h>     //Used for str commands
#include <stdbool.h>    //Used for boolean type commands
#include <ctype.h>      //Used for toLoweCase function

typedef struct{             //Struct Creation
    char title[50];         //title
    char author[30];        //author
    int year;               //year
    int availStatus;        //Available status
    char availability[50];  //Available status translated
} book;

//Function pre-declaration
void bookDisplay(int i, book *Books);
void availabilityChange(int bookN, book *ptr);
void filterBy(int bookN, book *ptr);
void searchBook(int bookN, book *ptr);

void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main(){
    int bookN; // number of books
    do {
        printf("How many books do you want to input (5+ Books needed): ");
        scanf("%d", &bookN);
        getchar();      // Removes '\n' introduced from the previous scanf
    } while (bookN < 2);

    book Books[bookN]; //   creation of an array struct
    book *ptr = Books; //   Pass the array struct to a pointer

    for(int i = 0; i < bookN; i++){
        printf("Book's %d title: ", i + 1);
        fgets(ptr[i].title, 50, stdin);
        ptr[i].title[strcspn(ptr[i].title, "\n")] = '\0';       // Removes '\n'

        printf("Book's %d author: ", i + 1);
        fgets(ptr[i].author, 50, stdin);
        ptr[i].author[strcspn(ptr[i].author, "\n")] = '\0';     // Removes '\n'

        printf("Book's %d year: ", i + 1);
        scanf("%d", &ptr[i].year);
        getchar();

        do {
            printf("Book's %d availability (0 = Not available or 1 = Available): ", i + 1);
            scanf("%d", &ptr[i].availStatus);
            getchar();
        }while(ptr[i].availStatus != 0 && ptr[i].availStatus != 1);

        //calculation for availability
        if (ptr[i].availStatus == 0){
            strcpy(ptr[i].availability, "Not available for purchase");
        }
        else{
            strcpy(ptr[i].availability, "Available for purchase");
        }
    }
    
    printf("\n"); //space

    //menu 
    int menuChoice;
    do {
        printf("1. Display of all the books\n");
        printf("2. Search for a book\n");
        printf("3. Change the availability\n");
        printf("4. Filter by year or author\n");
        printf("5. Exit\n\n");
        printf("Type your answer : ");
        scanf("%d", &menuChoice);
        getchar();
        switch(menuChoice) {
            case 1:
                printf("\n------[ All Book Display ] ------\n");
                for (int i = 0; i < bookN; i++){
                    bookDisplay(i, ptr);
                }
                break;
            case 2:
                searchBook(bookN, ptr);
                break;
            case 3:
                availabilityChange(bookN, ptr);
                break;
            case 4:
                filterBy(bookN, ptr);
                break;
            case 5:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice, try again\n");
        } 
    } while(menuChoice != 5);
}

//Display book 'X
void bookDisplay(int i, book *Books){
    printf(" \n------ Book %d ------\n", i + 1);
    printf("Title           : %s, \n", Books[i].title);
    printf("Author          : %s, \n", Books[i].author);
    printf("Year            : %d, \n", Books[i].year );
    printf("Availability    : %s\n\n", Books[i].availability);
}

//Change availability
void availabilityChange(int bookN, book *ptr){
    char compareTitle[50];
        printf("Which book are you searching for? : ");
        fgets(compareTitle, 50, stdin);
        compareTitle[strcspn(compareTitle, "\n")] = '\0';
        bool found = false;
        for (int i = 0; i < bookN; i++){
            if (strcmp(compareTitle, ptr[i].title) == 0) {
                bookDisplay(i, ptr);
                found = true;   //this means the book has been found
                printf("\n"); 
                if(ptr[i].availStatus == 1) {
                    char yes_no[4];
                    do{
                        printf("Do you want to borrow this book? : ");
                        fgets(yes_no, 4, stdin);
                        toLowerCase(yes_no);

                    }while (strcmp(yes_no, "yes") != 0 && strcmp(yes_no, "no") != 0);
                    //calculation User's answer.
                    if(strcmp(yes_no, "yes") == 0) {
                        ptr[i].availStatus = 0;
                        strcpy(ptr[i].availability, "Not available");
                        printf("The book is borrowed.\n\n");
                    }
                    else {
                        printf("You cancelled the borrowing.\n");
                    }
                }
                else {
                    printf("The book is not available right now.\n\n");
                }

            }
        }
        if (found == false){
            printf("Book has not been found\n\n");
        } 
}

//Search by year and by author
void filterBy(int bookN, book *ptr) {
    int filterChoice;
    printf("Filter by\n");
    printf("    1. By year\n");
    printf("    2. By author\n");

    do{ //Validity check for filtering
        printf("Choice: ");
        scanf("%d", &filterChoice);
        getchar();
    } while (filterChoice < 1 || filterChoice > 2);

    switch (filterChoice) //Filter switch
    {
    case 1: //search by year
        int filterYear;
        bool yearFound = false;
        printf("Enter the book of the year you are searching for : ");
        scanf("%d", &filterYear);
        getchar();
        printf("Books published in %d\n", filterYear);
        for (int i = 0; i < bookN; i++){
        if (filterYear == ptr[i].year){
                printf("\n%d. %s\n\n", i+1, ptr[i].title);
                yearFound = true;
            }
        }

        if (yearFound == false){
            printf("No books have been published that year.\n");
        }

        break;
    case 2: //search by author
        char filterAuthor[30];
        bool authorFound = false;
        printf("Enter the author of the book you are searching for : ");
        fgets(filterAuthor, 30, stdin);
        filterAuthor[strcspn(filterAuthor, "\n")] = '\0';
        for (int i = 0; i < bookN; i++){
            if (strcmp(filterAuthor, ptr[i].author) == 0){
                printf("%d. %s\n", i + 1, ptr[i].title);
                authorFound = true;
            }
        }

        if (authorFound == false){
            printf("The author was not found\n");
        }

        break;
    default:
        printf("Invalid option, try again\n"); 
    }
}

//Search book function
void searchBook(int bookN, book *ptr){
    char compareTitle[50];
    printf("Which book are you searching for? : ");
    fgets(compareTitle, 50, stdin);
    compareTitle[strcspn(compareTitle, "\n")] = '\0';
    bool found = false;
    for (int i = 0; i < bookN; i++){
        if (strcmp(compareTitle, ptr[i].title) == 0){
            printf("[This book has been successfully found!]\n\n");
            bookDisplay(i, ptr);
            found = true;
        }
    } if (found == false){
        printf("This book was not found\n");
    }
}
