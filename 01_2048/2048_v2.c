#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool tfeWon(){
    return false;
}

bool tfeLost(){
    return false;
}

int tfePlayerInput(){
    int tfeInput, tfeInputArr[6] = {0, 2, 4, 6, 8};
    
    do{
        printf("Please choose a direction by pressing the corresponding number\n");
        printf("┏━━━━━━━━━━━┓\n");
        printf("┃     ˄     ┃\n");
        printf("┃     8     ┃\n");
        printf("┃ ˂4     6˃ ┃\n");
        printf("┃     2     ┃\n");
        printf("┃     ˅     ┃\n");
        printf("┗━━━━━━━━━━━┛\n");

        scanf("%i", &tfeInput);
    } while (!valInArr(tfeInputArr, tfeInput, 6));
    
    return tfeInput;
}

void tfeDisplayField(){
    printf("┏━━━━┳━━━━┳━━━━┳━━━━┓\n");
    printf("┃%s┃%s┃%s┃%s┃\n", tfefield[0][0], tfefield[0][1], tfefield[0][2], tfefield[0][3]);
    printf("┣━━━━╋━━━━╋━━━━╋━━━━┫\n");
    printf("┃%s┃%s┃%s┃%s┃\n", tfefield[1][0], tfefield[1][1], tfefield[1][2], tfefield[1][3]);
    printf("┣━━━━╋━━━━╋━━━━╋━━━━┫\n");
    printf("┃%s┃%s┃%s┃%s┃\n", tfefield[2][0], tfefield[2][1], tfefield[2][2], tfefield[2][3]);
    printf("┣━━━━╋━━━━╋━━━━╋━━━━┫\n");
    printf("┃%s┃%s┃%s┃%s┃\n", tfefield[3][0], tfefield[3][1], tfefield[3][2], tfefield[3][3]);
    printf("┗━━━━┻━━━━┻━━━━┻━━━━┛\n");
}

void tfeTurn(){
    int tfeDirection = tfePlayerInput();
    bool tfeMoved = false;
    tfeMove(tfeField, tfeDirection, &tfeMoved);
    tfeMerge(tfeField, tfeDirection, &tfeMoved);
    tfeMove(tfeField, tfeDirection, &tfeMoved);
    tfeGenerateNewTile(tfeField, tfeMoved);
    tfeDisplayField(tfeField);
    if(tfeWon() || tfeLost()){
        return false;
    }else{
        return true;
    }
}   

int main(){
    srand(time(NULL));
    int tfeField[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    tfeRules();
    tfeGenerateNewTile(tfeField, true);
    tfeGenerateNewTile(tfeField, true);
    tfeDisplayField(tfeField);

    while(tfeTurn());
}