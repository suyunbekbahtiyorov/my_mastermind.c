 #include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char* input_str(){ 
    char ch;
    int i = 0;
    char* a = (char*)malloc(sizeof(char)*15);
    while(read(0, &ch, 1) > 0){
        if(ch == '\n'){
            return a;
        }
        a[i++] = ch;
    }
    return NULL;
}

int str_ind(char* a,char b){
    for(int i = 0; a[i]; i++){
        if(a[i] == b){
            return i;
        }
    }
    return 0;
}

int sort(char* a,char b){
    for(int i = 0; a[i]; i++){
        if(a[i] == b){
            return 1;
        }
    }
    return 0;
}

int my_strlen(char* inp){
    int i;
    for(i = 0; inp[i]; i++){}
    return i;
}

int wrong(char* a){
    if(my_strlen(a) != 4){
        return 1;
    }
    for(int i = 0;a[i];i++){
        if(a[i] < '9' && a[i] > '0'){
            return 1;
        }else{
            for(int l = i+1;a[l];l++){
                if(a[i] == a[l]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int well_p(char* a,char* b){
    int well_p = 0;
    for(int i = 0;a[i];i++){
        if(a[i] == b[i]){
            well_p++;
        }
    }
    return well_p;
}

int miss_p(char* a,char* b){
    int miss_p = 0;
    for(int i = 0;a[i];i++){
        if(a[i] != b[i]){
            for(int k = 0;b[k];k++){
                if(a[i] == b[k]){
                    miss_p++;
                    break;
                }
            }
        }
    }
    return miss_p;
}

char* random_num(){
    char* secret = (char*)malloc(4);
    int ind = 0;
    srand(time(0));
    while(strlen(secret) < 4){
        char con = rand() % 8 + '0';
        if(sort(secret, con) == 0){
            secret[ind] = con;
            ind++;
        }
    }
    return secret;
}

void mastermind_input(char* secret, int round){
    char* input = (char*)malloc(4);
    int i = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while(i < round){
        printf("---\nRound %d\n",i);
        write(0,">",1);
        input = input_str();
        if(input == NULL) return;
        if(!wrong(input)){
            printf("Wrong input!\n");
            continue;
        }
       
        if(well_p(secret,input) == 4){
            printf("Congratz! You did it! \n");
            break;
        }
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n",well_p(secret,input),miss_p(secret,input));
        i++;
    }
}

void mastermind(int ac,char** av){
    int flag_1 = 0,flag_2 = 0;
    char* secret = (char*)malloc(4);
    int round;
    for(int i = 0; i < ac; i++){
        if(strcmp(av[i], "-c") == 0){
            secret = av[i+1];
            flag_1++;
        }
         if(strcmp(av[i], "-t") == 0){
            round = atoi(av[i+1]);
            flag_2++;
        }
    }
    if(flag_1 == 0){
        secret = random_num();
    }else if(flag_2 == 0){
        round = 10;
    }
    mastermind_input(secret, round);
}

int main(int ac, char**av) {
    mastermind(ac, av);
}
