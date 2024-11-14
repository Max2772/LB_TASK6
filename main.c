#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
#define BUFFER_SIZE 4096

int parse_int(char *string, int *integer);
int stringToInteger();
long long get_free_memory();
long double mysqrt(long long x);
void magicSquare(long long n);
void evenMagicSquare(long long **square, long long n);
void twiceEvenMagicSquare(long long **square, long long n);
void oddMagicSquare(long long **square, long long n);
int checkSquare(long long **square, long long n);

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
    return 0;
}

int checkSquare(long long **square, long long n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += square[i][0];
    }
    int temp;
    for(int i = 0; i < n; i++){ // Проверка строк
        temp = 0;
        for(int j = 0; j < n; j++){
            temp += square[i][j];
        }
        if(temp != sum)
            return 0;
    }

    for(int i = 1; i < n; i++){ // Проверка столбцов
        temp = 0;
        for(int j = 0; j < n; j++){
            temp += square[i][j];
        }
        if(temp != sum)
            return 0;
    }
    temp = 0;
    for(int i = 0, j = 0; i < n; i++, j++){ // Проверка главной диагонали
        temp += square[i][j];
    }
    if(temp != sum)
        return 0;

    temp = 0;

    for(int i = n - 1, j = 0; i >= 0; i--, j++){ // Проверка побочной диагонали
    temp += square[i][j];
    }
    if(temp != sum)
        return 0;

    return 1;
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

int stringToInteger(){
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


long double mysqrt(long long x){
    long double left = 0;
    long double right = x;
    long double middle;
    for(int i = 0; i < 200; i++){
        middle = (left + right) / 2;
        if(middle * middle > x){
            right = middle;
        }else if(middle * middle < x){
            left = middle;
        }
    }
    return middle;
}

long long get_free_memory() {
    FILE *fp = fopen("/proc/meminfo", "r");
    
    long free_memory = 0;
    long swap_memory = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemAvailable: %ld kB", &free_memory) == 1) {
            free_memory *= 1024;
            break;
        }
    }
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "SwapFree: %ld kB", &swap_memory) == 1) {
            swap_memory *= 1024;
            break;
        }
    }
    fclose(fp);
    return free_memory + swap_memory;
}

void magicSquare(long long n){
    long long **square = (long long **)malloc(n * sizeof(long long *));
    for (long long i = 0; i < n; i++) {
        square[i] = (long long *)malloc(n * sizeof(long long));
        for (long long j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }

    if(n % 2 == 1){
        oddMagicSquare(square, n);
    }else if(n % 4 == 0){
        twiceEvenMagicSquare(square, n);
    }else{
        evenMagicSquare(square, n);
    }
    long long N = checkSquare(square, n);
    printf("Магический квадрат порядка %lld:\n", N);
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < n; j++) {
            printf("%10lld ", square[i][j]);
        }
        printf("\n");
    }

    for (long long i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}

void evenMagicSquare(long long **square, long long n) {
    oddMagicSquare(square, n / 2);
    for (int z = 0; z < n / 2; z++) {
        for (int y = 0; y < n / 2; y++) {
            square[z + n / 2][y + n / 2] = square[z][y] + n * n / 4;
            square[z][y + n / 2] = square[z][y] + 2 * n * n / 4;
            square[z + n / 2][y] = square[z][y] + 3 * n * n / 4;
        }
    }

    int pillar = n / 2 - 3;

    for (int z = 0; z < n / 2; z++) {
        for (int y = (n / 2) - (pillar / 2); y < (n / 2) + (pillar / 2); y++) {
            int k;
            k = square[z][y];
            square[z][y] = square[z + n / 2][y];
            square[z + n / 2][y] = k;
        }
    }

    int k;
    k = square[0][0];
    square[0][0] = square[n / 2][0];
    square[n / 2][0] = k;

    k = square[n / 2 - 1][0];
    square[n / 2 - 1][0] = square[n - 1][0];
    square[n - 1][0] = k;

    for (int z = 1; z < n / 2 - 1; z++) {
        int k;
        k = square[z][1];
        square[z][1] = square[z + n / 2][1];
        square[z + n / 2][1] = k;
    }

}

void twiceEvenMagicSquare(long long **square, long long n){
    long long num = 1;
    long long i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++, num++) {
            square[i][j] = num;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if((i < n / 4 || i >= 3 * n / 4) && (j < n / 4 || j >= 3 * n / 4)){
                square[i][j] = n * n + 1 - square[i][j];
            }else if ((i >= n / 4 && i < 3 * n / 4) && (j >= n / 4 && j < 3 * n / 4)){
                square[i][j] = n * n + 1 - square[i][j];
            }
        }
    }
}

void oddMagicSquare(long long **square, long long n){
    long long num = 1;
    long long i = 0, j = n / 2;

    while (num <= n * n) {
        square[i][j] = num;
        num++;
        long long newi = (i - 1 + n) % n;
        long long newj = (j + 1) % n;

        if (square[newi][newj] != 0) {
            i = (i + 1) % n;
        } else {
            i = newi;
            j = newj;
        }
    }
}