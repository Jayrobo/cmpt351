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
	//trace_start(ptr);
}

Trace::Trace(char* filename)
{
	head = NULL;
	//trace_start(filename);
}

void Trace::trace_start(char* filename) //filename is array pointer
{
	new_file.open(filename);
	new_file << "["<<endl;
	//trace_event_start("test", "test", "test");
	//trace_end();
}

void Trace::trace_end()
{
	trace_flush();
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
		//refer to text book on pg 147 in Figure 4-8
		Event* temp = new Event(Original); //copy the first event
		Event* temphead = temp;  //point to the head of the temp
		while (Original != NULL)
		{
			Original = Original->getEventNext(); //iterate to the next Event

			if (Original != NULL)
			{
				Event* curTemp = new Event(Original);
				temp->setEventNext(curTemp);
				temp = temp->getEventNext();
			}
		}
		temp = temphead; //after copy all the object, point to where the head of temp 

		//----------------------------------------------------//

		//-------Insert Event Start between "B" and "E"-------//
		//Refer to textbook on pg 277 in Figure 9-5
		Event* prePtr;
		Event* curPtr;

		while (temp != NULL)
		{
			prePtr = temp;
			temp = temp->getEventNext();
			curPtr = temp;

			if (prePtr->getPh() == "B" && curPtr == NULL)
			{
				prePtr->setEventNext(Event_Start);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}

			else if (prePtr->getPh() == "B" && curPtr->getPh() == "E")
			{
				prePtr->setEventNext(Event_Start);
				Event_Start->setEventNext(curPtr);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
			else if (curPtr == NULL)
			{
				prePtr->setEventNext(Event_Start);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}

		 }
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
	else
	{
		Event* Original = head;
		//---------------------Deep Copy-----------------------//
		//refer to text book on pg 147 in Figure 4-8
		Event* temp = new Event(Original); //copy the first event
		Event* temphead = temp;  //point to the head of the temp
		while (Original != NULL)
		{
			Original = Original->getEventNext(); //iterate to the next Event

			if (Original != NULL)
			{
				Event* curTemp = new Event(Original);
				temp->setEventNext(curTemp);
				temp = temp->getEventNext();
			}
		}
		temp = temphead;
		//----------------------------------------------------//

		//-------Insert Event Start between "B" and "E"-------//
		//Refer to textbook on pg 277 in Figure 9-5
		Event* prePtr;
		Event* curPtr;

		while (temp != NULL)
		{
			prePtr = temp;
			temp = temp->getEventNext();
			curPtr = temp;

			if (prePtr->getPh() == "B" && curPtr == NULL)
			{
				Event_End->setName(prePtr->getName());
				Event_End->setCat(prePtr->getCat());
				prePtr->setEventNext(Event_End);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}

			else if (prePtr->getPh() == "B" && curPtr->getPh() == "E")
			{
				Event_End->setName(prePtr->getName());
				Event_End->setCat(prePtr->getCat());
				prePtr->setEventNext(Event_End);
				Event_End->setEventNext(curPtr);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
			else if (curPtr == NULL)
			{
				prePtr->setEventNext(Event_End);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
		}
	}
}

void Trace::trace_instant_global(char* name)
{
		Event* Event_instGlobal = new Event(); //use default constructor
		Event_instGlobal->setName(name);
		Event_instGlobal->setPh("i");
		Event_instGlobal->setPid("TEST");
		Event_instGlobal->setTid("TEST");

		// check chronos
		system_clock::time_point tp = system_clock::now();
		system_clock::duration ts = tp.time_since_epoch();

		Event_instGlobal->setTs(ts);

		if (head == NULL) {
			head = Event_instGlobal;
		}
		else
		{
			Event* Original = head;
			//---------------------Deep Copy-----------------------//
			//refer to text book on pg 147 in Figure 4-8
			Event* temp = new Event(Original); //copy the first event
			Event* temphead = temp;  //point to the head of the temp
			while (Original != NULL)
			{
				Original = Original->getEventNext(); //iterate to the next Event

				if (Original != NULL)
				{
					Event* curTemp = new Event(Original);
					temp->setEventNext(curTemp);
					temp = temp->getEventNext();
				}
			}
			temp = temphead; //after copy all the object, point to where the head of temp 

							 //----------------------------------------------------//
							 //-------Insert Event Start between "B" and "E"-------//
							 //Refer to textbook on pg 277 in Figure 9-5
			Event* prePtr;
			Event* curPtr;

			while (temp != NULL)
			{
				prePtr = temp;
				temp = temp->getEventNext();
				curPtr = temp;

				//edit if there is a specifc spot that the object should be inserted to
				/*if (prePtr->getPh() == "B" && curPtr == NULL)
				{
				Event_instGlobal->setName(prePtr->getName());
				Event_instGlobal->setKey(prePtr->getKey());
				Event_instGlobal->setVal(prePtr->getVal());
				prePtr->setEventNext(Event_Count);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
				}

				else if (prePtr->getPh() == "B" && curPtr->getPh() == "C")
				{
				Event_instGlobal->setName(prePtr->getName());
				Event_instGlobal->setKey(prePtr->getKey());
				Event_instGlobal->setVal(prePtr->getVal());
				prePtr->setEventNext(Event_instGlobal);
				Event_instGlobal->setEventNext(curPtr);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
				}*/
				/*else*/ if (curPtr == NULL)
				{
					prePtr->setEventNext(Event_instGlobal);
					temp = prePtr;
					temp = temphead;
					head = temp;
					break;
				}
			}
		}
}

void Trace::trace_object_new(char* name, void* obj_pointer)
{

}

void Trace::trace_object_gone(char* name, void* obj_pointer)
{

}

void Trace::trace_counter(char* name, char* key, char* value)
{
	Event* Event_Count = new Event(name, key, value,"C");
	
	// check chronos
	system_clock::time_point tp = system_clock::now();
	system_clock::duration ts = tp.time_since_epoch();

	Event_Count->setTs(ts);

	if (head == NULL) {
		head = Event_Count;
	}
	else
	{
		Event* Original = head;
		//---------------------Deep Copy-----------------------//
		//refer to text book on pg 147 in Figure 4-8
		Event* temp = new Event(Original); //copy the first event
		Event* temphead = temp;  //point to the head of the temp
		while (Original != NULL)
		{
			Original = Original->getEventNext(); //iterate to the next Event

			if (Original != NULL)
			{
				Event* curTemp = new Event(Original);
				temp->setEventNext(curTemp);
				temp = temp->getEventNext();
			}
		}
		temp = temphead; //after copy all the object, point to where the head of temp 

						 //----------------------------------------------------//
						 //-------Insert Event Start between "B" and "E"-------//
						 //Refer to textbook on pg 277 in Figure 9-5
		Event* prePtr;
		Event* curPtr;

		while (temp != NULL)
		{
			prePtr = temp;
			temp = temp->getEventNext();
			curPtr = temp;

			//edit if there is a specifc spot that the object should be inserted to
			/*if (prePtr->getPh() == "B" && curPtr == NULL)
			{
				Event_Count->setName(prePtr->getName());
				Event_Count->setKey(prePtr->getKey());
				Event_Count->setVal(prePtr->getVal());
				prePtr->setEventNext(Event_Count);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}

			else if (prePtr->getPh() == "B" && curPtr->getPh() == "C")
			{
				Event_Count->setName(prePtr->getName());
				Event_Count->setKey(prePtr->getKey());
				Event_Count->setVal(prePtr->getVal());
				prePtr->setEventNext(Event_Count);
				Event_Count->setEventNext(curPtr);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}*/
			/*else*/ if (curPtr == NULL)
			{
				prePtr->setEventNext(Event_Count);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
		}
	}
}

void Trace::trace_flush()
{
	Event* temp = head;

	while (temp != NULL)
	{
		new_file << "{ \"Name\": " << "\"" << temp->getName() << "\", ";
		
		if (temp->getCat() != NULL)
		{
			new_file << "\"cat\": " << "\"" << temp->getCat() << "\", ";
		}

		if (temp->getPh() != NULL)
		{
			new_file << "\"ph\": " << "\"" << temp->getPh() << "\", ";
		}

		if (temp->getPid() != NULL)
		{
			new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";
		}

		if (temp->getTid() != NULL)
		{
			new_file << "\"tid\": " << "\"" << temp->getTid() << "\", ";
		}

		if (temp->getPh() == "i") // print the scope for instant events, s
		{
			new_file << "\"s\": " << "\"g \", ";
		}

		new_file << "\"ts\": " << "\"" << temp->getTs().count() * system_clock::period::num / system_clock::period::den / 1000000 << "\"} " << endl;

		if(temp->getArgs() != NULL)
		{
			new_file << "\"args\": {" << endl;
			
		}

		if (temp->getKey() != NULL)
		{
			new_file << "\"args\": {" << "\"" << temp->getKey() << "\": ";
		}

		if (temp->getVal() != NULL)
		{
			new_file << temp->getVal() << "}"<<endl;
		}

		temp = temp->getEventNext();
	}
}