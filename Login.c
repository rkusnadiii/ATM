#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int login(char * pase){
  char nama[16];
  int loop=0;
  while(1){
    cursor(50,4);
    printf("Password:");
    while(1){
      int x=_getch();
      if(x==13) break;
      else if(x==8&&loop>0){
        printf("\b \b");
        nama[loop]=0;
        loop--;
      }
      else{
        printf("*");
        nama[loop]=x;
        loop++;
      }
    }
    nama[loop]=0;
    int l;
    for(l=0;l<=strlen(nama);l++){
      if(l==strlen(nama)) return 0;
      else if(nama[l]!=pase[l]){
        loop=0;
        cursor(40,5);
        printf("Maaf Password yang anda masukan salah!!");
        _getch();
        system("cls");
        
      }
    }
  }
}


