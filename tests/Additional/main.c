#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>
#include "../../funcs.c"
#define BUFFER_SIZE 4096




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


TEST(ReadIntegerTest, sqrt1){
    long long N = 2025;
    EXPECT_EQ(mysqrt(2025), 45);
}

TEST(ReadIntegerTest, sqrt2){
    long long N = 2;
    EXPECT_NEAR(mysqrt(N), 1.414213562, 0.00001); 
}

TEST(ReadIntegerTest, checkSquare1_ODD){
    int n = 3;
    long long **square = (long long **)malloc(n * sizeof(long long *));
    for (long long i = 0; i < n; i++) {
        square[i] = (long long *)malloc(n * sizeof(long long));
        for (long long j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }
    oddMagicSquare(square, n);
    
    EXPECT_EQ(checkSquare(square, n), 1); 

    for (long long i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

TEST(ReadIntegerTest, checkSquare1_twiceEVEN){
    int n = 4;
    long long **square = (long long **)malloc(n * sizeof(long long *));
    for (long long i = 0; i < n; i++) {
        square[i] = (long long *)malloc(n * sizeof(long long));
        for (long long j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }
    twiceEvenMagicSquare(square, n);
    
    EXPECT_EQ(checkSquare(square, n), 1); 

    for (long long i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

TEST(ReadIntegerTest, checkSquare1_EVEN){
    int n = 6;
    long long **square = (long long **)malloc(n * sizeof(long long *));
    for (long long i = 0; i < n; i++) {
        square[i] = (long long *)malloc(n * sizeof(long long));
        for (long long j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }
    evenMagicSquare(square, n);
    
    EXPECT_EQ(checkSquare(square, n), 1); 

    for (long long i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}






int main() {
    printf("Программа, для построения магического квадрата\n");
    printf("Выполнил Бибиков Максим, группа 453502\n");
    long long max_N = mysqrt((16 + get_free_memory()) / 8);
    printf("Введите порядок магического квадрата(натуральное число, не превосходящее %lld): ", max_N);
    long long N = stringToInteger();
        
    while(N < 1 || N == 2){
        if(N < 1){
        printf("Некорекктный ввод! Введите N(натуральное число не превосходящее %lld): ", max_N);
        }else if(N == 2){
            printf("Невозможно построить магический квадрат с порядком 2! Введите новое N: ");
        }
        N = stringToInteger();
    }

    magicSquare(N);
    return RUN_ALL_TESTS();
}



