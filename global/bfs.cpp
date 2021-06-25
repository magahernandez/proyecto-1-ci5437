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
#include <iostream>
#define MAX_LINE_LENGTH 999

using namespace std;

int BFS(state_t * goal, int duplicate) {

  state_t state, child; // NOTE: "child" will be a predecessor of state, not a successor
  PriorityQueue < state_t > open; // used for the states we have generated but not yet expanded (the OPEN list)
  state_map_t * map = new_state_map(); // contains the cost-to-goal for all states that have been generated
  int dist, d, ruleid, hist2, history;
  ruleid_iterator_t iter; // iterator over rules for state
  history = init_history;
  unordered_map < int, int > nodes;
  int * new_history;

  /* add goal state */
  open.Add(0, 0, * goal);
  if (duplicate) {
    state_map_add(map, goal, history);
  }

  // get current distance from goal; since operator costs are
  // non-negative this distance is monotonically increasing
  d = open.CurrentPriority();

  while (!open.Empty()) {
    if (open.CurrentPriority() == d) {
      nodes[d] = nodes[d] + 1;
    } else if (d == 0) {
      printf("\n%d\t%d\t", d, nodes[d]);
      d = open.CurrentPriority();
      nodes[d] = 1;
    } else {
      printf("%f\n%d\t%d\t", (float) nodes[d] / (float) nodes[d - 1], d, nodes[d]);
      d = open.CurrentPriority();
      nodes[d] = 1;
    }

    // remove top state from priority state
    state = open.Top();
    open.Pop();

    if (duplicate) {
      new_history = state_map_get(map, & state);
      history = * new_history;
    }

    // look at all predecessors of the state
    init_bwd_iter( & iter, & state);

    while ((ruleid = next_ruleid( & iter)) >= 0) {

      if (duplicate) {
        //init_fwd_iter(&iter, &state);
        if (!bwd_rule_valid_for_history(history, ruleid)) continue;
        apply_bwd_rule(ruleid, & state, & child);

        hist2 = next_bwd_history(history, ruleid);
        state_map_add(map, & child, hist2);
      } else {
        apply_bwd_rule(ruleid, & state, & child);
      }
      int child_d = d + get_bwd_rule_cost(ruleid);
      open.Add(child_d, child_d, child);
    }
  }

  return -1;
}

int main(int argc, char ** argv) {
  printf("BFS\n");
  printf("D\tNodes\tBranch\n");
  state_t goal;
  int result, goal_id, duplicate;
  duplicate = atoi(argv[1]);
  printf("%s", argv[1]);
  // add goal states
  first_goal_state( & goal, & goal_id);

  // BFS
  BFS( & goal, duplicate);
}