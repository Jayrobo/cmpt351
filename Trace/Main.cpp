#include <iostream>
#include "Trace.h"
#include "Event.h"

using namespace std;

int main()
{	
	//Trace* test_constructor0 = new Trace();
	Trace* test_constructor1 = new Trace("Sample.json");
	
	system("pause");
	return 0;
}