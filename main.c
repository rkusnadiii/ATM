#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "Login.h"
#pragma comment (lib,"libmysql.lib")
#pragma comment (lib,"mysqlclient.lib")

struct acc_type
{
    char username[20];
    int password;
    char nama[30];
    char alamat[100];
    char kota[30];
    char telepon[12];
    int norek;
    int saldo;
};



int cursor(int X, int Y);
void Create_new_account();
void Cash_Deposit();
void Cash_withdrawl();
void Account_information();
void Log_out();
void display_options();
void menu();

/* main program */
int main()
{
    FILE* fp;
    fp = fopen("Deposit.txt", "w");
    fp = fopen("Withdraw.txt", "w");
    fp = fopen("Info.txt", "w");
    fp = fopen("Create.txt", "w");
    MYSQL* handle = NULL;
    MYSQL_ROW row;
    handle = mysql_init(handle);
    mysql_real_connect(handle, "localhost", "root", "123456", "bank", 3306, NULL, 0);
    mysql_query(handle, "SELECT * FROM  databank");
    MYSQL_RES* item = mysql_store_result(handle);
    row = mysql_fetch_row(item);
    char usernamee[6];
    cursor(35, 0);
    printf("***** Welcome to Bank Application *****");
    cursor(50, 3);
    printf("Username:");
    scanf("%s", &usernamee);
    login(row[1]);
    char option;
    cursor(35, 0);
    printf("***** Welcome to Bank Application *****");
    while (1)
        {
            system("cls");
            cursor(35, 0);
            printf("***** Welcome to Bank Application *****");
            display_options();
            printf("Please enter any options (1/2/3/4/5/6) ");
            printf("to continue : ");

            option = _getch();
            printf("%c \n", option);
            switch (option)
            {
            case '1': Create_new_account();
                break;
            case '2': Cash_Deposit(usernamee);
                break;
            case '3': Cash_withdrawl(usernamee);
                break;
            case '4': Account_information(usernamee);
                break;
            case '5': return 0;
                break;
                cursor(35, 7);
                printf("(1/2/3/4/5/6) to continue \n ");
                break;
            }
        
         }
    mysql_close(handle);
    return 0;
}



/*Function to display available options in this application*/


void display_options()
{
    cursor(35, 1);
    printf("1. Create new account");
    cursor(35, 2);
    printf("2. Cash Deposit");
    cursor(35, 3);
    printf("3. Cash withdrawl");
    cursor(35, 4);
    printf("4. Account information");
    cursor(35, 5);
    printf("5. Log out");
    cursor(15, 6);
    printf("Please enter one of the options");
}

/* Function to create new account */

void Create_new_account()
{
    char username[20];
    int password;
    char nama[30];
    int norek;
    char alamat;
    char telp[20];
    char kota[20];
    int saldo;
    printf("\nEnter the bank username           : ");
    scanf("%s", &username);
    printf("\nEnter the bank password           : ");
    scanf("%d", &password);
    printf("\nEnter the account name            : ");
    scanf("%s", &nama);
    printf("\nEnter the account number(1 to 9)  : ");
    scanf("%d", &norek);
    printf("\nEnter the city                    : ");
    scanf("%s", &kota);
    printf("\nEnter phone number                :");
    scanf("%s", &telp);
    printf("\nEnter amount of money             :");
    scanf("%d", &saldo);
    printf("\nEnter the account holder address  : ");
    scanf("%s", &alamat);
    MYSQL* handle = NULL;
    handle = mysql_init(handle);
    mysql_real_connect(handle, "localhost", "root", "123456", "bank", 3306, NULL, 0);
    mysql_query(handle, "SELECT * FROM databank");
    mysql_query(handle, "INSERT INTO * databank VALUES(%s,%d,%s,%s,%s,%s,%d,%d)", username, password, nama, alamat, kota, telp, norek, saldo);
    printf("SUCSESS!!!");
    FILE* fp = fopen("Create.txt", "a");
    fprintf(fp, "username:%s\nPassword:******\nNama:%s\nAlamat;%s %s\n Norek:%d\n Notelp:%s\n Jumlah setoran:%d", username, nama, alamat, kota, norek, telp, saldo);
    fclose(fp);
    _getch();
}

