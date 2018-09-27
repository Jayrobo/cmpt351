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
	tstart = steady_clock::now();
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

	steady_clock::time_point tstop = steady_clock::now();
	std::chrono::duration<double> ts = tstop - tstart;
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

	//system_clock::time_point tp = system_clock::now();
	//system_clock::duration ts = tp.time_since_epoch();

	//Event_End->setTs(ts);

	steady_clock::time_point tstop = steady_clock::now();
	std::chrono::duration<double> ts = tstop - tstart;
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
		steady_clock::time_point tstop = steady_clock::now();
		std::chrono::duration<double> ts = tstop - tstart;
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

			 //instant global can be inserted anywhere so lets insert at the end
			 if (curPtr == NULL)
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
	Event* Event_objectNew = new Event(); //use default constructor
	Event_objectNew->setName(name);
	Event_objectNew->setObjPtr(obj_pointer);
	Event_objectNew->setPh("N");
	Event_objectNew->setPid("TEST");
	Event_objectNew->setTid("TEST");

	// check chronos
	steady_clock::time_point tstop = steady_clock::now();
	std::chrono::duration<double> ts = tstop - tstart;
	Event_objectNew->setTs(ts);

	if (head == NULL) {
		head = Event_objectNew;
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

			if (curPtr == NULL)
			{
				prePtr->setEventNext(Event_objectNew);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
		}
	}
}

void Trace::trace_object_gone(char* name, void* obj_pointer)
{
	Event* Event_objectGone = new Event(); //use default constructor
	Event_objectGone->setName(name);
	Event_objectGone->setObjPtr(obj_pointer);
	Event_objectGone->setPh("D");
	Event_objectGone->setPid("TEST");
	Event_objectGone->setTid("TEST");

	// check chronos
	steady_clock::time_point tstop = steady_clock::now();
	std::chrono::duration<double> ts = tstop - tstart;
	Event_objectGone->setTs(ts);

	if (head == NULL) {
		head = Event_objectGone;
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

			if (curPtr == NULL)
			{
				prePtr->setEventNext(Event_objectGone);
				temp = prePtr;
				temp = temphead;
				head = temp;
				break;
			}
		}
	}
}

void Trace::trace_counter(char* name, char* key, char* value)
{
	Event* Event_Count = new Event(name, key, value, "C");
	steady_clock::time_point tstop = steady_clock::now();
	std::chrono::duration<double> ts = tstop - tstart;
	Event_Count->setTs(ts);
	Event_Count->setPid("TEST");
	Event_Count->setTid("TEST");


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
	
			if (curPtr == NULL)
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
		//-------------Base on Current Finding----------------//
			if (temp->getPh() == "B")
			{
				new_file << "{ \"name\": " << "\"" << temp->getName() << "\", ";
				new_file << "\"cat\": " << "\"" << temp->getCat() << "\", ";
				new_file << "\"ph\": " << "\"" << temp->getPh() << "\", ";
				new_file << "\"ts\": " << temp->getTs().count() * 1000000 << ", ";
				new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";
				new_file << "\"tid\": " << "\"" << temp->getTid() << "\", ";

				//missing args
				if (temp->getArgsCur() != NULL)
				{
					arguements* tempArg = temp->getArgsCur();
					new_file << "\"args\": " << "{";

					while (tempArg != NULL)
					{
						new_file << "\""<< tempArg->args << "\": ";
						new_file << "\""<< tempArg->val << "\" ";
						tempArg = tempArg->next;
					}

					if (temp->getEventNext() == NULL)
					{
						new_file << "}}" << endl;
					}
					else
					{
						new_file << "}}," << endl;
					}
					
				}
			}
			else if (temp->getPh() == "E")
			{
				//don't need to print name and category
				new_file << "{ \"ph\": " << "\"" << temp->getPh() << "\", ";
				new_file << "\"ts\": " << temp->getTs().count() * 1000000 << ", ";
				new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";
				new_file << "\"tid\": " << "\"" << temp->getTid() << "\", ";

				//missig args
				if (temp->getArgsCur() != NULL)
				{
					arguements* tempArg = temp->getArgsCur();
					new_file << "\"args\": " << "{";

					while (tempArg != NULL)
					{
						new_file << "\"" << tempArg->args << "\": ";
						new_file << "\"" << tempArg->val << "\" ";
						tempArg = tempArg->next;
					}

					if (temp->getEventNext() == NULL)
					{
						new_file << "}}" << endl;
					}
					else
					{
						new_file << "}}," << endl;
					}

				}
			}
			else if (temp->getPh() == "i")
			{
				new_file << "{ \"name\": " << "\"" << temp->getName() << "\", ";
				//cat is not necessary because the trace funtion does not include it
				//new_file << "\"cat\": " << "\"" << temp->getCat() << "\", ";
				new_file << "\"ph\": " << "\"" << temp->getPh() << "\", ";
				new_file << "\"ts\": " << temp->getTs().count() * 1000000 << ", ";
				new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";
				new_file << "\"tid\": " << "\"" << temp->getTid() << "\", ";

				if (temp->getEventNext() == NULL)
				{
					new_file << "\"s\" : " << "\"g\" }"<<endl; //for instant global event
														//last event don't need colma
				}
				else
				{
					new_file << "\"s\" : " << "\"g\" },"<<endl; //for instant global event
				}
				//no need arguments
			}
			else if (temp->getPh() == "N" || temp->getPh() == "D")
			{
				new_file << "{ \"name\": " << "\"" << temp->getName() << "\", ";
				//not necessary to print a category
				//new_file << "\"cat\": " << "\"" << temp->getCat() << "\", ";
				new_file << "\"ph\": " << "\"" << temp->getPh() << "\", ";
				///////////////////////DOUBLE CHECK ID/////////////////////////////
				new_file << "\"id\": " << "\"" <<"0x"<< temp->getObjPtr()<< "\", ";
				new_file << "\"ts\": " << temp->getTs().count() * 1000000 << ", ";
				new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";

				//don't need argument
				if (temp->getEventNext() == NULL)
				{
					new_file << "\"tid\": " << "\"" << temp->getTid() << "\"} "<<endl; //last event don't need colma
				}
				else
				{
					new_file << "\"tid\": " << "\"" << temp->getTid() << "\"}, "<<endl;
				}
			}
			else //else if ph is C
			{
				new_file << "{ \"name\": " << "\"" << temp->getName() << "\", ";
				//not necessary to print a category
				//new_file << "\"cat\": " << "\"" << temp->getCat() << "\", ";
				new_file << "\"ph\": " << "\"" << temp->getPh() << "\", ";
				new_file << "\"ts\": " << temp->getTs().count() * 1000000<< ", ";
				new_file << "\"pid\": " << "\"" << temp->getPid() << "\", ";
				//missing args

				if (temp->getArgsCur() != NULL)
				{
					arguements* tempArg = temp->getArgsCur();
					new_file << "\"args\": " << "{";

					while (tempArg != NULL)
					{
						new_file << "\"" << tempArg->args << "\": ";
						new_file << "\"" << tempArg->val << "\" ";
						tempArg = tempArg->next;
					}

					if (temp->getEventNext() == NULL)
					{
						new_file << "}}" << endl;
					}
					else
					{
						new_file << "}}," << endl;
					}

				}
			}
	

/*will need to work on these data type
		if(temp->getArgs() != NULL)
		{
			new_file << "\"args\": {" << endl;
			
		}

		if (temp->getKey() != NULL)
		{
			new_file << "\"args\": {" << "\"" << temp->getKey() << "\": ";
		}
*/
		temp = temp->getEventNext();
	}
}