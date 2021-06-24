#include <iostream>

state_map_t *map1;
abstraction_t *abs1;
state_t abs_state1;

state_map_t *map2;
abstraction_t *abs2;
state_t abs_state2;

state_map_t *map3;
abstraction_t *abs3;
state_t abs_state3;

state_map_t *map4;
abstraction_t *abs4;
state_t abs_state4;

void PDB(){

	FILE *f1 = fopen("24-puzzle_abstraction_4.pdb","r");
	abs1 = read_abstraction_from_file("24-puzzle_abstraction_4.abst");
	map1 = read_state_map(f1);
	fclose(f1);

	FILE *f2 = fopen("24-puzzle_abstraction_5.pdb","r");
	abs2 = read_abstraction_from_file("24-puzzle_abstraction_5.abst");
	map2 = read_state_map(f2);
	fclose(f2);

	FILE *f3 = fopen("24-puzzle_abstraction_6.pdb","r");
	abs3 = read_abstraction_from_file("24-puzzle_abstraction_6.abst");
	map3 = read_state_map(f3);
	fclose(f3);

	FILE *f4 = fopen("24-puzzle_abstraction_7.pdb","r");
	abs4 = read_abstraction_from_file("24-puzzle_abstraction_7.abst");
	map4 = read_state_map(f4);
	fclose(f4);
}

unsigned heuristic(state_t state){
	
	// compute PDB value for state
	abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);
	abstract_state(abs3, &state, &abs_state3);
	abstract_state(abs4, &state, &abs_state4);

	return (*state_map_get(map1, &abs_state1) + *state_map_get(map2, &abs_state2) + *state_map_get(map3, &abs_state3) + *state_map_get(map4, &abs_state4));
}