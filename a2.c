#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>

//Function Initializations
int random_num(List L);
void display_card(int arr[5][5], List L);
void winner(int arr[5][5], List L);
void rangeCard (int arr[5][5],char *argv[]);
void repeats (int arr[5][5], char *argv[]);

int main(int argc, char *argv[]){
    system("clear");

    //EXIT 1
    if (argv[1] == '\0' || argv[3] != '\0' || argv[2] == '\0'){
       fprintf(stderr,"Usage: %s seed cardFile\n",argv[0]);
       exit(1);
    }

    //EXIT 2
    int seed = atoi(argv[1]);
    int index =0;
    for (index = 0; index < strlen(argv[1]); index++) {
        if ((argv[1])[index] < 48 || (argv[1])[index] > 57){
           fprintf(stderr,"Expected integer seed, but got %s\n",argv[1]);
           exit(2);
        }
    }

    FILE *fp;
    fp = fopen(argv[2],"r");

    //EXIT 3
    if (fp == NULL) {
       fprintf(stderr,"%s is nonexistent or unreadable\n",argv[2]);
       exit(3);
    }

    srand(seed);

    int arrC[25];
    int arrCard[5][5]; //Contains the card

    int numP, i = 0;

    int qq=0;
    int count = 0;
     
    //EXIT 4
    while(count != EOF){
        count = fscanf(fp,"%3d %3d %3d %3d %3d",&arrC[qq], &arrC[qq+1], &arrC[qq+2], &arrC[qq+3], &arrC[qq+4]);
        if (count != -1 && count != 5){
            fprintf(stderr,"%s has bad format\n",argv[2]);
            exit(4);
        }
        qq=qq+5;
    }

    int counT = 0;
    int j=0;
    for (i=0; i<5; i++){
      for (j=0; j<5; j++){
        arrCard[i][j] = arrC[counT];
        counT++;
      }
    }

    if (arrCard[2][2] != 0){
       fprintf(stderr,"%s has bad format\n",argv[2]);
       exit(4);
    }

    //EXIT 4
    rangeCard(arrCard, argv);
    repeats (arrCard, argv);

    List callList;
    init(0, &callList);

    print(callList);

    add(&callList, 0);
    display_card(arrCard, callList);


    char keys[50];
    printf("enter any non-enter key for Call (q to quit): ");
    fgets(keys, sizeof keys, stdin);

    while ((keys[0] != 'q')){
       //Checkt to see if the enter key was pressed
       if (keys[0] != '\n') {
          system("clear");
          for (i=0; i< strlen(keys)-1; i++){
              if( keys[i] == 113 || keys[i] == 81 ){
                system("clear");
                print(callList);
                display_card(arrCard, callList);
                winner(arrCard, callList);
                exit(0);
              }
              int num = random_num(callList);
              add(&callList, num); //Adding valuse to list
          }
          print(callList);
          display_card(arrCard, callList);
          winner(arrCard, callList);
          printf("enter any non-enter key for Call (q to quit): ");
          fgets(keys, sizeof keys, stdin);
       }else{
          system("clear");
          print(callList);
          display_card(arrCard, callList);
          winner(arrCard, callList);
          printf("enter any non-enter key for Call (q to quit): ");
          fgets(keys, sizeof keys, stdin);
       }
    }

    fclose(fp);
    exit(0);
}


//CHECKS THE RANGE FOR EACH COLUMN
void rangeCard (int arr[5][5],char *argv[]) {
    int min = 1;
    int max = 15;
    int indexR = 0;
    int indexC = 0;
    for (indexR=0; indexR<5; indexR++){
        for (indexC=0; indexC<5; indexC++){
           if ( indexC != 2 && indexR != 2){
               if ( arr[indexC][indexR] < min || arr[indexC][indexR] > max ){
                   fprintf(stderr,"%s has bad format\n",argv[2]);
                   exit(4);
               }
           }
        }
        min = (min+15);
        max = (max+15);
    }
}

void repeats (int arr[5][5],char *argv[]){
     int i = 0;
     int j = 0;
     int k =0;
     for (i=0; i<5; i++){
         for (j = 0; j<5; j++){
              int temp = (j+1);
              for (k = temp; k<5; k++){
                  if (arr[j][i] == arr[k][i]){
                     fprintf(stderr,"%s has bad format\n",argv[2]);
                     exit(4);
                  }
              }
         }
     }
}

//GENERATES A UNIQUE RANDOM NUMEBRS
int random_num(List L){
    int min = 1;
    int max = 75;
    int rNum = (rand() % (max - min + 1)) + min;
    if (found(L,rNum) == 0) {
        while(found(L,rNum) == 0){
            rNum = (rand() % (max - min + 1)) + min;
        }
    }
    return rNum;
}

void winner (int arr[5][5], List L){
     int i=0;
     int j=0;
     for (i=0; i<5; i++){
        int winRow = 0;
        int winCol = 0;
        for (j=0; j<5; j++){
            if (found(L,arr[i][j]) == 0){
               winRow++;
            }
            if (found(L,arr[j][i]) == 0){
               winCol++;
            }
        }

        if (winCol == 5 || winRow == 5) {
           printf("WINNER\n");
           exit(0);
        }
     }
     int topL = found(L,arr[0][0]);
     int topR = found(L,arr[0][4]);
     int botL = found(L,arr[4][0]);
     int botR = found(L,arr[4][4]);
     if ( topL == 0 && topR == 0 && botL == 0 &&  botR == 0) {
        printf("WINNER\n");
        exit(0);
     }
}

void display_card(int arr[5][5], List L){
     int i=0;
     int j=0;

     for (i=0; i<5; i++){
      printf("\n");
      if (i == 0){
        printf("L   I   N   U   X\n");
      }

      for (j=0; j<5; j++){
        if (found(L,arr[i][j]) == 0){
           if (arr[i][j] < 10){
              printf("0%dm ", arr[i][j]);
            }else{
              printf("%dm ", arr[i][j]);
            }
        }else{
            if (arr[i][j] < 10){
              printf("0%d  ", arr[i][j]);
            }else{
              printf("%d  ", arr[i][j]);
            }
        }
      }
     }
    printf("\n");
}
