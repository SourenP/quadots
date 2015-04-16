#include <iostream>
#include "Space.h"
using namespace std;

int main()
{
	Space *s = new Space(400, 400, 24);

	// Example use
    s->CreateDot(200, 200, 0, 0, 0, make_pair(1,1), 2);
    s->CreateDot(200, 200, 0, 0, 0, make_pair(-1,-1), 2);
    s->CreateDot(200, 200, 0, 0, 0, make_pair(1,-1), 2);
    s->CreateDot(200, 200, 0, 0, 0, make_pair(-1,1), 2);
    s->run();

	delete s;
	return 0;
}