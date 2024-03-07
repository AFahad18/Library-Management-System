#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void Password();
void password();
void Administrator();
void Menu1();
void students_section();
void Menu();
void AddBooks();
void ViewBooks();
void SearchBooks();
void Writer_Books();
void EditBooks();
void RemoveBooks();
void Highest_Price_Book();
void IssueBooks();
void issuebook();
void view_issue_book();
void search_issued_book();
void remove_issued_book();
int date_time(void);

////ftell()is used to find out current file position pointer in the file and to starting of the file.
//rewind() sets the file position to the beginning of the file.
//fseek() function is used to move file pointer position to the given location.

///Global variable
///Structure

typedef struct
{
    int dd, mm, yy;
} Date;
struct Books
{
    int id;
    char s_name[33];
    char b_name[33];
    char writer[33];
    int quantity;
    float price;
    Date iss;
    Date duedate;
};

struct Books book;

FILE *fp, *fp1, *fp2;

int i = 1;
char ch;

int main()
{
    system("TITLE Library Management");
    Password();
}

void Menu()
{
    system("cls");
    int j;
    char show[13] = "Main Menu";
    printf("\n\n\n\t\t");
    for (j = 0; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf(" ");
    for (j = 0; j <= 9; j++)
    {
        Sleep(10);
        printf("%c", show[j]);
    }
    for (j = 0; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf("\n\n\t\t 1. Administrator Section");
    printf("\n\t\t 2. Students Section");
    printf("\n\t\t 3. Exit");
    printf("\n\n\t\t");
    for (j = 0; j <= 48; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf("\n\t\t ");
    date_time();
    printf("\n\n\t\tEnter Your Choice: ");
    //scanf("%d", &n);
    switch (getch())
    {
    case '1':
        Administrator();
        break;
    case'2':
        students_section();
        break;
    case '3':
        system("cls");
        printf("\n\n\t\t************************************************\n");
        printf("\t\t*********** Library Management System **********\n");
        printf("\t\t************************************************\n");
        printf("\n\n\t\tThe Project is made by- \n\n");
        printf("\t\t\t\tABU BAKAR FAHAD.\n\n");
        printf("\t\t\t\tMITHILA FARJANA.\n\n");
        printf("\t\t\t\tSADIA ISLAM.\n\n");
        printf("\t\t************************************************\n");
        printf("\t\t******** UNITED INTERNATIONAL UNIVERSITY *******\n");
        printf("\t\t************************************************\n");
        printf("\t\t");
        date_time();
        printf("\t\t\tThe program is exiting in 5 second...........\n");
        Sleep(5000);
        exit(0); ///Exit Successful

    default:
        printf("\n\n\t\t\aIncorrect Choice!\n");
        printf("\t\t\tPress any key to try again.....");
        getch();
        Menu();
        break;
    }
}

void AddBooks()
{
    system("cls");
    int n, flag = 0;

    char ch;
    printf("\n\n\t\t***************** Add Books *****************\n\n");

    printf("\n\n\t\t 1.To Add Book's\n\t\t 2.Return Administrator Section\n\t\t 3.Go to Main Menu\n\n");
    printf("\t\t Enter Your Choice: ");

    switch (getch())
    {
    case '1':
        system("cls");
        fp = fopen("info.dat", "rb+"); ///here info.dat is a binary file.

        if (fp == NULL)
        {
            fp = fopen("info.dat", "wb");
            fclose(fp);
            fp = fopen("info.dat", "rb+");
        }
        printf("\n\n\t\t Enter ID: ");
        scanf("%d", &n);
        fseek(fp, 0, 0); /*It will move the cursor to the beginning
                        of the file or we can use rewind(fp)*/
        //Check id is available or not
        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            /*It will read 1 by 1 line from File.If it
            didn't found any line it will be 0.
            For this the condition will be false.*/
            if (n == book.id)
            {
                printf("\n\n\t\t\a This book is already in Library.");
                flag = 1;
                Sleep(500);
                printf("\n\t\t Add any more books?(Y / N): ");
                ch = getch();
                if (ch >= 'a' && ch <= 'z')
                {
                    ch = ch - 32;
                }
                if (ch == 'Y')
                {
                    AddBooks();
                }
                else
                {
                    AddBooks();
                }
            }
        }
        if (flag == 1)
        {
            getch();
            system("cls");
            AddBooks();
        }

        book.id = n;

        printf("\n\t\t Enter Book Name: ");
        getchar();
        scanf("%[^\n]", book.b_name);

        printf("\t\t Enter Writer Name: ");
        getchar();
        scanf("%[^\n]", book.writer);

        printf("\t\t Enter Quantity: ");
        scanf("%d", &book.quantity);

        printf("\t\t Enter Price: ");
        scanf("%f", &book.price);

        fseek(fp, 0, 2);                    //We can use SEEK_END alternative of 2.
        fwrite(&book, sizeof(book), 1, fp); //It will write 1 by 1 line from File.
        fclose(fp);

        printf("\n\n\t\t Successfully Add Book's...\n");
        Sleep(500);
        printf("\n\t\t Add any more books?(Y / N): ");
        ch = getch();
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - 32;
        }
        if (ch == 'Y')
        {
            AddBooks();
        }
        else
        {
            AddBooks();
        }
        break;
    case '2':
        Menu1();
        break;
    case '3':
        Menu();
        break;
    default:
        printf("\n\n\t\t\a Wrong Choice.\n\n");
        printf("\t\t\a Press any key to try again.....");
        getch();
        AddBooks();
    }
}

void ViewBooks()
{
    system("cls");
    int total = 0;
    printf("\n\n\t\t\t******************************************");
    printf("\n\t\t\t************* View Book List *************\n");
    printf("\t\t\t******************************************\n\n");
    printf("   ID\t\tBook Name\t\tWriter\t\tQuantity\t Price\n");

    fp = fopen("info.dat", "rb+");
    if (fp == NULL)
    {
        LibraryNULL:
        // Library NULL
        printf("\n\n\t\t\a There is no Books in Library.");
        printf("\n\t\t   Press any key to go to Student section....");
        getchar();
        students_section();
    }
    fread(&book, sizeof(book), 1, fp);
    if (strlen(book.b_name) == 0)
        goto LibraryNULL;

    rewind(fp);
    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        printf("\n   %-13d", book.id);
        printf("%-24s", book.b_name);
        printf("%-18s", book.writer);
        printf("%-15d", book.quantity);
        printf("%.3f", book.price);
        total += book.quantity;
    }
    fclose(fp);
    printf("\n\n\t\t\t\tTotal Books: %d", total);
    printf("\n\n\t\tPress Any key to go to Main Menu......");
    getchar();
    students_section();
}

