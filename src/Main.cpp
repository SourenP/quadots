#include <iostream>
#include "Space.h"
using namespace std;

int main()
{
	Space *theSpace = new Space(400, 400, 24);
	delete theSpace;	
	return 0;
}