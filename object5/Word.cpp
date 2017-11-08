#include"Word.h"

Word::Word(){
	count = 0;
}
Word::Word(std::string _word, int _count):word(_word), count(_count){}
Word::~Word() {};