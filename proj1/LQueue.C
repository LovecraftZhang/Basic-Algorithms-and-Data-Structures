/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
#include "LQueue.h"

using namespace std;

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//--- Definition of move_to_front()
void Queue::move_to_front(const QueueElement &value) {
    Queue::NodePointer temp = myFront;
    Queue::NodePointer temp_pre = myFront;
    if (myFront == myBack) {

    } else {
        while(temp != NULL) {
            if (value == temp->data) {
                Node *curr = new Node(value, myFront);
                myFront = curr;
                if (temp == myBack) {
                    myBack = temp_pre;
                }

                temp_pre->next = temp->next;
                break;
            }
            temp_pre = temp;
            temp = temp->next;
        }
    }
}

//--- Definition of merge_two_queues()
void Queue::merge_two_queues(Queue &original) {
    if (original.empty()) {

    } else if (empty()){

        while (original.myFront != NULL) {
            enqueue(original.myFront->data);
            original.dequeue();
        }
    } else {
        Queue::NodePointer temp_p = myFront; // pointer points to the element before temp
        Queue::NodePointer temp = myFront; // pointer in this
        Queue::NodePointer temp_o = original.myFront; // pointer in original
        while(temp != NULL) {
            if (temp_o == NULL) {
                break;
            } else {
                if (temp_o->data > temp->data) {
                    temp_p = temp;
                    temp = temp->next;
                } else {
                    if (temp_p == temp) {
                        Node *curr = new Node(temp_o->data, temp);
                        temp_p = curr;
                        myFront = curr;
                        Queue::NodePointer temp_d = temp_o;// point to the data in original needed to delete
                        original.myFront = original.myFront->next;
                        temp_o = temp_o->next;
                        delete temp_d;
                    } else {
                        Node *curr = new Node(temp_o->data, temp);
                        temp_p->next = curr;
                        temp_p = curr;
                        Queue::NodePointer temp_d = temp_o;// point to the data in original needed to delete
                        original.myFront = original.myFront->next;
                        temp_o = temp_o->next;
                        delete temp_d;
                    }
                }
            }
        }

        while (temp_o != NULL) {

            temp = new Node(temp_o->data, temp_o->next);
            temp_p->next = temp;
            myBack = temp;
            Queue::NodePointer temp_d = temp_o;
            if (temp_o->next != NULL) {
                temp_o = temp_o->next;
                delete temp_d;
            } else {
                temp_o = temp_o->next;
                original.myBack = 0;
                original.myFront = 0;
                delete temp_d;
            }

        }
    }

}

//--- Definition of move_ater_front()
void Queue::move_after_front() {
    if (myBack == myFront) {

    } else if (myFront->next == myBack) {

    } else {
        Node *curr = myFront;
        while (curr->next != myBack) {
            curr = curr->next;
        }
        Queue::NodePointer temp = new Node(myBack->data, NULL);
        temp->next = myFront->next;
        myFront->next = temp;
        Queue::NodePointer temp_d = myBack;
        myBack = curr;
        myBack->next = NULL;
        delete temp_d;
    }
}

//--- Definition of size()
int Queue::size() {
    Queue::NodePointer temp = myFront;
    int i = 0;
    if (empty()) {
        return i;
    } else {
        i++;
        while (temp != myBack) {
            ++i;
            temp = temp->next;
        }
        return i;
    }

}



