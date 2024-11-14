#include <gtest/gtest.h>

extern "C" {
    #include "../funcs.c"
    #include "../head.h"
}

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

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}