// Displaying account informations

void Account_information(char* data)
{
    int x = 0;
    system("cls");
    MYSQL* handle = NULL;
    MYSQL_ROW* row;
    MYSQL_FIELD* field;
    handle = mysql_init(handle);
    mysql_real_connect(handle, "localhost", "root", "123456", "bank", 3306, NULL, 0);
    mysql_query(handle, "SELECT * FROM  databank");
    MYSQL_RES* item = mysql_store_result(handle);
    field = mysql_fetch_fields(item);
    row = mysql_fetch_row(item);
    mysql_fetch_field(item);
        if (strcmp(data,row[0])==0) {
            printf("Nama:%s", row[2]);
            printf("\nAlamat:%s,%s", row[3], row[4]);
            printf("\nSaldo:Rp.%s", row[7]);
            FILE* fp = fopen("Info.txt", "a");
            fprintf(fp, "Nama:%s\nAlamat:%s,%s\nSaldo;Rp.%s", row[2], row[3], row[4], row[7]);
            fclose(fp);
        }
        else printf("WRONG USERNAME!!!");
    mysql_close(handle);
    _getch();
    system("cls");
}

// Function to deposit amount in an account

void Cash_Deposit(char* data)
{
    system("cls");
    MYSQL* handle = NULL;
    MYSQL_ROW* row;
    MYSQL_FIELD* field;
    handle = mysql_init(handle);
    mysql_real_connect(handle, "localhost", "root", "123456", "bank", 3306, NULL, 0);
    mysql_query(handle, "SELECT * FROM  databank");
    MYSQL_RES* item = mysql_store_result(handle);
    field = mysql_fetch_fields(item);
    row = mysql_fetch_row(item);
    mysql_fetch_field(item);
    int jml;
    int a;
    if (strcmp(data, row[0]) == 0) {
        printf("Deposit:");
        scanf("%d", &jml);
        printf("Completed!!\nDeposit:%d", jml);
        a = jml = row[7];
        mysql_query(handle, "SELECT * FROM  databank");
        mysql_query(handle, "INSERT INTO * databank VALUES(%s,%d,%s,%s,%s,%s,%d,%d)",row[0],row[1],row[2],row[3],row[4],row[5],row[6],a);
        FILE* fp = fopen("Deposit.txt", "a");
        fprintf(fp, "Deposit Sukses\nDeposit:%d",jml);
        fclose(fp);
        _getch();
    }
    else printf("WRONG USERNAME!!!");
    _getch();
}

// Function to withdraw amount from an account

void Cash_withdrawl(char* data)
{
    system("cls");
    int inp;
    int a;
    MYSQL* handle = NULL;
    MYSQL_ROW* row;
    MYSQL_FIELD* field;
    handle = mysql_init(handle);
    mysql_real_connect(handle, "localhost", "root", "123456", "bank", 3306, NULL, 0);
    mysql_query(handle, "SELECT * FROM  databank");
    MYSQL_RES* item = mysql_store_result(handle);
    field = mysql_fetch_fields(item);
    row = mysql_fetch_row(item);
    mysql_fetch_field(item);
    if (strcmp(data, row[0]) == 0) {
        printf("AMount money:");
        scanf("%d", &inp);
        if (inp < row[7]) {
            printf("Sucsess!!!");
            a = row[7] - inp;
            mysql_query(handle, "SELECT * FROM  databank");
            mysql_query(handle, "INSERT INTO * databank VALUES(%s,%d,%s,%s,%s,%s,%d,%d)", row[0], row[1], row[2], row[3], row[4], row[5], row[6], a);
            FILE* fp = fopen("Withdraw.txt", "a");
            fprintf(fp, "Penarikan Sukses\nDitarik:%d", inp);
            fclose(fp);
            _getch();
        }
        else {
            printf("Failed!!! insufficient balance");
            _getch();

        }
    }
    else printf("WRONG USERNAME!!!");
    _getch();
}
int cursor(int X, int Y) {
    COORD pos;
    pos.X = X;
    pos.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
