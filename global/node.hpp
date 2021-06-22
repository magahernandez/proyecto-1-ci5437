#ifndef _NODE_HPP
#define _NODE_HPP

class Node {
    
    public:
    	state_t state;	// Node state
    	Node *parent;   // Parent node
    	unsigned g;	    // Cost
    	Node(state_t state, Node *parent, unsigned g);
};

Node::Node(state_t new_state, Node *new_parent, unsigned new_g) {
	state = new_state;
	parent = new_parent;
	g = new_g;
}
#endif // _NODE_HPP