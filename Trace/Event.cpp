#include <iostream>
#include "Event.h"
#include <chrono>

using namespace std::chrono;



Event::Event()
{
	pid = "1234";
	tid = "1234";

	//Doesn't require to be changed yet
	name = NULL;
	cat = NULL;
	ph = NULL;
	arguements* temp = new arguements;
	temp->args = NULL;
	temp->val = NULL;
	temp->next = NULL;
	setArgsNext(temp);
	//key = NULL;
	objPtr = NULL;
	next = NULL;
}

Event::Event(char* Event_name, char* Event_categories, char* Event_argument)
{
	name = Event_name;
	cat = Event_categories;
	//args = Event_argument;

	arguements* temp = new arguements;
	temp->args = Event_argument;
	temp->val = "Sample"; //if no value assigned just have value as a sample
	temp->next = NULL;
	setArgsNext(temp);

	//Doesn't require to be changed yet
	ph = NULL;
	pid = NULL;
	tid = NULL;
	next = NULL;
	//key = NULL;
	//value = NULL;
	objPtr = NULL;
}

Event::Event(char* Event_name, char* Event_key, char* Event_value, char* ctr)
{
	name = Event_name;
	//key = Event_key;
	//value = Event_value;
	arguements* temp = new arguements;
	temp->args = Event_key;
	temp->val = Event_value; //if no value assigned just have value as a sample
	temp->next = NULL;
	setArgsNext(temp);
	ph = ctr;

	//Doesn't require to be changed yet
	cat = NULL;
	//args = NULL;
	pid = NULL;
	tid = NULL;
	next = NULL;
	objPtr = NULL;
}

Event::Event(char* Event_argument)
{

	//args = Event_argument;
	arguements* temp = new arguements;
	temp->args = Event_argument;
	temp->val = "Sample"; //if no value assigned just have value as a sample
	temp->next = NULL;
	setArgsNext(temp);

	//Doesn't require to be changed yet
	name = NULL;
	cat = NULL;
	ph = NULL;
	pid = NULL;
	tid = NULL;
	//key = NULL;
	//value = NULL;
	objPtr = NULL;
	next = NULL;
}

Event::Event(Event* Event_obj)
{
	name = Event_obj->getName();
	cat = Event_obj->getCat();
	ph = Event_obj->getPh();
	pid = Event_obj->getPid();
	tid = Event_obj->getTid();
	ts = Event_obj->getTs();
	if (argu != NULL)
	{
		argu->args = Event_obj->getArgs();
		argu->val = Event_obj->getVal();
		argu->next = Event_obj->getArguNext();
	}
	objPtr = Event_obj->getObjPtr();
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

//------------------Structure--------------------------//
void Event::setArgs(char* Event_arguments)
{
	argu->args = Event_arguments;
}

void Event::setKey(char* Event_key)
{
	argu->args = Event_key;
}

void Event::setVal(char* Event_value)
{
	argu->val = Event_value;
}

void Event::setArgsNext(arguements* Event_Argument)
{

	arguements* temp = argu;

	if (temp == NULL)
	{
		temp = Event_Argument;
	}

	argu = temp;

}
//------------------------------------------------------//

void Event::setObjPtr(void* Event_objPtr) {
	objPtr = Event_objPtr;
}

void Event::setPh(char* Event_type)
{
	ph = Event_type;
}

void Event::setTs(std::chrono::duration<double> Event_Timestamp)
{
	ts = Event_Timestamp;
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
std::chrono::duration<double> Event::getTs()
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
	return argu->args;
}
char* Event::getKey()
{
	return argu->args;
}
char* Event::getVal()
{
	return argu->val;
}
arguements* Event::getArguNext()
{
	return argu->next;
}
void* Event::getObjPtr() 
{
	return objPtr;
}

Event* Event::getEventNext()
{
	return next;
}