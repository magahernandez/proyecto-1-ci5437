#include <vector>
#include "priority_queue.hpp"
#include "node.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <stdbool.h>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>

#define MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes;

Node * dfs(Node * n, unsigned bound, unsigned * nextBound,
  const int history) {
  unsigned t = INT_MAX;
  unsigned f = ( * n).g + heuristic(( * n).state);
  state_t child; // NOTE: "child" will be a predecessor of state, not a successor
  int ruleid;
  int c_history;
  ruleid_iterator_t iter;
  Node * next;

  if (f > bound) {
    * nextBound = f;
    return NULL;
  }

  if (is_goal( & ( * n).state)) {
    * nextBound = ( * n).g;
    return n;
  }

  ++nodes;

  init_fwd_iter( & iter, & ( * n).state); // initialize iterator
  while ((ruleid = next_ruleid( & iter)) >= 0) {
    apply_fwd_rule(ruleid, & ( * n).state, & child); // Apply rule to the state

    if (!fwd_rule_valid_for_history(history, ruleid))
      continue;
    c_history = next_fwd_history(history, ruleid); // next history for child

    Node n_child(child, n, (( * n).g + 1));
    next = dfs( & n_child, bound, nextBound, c_history); // Again
    if (next != NULL) {
      return next;
    }
    t = std::min(t, * nextBound);
  }
  * nextBound = t;
  return NULL;
}

Node idaStar(state_t * start) {
  Node init( * start, NULL, 0);
  Node * final;
  unsigned bound = heuristic( * start);
  unsigned nextBound;

  while (true) {
    final = dfs( & init, bound, & nextBound, init_history);

    if (final != NULL) {
      return *final;
    }
    bound = nextBound;
  }

}

int main(int argc, char ** argv) {

  // VARIABLES FOR INPUT
  char str[MAX_LINE_LENGTH + 1];
  ssize_t nchars;
  state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

  ifstream file;
  string line;
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

  printf("Id \t Instance \t\t\t\t\t Time-In-Secs \tGenerated Nodes\t\tDistance\t\n");

  while (!file.eof()) {

    getline(file, line);

    nchars = read_state(line.c_str(), & state);
    if (nchars <= 0) {
      printf("ERROR");
      continue;
    }

    startTime = clock();
    nodes = 0;
    Node a_star = idaStar( & state);
    endTime = clock();
    runTime = (endTime - startTime) / (double) CLOCKS_PER_SEC;
    ++number_of_lines;

    printf("%d \t %s \t %f \t %ld \t\t\t %d\n", number_of_lines, line.c_str(), runTime, nodes, a_star.g);

  }

  file.close();

  return 0;
}