void SearchBooks()
{
    system("cls");
    int n, flag = 0;
    char ch, str[33] = "";
    printf("\n\n\t\t***************** Search Book *****************\n\n");
    fp = fopen("info.dat", "rb");
    if (fp == NULL)
    {
        SearchBooksNULL:
        // Search Book NULL
        printf("\n\n\t\t\a There is no Books in Library.");
        printf("\n\t\t   Press any key to go to Student section....");
        getchar();
        students_section();
    }
    fread(&book, sizeof(book), 1, fp);
    if (strlen(book.b_name) == 0)
        goto SearchBooksNULL;

    rewind(fp);
    printf("\n\n\t\t 1.Search By ID\n\t\t 2.Search By Book Name\n\t\t 3.Student's Section\n");
    printf("\n\t\t Enter Your Choice: ");
    switch (getch())
    {
    case '1':
    {
        system("cls");
        printf("\n\n\t\t Enter Book ID: ");
        scanf("%d", &n);

        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (n == book.id)
            {
                printf("\n\n\n\t\t\tBook Is Found. \n\n");
                printf("\t\t ID: %d\n", book.id);
                printf("\t\t Book Name: %s\n", book.b_name);
                printf("\t\t Writer: %s\n", book.writer);
                printf("\t\t Quantity: %d\n", book.quantity);
                printf("\t\t Price: %.3f\n\n", book.price);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\n\t\t\a Book is Not Found. ");
        }
        getchar();
        printf("\n\t\t Search any more books?(Y / N): ");
        ch = getch();
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - 32;
        }
        if (ch == 'Y')
        {
            SearchBooks();
        }
        else
        {
            SearchBooks();
        }
    }
    break;
    case '2':
    {
        system("cls");
        printf("\n\n\t\t Enter Book Name: ");
        scanf("%[^\n]", str);

        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (strcmpi(str, book.b_name) == 0)
            {
                printf("\n\n\n\t\t\tBook Is Found. \n\n");
                printf("\t\t ID: %d\n", book.id);
                printf("\t\t Book Name: %s\n", book.b_name);
                printf("\t\t Writer: %s\n", book.writer);
                printf("\t\t Quantity: %d\n", book.quantity);
                printf("\t\t Price: %.3f\n\n", book.price);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\n\t\t\a Book is Not Found. ");
        }
        getchar();
        printf("\n\n\t\t Search any more books?(Y / N): ");
        ch = getch();
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - 32;
        }
        if (ch == 'Y')
        {
            SearchBooks();
        }
        else
        {
            SearchBooks();
        }
    }
    break;
    case '3':
        students_section();
        break;
    default:
        printf("\n\t\t\a You Enter Wrong Choice!\n");
        printf("\t\t\t Press Any Key to Enter Your Choice Again....");
        getchar();
        SearchBooks();
        break;
    }
    fclose(fp);
}

