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
#include <unordered_map>

#define  MAX_LINE_LENGTH 999

using namespace std;

int BFS(state_t *goal, int duplicate){
    return -1;
}

int main(int argc, char **argv)
{
    state_t goal;
    int finished, goal_id, duplicate;
    duplicate = atoi(argv[1]);

    printf("BFS");
    //first_goal_state(&goal, &goal_id);
    finished = BFS(&goal, duplicate);
    return 0;
}
