#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_bracket(char* array)
{
    char* string = (char*)malloc(strlen(array) + 2 * sizeof(char));
    string[0] = '(';
    int i = 1;
    for(int y = 0; array[y]; y++){
        string[i++] = array[y];
    }
    string[i++] = ')';
    return string;
}

int check_is_correct(char* bracket){
    int sum = 0;
    for(int i = 0 ; bracket[i]; i++){
        if(bracket[i] == '/' && bracket[i+1] == '0'){
            printf("divide by zero");
            return 1;
        }
        if(bracket[i] == '(') sum++;
        else if(bracket[i] == ')') sum--;
        if(sum < 0){
            printf("parse error\n");
            return 1;
        }
    }
    if(sum != 0){
        printf("parse error\n");
        return 1;
    }
    return 0;
}

char* reverse(char* s1, char opt){
    char* str = malloc(strlen(s1));
    int i = 0;
    if(opt == '-'){
        str[0] = opt;
        i++;
    }
    for(int j = strlen(s1) -1; j >= 0; j--){
        str[i++] = s1[j];
    }
    return str;
}

char* get_last(char* bracket){
    char* result = malloc(sizeof(char) * strlen(bracket));
    for(int i = 0; bracket[i]; i++){
        if(bracket[i] == ')'){
            for(int j = i, ind = 0; 1; j--){
                result[ind++] = bracket[j];
                if(bracket[j] == '(') return reverse(result, '+');
            }
        }
    }
    return NULL;
}

char* to_level( char* last_bracket){
    char* result = malloc(strlen(last_bracket));
    for(int i = 0 , ind = 0; last_bracket[i]; i++){
        if((last_bracket[i] == '+' && last_bracket[i + 1] == '-') || (last_bracket[i] == '-' && last_bracket[i + 1] == '+' )){
            result[ind++] = '-';
            i++;
        }else if( last_bracket[i] == '+' && last_bracket[i + 1] == '+'){
            result[ind++] = '+';
            i++;
        }else if( last_bracket[i] == '-' && last_bracket[i + 1] == '-'){
            result[ind++] = '+';
            i++;
        }else{
            result[ind++] = last_bracket[i];
        }
    }
    return result;
}

int check_is_operator(char symbl){
    if(symbl == '+' || symbl == '-' || symbl == '/' || symbl == '*' || symbl == '%') return 1;
    return 0;
}

char* int_to_char(int dec){
    char* result = malloc(50);
    int i = 0;
    char flag = '+';
    if(dec < 0){
        dec = dec * -1;
        flag = '-';
    }
    while(dec){
        result[i] = dec % 10 + 48;
        dec = dec/10;
        i++;
    }
    return reverse(result , flag);
}

char* result_(int left, int right, char operator){
    int temp;
    if(operator == '+' ){
        temp = left + right;
        return int_to_char(temp);
    }else if(operator == '-'){
        temp = left - right;
        return int_to_char(temp);
    }else if(operator == '*'){
        temp = left * right;
        return int_to_char(temp);
    }else if(operator == '/'){
        temp = left / right;
        return int_to_char(temp);
    }else if(operator == '%'){
        temp = left % right;
        return int_to_char(temp);
    }
    return NULL;
}

int move_to_left(char* last_bracket, int i ){
    for(; i >= 0; i--){
        if( last_bracket[i] == '-' || (last_bracket[i] <= '9' && last_bracket[i] >= '0')){   
        }else {
            return i+1;
        }
    }
    return i;
}


int move_to_right(char* last_bracket, int i ){
    for(; last_bracket[i]; i++){
        if(last_bracket[i] == '-' || (last_bracket[i] <= '9' && last_bracket[i] >= '0')){
            return i;
        }
    }
    return i;
}

int move_right(char* last_bracket, int i){
    int num = i;
    for(; last_bracket[i]; i++){
        if( (last_bracket[i] <= '9' && last_bracket[i] >= '0') || (last_bracket[num] == '-' && num == i)){
        }else {
            return  i - 1;
        }
    }
    return i-1;
}

char* add_result( char* last_bracket, char* result, int left, int right){
    char* str = malloc(strlen(last_bracket));
    int flag = 0;
    int ind = 0;
    for(int i = 0 ; last_bracket[i]; i++){
        if(i == left){
            flag = 1;
            while (*result) {
                str[ind++] = *result;
                result++;
            }
        }
        else if(flag == 0) str[ind++] = last_bracket[i];
        else if( i == right) flag = 0;
    }
    return str;
}

