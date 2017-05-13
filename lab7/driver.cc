#include "Hashtable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void usage(char* argv[]) {
	cerr << "Usage: " << argv[0] << " scheme numberOfKeys sizeOfTable" << endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int n, m;
	srand(time(0));

	if (argc == 1) {
		cout << "Running your test code..." << endl;
		/* ADD YOUR TEST CODE HERE */
		Hashtable L(1000000);
		for (int i = 0; i < 750000; i++) {
			L.linsert(rand() + 1);
		}
		cout << "Linear with 7500 keys and size 10000: \n";
		L.printStats();

		Hashtable Q(1000000);
		for (int i = 0; i < 750000; i++) {
			Q.qinsert(rand() + 1);
		}
		cout << "Qinear with 7500 keys and size 10000: \n";
		Q.printStats();

		Hashtable D(1000000);
		for (int i = 0; i < 750000; i++) {
			D.dinsert(rand() + 1);
		}
		cout << "Dinear with 7500 keys and size 10000: \n";
		D.printStats();
		return 0;
	}
	
	if (argc != 4) {
		usage(argv);
	}
	n = atoi(argv[2]);
	m = atoi(argv[3]);
	Hashtable H(m);
	
	switch(argv[1][0]) {
	case 'l':
		for (int i=0; i<n; ++i) {
			H.linsert(rand() + 1);
		}
		//    H.print();
		cout << "Linear: ";  
		H.printStats();
		break;
	case 'q':
		for (int i=0; i<n; ++i) {
			H.qinsert(rand() + 1);
		}
		//    H.print();
		cout << "Quadratic: ";
		H.printStats();
		break;
	case 'd':
		for (int i=0; i<n; ++i) {
			H.dinsert(rand() + 1);
		}
		//    H.print();
		cout << "Double Hashing: "; 
		H.printStats();
		break;
	default:
		usage(argv);
	}
}

