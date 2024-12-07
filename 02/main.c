#include <stdio.h>
#include <unistd.h>


int isSafe(int arr[]){
    int diff = arr[1] - arr[0];
    if (diff == 0 || diff > 3 || diff < -3)
        return 0;

    if (diff > 0)
        for(int i = 2; i<20 && arr[i] != 0; i++){
            diff = arr[i] - arr[i-1];
            if (diff == 0 || diff < 0 || diff > 3)
                return 0;
        }
    else for(int i = 2; i<20 && arr[i] != 0; i++){
            diff = arr[i] - arr[i-1];
            if (diff == 0 || diff > 0 || diff < -3)
                return 0;
        };
    return 1;
}
void del(int arr[], int pos){
    int i;
    for(i = pos; arr[i]!=0; i++){
        arr[i] = arr[i+1];
    }
}
void add(int arr[], int pos, int val){
    int i;
    for(i = 0; arr[i] != 0; i++);
    for(; i != pos; i--){
        arr[i] = arr[i-1];
    }
    arr[i] = val;
}
void dampener(int arr[]){
    int buffer;
    for(int i = 0; arr[i] != 0; i++){
        buffer = arr[i];
        del(arr, i);
        if(isSafe(arr))
            return;
        add(arr, i, buffer);
    }
}

int main() {

    ///directory of the input archive
    char* dir="/home/choped/Documents/projects/advent_of_code/02";

    ///name of the file with the data
    char* file_name="input";

    chdir(dir);

    FILE *f = fopen(file_name, "r");

    int buffer[20];
    int i, count = 0;

    while(!feof(f)){
        i = 0;
        fscanf(f, "%d", buffer + i);
        while(fgetc(f) == ' '){
            i++;
            fscanf(f, "%d", buffer + i);
        }
        count += isSafe(buffer);


        for(int j = 0; j<20; j++)
            buffer[j] = 0;
    };
    printf("First part: %d\n", count);

    rewind(f);
    count = 0;
    int bool;
    while(!feof(f)){
        i = 0;
        fscanf(f, "%d", buffer + i);
        while(fgetc(f) == ' '){
            i++;
            fscanf(f, "%d", buffer + i);
        }
        bool = isSafe(buffer);
        if(!bool){
            dampener(buffer);
            bool = isSafe(buffer);
        }
        count += bool;

        for(int j = 0; j<20; j++)
            buffer[j] = 0;
    };
    printf("Second part: %d\n", count);

    return 0;
}