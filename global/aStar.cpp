#include <vector>
#include "priority_queue.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <time.h>

#define  MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes;

int aStar(state_t *state){
    return -1;
}

int main(int argc, char **argv){

    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    ifstream file;
    string line;
    int a_star_distance;
    float runTime;
    clock_t startTime, endTime;
    int number_of_lines = 0;

    printf("Input test: ");

    if (fgets(str, sizeof str, stdin) == NULL) {
        printf("ERROR");
        return 0;
    }

    str[strlen(str)-1] = '\0';
    file.open(str);

    if (!file.is_open()) {
        printf("ERROR");
        return -1;
    }

    printf("Id \t Instance \t\t\t\t Time-In-Secs \tGenerated Nodes\t\tDistance\t\n");

    while (!file.eof()) {

        getline(file, line);

        nchars = read_state(line.c_str(), &state);
        if (nchars <= 0) {
            printf("ERROR");
            continue;
        }

        startTime = clock();
        nodes = 0; 
        a_star_distance = aStar(&state);
        endTime = clock();
        runTime = (endTime - startTime) / (double) CLOCKS_PER_SEC;
        ++number_of_lines;

        printf("%d \t %s \t %f \t %ld \t\t\t %d\n",number_of_lines, line.c_str(), runTime, nodes, a_star_distance);
        
    }

    file.close();

    return 0;
}