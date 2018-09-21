#include <iostream>
#include "Event.h"
#include <chrono>

using namespace std::chrono;

Event::Event()
{
	//Doesn't require to be changed yet
	name = NULL;
	cat = NULL;
	ph = NULL;
	pid = NULL;
	tid = NULL;
	args = NULL;
	key = NULL;
	value = NULL;
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
	key = NULL;
	value = NULL;
}

Event::Event(char* Event_name, char* Event_key, char* Event_value, char* ctr)
{
	name = Event_name;
	key = Event_key;
	value = Event_value;
	ph = ctr;

	//Doesn't require to be changed yet
	cat = NULL;
	args = NULL;
	pid = NULL;
	tid = NULL;
	next = NULL;
}

Event::Event(char* Event_argument)
{

	args = Event_argument;

	//Doesn't require to be changed yet
	name = NULL;
	cat = NULL;
	ph = NULL;
	pid = NULL;
	tid = NULL;
	key = NULL;
	value = NULL;
	next = NULL;
}

Event::Event(Event* Event_obj)
{
	name = Event_obj->getName();
	cat = Event_obj->getCat();
	ph = Event_obj->getPh();
	pid = Event_obj->getPid();
	tid = Event_obj->getTid();
	args = Event_obj->getArgs();
	key = Event_obj->getKey();
	value = Event_obj->getVal();
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

void Event::setKey(char* Event_key)
{
	key = Event_key;
}

void Event::setVal(char* Event_value)
{
	value = Event_value;
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
char* Event::getKey()
{
	return key;
}
char* Event::getVal()
{
	return value;
}

Event* Event::getEventNext()
{
	return next;
}