void Writer_Books()
{
    int flag = 0;
    char ch, str[33] = "";
    system("cls");
    printf("\n\n\t\t**************** Writer All Books *****************");
    fp = fopen("info.dat", "rb");
    if (fp == NULL)
    {
        WriterBooksNULL:
        // Writer Books NULL
        printf("\n\n\t\t\a There is no Books in Library.");
        printf("\n\t\t   Press any key to go to Student section....");
        getchar();
        students_section();
    }
    fread(&book, sizeof(book), 1, fp);
    if (strlen(book.b_name) == 0)
        goto WriterBooksNULL;

    rewind(fp);
    printf("\n\n\t\t Enter Writer Name: ");
    scanf("%[^\n]", str);
    printf("\n");

    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (strcmpi(str, book.writer) == 0)
        {
            flag = 1;
            printf("\t\t ID: %d\n", book.id);
            printf("\t\t Book Name: %s\n", book.b_name);
            printf("\t\t Writer: %s\n", book.writer);
            printf("\t\t Quantity: %d\n", book.quantity);
            printf("\t\t Price: %.3f\n\n", book.price);
        }
    }
    if (flag == 0)
    {
        printf("\n\n\t\t\a No Books Found In This Writer!");
    }
    fclose(fp);
    getchar();
    printf("\n\n\t\t Search any more books?(Y / N): ");
    ch = getch();
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    if (ch == 'Y')
    {
        Writer_Books();
    }
    else
    {
        students_section();
    }
}

void EditBooks()
{
    system("cls");
    int n, flag = 0;
    printf("\n\n\t\t************* Edit Book's Record ************\n\n");

    printf("\n\n\t\t 1.Edit Book's By Id\n\t\t 2.Return Administrator\n\t\t 3.Go to Main Menu\n\n");
    printf("\t\t Enter Your Choice: ");

    switch (getch())
    {
    case '1':
        system("cls");

        fp = fopen("info.dat", "rb+");
        if (fp == NULL)
        {
            EditBooksNULL:
            // Edit Books NULL
            printf("\n\n\t\t\a There is no Books in Library.");
            printf("\n\t\t   Press any key to go to Administrator Menu....");
            getchar();
            Menu1();
        }
        fread(&book, sizeof(book), 1, fp);
        if (strlen(book.b_name) == 0)
            goto EditBooksNULL;

        rewind(fp);
        printf("\n\n\t\t****************** Edit Book's ******************");
        printf("\n\n\t\t Enter ID: ");
        scanf("%d", &n);

        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (n == book.id)
            {
                printf("\n\t\t Book is Available.\n");
                printf("\n\t\t ID: %d\n", book.id);
                printf("\n\t\t Enter New Name: ");
                getchar();
                scanf("%[^\n]", book.b_name);
                printf("\n\t\t Enter New Writer: ");
                getchar();
                scanf("%[^\n]", book.writer);
                printf("\n\t\t Enter New Quantity: ");
                scanf("%d", &book.quantity);
                printf("\n\t\t Enter New Price: ");
                scanf("%f", &book.price);
                fseek(fp, ftell(fp) - sizeof(book), 0);
                //-sizeof(book) use here to remove the line.
                //ftell()is used to find out current file position pointer in the file and to starting of the file.
                fwrite(&book, sizeof(book), 1, fp);
                fclose(fp);
                printf("\n\n\t\t The record is modified.");
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\n\t\t\a Book is Not Found!");
            getchar();
        }
        printf("\n\n\t\t Edit any more books?(Y / N): ");
        ch = getch();
        if (ch >= 'a' && ch <= 'z')
        {
            ch = ch - 32;
        }
        if (ch == 'Y')
        {
            EditBooks();
        }
        else
        {
            EditBooks();
        }
        break;
    case '2':
        Menu1();
        break;
    case '3':
        Menu();
        break;
    default:
        printf("\n\n\t\t\a Wrong Choice\n");
        printf("\t\t Press any key to try again.....\n");
        getch();
        EditBooks();
        break;
    }
}

