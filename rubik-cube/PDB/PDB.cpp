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

unsigned max;

void PDB(){

	FILE *f1 = fopen("rubik3Sticker_rubik3Sticker_abstraction_corner.pdb","r");
	abs1 = read_abstraction_from_file("rubik3Sticker_rubik3Sticker_abstraction_corner.abst");
	map1 = read_state_map(f1);
	fclose(f1);

	FILE *f2 = fopen("rubik3Sticker_rubik3Sticker_abstraction_edge1.pdb","r");
	abs2 = read_abstraction_from_file("rubik3Sticker_rubik3Sticker_abstraction_edge1.abst");
	map2 = read_state_map(f2);
	fclose(f2);

	FILE *f3 = fopen("rubik3Sticker_rubik3Sticker_abstraction_edge3.pdb","r");
	abs3 = read_abstraction_from_file("rubik3Sticker_rubik3Sticker_abstraction_edge3.abst");
	map3 = read_state_map(f3);
	fclose(f3);
}

unsigned heuristic(state_t state){

	// compute PDB value for state
	abstract_state(abs1, &state, &abs_state1);
	abstract_state(abs2, &state, &abs_state2);
	abstract_state(abs3, &state, &abs_state3);

	max = std::max(*state_map_get(map1, &abs_state1), std::max(*state_map_get(map2, &abs_state2), *state_map_get(map3, &abs_state3)));

	return (max);
}