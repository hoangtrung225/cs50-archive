#include <spl/gwindow.h>
#include <spl/gevents.h>
#include <spl/gobjects.h>

int main(void)
{
	GWindow window = newGWindow(320, 240);
	GOval circle = newGOval(0, 0, 40, 40);
	add(window, circle);
	while (true)
	{
		GEvent event = getNextEvent(MOUSE_EVENT);
		if (event != NULL)
		{
			if (getEventType(event) == MOUSE_MOVED)
			{
				double x = getX(event);
				double y = getY(event);
				setLocation(circle, x, y);
			}
		}
	}
	return 0;
}
