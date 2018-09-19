#include <iostream>
#include <fstream>
#include <chrono>
#include "Trace.h"
#include "Event.h"

Trace::Trace()
{
	//char filename[] = "testing.json";  -------> could initialize the ptr directly
	char *ptr = "testing.json";
	head = NULL;
	trace_start(ptr);
}

Trace::Trace(char* filename)
{
	head = NULL;
	trace_start(filename);
}

void Trace::trace_start(char* filename) //filename is array pointer
{
	new_file.open(filename);
	new_file << "["<<endl;
	trace_event_start("test", "test", "test");
	trace_end();
}

void Trace::trace_end()
{
	new_file << "{ \"Name\": " << "\"" << head->getName() << "\", ";
	new_file << "\"cat\": " << "\"" << head->getCat() << "\", ";

	if (head->getPh() != NULL)
	{
		new_file << "\"ph\": " << "\"" << head->getPh() << "\", ";
	}

	if (head->getPid() != NULL)
	{
		new_file << "\"pid\": " << "\"" << head->getPid() << "\", ";
	}

	if (head->getTid() != NULL)
	{
		new_file << "\"tid\": " << "\"" << head->getTid() << "\", ";
	}

	new_file << "\"ts\": " << "\"" << head->getTs().count() * system_clock::period::num / system_clock::period::den / 1000000 << "\"} " << endl;
	new_file << "]";
	new_file.close();
}

void Trace::trace_event_start(char* name, char* categories, char* argument)
{
	Event* Event_Start = new Event(name,categories,argument); //temporary event
	Event_Start->setPh("B");
	Event_Start->setPid("TEST");
	Event_Start->setTid("TEST");

	system_clock::time_point tp = system_clock::now();
	system_clock::duration ts = tp.time_since_epoch();

	Event_Start->setTs(ts);


	if (head == NULL) {
		head = Event_Start;
	}
	else
	{
		Event* Original = head;
		//---------------------Deep Copy-----------------------//
		Event* temp = new Event();
		temp->setEventNext(Original->getEventNext()); //copy the first Event
		while (Original != NULL)
		{
			Original = Original->getEventNext(); //iterate to the next Event
			Event* curTemp = new Event(); 
			curTemp->setEventNext(Original->getEventNext());
			
			temp->setEventNext(curTemp);
			temp = temp->getEventNext();
		}

		temp->setEventNext(NULL);
		//----------------------------------------------------//

		//-------Insert Event Start between "B" and "E"-------//


	}

}

void Trace::trace_event_end(char* argument)
{
	Event* Event_End = new Event(argument); //temporary event
	//name and categories are not input of the fuction, need to be the same as the beginning
	Event_End->setPh("E");
	Event_End->setPid("TEST");
	Event_End->setTid("TEST");

	system_clock::time_point tp = system_clock::now();
	system_clock::duration ts = tp.time_since_epoch();

	Event_End->setTs(ts);

	Event* temp = head;

	if (temp == NULL) {
		head = Event_End;
	}
/*	else
	{

		while (temp != NULL)
		{
			if (temp->getEventNext() == NULL)
			{

			}
			temp = temp->getEventNext();
		}
	}*/

}

void Trace::trace_instant_global(char* name)
{

}

void Trace::trace_object_new(char* name, void* obj_pointer)
{

}

void Trace::trace_object_gone(char* name, void* obj_pointer)
{

}

void Trace::trace_counter(char* name, char* key, char* value)
{

}

void Trace::trace_flush()
{

}