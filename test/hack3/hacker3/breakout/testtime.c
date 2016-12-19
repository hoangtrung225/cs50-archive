// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

int main(void)
{
	
	double timeold = 0, timer;
	GWindow window = newGWindow(320,240);
	
	while (true)
	{
						
		GEvent event = getNextEvent(MOUSE_EVENT);
		
		if (event != NULL)
		{
			if (getEventType(event) == MOUSE_MOVED)
			{
				timer = getEventTime(event);
				printf("%f\n",timer);
				
				timeold=timer;
			}
		}
	}
}
				
		
