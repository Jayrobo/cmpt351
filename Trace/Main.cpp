#include <iostream>
#include "Trace.h"
#include "Event.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

void recur(int counter, Trace* Event_test);

int main()
{	
	//-----------------------Test Trace--------------------------//
	//Trace* test_constructor0 = new Trace();
	///*
	char* fileName = "sample.json";
	Trace* test_trace = new Trace(fileName);
	test_trace->trace_start(fileName);

	test_trace->trace_event_start("test", "test", "test");
	test_trace->trace_event_start("test2", "test2", "test2");
	recur(50, test_trace);
	test_trace->trace_event_end("test");
	test_trace->trace_event_end("test2");


	//void ptr-www.learncpp.com/cpp-tutorial/613-void-pointers/
	//test code
	//struct test
	//{
	//	int testVar;
	//};
	//test testptr;
	void* ptr;
	ptr = &test_trace;

	//test_trace->trace_object_new("new", ptr); //N
	//test_trace->trace_object_gone("gone",ptr );//D
	
	test_trace->trace_end();
	system("pause");
	return 0;
}

void recur(int counter, Trace* Event_test)
{
	counter--;
	if (counter > 1)
	{
		if (counter% 2 == 1)
		{
			Event_test->trace_event_start("test3", "test3", "test3");
			Event_test->trace_counter("ctr", "cats", "10");//check ctr events
			Event_test->trace_counter("ctr", "cats", "50");//check ctr events
			recur(counter, Event_test);
			Event_test->trace_event_end("test3");
		}
		else
		{
			Event_test->trace_event_start("test4", "test4", "test4");
			Event_test->trace_counter("ctr", "cats", "10");//check ctr events
			Event_test->trace_counter("ctr", "cats", "50");//check ctr events
			recur(counter, Event_test);
			Event_test->trace_event_end("test4");
		}
	}
}











/*steady_clock::time_point tstart = steady_clock::now();
for (int i = 0; i < 5000; i++)
{
cout << " ";
}
steady_clock::time_point tstop = steady_clock::now();

cout << endl <<  duration_cast<microseconds>(tstop - tstart).count() << endl;

tstop = steady_clock::now();

for (int i = 0; i < 5000; i++)
{
cout << " ";
}
cout << endl << duration_cast<microseconds>(tstop - tstart).count() << endl;*/
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