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
#define MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes;

int aStar(state_t * start) {

  state_t state, child; // NOTE: "child" will be a predecessor of state, not a successor
  int g, ruleid;
  ruleid_iterator_t iter;
  PriorityQueue < state_t > open; // used for the states we have generated but not yet expanded (the OPEN list)
  state_map_t * distance = new_state_map(); // contains the distance 

  state_map_add(distance, start, 0);
  open.Add(0, 0, * start);

  while (!open.Empty()) {

    // get current distance from start;
    g = open.CurrentPriority();

    // remove top start from priority state
    state = open.Top();
    open.Pop();

    int * old_distance = state_map_get(distance, & state);
    ++nodes;

    if ((old_distance == NULL) || (g < * old_distance) || (!compare_states( & state, start))) {

      state_map_add(distance, & state, g);

      if (is_goal( & state)) {
        return g;
      }

      init_fwd_iter( & iter, & state); // initialize iterator 
      while ((ruleid = next_ruleid( & iter)) >= 0) {
        apply_fwd_rule(ruleid, & state, & child); // Apply rule to the state

        int child_g = g + get_fwd_rule_cost(ruleid);
        int child_h = heuristic(child);
        int child_f = child_g + child_h;

        if (child_h < INT_MAX) {
          // add to open with the new distance
          open.Add(child_f, child_g, child);

        }
      }
    }
  }
  return -1;
}

int main(int argc, char ** argv) {

  // VARIABLES FOR INPUT
  char str[MAX_LINE_LENGTH + 1];
  ssize_t nchars;
  state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

  ifstream file;
  string line;
  int a_star;
  float runTime;
  clock_t startTime, endTime;
  int number_of_lines = 0;

  PDB();

  printf("Input test: ");

  if (fgets(str, sizeof str, stdin) == NULL) {
    printf("ERROR");
    return 0;
  }

  str[strlen(str) - 1] = '\0';
  file.open(str);

  if (!file.is_open()) {
    printf("ERROR");
    return -1;
  }

  printf("Id \t Instance \t\t\t\t Time-In-Secs \tGenerated Nodes\t\tDistance\t\n");

  while (!file.eof()) {

    getline(file, line);

    nchars = read_state(line.c_str(), & state);
    if (nchars <= 0) {
      printf("ERROR");
      continue;
    }

    startTime = clock();
    nodes = 0;
    a_star = aStar( & state);
    endTime = clock();
    runTime = (endTime - startTime) / (double) CLOCKS_PER_SEC;
    ++number_of_lines;

    printf("%d \t %s \t %f \t %ld \t\t\t %d\n", number_of_lines, line.c_str(), runTime, nodes, a_star);

  }

  file.close();

  return 0;
}