#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>
#define BUFFER_SIZE 4096

int parse_int(char *string, int *integer);
int countBombs(char **field, int n, int m, int x, int y);
int StringToInteger();






TEST(ReadIntegerTest, INT_ValidInput1) {
    char testString[] = "777\n";  
    int integer;
    
    EXPECT_EQ(parse_int(testString, &integer), 1); 
    EXPECT_EQ(integer, 777); 
}

TEST(ReadIntegerTest, INT_ValidInput2) {
    char testString[] = "3.1415\n";  
    int integer;
    
    EXPECT_EQ(parse_int(testString, &integer), 0);
}

TEST(ReadIntegerTest, INT_ValidInput3) {
    char testString[] = "abc\nkdskosmgomsongonsdgn\n";  
    int integer;
    
    EXPECT_EQ(parse_int(testString, &integer), 0);
}


TEST(ReadIntegerTest, countBombs1){
    int N = 3;
    int M = 3;
    char **field = (char**)malloc(sizeof(char*) * N);
    for(int i = 0; i < N; i++){
        field[i] = (char*)malloc(sizeof(char) * M);
    }
    
    int cnt = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(cnt == 0){
                field[i][j] = ' ';
                cnt++;
            }else{
                field[i][j] = '*';
                cnt--;
            }
        }
    }
        
    EXPECT_EQ(countBombs(field, N, M, 1, 1), 4);

    for(int i = 0; i < N; i++){
        free(field[i]);
    }
    free(field);
}





int main(){
    printf("Программа, для составления игрового поля игры Сапёр\n");
    printf("Выполнил Бибиков Максим, группа 453502\n");
    while(1){
        printf("Введите 1, если хотите выполнить программу, или 2, если хотите завершить работу программы\n");
        int type = StringToInteger();

        if(type == 2)
            break;
        else if(type != 1 && type != 2)
            continue;
        
        
        printf("Введите N(длина поля): ");
        int N;
        while(1){
            N = StringToInteger();
            if(N < 1){
                printf("Некорректный ввод, введите N(Целое неотрицательное число): ");
                continue;
            }
            break;
        }
        printf("Введите M(ширина поля): ");
        int M;
        while(1){
            M = StringToInteger();
            if(M < 1){
                printf("Некорректный ввод, введите M(Целое неотрицательное число): ");
                continue;
            }
            break;
        }
    
    char **arr = (char**)malloc(sizeof(char*) * N);
    for(int i = 0; i < N; i++){
        arr[i] = (char*)malloc(sizeof(char) * M);
    }        

        for(int i = 0; i < N; i++){
            printf("%d строка:\n", i+1);
            for(int j = 0; j < M; j++){
                printf("Введите символ: ");
                arr[i][j] = getchar(); 
                while(arr[i][j] != '.' && arr[i][j] != '*'){
                    printf("Некорректный ввод! Введите *(бомба) или .(пустая ячейка): ");
                    while (getchar() != '\n');
                    arr[i][j] = getchar();
                }
                while (getchar() != '\n'); 
            }
        }
    
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == '*')
                printf("* ");
            else{
                int bombs = countBombs(arr, N, M, i, j);
                arr[i][j] = '0' + bombs;
                printf("%c ", arr[i][j]);
            }
        }
        printf("\n");
    }


        for(int i = 0; i < N; i++){
            free(arr[i]);
        }
        free(arr);
    }

    return RUN_ALL_TESTS();
}



int countBombs(char** field, int N, int M, int x, int y){
    int bombs = 0;
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            int nx = dx + x;
            int ny = dy + y;
            
            if(nx >= 0 && nx < N && ny >= 0 && ny < M && field[nx][ny] == '*')
            bombs++;
        }
    }
    
    return bombs;
}




int parse_int(char *string, int *integer){
    int i = 0;
    while(isspace(string[i])) i++; // while(isspace([string[i]])) i++;
    int length = strlen(string);
    if(length == i) return 0; 

    char int_buffer[BUFFER_SIZE];
    int int_chars = 0;

    if(string[i] == '-'){
        int_buffer[int_chars] = '-';
        int_chars++; i++;

        if(!isdigit(string[i])) return 0;
    }
    
    while(i < length && !isspace(string[i])){ // isspace can't be modifed, fck
        if(!isdigit(string[i])) return 0;
        
        int_buffer[int_chars] = string[i];
        int_chars++;
        i++;
    }
    int_buffer[int_chars] = '\0';

    while(isspace(string[i])) i++; // isspace cmon

    if(string[i] != '\0') return 0;

    *integer = atoi(int_buffer);

    return 1;
}

int StringToInteger(){
        int type;
        int parsed_correct = 1;
        do{
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        parsed_correct = parse_int(buffer, &type);
        if(parsed_correct == 0)
            printf("Некорректный ввод, введите ещё раз!\n");
        }while(parsed_correct == 0);

        return type;
}