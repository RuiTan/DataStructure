#include "Node.h"

Node::Node(){
	left = right = up = down = NULL;
	x_index = y_index = 0;
}
Node::Node(char _data) {
	Node();
	data = _data;
}
Node::~Node() {
	left = right = up = down = NULL;
	x_index = y_index = 0;
}
