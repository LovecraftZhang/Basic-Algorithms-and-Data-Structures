/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"

using namespace std;


void print(Queue q) { q.display(cout); }

int main(void) {
    Queue q1;
    cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

    cout << "How many elements to add to the queue? ";
    int numItems = 0;
    cin >> numItems;
    for (int i = 1; i <= numItems; i++)
        q1.enqueue(100 * i);

    cout << "Contents of queue q1 (via  print):\n";
    print(q1);
    cout << endl;

    cout << "Remove front -- Queue contents: ";
    q1.dequeue();
    q1.display(cout);

    Queue q2;
    //q2 = q1;
    q2.enqueue(410);
    q2.enqueue(7);
    q2.enqueue(3);
    cout << "Contents of queue q2 after initialize (via  print):\n";
    print(q2);
    cout << endl;

    q2.move_to_front(3);
    cout << "q2 move to front:\n";
    print(q2);
    cout << endl;

    q2.move_after_front();
    cout << "q2 move the back after front:\n";
    print(q2);
    cout << endl;

    q1.merge_two_queues(q2);
    cout << "q1.merge_two_queues(q2):\n";
    print(q1);
    cout << endl;

    cout << "size of q1:" << q1.size() << endl;
    cout << "size of q2:" << q2.size() << endl;

    cout << "Generate an empty list q3" << endl;
    Queue q3;
    q1.merge_two_queues(q3);
    cout << "q1.merge_two_queues(q3):\n";
    print(q1);
    cout << endl;

    q3.merge_two_queues(q1);
    cout << "q3.merge_two_queues(q1):\n";
    print(q3);
    cout << "size of q1:" << q1.size() << endl;


    cout << "Queue q2 empty? " << q2.empty() << endl;

    cout << "Front value in q2: " << q2.front() << endl;

    cout << "enqueue 3 to q2" << endl;

    q2.enqueue(3);

    while (!q2.empty()) {
        cout << "Remove front -- Queue contents: ";
        q2.dequeue();
        q2.display(cout);
    }

    cout << "Trying to remove front of q2 " << endl;
    q2.dequeue();
    //system("PAUSE");
    return 0;
}
