#include <iostream>
#include <ctime>
#include <cstdlib>
#include "LQueue.h"

using namespace std;
// variables for main runway
int duration, landingRate, takeOffRate, landingTime, takeOffTime;
int i = 1;
int tot_num_lading = 0, tot_num_takingoff = 0;
double totalWaitTime_l = 0, totalWaitTime_t = 0;
int max_landing = 0, max_takingOff = 0;
bool isLanding = false, isTakingOff = false;
int processingTime = -1;

Queue landing, takeOff;

// variables for temp runway
int processingTime_t = -1;
bool isLanding_t = false, isTakingOff_t = false;

Queue landing_t, takeOff_t;



void main_runway();
void temp_runway();


int main(void) {

    srand((unsigned)time(0)); // generate random numbers

    cout << "Enter:\n" << endl;

    cout << "Time for a plane to land (in minutes):" << endl;
    cin >> landingTime;


    cout << "Time for a plane to takeOff (in minutes):" << endl;

    cin >> takeOffTime;
    cout << "Landing rate (planes per hour):" << endl;
    cin >> landingRate;


    cout << "Takeoff rate (planes per hour):" << endl;
    cin >> takeOffRate;


    cout << "How long to run the simulation (in minutes):" << endl;
    cin >> duration;

    while (i <= duration) {
        // generate two random number from 1 to 60.
        int number1 = rand() % 60 +1;
        int number2 = rand() % 60 +1;

        cout << "Time = " << i << endl;

        if (i == 60) {
            cout << "No new takeoffs or landings will be generated on Temp_runway.\n" << endl;
        }

        // receive the landing requests
        if (number1 % 60 < landingRate) {
            // Plane number is depending on the "current time" at that moment.
            // if there are move plane wait in main_runway, make them go to temp_runway;
            if ((landing_t.size() < landing.size()) && (i < 60)) {
                landing_t.enqueue(1000 + i);
                cout << "Plane" << 1000 + i << " wants to land; added to land queue of temp_runway. " << landing_t.size() << " in queue\n" << endl;

                // For bonus(1),
                // Planes with a plane number which mods 7 equals 0 are large planes with huge number of passengers,
                // and they have priority to land.
                if ((1000 + i) % 7 == 0) {
                    if (isLanding) {
                        landing.move_after_front();
                        cout << "Plane " << 1000 + i << " has priority to land.\n" << endl;
                    } else {
                        landing.move_to_front(1000 + i);
                        cout << "Plane " << 1000 + i << " has priority to land.\n" << endl;
                    }
                }
            } else {
                landing.enqueue(1000 + i);
                cout << "Plane" << 1000 + i << " wants to land; added to land queue of main_runway. " << landing.size() << " in queue\n" << endl;

                if ((1000 + i) % 7 == 0) {
                    if (isLanding_t) {
                        landing.move_after_front();
                        cout << "Plane " << 1000 + i << " has priority to land.\n" << endl;
                    } else {
                        landing.move_to_front(1000 + i);
                        cout << "Plane " << 1000 + i << " has priority to land.\n" << endl;
                    }
                }

            }

            // total number of landing plain added to queues
            tot_num_lading++;

            // refresh the maximum number of landing plane
            if (max_landing < landing.size()) {
                max_landing = landing.size();
            } else if (max_landing < landing_t.size()) {
                max_landing = landing_t.size();
            }


        }

        // receive the taking off requests
        if (number2 % 60 < takeOffRate) {
            // (1000 + i + 1) makes the taking off plane has different value with the landing plane which is generated at the same time.

            if ((takeOff_t.size() < takeOff.size()) && (i < 60)) {
                takeOff_t.enqueue(1000 + i +1);
                cout << "Plane" << 1000 + i << " wants to takeoff; added to takeoff queue of temp_runway. " << takeOff_t.size() << " in queue\n" << endl;
            } else {
                takeOff.enqueue(1000 + i + 1);
                cout << "Plane" << 1000 + i << " wants to takeoff; added to takeoff queue of main_runway. " << takeOff.size() << " in queue\n" << endl;
            }

            tot_num_takingoff++;

            if (max_takingOff < takeOff.size()) {
                max_takingOff = takeOff.size();
            } else if (max_takingOff < takeOff_t.size()) {
                max_takingOff = takeOff_t.size();
            }

        }


        // process in main_runway
        main_runway();

        // process in temp_runway
        if (i < 60) {
            temp_runway();
        } else if (isLanding_t) {
            temp_runway();
        } else if (isTakingOff_t) {
            temp_runway();
        } else {
            if (!landing_t.empty() || !takeOff_t.empty()) {
                landing.merge_two_queues(landing_t);
                takeOff.merge_two_queues(takeOff_t);
                cout << "Temp_runway colsed. planes are in the queue of main runway" << endl;
            }
        }

        i++;
    }

    cout << "No new takeoffs or landings will be generated.\n" << endl;

    while ((!landing.empty())||(!takeOff.empty())) {
        cout << "Time = " << i << endl;

        main_runway();

        i++;
    }
    cout << "STATISTICS:" << endl;
    cout << "Maximum number of planes in landing queue was:"  << max_landing << endl;
    cout << "Average minutes spent waiting to land:" << totalWaitTime_l / tot_num_lading << endl;
    cout << "Maximum number of planes in takeoff queue was:" << max_takingOff << endl;
    cout << "Average minutes spent waiting to takeoff:" << totalWaitTime_t / tot_num_takingoff << endl;
    return 0;

}


