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

		Event(char* Event_name, char* Event_key, char* Event_value, char* ctr); //ctr events

		Event(char* Event_argument);

		Event(Event* Event_obj);
		
		//Setter and Getter
		void setName(char* Event_name);

		void setCat(char* Event_categories);

		void setArgs(char* Event_arguments);

		void setKey(char* Event_key);

		void setVal(char* Event_value);

		void setPh(char* Event_type);

		void setPid(char* Event_Process_ID);

		void setTid(char* Event_Thread_ID);

		void setId(char* Event_ID);


		//find relevent infomation @https://www.geeksforgeeks.org/chrono-in-c/
		void setTs(std::chrono::duration<double> Event_Timestamp);

		void setEventNext(Event* nextEvent);

		char* getName();
		char* getCat();
		char* getPh();
		std::chrono::duration<double> getTs();
		char* getPid();			//
		char* getTid();			//
		char* getArgs();
		char* getKey();
		char* getVal();
		char* getId();

		Event* getEventNext(); //pointing to the next in the list

    private:
		char* name;
		char* cat;
		char* ph;
		//char* ts;
		//double* ts;
		std::chrono::duration<double> ts;
		char* pid;
		char* tid;
		char* args;
		char* key;
		char* value;
		char* id;

		Event* next;
};
#endif
