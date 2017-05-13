#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL)); // Do not know what this means,
                       //but it was used to get different number;
    
    while (true) {
        int number = rand() % 100 +1;
        int guess;
        char answer;
        
        std::cout << number << "\n" << std::endl; // for testing
        
        while (true) {
            std::cout << "Guess a number between 1 to 100." << std::endl;
            std::cin >> guess;
            
            if (guess != number) {
                std::cout << "This is incorrect." << std::endl;
                
                std::cout << "Do you want to play again? (Y/N)" << std::endl;
                std::cin >> answer;
                
                if (answer == 'n' || answer == 'N') {
                    break;
                } else if (answer == 'y' || answer == 'Y') {
                    std::cout << "\n\n" << std::endl;
                } else {
                    std::cout << "Please enter Y/N." << std::endl;
                }
            } else {
                std::cout << "This is correct!" << std::endl;
                break;
            }
        }
        break;
        
    }
}