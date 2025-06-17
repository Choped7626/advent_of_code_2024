#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void ord_shell (int v [], int n) {
    int incremento, i, j, tmp;
    bool seguir;
    incremento = n;

    do {
        incremento /= 2;
        for (i = incremento; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;
            while (j - incremento >= 0 && seguir) {
                if(tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j -  incremento;
                }
                else
                    seguir = false;
            }
            v[j] = tmp;
        }
    } while(incremento != 0);
}

int main(void) {

    ///directory of the input archive
    char* dir="/home/choped/Documents/projects/advent_of_code/01";

    ///name of the file with the data
    char* file_name="input";

    chdir(dir);

    FILE *f = fopen(file_name, "r");
    int ch;
    int lineas = 0;
    int i = 0;

    if(f == NULL){
        printf("putada no abre o no existe");
        return -1;
    }

    while(!feof(f)){
        ch = fgetc(f);
        if(ch == '\n'){
            lineas++;
        }
    }

    fclose(f);

    f = fopen(file_name, "r");

    int lista_izq[lineas], lista_der[lineas];

    ///it would be better to get the info and then use strtol to convert
    ///it to ints but in this case it will work well like this due to the format of the file
    while (fscanf(f, "%d %d", &lista_izq[i], &lista_der[i]) == 2){
        i++;
    }

    ord_shell(lista_izq, lineas);
    ord_shell(lista_der, lineas);

    ///first part

    int distancia_total = 0;

    i = 0;
    int tmp1, tmp2;
    while (i != lineas){
        tmp1 = lista_izq[i] - lista_der[i];
        tmp2 = lista_der[i] - lista_izq[i];

        if (tmp1 > tmp2){
            distancia_total += tmp1;
        }else
            distancia_total += tmp2;

        i++;
    }

    printf("total_distance = %d\n", distancia_total);

    ///first part

    ///second part

    int similarity_score = 0;

    for (int j = 0; j < lineas; ++j) {
        for (int k = 0; k < lineas; ++k) {
            int cnt = 0;
            if(lista_izq[j] == lista_der[k]){
                cnt++;
            }
            similarity_score += lista_izq[j] * cnt;
        }
    }

    printf("similarity_score = %d\n", similarity_score);

    ///second part

}