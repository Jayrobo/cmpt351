#include <iostream>
#include "Trace.h"
#include "Event.h"

using namespace std;

int main()
{	
	//Trace* test_constructor0 = new Trace();
	char* fileName = "sample.json";
	Trace* test_trace = new Trace(fileName);
	test_trace->trace_start(fileName);
	test_trace->trace_event_start("test", "test", "test");
	test_trace->trace_end();



	/*Event* Obj1 = new Event("test", "test", "test");
	cout << "{ \"Name\": " << "\"" << Obj1->getName() << "\", ";
	cout << "\"cat\": " << "\"" << Obj1->getCat() << "\", ";

	if (Obj1->getPh() != NULL)
	{
		cout << "\"ph\": " << "\"" << Obj1->getPh() << "\", ";
	}

	if (Obj1->getPid() != NULL)
	{
		cout << "\"pid\": " << "\"" << Obj1->getPid() << "\", ";
	}

	if (Obj1->getTid() != NULL)
	{
		cout << "\"tid\": " << "\"" << Obj1->getTid() << "\", ";
	}

	cout << "\"ts\": " << "\"" << Obj1->getTs().count() * system_clock::period::num / system_clock::period::den / 1000000 << "\"} " << endl;*/

	system("pause");
	return 0;
}