#include <iostream>

int main () {
  int x = 5, y = 15;
  int * p1, *p2;
  p1 = &x;
  p2 = &y;
  *p1 = 6;
  *p1 = *p2;
  p2 = p1;
  *p1 = *p2+10; // Same address, different value???

  std::cout << x << " "<< y << " " << p1 << " " << p2 << " " << std::endl;
  return 0; 
}