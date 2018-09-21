#include <iostream>
#include "Trace.h"
#include "Event.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{	
	//-----------------------Test Trace--------------------------//
	//Trace* test_constructor0 = new Trace();
	///*
	char* fileName = "sample.txt";
	Trace* test_trace = new Trace(fileName);
	test_trace->trace_start(fileName);
	test_trace->trace_event_start("test", "test", "test");
	test_trace->trace_event_end("test2");
	test_trace->trace_event_start("test3", "test3", "test3");
	test_trace->trace_event_end("test2");
	test_trace->trace_counter("ctr", "cats", "10");//check ctr events
	test_trace->trace_end();

	system_clock::time_point tp = system_clock::now();
	system_clock::duration ts = tp.time_since_epoch();
	cout << ts.count()<<endl;

	//*/

	//-----------------------Test Event--------------------------//
	/*
	Event* Obj1 = new Event("test", "test", "test");
	Obj1->setPh("B");
	Obj1->setPid("test");
	Obj1->setTid("test");
	Event* Obj2 = new Event(Obj1);
	Event* head = Obj1;

	Obj1->setEventNext(Obj2);
	Event* temp = head;

	while (temp != NULL)
	{
		cout << "{ \"Name\": " << "\"" << temp->getName() << "\", ";
		cout << "\"cat\": " << "\"" << temp->getCat() << "\", ";

		if (temp->getPh() != NULL)
		{
			cout << "\"ph\": " << "\"" << temp->getPh() << "\", ";
		}

		if (temp->getPid() != NULL)
		{
			cout << "\"pid\": " << "\"" << temp->getPid() << "\", ";
		}

		if (temp->getTid() != NULL)
		{
			cout << "\"tid\": " << "\"" << temp->getTid() << "\", ";
		}

		cout << "\"ts\": " << "\"" << temp->getTs().count() * system_clock::period::num / system_clock::period::den / 1000000 << "\"} " << endl;

		temp = temp->getEventNext();
	}
	*/
	system("pause");
	return 0;
}