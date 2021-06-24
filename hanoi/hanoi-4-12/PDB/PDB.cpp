#include <iostream>

state_map_t *map1;
abstraction_t *abs1;
state_t abs_state1;

state_map_t *map2;
abstraction_t *abs2;
state_t abs_state2;

unsigned max;

void PDB(){

	FILE *f1 = fopen("hanoi-12-4_abstraction_1.pdb","r");
	abs1 = read_abstraction_from_file("hanoi-12-4_abstraction_1.abst");
	map1 = read_state_map(f1);
	fclose(f1);

	FILE *f2 = fopen("hanoi-12-4_abstraction_2.pdb","r");
	abs2 = read_abstraction_from_file("hanoi-12-4_abstraction_2.abst");
	map2 = read_state_map(f2);
	fclose(f2);
}

unsigned heuristic(state_t state){

	// compute PDB value for state
	abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);

	max = std::max(*state_map_get(map1, &abs_state1), (*state_map_get(map2, &abs_state2)));

	return (max);
}