void RemoveBooks()
{
    system("cls");
    int j, n, flag = 0;
    char ch, s;
    char name[33] = "";
    char show[18] = "Remove Books";
    printf("\n\n\t\t");
    for (j = 1; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf(" ");
    for (j = 0; j <= 12; j++)
    {
        Sleep(10);
        printf("%c", show[j]);
    }
    for (j = 1; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf("\n\n\t\t 1.Remove By Id.\n\t\t 2.Remove By Book Name\n\t\t 3.Return Administrator\n\t\t 4.Go to Main Menu");
    printf("\n\n\t\t Enter Your Choice: ");

    switch (getch())
    {
    case '1':
        system("cls");
        printf("\n\n\t\t***************** Remove Book's ****************");
        printf("\n\n\t\t Enter Id for Remove Book: ");
        scanf("%d", &n);

        fp = fopen("info.dat", "rb+");
        if (fp == NULL)
        {
            RemoveBooksNULL:
            // Remove Books NULL
            printf("\n\n\t\t\a There is no Books in Library.");
            printf("\n\t\t   Press any key to go to Administrator Menu....");
            getchar();
            ///Menu1();
        }
        fread(&book, sizeof(book), 1, fp);
        if (strlen(book.b_name) == 0)
            goto RemoveBooksNULL;

        rewind(fp);
        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (n == book.id)
            {
                printf("\n\t\t Book Is Available");
                printf("\n\t\t Book Name is: %s", book.b_name);
                printf("\n\t\t Writer Name is: %s\n", book.writer);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\a Book is not Available!");
        }
        else
        {
            printf("\n\n\t\t Do You Want To Remove It?(Y/N): ");
            s = getch();
            if (s >= 'a' && s <= 'z')
            {
                s = s - 32;
            }
            if (s == 'Y')
            {
                fp1 = fopen("remove.dat", "wb"); //Create New binary file for copy.
                rewind(fp);
                while (fread(&book, sizeof(book), 1, fp) == 1)
                {
                    /* Copy All data from old file to new file
                        without User given id.It will read 1 by 1 line
                        from File. If it didn't found any line it will be
                        0. For this the condition will be false.
                    */
                    if (n != book.id)
                    {
                        fseek(fp1, 0, 1);
                        ///SEEK_CUR==1
                        fwrite(&book, sizeof(book), 1, fp1);
                        /*Write all in temporary file except that
                        we want to remove*/
                    }
                }
                fclose(fp);
                fclose(fp1);

                remove("info.dat"); ///To remove main file
                /*Now Rename new file to old file name.
                Copy all item from temporary file to fp except that
                we want to delete*/
                rename("remove.dat", "info.dat");
                /*Now open rename file through pointer(fp).
                And Close the file.*/
                fp = fopen("info.dat", "rb");
                fclose(fp);
                printf("\n\n\t\t Successfully Remove");
                Sleep(100);
            }

            else
            {
                RemoveBooks();
            }
        }
        break;
    case '2':
        system("cls");
        printf("\n\n\t\t***************** Remove Book's ******************");
        printf("\n\n\t\t Enter Book Name for Remove Book: ");
        scanf("%[^\n]", name);

        fp = fopen("info.dat", "rb+");
        if (fp == NULL)
        {
            RemoveBooksNULL2:
            // Remove Books NULL 2
            printf("\n\n\t\t\a There is no Books in Library.");
            printf("\n\t\t   Press any key to go to Administrator Menu....");
            getchar();
            Menu1();
        }
        fread(&book, sizeof(book), 1, fp);
        if (strlen(book.b_name) == 0)
            goto RemoveBooksNULL2;

        rewind(fp);
        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (strcmpi(name, book.b_name) == 0)
            {
                printf("\n\t\t Book Is Available");
                printf("\n\t\t Book Name is: %s", book.b_name);
                printf("\n\t\t Writer Name is: %s", book.writer);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\a Book is not Available!");
        }
        else
        {
            printf("\n\n\t\t Do You Want To Remove It?(Y/N): ");
            s = getch();

            if (s >= 'a' && s <= 'z')
            {
                s = s - 32;
            }
            if (s == 'Y')
            {
                fp1 = fopen("remove.dat", "wb"); //Create New binary file for copy.
                rewind(fp);
                while (fread(&book, sizeof(book), 1, fp) == 1)
                {
                    /* Copy All data from old file to new file
                        without User given id.It will read 1 by 1 line
                        from File. If it didn't found any line it will be
                        0. For this the condition will be false.
                    */
                    if (strcmpi(name, book.b_name) != 0)
                    {
                        fseek(fp1, 0, 1);
                        ///SEEK_CUR==1
                        fwrite(&book, sizeof(book), 1, fp1);
                        /*Write all in temporary file except that
                        we want to remove*/
                    }
                }
                fclose(fp);
                fclose(fp1);

                remove("info.dat"); ///To remove main file
                /*Now Rename new file to old file name.
                Copy all item from temporary file to fp except that
                we want to delete*/
                rename("remove.dat", "info.dat");
                /*Now open rename file through pointer(fp).
                And Close the file.*/
                fp = fopen("info.dat", "rb");
                fclose(fp);
                printf("\n\n\t\t Successfully Remove");
                Sleep(300);
            }

            else
            {
                RemoveBooks();
            }
        }

        break;

    case '3':
        Menu1();
        break;
    case '4':
        Menu();
        break;
    default:
        printf("\n\n\t\t\a Wrong Choice!");
        printf("\n\t\t   Press any key to try again.....");
        getch();
        RemoveBooks();
    }
    getchar();
    printf("\n\n\t\t Remove any more books?(Y / N): ");
    ch = getch();
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    if (ch == 'Y')
    {
        RemoveBooks();
    }
    else
    {
        RemoveBooks();
    }
}

void Highest_Price_Book()
{
    system("cls");
    int j;
    struct Books highest;
    highest.price = 0;
    char ch[45] = "Highest Price Book Information From Library";
    printf("\n\n\t");
    for (j = 0; j < 13; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf(" ");
    for (j = 0; j < 44; j++)
    {
        Sleep(17);
        printf("%c", ch[j]);
    }
    for (j = 0; j < 13; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf("\n\n");
    fp = fopen("info.dat", "rb");

    if (fp == NULL)
    {
        HighestPriceBooksNULL:
        // Highest Price NULL
        printf("\n\n\t\t\a There is no Books in Library.");
        printf("\n\t\t   Press any key to go to Student section....");
        getchar();
        students_section();
    }
    fread(&book, sizeof(book), 1, fp);
    if (strlen(book.b_name) == 0)
        goto HighestPriceBooksNULL;

    rewind(fp);

    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (highest.price <= book.price)
        {
            highest = book;
        }
    }
    rewind(fp);
    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (highest.price == book.price)
        {
            highest = book;
            printf("\n\n\n\t\t\tBook Is Found. \n\n");
            printf("\t\t ID: %d\n", highest.id);
            printf("\t\t Book Name: %s\n", highest.b_name);
            printf("\t\t Writer: %s\n", highest.writer);
            printf("\t\t Quantity: %d\n", highest.quantity);
            printf("\t\t Price: %.3f\n\n", highest.price);
        }
    }

    printf("\n\n\t\tPress Any key to go to Student Section......");
    getch();
    students_section();
}

void IssueBooks() /// Issue Section
{
    system("cls");
    int j;
    char ch, s;
    char name[33] = "";
    char show[18] = "Issue Books";
    printf("\n\n\t\t");
    for (j = 1; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf(" ");
    for (j = 0; j <= 11; j++)
    {
        Sleep(10);
        printf("%c", show[j]);
    }
    for (j = 1; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }

    printf("\n\n\t\t 1.Issue a Book");
    printf("\n\t\t 2.View Issued Books");
    printf("\n\t\t 3.Search Issued Book By ID");
    printf("\n\t\t 4.Remove Issued Book");
    printf("\n\t\t 5.Go to Administrator");
    printf("\n\n\t\t Enter a Choice: ");

    switch (getch())
    {
    case '1':
        issuebook();
        break;
    case '2':
        view_issue_book();
        break;
    case '3':
        search_issued_book();
        break;
    case '4':
        remove_issued_book();
        break;
    case '5':
        Menu1();
        break;
    default:
        printf("\n\n\t\a Wrong Choice: ");
        printf("\n\t\t\t Press any key to try again........\n");
        getchar();
        IssueBooks();
    }
}

void issuebook() ///Issue a Book's
{
    system("cls");
    FILE *fp3;
    int x, flag = 0;
    printf("\n\n\t\t***************** Issue Book's ******************\n");
    printf("\n\t\t Enter the Book Id: ");
    scanf("%d", &x);
    fp = fopen("info.dat", "rb+");

    if (fp == NULL)
    {
        IssueBooksNULL:
        // Issue Books NULL
        printf("\n\n\t\t\a There is no Books in Library.");
        printf("\n\t\t   Press any key to go to Administrator Menu....");
        getchar();
        Menu1();
    }
    rewind(fp);
    fread(&book, sizeof(book), 1, fp);
    if (strlen(book.b_name) == 0)
        goto IssueBooksNULL;

    rewind(fp);

    fp2 = fopen("Issue.dat", "ab+");
    while (fread(&book, sizeof(book), 1, fp) == 1)
    {
        if (x == book.id)
        {
            printf("\n\n\t\t The book record is available.\n\n");
            printf("\t\t There are %d Unissued books in library.\n", book.quantity);
            printf("\n\t\t The name of the book is- %s\n", book.b_name);
            printf("\n\t\t Enter student name: ");
            getchar();
            scanf("%[^\n]", book.s_name);
            printf("\n\t\t Enter the Current Date (DD-MM-YY): ");
            scanf("%d %d %d", &book.iss.dd, &book.iss.mm, &book.iss.yy);
            printf("\n\t\t Issued date is %d-%d-%d", book.iss.dd, book.iss.mm, book.iss.yy);
            printf("\n\n\t\t The BOOK of ID %d is issued.\n", book.id);

            ///For Return Date
            book.duedate.dd = book.iss.dd + 15;
            book.duedate.mm = book.iss.mm;
            book.duedate.yy = book.iss.yy;

            if (book.duedate.dd > 30)
            {
                book.duedate.mm += book.duedate.dd / 30;
                book.duedate.dd -= 30;
            }
            if (book.duedate.mm > 12)
            {
                book.duedate.yy += book.duedate.mm / 12;
                book.duedate.mm -= 12;
            }
            printf("\n\t\t To be return: %d-%d-%d", book.duedate.dd, book.duedate.mm, book.duedate.yy);
            fseek(fp2, sizeof(book), 2); //SEEK_END==2

            fwrite(&book, sizeof(book), 1, fp2);
            fclose(fp2);
            flag = 1;
        }
    }
    fclose(fp);
    if (flag == 0)
    {
        printf("\n\n\t\t\a Book is Not Found!");
    }
    else
    {
        printf("\n\n\t\t Successfully Issued Book's.");

        fp = fopen("info.dat", "rb+");
        fp3 = fopen("tmp.dat", "wb+");
        rewind(fp);
        while (fread(&book, sizeof(book), 1, fp) == 1)
        {
            if (x == book.id)
            {
                book.quantity--;
            }
            fwrite(&book, sizeof(book), 1, fp3);
        }
        fclose(fp);
        fclose(fp3);
        remove("info.dat");
        rename("tmp.dat", "info.dat");
        fp = fopen("info.dat", "rb+");
        fclose(fp);
    }
    getchar();
    printf("\n\t\t Issue any more books?(Y / N): ");
    ch = getch();
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    if (ch == 'Y')
    {
        issuebook();
    }
    else
    {
        IssueBooks();
    }
}

void view_issue_book() ///Show issued book's list
{
    system("cls");
    printf("\n\n\t\t*************** ISSUED BOOKS LIST ****************\n\n");

    printf("   ID\t    Student Name\tBook Name\t    Issued Date\t\tReturn Date\n");

    fp1 = fopen("Issue.dat", "rb+");

    if (fp1 == NULL)
    {
        ViewIssueBooksNULL:
        // View Issue Books NULL
        printf("\n\n\t\t\a There is no Issued Books in Library.");
        printf("\n\t\t   Press any key to go to Issue section....");
        getch();
        IssueBooks();
    }
    fread(&book, sizeof(book), 1, fp1);
    if (strlen(book.b_name) == 0)
        goto ViewIssueBooksNULL;

    rewind(fp1);
    while (fread(&book, sizeof(book), 1, fp1) == 1)
    {
        printf("\n   %-9d", book.id);
        printf("%-20s", book.s_name);
        printf("%-21s", book.b_name);
        printf("%-1d-%-1d-%-15d", book.iss.dd, book.iss.mm, book.iss.yy);
        printf("%d-%d-%d", book.duedate.dd, book.duedate.mm, book.duedate.yy);
    }
    fclose(fp1);
    printf("\n\n\t\tPress Any key to Return......");
    getch();
    IssueBooks();
}

void search_issued_book() ///Search Issued book by id
{
    system("cls");
    int x, flag = 0;
    printf("\n\n\t\t************* Search Issued Book's By Id *************\n");
    printf("\n\t\t Enter Id: ");
    scanf("%d", &x);
    fp2 = fopen("Issue.dat", "rb");

    if (fp2 == NULL)
    {
        SearchBooksNULL:
        // Search Issue Books NULL
        printf("\n\n\t\t\a There is no Issued Books in Library.");
        printf("\n\t\t   Press any key to go to Issue section....");
        getchar();
        IssueBooks();
    }
    fread(&book, sizeof(book), 1, fp2);
    if (strlen(book.b_name) == 0)
        goto SearchBooksNULL;

    rewind(fp2);
    while (fread(&book, sizeof(book), 1, fp2) == 1)
    {
        if (x == book.id)
        {
            printf("\n\n\t\t The Book has taken by Mr./Miss. %s", book.s_name);
            printf("\n\t\t Issued Date: %d-%d-%d", book.iss.dd, book.iss.mm, book.iss.yy);
            printf("\n\t\t Returning Date: %d-%d-%d", book.duedate.dd, book.duedate.mm, book.duedate.yy);
            flag = 1;
        }
    }
    fclose(fp2);
    if (flag == 0)
        printf("\n\n\t\t\a No record Found!\n");
    else
        printf("\n\n\t\t Successfully Search Book Information.");
    getchar();
    printf("\n\t\t Search any more books?(Y / N): ");
    ch = getch();
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    if (ch == 'Y')
    {
        search_issued_book();
    }
    else
    {
        IssueBooks();
    }
}

void remove_issued_book() ///Remove Issued Books
{
    system("cls");
    int n, flag = 0;
    char s;
    printf("\n\n\t\t*************** Remove Issued Book's *****************\n");

    fp2 = fopen("Issue.dat", "rb+");

    if (fp2 == NULL)
    {
        RemoveIssueBooksNULL:
        // Remove Issue Books NULL
        printf("\n\n\t\t\a There is no Issued Books in Library.");
        printf("\n\t\t   Press any key to go to Issue section....");
        getchar();
        IssueBooks();
    }
    fread(&book, sizeof(book), 1, fp2);
    if (strlen(book.b_name) == 0)
        goto RemoveIssueBooksNULL;

    rewind(fp2);
    printf("\n\t\t Enter Book Id For Remove: ");
    scanf("%d", &n);
    while (fread(&book, sizeof(book), 1, fp2) == 1)
    {
        if (n == book.id)
        {
            printf("\n\n\n\t\t\tBook Is Found. \n\n");
            printf("\t\t Book Name: %s\n", book.b_name);
            printf("\t\t Student's Name: %s\n", book.s_name);
            printf("\t\t Issued Date: %d-%d-%d\n", book.iss.dd, book.iss.mm, book.iss.yy);
            printf("\t\t DueDate: %d-%d-%d\n", book.duedate.dd, book.duedate.mm, book.duedate.yy);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("\n\t\t\a Book is not Available!");
    }
    else
    {
        printf("\n\n\t\t Do You Want To Remove It?(Y/N): ");
        s = getch();
        if (s >= 'a' && s <= 'z')
        {
            s = s - 32;
        }
        if (s == 'Y')
        {
            fp1 = fopen("rissue.dat", "wb"); //Create New binary file for copy.
            rewind(fp2);
            while (fread(&book, sizeof(book), 1, fp1) == 1)
            {
                /* Copy All data from old file to new file
                    without User given id.It will read 1 by 1 line
                    from File. If it didn't found any line it will be
                    0. For this the condition will be false.
                */
                if (n != book.id)
                {
                    fseek(fp2, 0, 1);
                    ///SEEK_CUR==1
                    fwrite(&book, sizeof(book), 1, fp1);
                    /*Write all in temporary file except that
                    we want to remove*/
                }
            }
            fclose(fp2);
            fclose(fp1);

            remove("Issue.dat"); ///To remove main file
            /*Now Rename new file to old file name.
            Copy all item from temporary file to fp except that
            we want to delete*/
            rename("rissue.dat", "Issue.dat");
            /*Now open rename file through pointer(fp).
            And Close the file.*/
            fp = fopen("info.dat", "rb");
            FILE *fp3;
            fp3 = fopen("tmp.dat", "wb+");
            rewind(fp);
            while (fread(&book, sizeof(book), 1, fp) == 1)
            {
                if (n == book.id)
                {
                    book.quantity++;
                }
                fwrite(&book, sizeof(book), 1, fp3);
            }
            fclose(fp);
            fclose(fp3);
            remove("info.dat");
            rename("tmp.dat", "info.dat");
            fp = fopen("info.dat", "rb+");
            fclose(fp);

            printf("\n\n\t\t Successfully Remove");
            Sleep(300);
        }
        else
            IssueBooks();
    }
    printf("\n\n\t\t Remove any more books?(Y / N): ");
    ch = getch();
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }
    if (ch == 'Y')
    {
        remove_issued_book();
    }
    else
    {
        IssueBooks();
    }
}

void Administrator()
{
    system("cls");
    password();
}

void Menu1()
{
    system("cls");
    printf("\n\n\t******************** Welcome to Administrator Section ***********************\n");
    printf("\n\t\t\t\t 1.Add Books\n\t\t\t\t 2.Remove Books\n\t\t\t\t 3.Edit Books\n\t\t\t\t 4.Issue Books\n\t\t\t\t 5.Main Menu\n\t\t\t\t 6.Go to Student's Section\n");
    printf("\n\t\t\t Enter Your Choice: ");


    switch (getch())
    {
    case '1':
        AddBooks();
        break;
    case '2':
        RemoveBooks();
        break;
    case '3':
        EditBooks();
        break;
    case '4':
        IssueBooks();
        break;
    case '5':
        Menu();
        break;
    case '6':
        students_section();
        break;
    default:
        printf("\n\n\t\t\a Wrong Choice!\n");
        printf("\t\t\t  Press any key to try again.....");
        getch();
        Menu1();
    }
}

void students_section()
{
    system("cls");
    int j;
    char show[] = "Welcome To Student's Section";
    printf("\n\n\n\t");
    for (j = 0; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }
    printf(" ");
    for (j = 0; j <= 28; j++)
    {
        Sleep(10);
        printf("%c", show[j]);
    }
    for (j = 0; j <= 18; j++)
    {
        Sleep(10);
        printf("*");
    }

    printf("\n\n\t\t 1.Show All Books\n\t\t 2.Highest Price Book\n\t\t 3.All Books Of Given Writer\n\t\t 4.Search Books\n\t\t 5.Main Menu\n\t\t 6.Go to Administrator Section\n");

    printf("\n\n\t\tEnter Your Choice: ");

    switch (getch())
    {
    case '1':
        ViewBooks();
        break;
    case '2':
        Highest_Price_Book();
        break;
    case '3':
        Writer_Books();
        break;
    case '4':
        SearchBooks();
        break;
    case '5':
        Menu();
        break;
    case '6':
        Administrator();
    default:
        printf("\n\n\t\t\aIncorrect Choice!\n");
        printf("\t\t\tPress any key to try again.....");
        getch();
        students_section();
        break;
    }
}

void Password() ///For Main Menu
{
    system("cls");
    char pass1[8] = {"13579"};
    char pass2[8] = "";
    char show[37] = "WELCOME TO LIBRARY MANAGEMENT SYSTEM";
    int j;
    printf("\n\n\n\t");
    for (j = 0; j <= 15; j++)
    {
        Sleep(40);
        printf("*");
    }
    printf(" ");
    for (j = 0; j <= 36; j++)
    {
        Sleep(40);
        printf("%c", show[j]);
    }
    for (j = 0; j <= 15; j++)
    {
        Sleep(40);
        printf("*");
    }
    printf("\n\n\n\t\t Please Enter Correct Password....");
    printf("\n\t\t Enter Your Password: ");
    gets(pass2);
    if (strcmp(pass1, pass2) == 0)
    {
        printf("\n\n\t\tPassword Match.\n");
        printf("\n\t\t\tPress any key to continue.........\n");
        getchar();
    }
    else
    {
        if (i == 3)
        {
            printf("\n\n\t\t\aYou are trying the incorrect password 3 times.\n");
            printf("\n\t\t   The Program will end after 2 seconds.\n");
            Sleep(2000);
            exit(0); ///Exit Successful
        }
        printf("\n\n\t\t\aIncorrect Password! %d times Out of 3 times.\n", i);
        printf("\n\t\t\tPress any key to try again.........\n");
        getchar();
        system("cls");
        i++;

        Password();
    }
    Menu();
}

void password()
{
    system("cls");
    int j;
    char x[32] = "Welcome To Administrator Section";
    char pass3[10] = {"2468"};
    char pass4[10] = "";

    printf("\n\n\n\t");
    for (j = 1; j <= 18; j++)
    {
        Sleep(20);
        printf("*");
    }
    printf("  ");
    for (j = 0; j <= 33; j++)
    {
        Sleep(20);
        printf("%c", x[j]);
    }
    for (j = 1; j <= 18; j++)
    {
        Sleep(20);
        printf("*");
    }
    printf("\n\n\t\t You can not access this section without correct password...");
    printf("\n\n\t\t\t Enter Your Password: ");
    fflush(stdin);
    //getch();
    gets(pass4);
    if (strcmp(pass3, pass4) == 0)
    {
        printf("\n\n\t\tPassword Match.\n");
        printf("\n\t\t\tPress any key to continue.........\n");
        getchar();
    }
    else
    {
        if (i == 3)
        {
            printf("\n\n\t\t\aYou are trying the incorrect password 3 times.\n");
            printf("\n\t\t   You are Going To Main Menu after 2 second.\n");
            Sleep(2000);
            Menu();
        }
        printf("\n\n\t\t\aIncorrect Password! %d times Out of 3 times.\n", i);
        printf("\n\t\t\tPress any key to try again.........\n");
        getchar();
        system("cls");
        i++;

        password();
    }
    Menu1();
}
int date_time(void) //for time
{
    time_t date_time;
    time(&date_time);
    printf("Date and time:%s\n", ctime(&date_time));

    return 0;
}
