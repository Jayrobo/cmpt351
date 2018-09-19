#include <iostream>
#include "Event.h"
#include <chrono>

using namespace std::chrono;

Event::Event()
{
	name = "Tested";
	cat = "Tested";

	//Doesn't require to be changed yet
	ph = NULL;
	pid = NULL;
	tid = NULL;
	args = NULL;
	next = NULL;
}

Event::Event(char* Event_name, char* Event_categories, char* Event_argument)
{
	name = Event_name;
	cat = Event_categories;
	args = Event_argument;

	//Doesn't require to be changed yet
	ph = NULL;
	pid = NULL;
	tid = NULL;
	next = NULL;
}

void Event::setName(char* Event_name)
{
	name = Event_name;
}

void Event::setCat(char* Event_categories)
{
	cat = Event_categories;
}

void Event::setArgs(char* Event_arguments)
{
	args = Event_arguments;
}

void Event::setPh(char* Event_type)
{
	ph = Event_type;
}

system_clock::duration Event::setTs(system_clock::duration Event_Timestamp)
{
	return ts = Event_Timestamp;
}

void Event::setPid(char* Event_Process_ID)
{
	pid = Event_Process_ID;
}

void Event::setTid(char* Event_Thread_ID)
{
	tid = Event_Thread_ID;
}

void Event::setEventNext(Event* nextEvent)
{
	next = nextEvent;
}

char* Event::getName()
{
	return name;
}
char* Event::getCat()
{
	return cat;
}
char* Event::getPh()
{
	return ph;
}
system_clock::duration Event::getTs()
{
	return ts;
}
char* Event::getPid()
{
	return pid;
}
char* Event::getTid()
{
	return tid;
}
char* Event::getArgs()
{
	return args;
}

Event* Event::getEventNext()
{
	return next;
}