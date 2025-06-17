#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


int pasar_a_num(char arr[], int tal) {
    int num = 0;
    for (int i = 0; i < tal; ++i) {
        num = num * 10 + (arr[i] - '0');
    }
    return num;
}


int calculate_sum(int sol[], int n, int posDo[], int do_size, int posDont[], int dont_size, int posMulIni[]) {

    int sum = 0;

    bool include[n];

    for (int i = 0; i < n; i++) {
        include[i] = true;
    }

    int menor = do_size >= dont_size ? dont_size : do_size;

    for (int i = 0; i < menor; ++i) {
        for (int j = 0; j < n; ++j) {
            if (posDo[i] <= posMulIni[j]){
                include[j] = true;
            }
            if (posDont[i] <= posMulIni[j]){
                include[j] = false;
            }
        }
    }

    if (menor == do_size) {

        for (int i = menor; i < dont_size; ++i) {
            for (int j = 0; j < n; ++j) {
                if (posDont[i] <= posMulIni[j]){
                    include[j] = false;
                }
            }
        }

    } else if (menor == dont_size) {

        for (int i = menor; i < do_size; ++i) {
            for (int j = 0; j < n; ++j) {
                if (posDont[i] <= posMulIni[j]){
                    include[j] = false;
                }
            }
        }

    }

    for (int i = 0; i < n; i++) {
        if (include[i]) {
            sum += sol[i];
        }
    }

    return sum;
}
int main(void) {
    ///directory of the input archive
    char* dir="/home/choped/Documents/projects/advent_of_code/03";

    ///name of the file with the data
    char* file_name="test";

    chdir(dir);

    FILE *f = fopen(file_name, "r");

    if(f == NULL){
        printf("putada no abre o no existe");
        return -1;
    }

    char ch;

    int sol[10000];

    int l = 0;

    int pos = 0;

    int numMul = 0;

    int posInicial = 0;

    int numDo = 0;

    int numDont = 0;

    int posMulIni[10000];

    int posMulFin[10000];

    int posDo[10000];

    int posDont[10000];

    while ((ch = fgetc(f)) != EOF){

        if(ch == 'm'){

            posInicial = pos;

            pos++;
            if((ch = fgetc(f)) == EOF)
                break;

            if (ch == 'u'){
                pos++;
                if((ch = fgetc(f)) == EOF)
                    break;

                if (ch == 'l'){
                    pos++;
                    if((ch = fgetc(f)) == EOF)
                        break;

                    if (ch == '('){
                        pos++;
                        if((ch = fgetc(f)) == EOF)
                            break;

                        int i = 0;
                        char int1[100];

                        while((ch - '0') >= 0 && (ch - '0') <= 9) {

                            int1[i] = ch;
                            i++;

                            pos++;
                            if ((ch = fgetc(f)) == EOF)
                                break;
                        }

                        if (ch == ','){
                            pos++;
                            if((ch = fgetc(f)) == EOF)
                                break;

                            int j = 0;
                            char int2[100];

                            while ((ch - '0') >= 0 && (ch - '0') <= 9){

                                int2[j] = ch;
                                j++;

                                pos++;
                                if((ch = fgetc(f)) == EOF)
                                    break;
                            }

                            if(ch == ')'){

                                int x = pasar_a_num(int1, i);

                                int y = pasar_a_num(int2, j);

                                sol[l] = x * y;

                                posMulIni[l] = posInicial;

                                posMulFin[l] = pos;

                                l++;

                                numMul = l;
                            }
                        }
                    }
                }
            }
        }
        pos++;
    }

    int sum = 0;

    for (int i = 0; i < l; ++i) {
        sum += sol[i];
    }

    printf("%d\n", sum);

    fclose(f);

    f = fopen(file_name, "r");

    pos = 0;

    l = 0;

    while ((ch = fgetc(f)) != EOF){

        if(ch == 'd'){

            posInicial = pos;

            pos++;
            if((ch = fgetc(f)) == EOF)
                break;

            if (ch == 'o'){
                pos++;
                if((ch = fgetc(f)) == EOF)
                    break;

                if (ch == '('){
                    pos++;
                    if((ch = fgetc(f)) == EOF)
                        break;

                    if (ch == ')'){

                        posDo[l] = posInicial;

                        l++;

                        numDo = l;

                    }
                }
            }
        }
        pos++;
    }

    fclose(f);

    f = fopen(file_name, "r");

    pos = 0;

    l = 0;

    while ((ch = fgetc(f)) != EOF){

        if(ch == 'd'){

            posInicial = pos;

            pos++;
            if((ch = fgetc(f)) == EOF)
                break;

            if (ch == 'o'){
                pos++;
                if((ch = fgetc(f)) == EOF)
                    break;

                if (ch == 'n'){
                    pos++;
                    if((ch = fgetc(f)) == EOF)
                        break;

                    if (ch == '\''){
                        pos++;
                        if((ch = fgetc(f)) == EOF)
                            break;

                        if(ch == 't'){
                            pos++;
                            if((ch = fgetc(f)) == EOF)
                                break;

                            if (ch == '('){
                                pos++;
                                if((ch = fgetc(f)) == EOF)
                                    break;

                                if (ch == ')'){

                                    posDont[l] = posInicial;

                                    l++;

                                    numDont = l;

                                }
                            }
                        }
                    }
                }
            }
        }
        pos++;
    }

    int dammn = calculate_sum(sol, numMul, posDo, numDo, posDont, numDont, posMulIni);

    printf("%d\n", dammn);
}