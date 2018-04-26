Ashley Wu

For this homework I first changed Makefile and then changed main.c.

I think the hardest part of this homework is to find out what the original code does. After reading the main function for several times, and from the information provied by our TA. I found out that the original code was doing something in the loop that goes through a 2D pixel plane. A way to do multithreading on this code is to use multithreading to go through the 2D plane. 

I found out in the discussion that vertically divide the 2D plane is more efficient because it's more cache friendly. So I implemented multithreading vertically.

One problem I encountered is that at the end of the original main function, the code prints out what is in the pixel. But if I do multithreading, I won't be able to control which pixel gets printed first because I don't know which thread will finish first. To solve this, I created an array as global variable to hold the pixel values and print it out after all threads finish calculating. 

To implement multithreading, I read the Wikipedia page for POSIX Threads and it helped a lot.

The real time for 8-thread version is muush faster than others. I'm expecting the systime to increase in order but surprisingly the systime for 1-test is higher than 2-test and 3-test. Maybe due to different workflow on linux server.