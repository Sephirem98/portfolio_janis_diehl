// TODO
// Check code for functionality
// Potentially add to TODO

/**
 * @file 2048.c
 * @author Janis Diehl
 * @brief Selfmade Version of the mobile game "2048" written in C
 * @version 0.1
 * @date 2024-01-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Add leave option to tfeMerge and tfeCompress (Pressing 0)

void tfeRules(){
    printf("These are the rules to be\n");
}

/**
 * @brief looks for a certain value in a given array
 * 
 * @param arr 
 * @param searchVal 
 * @param arrSize 
 * @return int 
 */
int valInArr(int arr[], int searchVal, int arrSize){
    for(int i = 0; i < arrSize; i++){
        if(arr[i] == searchVal){
            return 1;   
        }
    }
    return 0;
}

/**
 * @brief User input
 * 
 * @return int 
 */
int tfePlayerInput(){
    int tfeInput, tfeInputArr[6] = {0, 2, 4, 5, 6, 8};
    
    do{
        printf("Please do something\n");
        scanf("%i", &tfeInput);
    } while (!valInArr(tfeInputArr, tfeInput, 6));
    
    return tfeInput;
}

/**
 * @brief checks for win condition
 * 
 * @param tfeField 
 * @return int 
 */
int tfeWin(int tfeField[4][4]){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(tfeField[row][col] == 2048){
                printf("You won or i fucked up\n");
                break;
            }
        }
    }
}

/**
 * @brief Merges to tiles of the same value in the given direction if possible
 * 
 * @param tfeField 
 * @param tfeDirection 
 * @param tfeMovementCheck 
 */
void tfeMerge(int tfeField[4][4], int tfeDirection, int tfeMovementCheck){
    switch (tfeDirection){
    case 2:
        //Merge downwards
        for(int row = 3; row > 1; row--){
            for(int col = 0; col < 3; col++){
                if(tfeField[row-1][col] == tfeField[row][col]){
                    tfeField[row][col] *=2;
                    tfeField[row-1][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;

    case 4:
    //Merge leftwards
        for(int col = 0; col < 3; col++){
            for(int row = 0; row < 3; row++){
                if(tfeField[row][col+1] == tfeField[row][col]){
                    tfeField[row][col] *= 2;
                    tfeField[row][col+1] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;

    case 6:
        //Merge rightwards
        for(int col = 3; col > 1; col--){
            for(int row = 0; row < 3; row++){
                if(tfeField[row][col-1] == tfeField[row][col]){
                    tfeField[row][col] *= 2;
                    tfeField[row][col-1] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;

    case 8:
        //Merge upwards
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                if(tfeField[row+1][col] == tfeField[row][col]){
                    tfeField[row][col] *= 2;
                    tfeField[row+1][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;
    
    default:
        printf("Error: unexpected value for directional parameter in tfeMerge\n");

        break;
    }
}

/**
 * @brief Compresses the field by moving all tiles in the given direction if possible
 * 
 * @param tfeField 
 * @param tfeDirection 
 * @param tfeMovementCheck 
 */
void tfeCompress(int tfeField[4][4], int tfeDirection, int tfeMovementCheck){
    switch (tfeDirection){
    case 2:
    //compress downward
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                if(tfeField[row+1][col] == 0){
                    tfeField[row+1][col] == tfeField[row][col];
                    tfeField[row][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;
    
    case 4:
    //compress leftward
        for(int col = 3; col > 1; col--){
            for(int row = 0; row < 3; row ++){
                if(tfeField[row][col-1] == 0){
                    tfeField[row][col-1] == tfeField[row][col];
                    tfeField[row][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;
    
    case 6:
    //compress rightward
        for(int col = 0; col < 3; col++){
            for(int row = 0; row < 3; row ++){
                if(tfeField[row][col+1] == 0){
                    tfeField[row][col+1] == tfeField[row][col];
                    tfeField[row][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;
    
    case 8:
    //compress upward
        for(int row = 3; row > 1; row--){
            for(int col = 0; col < 3; col++){
                if(tfeField[row-1][col] == 0){
                    tfeField[row-1][col] == tfeField[row][col];
                    tfeField[row][col] = 0;
                    tfeMovementCheck = 1;
                }
            }
        }
        break;
    
    default:
        printf("Error: unexpected value for directional parameter in tfeCompress\n");
        
        break;
    }
}

/**
 * @brief Generates a new tile if there are empty tiles and the field moved this turn
 * 
 * @param tfeField 
 * @param tfeMovementCheck 
 */
void tfeGenerateNewTile(int tfeField[4][4], int tfeMovementCheck){
    //Check if movement happened
    //Check if there is an empty tile
    //Generate new tile (90% - 2 / 10% - 4)
    if(tfeMovementCheck == 1){
        for(int row = 0; row < 4; row++){
            if(valInArr(tfeField[row], 0, 4)){
                int tfeTileChance = rand()%10;
                int tfeRandRow;
                int tfeRandCol;

                do{
                    tfeRandRow = rand() % 4;
                    tfeRandCol = rand() % 4;
                } while (tfeField[tfeRandRow][tfeRandCol] != 0);

                if(tfeTileChance == 1){
                    tfeField[tfeRandRow][tfeRandCol] = 4;
                }else{
                    tfeField[tfeRandRow][tfeRandCol] = 2;            
                }
                break;
            }
        }
    }
}

/**
 * @brief Calls for every function to create a turn
 * 
 * @param tfeField 
 * @param tfeDirection 
 */
void tfeTurn(int tfeField[4][4], int tfeDirection){
    int tfeMovementCheck = 0;
    tfeCompress(tfeField, tfeDirection, tfeMovementCheck);
    tfeMerge(tfeField, tfeDirection, tfeMovementCheck);
    tfeCompress(tfeField, tfeDirection, tfeMovementCheck);
    tfeGenerateNewTile(tfeField, tfeMovementCheck);
    tfeWin(tfeField);
}

int main(){
    srand(time(NULL));
    int tfeField[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int tfeDirection = 0, tfeWinCheck = 0;

    tfeRules();
    tfeGenerateNewTile(tfeField, 1);
    tfeGenerateNewTile(tfeField, 1);

    do{
        tfeDirection = tfePlayerInput();
        tfeTurn(tfeField, tfeDirection);
        
    } while (tfeWinCheck == 0 && tfeDirection != 0);
        
}