// helper for the 1st runway, which is working all the time
void main_runway() {
    if (!landing.empty()) {
        if (processingTime == -1) {
            processingTime = landingTime;
            isLanding = true;
        }

        if (processingTime == 0) {
            cout << "Plane" << landing.front() << " land complete. (main_runway)\n" << endl;
            landing.dequeue();
            processingTime = -1;
            isLanding = false;
        } else {
            cout << "Plane" << landing.front() << " is landing. (main_runway) " << processingTime << " minutes to complete\n" << endl;
            processingTime--;
            totalWaitTime_l += landing.size() -1;
            totalWaitTime_t += takeOff.size();
        }
    } else if (!takeOff.empty()) {
        if (processingTime == -1) {
            processingTime = takeOffTime;
            isTakingOff = true;
        }
        if (processingTime == 0) {
            cout << "Plane" << takeOff.front() << " take off complete. (main_runway)\n" << endl;
            takeOff.dequeue();
            processingTime = -1;
            isTakingOff = false;
        } else {
            cout << "Plane" << takeOff.front() << " is taking off. (main_runway) " << processingTime << " minutes to complete\n" << endl;
            processingTime--;
            totalWaitTime_t += takeOff.size() - 1;
        }
    }
}

void temp_runway() {
    if (!landing_t.empty()) {
        if (processingTime_t == -1) {
            processingTime_t = landingTime;
            isLanding_t = true;
        }

        if (processingTime_t == 0) {
            cout << "Plane" << landing_t.front() << " land complete. (Temp_runway)\n" << endl;
            landing_t.dequeue();
            processingTime_t = -1;
            isLanding_t = false;
        } else {
            cout << "Plane" << landing_t.front() << " is landing. (Temp_runway) " << processingTime_t << " minutes to complete\n" << endl;
            processingTime_t--;
            totalWaitTime_l += landing_t.size() -1;
            totalWaitTime_t += takeOff_t.size();
        }ind
    } else if (!takeOff_t.empty()) {
        if (processingTime_t == -1) {
            processingTime_t = takeOffTime;
            isTakingOff_t = true;
        }
        if (processingTime_t == 0) {
            cout << "Plane" << takeOff_t.front() << " take off complete. (Temp_runway)\n" << endl;
            takeOff_t.dequeue();
            processingTime_t = -1;
            isTakingOff_t = false;
        } else {
            cout << "Plane" << takeOff_t.front() << " is taking off. (Temp_runway) " << processingTime_t << " minutes to complete\n" << endl;
            processingTime_t--;
            totalWaitTime_t += takeOff_t.size() - 1;
        }
    }
}



