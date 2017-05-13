NAME: Fang Zhang
No partner.
files:
runway.C - the runway implementation
LQueue.h
LQueue.C
LQueue_driver.C
Makefile
Part1.txt - test output for part 1
Part2.txt - text output for part 2
Error_checking.txt :reasonable error checking

For runway.cpp:
(1)There are two runways in this project.
	-main_runway is the main runway, which works all the time.
	-temp_runway is the temporary runway, which works in the same way as the main runway, but it will be closed after 60 minutes.
	-main_runway and temp_runway has different landing and taking off queues, and main_runway has the priority to be used. After the temp_runway is totally closed, the queues belongs to temp_runway will be merged with the queues belongs to main runway. This means planes wait in temp_runway will be transfer to the main_runway to continue waiting.

(2)Planes are defined by a number like “1001”. Planes with a plane number which mods 7 equals 0 are large planes with huge number of passengers, and they have priority to land.