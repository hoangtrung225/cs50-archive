#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
#define  PadW  60
#define	 PadH  10
GRect initPaddle(GWindow window);
#define radius 40

int main(void)
{
	GWindow window = newGWindow(WIDTH,HEIGHT);
	GRect paddle = initPaddle(window);
	GOval ball = newGOval(WIDTH/2 -radius,HEIGHT/2 -radius,radius*2,radius*2);
	add(window,ball);
	 while (true)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(event) - getWidth(paddle);
                setLocation(paddle, x, y);
                removeGWindow(window,ball);
            }
        }
    }
}
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect((WIDTH-PadW)/2,(HEIGHT - 5 - PadH),PadW,PadH);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window,paddle);
    return paddle;
}

				
