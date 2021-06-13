#ifndef _NODE_HPP
#define _NODE_HPP

class Node {
    
    public:
    	state_t state;	// Node state
    	Node *parent;   // Parent node
		int rule_id     // Rule id
    	unsigned g;	    // Cost
    	Node(state_t state, Node *parent, int rule_id, unsigned g);
};

#endif // _NODE_HPP