#ifndef QUEEN_H
#define QUEEN_H

class Queen{
	friend class Chessboard;
public:
	Queen(){};
	Queen(int _x, int _y):index_x(_x),index_y(_y){};
	~Queen(){};

private:
	int index_x, index_y;
};



#endif