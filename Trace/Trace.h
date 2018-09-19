#pragma once
#ifndef _TRACE_H
#define _TRACE_H

#include <iostream>
#include <fstream>
#include "Event.h"
using namespace std;

class Trace
{
	public:
		Trace(); //constructor
		//initialize the Trace file to the given file name 

		Trace(char* filename);

		void trace_start(char* filename);
		//strictly speaking 
		//void trace_start(char* filename) has the parameter equal to void trace_start(char* const message) or void trace_start(char message[])

		void trace_event_start(char* name, char* categories, char* argument);

		void trace_event_end(char* argument);

		void trace_instant_global(char* name);

		void trace_object_new(char* name, void* obj_pointer);

		void trace_object_gone(char* name, void* obj_pointer);

		void trace_counter(char* name, char* key, char* value);

		void trace_flush();

		void trace_end();

	private:

		ofstream new_file;
				
		char* name;
		char* categories;
		char* argument;

		Event* head;
};


//#include "Trace.cpp"
#endif