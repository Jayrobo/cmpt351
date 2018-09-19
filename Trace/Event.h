#pragma once
#ifndef _EVENT_H
#define _EVENT_H

#include <iostream>
#include <chrono>
using namespace std::chrono;

class Event 
{
	public:
		Event();

		Event(char* Event_name, char* Event_categories, char* Event_argument);

		Event(char* Event_argument);
		
		//Setter and Getter
		void setName(char* Event_name);

		void setCat(char* Event_categories);

		void setArgs(char* Event_arguments);

		void setPh(char* Event_type);

		void setPid(char* Event_Process_ID);

		void setTid(char* Event_Thread_ID);

		system_clock::duration setTs(system_clock::duration Event_Timestamp);

		void setEventNext(Event* nextEvent);

		char* getName();
		char* getCat();
		char* getPh();
		system_clock::duration getTs();
		char* getPid();			//
		char* getTid();			//
		char* getArgs();

		Event* getEventNext(); //pointing to the next in the list

    private:
		char* name;
		char* cat;
		char* ph;
		//char* ts;
		//double* ts;
		system_clock::duration ts;
		char* pid;
		char* tid;
		char* args;

		Event* next;
};
#endif
