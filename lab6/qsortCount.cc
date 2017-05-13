#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comps;

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

int qc(int n) {
    // Q3
    int p; //pivot
    if (n <= 1) {
        return 0;
    }
    p = randint(0, n);
    return n-1 + qc(p) + qc(n-p-1);  // sort: this array: n-1, small part: qc(q), large part: qc(n-q-1)
}

float c(int n){
    // Q4
    // C(n) = sum(from m=1 to n)[n-1+C(m-1)+C(n-m)]/n
    if(n <= 1)return 0;

    float sum = 0.0;
    float sum1 = 0.0, sum2 = 0.0;

    for(int m = 1;m <=n; m++){
        sum += n-1 +c(m-1) + c(n-m);
    }
    return sum / n;
}

void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a])
			swap(x[++m], x[i]);
        ++comps; // compare
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 3

int main(int argc, char *argv[]) {
	srand(time(0));
	int times = 100;
	int loop = times;

	// change the following code
	for (loop ; loop > 0; loop--) {
		x = new int[NN];
		for (int i=0; i<NN; ++i) {
			x[i] = rand() % NN;
		}

		quicksort(0, NN-1);
		for (int i=0; i<NN; ++i) {
			std::cout << x[i] << " ";
		}
		std::cout << std::endl;

		std::cout << "times of comparision so far: " << comps << std::endl;

		delete[] x;
	}

	std::cout << "average comparision: " << comps / times << std::endl;
    std::cout << "expected number(by qc(int)): " << qc(NN) << std::endl;
	return 0;
}

