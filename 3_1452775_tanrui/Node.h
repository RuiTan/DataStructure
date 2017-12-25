#pragma once
#ifndef NODE_H
#define NODE_H
#include "Maze.h"

class Node{
friend class Maze;
public:
	Node();
	Node(char);
	~Node();
private:
	Node *left, *right, *up, *down;
	int x_index, y_index;
	bool is_road;
	char data;
};

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

#endif // !NODE_H