char* run(char* last_bracket, int i){
    char* result;
    int num = atoi(&last_bracket[move_to_left(last_bracket, i-1 )]);
    int sum = atoi(&last_bracket[move_to_right(last_bracket, i+1)]);
    result = result_(num, sum,last_bracket[i]);
    last_bracket = add_result(last_bracket,result, move_to_left(last_bracket, i - 1) , move_right(last_bracket, i+1));
    return last_bracket;
}

char* remake_(char* last_bracket){
    for(int i = 0; last_bracket[i]; i++){
        if(last_bracket[i] == '*'){    
            last_bracket = run(last_bracket, i);
        }
        if(last_bracket[i] == '/'){
            last_bracket = run(last_bracket, i);
        }
        if(last_bracket[i] == '%'){
            last_bracket = run(last_bracket, i);
        }
    }
    for(int i = 0; last_bracket[i]; i++){
        if(last_bracket[i] == '+' && i != 0 && i != 1){
            last_bracket = run(last_bracket, i);
        }
        if(last_bracket[i] == '-' && i != 0 && i != 1){
            last_bracket = run(last_bracket, i);
        }
    }
    return last_bracket;
}

int get_right_bracket_ind(char* bracket){
    int i = 0;
    for(; bracket[i] ; i++)
        if(bracket[i] == ')') return i;
    return i;
}

int get_left_bracket_ind(char* bracket, int i){
    for(;i >= 0; i--)
        if(bracket[i] == '(') return i;
    return i;
}

char* out_of_bracket(char* last_bracket){
    char* result = malloc(strlen(last_bracket));
    int ind = 0;
    for (int i = 1; last_bracket[i] != ')'; i++) {
        result[ind++] = last_bracket[i];
    }
    // printf("%s\n",result);
    return result;
}

char* add_brackets_result( char* bracket, char* last_bracket){
    last_bracket = out_of_bracket(last_bracket);
    int r = get_right_bracket_ind(bracket);
    int l = get_left_bracket_ind(bracket,r);
    char* str = malloc(strlen(bracket));
    int flag = 0;
    int ind = 0;
    for(int i = 0 ; bracket[i]; i++){
        if(i == l){
            flag = 1;
            while (*last_bracket) {
                str[ind++] = *last_bracket;
                last_bracket++;
            }
        }
        else if(flag == 0) str[ind++] = bracket[i];
        else if( i == r) flag = 0;
    }
    return str;
}

int find_bracket(char* s1){
    for(int i = 0; s1[i]; i++){
        if(s1[i] == '(') return 1;
    }
    return 0;
}

void parsing_bracket(char* bracket){
    while (find_bracket(bracket) == 1) {
        char* last_bracket = get_last(bracket);
        last_bracket = to_level(last_bracket);
        last_bracket = remake_(last_bracket);
        bracket = add_brackets_result( bracket, last_bracket);
    }
    printf("%s\n", bracket);
}


char* no_space(char* str){
    char* res = (char*)malloc(sizeof(char)*strlen(str));
    for(int i = 0, ind = 0; str[i]; i++){
        if(str[i] != ' '){
            res[ind++] = str[i];
        }
    }
    return res;
}

int erro(char* str){
    for(int i =0; str[i]; i++){
        if((str[i] == '-' && str[i+1] == '/') || (str[i] == '-' && str[i-1] == '/') || (str[i] == '-' && str[i+1] == '*') || (str[i] == '-' && str[i-1] == '*') || (str[i] == '-' && str[i+1] == '%') || (str[i] == '-' && str[i-1] == '%')){
            return 1;
        }else if((str[i] == '+' && str[i+1] == '/') || (str[i] == '+' && str[i-1] == '/') || (str[i] == '+' && str[i+1] == '*') || (str[i] == '+' && str[i-1] == '*') || (str[i] == '+' && str[i+1] == '%') || (str[i] == '+' && str[i-1] == '%')){
            return 1;
        }else if(str[i] == '(' && str[i+1] == ')'){
            return 1;
        }else if((str[i] >= 65 && str[i] <= 90)|| (str[i] >= 97 && str[i] <= 122)){
            return 1;
        }else if(str[i] == '/' && str[i+1] == '0'){
            return 2;
        }
            
    }
    return 0;
}

int main(int ac, char** av){
    if(ac > 0){
    char* bracket = no_space(av[1]);
    int check = erro(bracket);
    if(check == 1){
        perror("parse error");
        return 1;
    }else if(check == 2){
        perror("divide by zero");
        return 1;
    }
    if ( 1 == check_is_correct(bracket)) return 0;
    bracket = add_bracket(bracket);
    parsing_bracket(bracket);
    }
    return 0;
}
