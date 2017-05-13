#include <iostream>

using namespace std;

int a[10];

void fill_array(int start, int increment);//declear a function

int main(int argc, const char * argv[]) {
    int start, increment;
    
    std::cout << "Enter a number as a start:" << endl;
    std::cin >> start;
    std::cout << "Enter a number as an increment" << endl;
    std::cin >> increment;
    
    fill_array(start, increment); // use the function
    
    for (int i = 0; i< 11; ++i) {
        cout << a[i] << endl;
    }
}

void fill_array(int start, int increment) {
    for (int i = 0; i < 11; ++i) {
        a[i] = start + i * increment;
    }
}