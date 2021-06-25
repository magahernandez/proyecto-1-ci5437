# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=1

psvn2c_core.c:
	cp ../../../psvn-for-ci5437/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../../psvn-for-ci5437/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../../psvn-for-ci5437/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

priority_queue.hpp:
	cp ../../../global/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp ../../../global/node.hpp ./node.hpp

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../../psvn-for-ci5437/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../../../psvn-for-ci5437/../global/succ.c
	$(CC) $(OPT) ../../../psvn-for-ci5437/../global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../../psvn-for-ci5437/../global/dist.cpp
	$(CXX) $(OPT) ../../../psvn-for-ci5437/../global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../../psvn-for-ci5437/../global/distSummary.cpp
	$(CXX) $(OPT) ../../../psvn-for-ci5437/../global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	$(CXX) $(OPT) ../../../psvn-for-ci5437/src/abstractor.cpp ../../../psvn-for-ci5437/src/psvn.cpp -o $@

%.gen: %.c ../../../psvn-for-ci5437/../global/generator.cc
	$(CXX) $(OPT) ../../../psvn-for-ci5437/../global/generator.cc -include $< -o $@
	rm -f $*.c

%.bfs: %.c ../../../global/bfs.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) -std=c++11 ../../../global/bfs.cpp -include $< -o $@
	
.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.c *.dist_pdb *.aStar *.hpp psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~