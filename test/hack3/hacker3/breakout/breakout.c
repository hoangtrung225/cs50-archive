//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

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

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3
// pad
#define  PadW  60
#define	 PadH  10
    
// velocity of Colission
double veloColis = 0;
double velocityX = 2.0;
double velocityY = 2.0;	

//ini the portion of bricks
int BrickW = 35;
int BrickH = 10;

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void Ballmove(GWindow window, GOval ball);
void Collison(GOval Ball, GObject Object);
GObject initCanons(GWindow window, GObject paddle);


int main(int argc, char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    
	// init guns paddle
	GObject canons = initCanons(window,paddle);
	
	//gun with the paddle
	GObject gunpad = newGCompound();
	addGCompound(gunpad, canons);
	add(window,gunpad);

    

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;
    
    // init time
    double timeold = 0;
    //int potion
    double OldX = 0;

	bool god = 0;
    // number of points initially
    int points = 0;
	double timenew = 0;
	if (argc == 1)
		god = 0;
	else if (strcmp(argv[1],"GOD") == 0)
		god = 1;
	
    // keep playing until game over
    if (god == 0)
    {
		int space = getX(paddle)-getX(gunpad);
    while (lives > 0 && bricks > 0)
    {
        // TODO
        
        GEvent movement = getNextEvent(MOUSE_EVENT);
        if (movement != NULL)
        {
			if (getEventType(movement) == MOUSE_MOVED)
			{
				timenew = getEventTime(movement);
				double x = getX(movement) - getWidth(paddle)/2;
				double y = HEIGHT - 5 - getHeight(paddle);
				setLocation(gunpad,x- space,0);
				setLocation(paddle,x,y);
			}
		}
		if (detectCollision(window, ball) != NULL)
		{
			if (strcmp(getType(detectCollision(window, ball)),"GRect") == 0)
			{
					// Ball collisse with brick 
					if (getY(ball) < HEIGHT/2)
					{
						removeGWindow(window,detectCollision(window,ball));
						points = points+1;
						updateScoreboard(window,label,points);
						velocityY = -velocityY;
						setSize(paddle,getWidth(paddle)-getWidth(paddle)/40,getHeight(paddle)-getHeight(paddle)/30);
						removeGWindow(window,gunpad);
						canons=initCanons(window,paddle);
						addGCompound(gunpad,canons);
						add(window,gunpad);
		
					}
					// Ball collise with pad
					else
					{
						if (timenew == timeold) 
							veloColis = 0;
						else
						{
							veloColis = (getX(movement)-OldX)/(timenew - timeold)/20;
							OldX = getX(movement);
						}
					}

			}
		}
		Ballmove(window, ball);
		timeold = timenew;
		veloColis = 0;
		if (getY(ball) > HEIGHT)
		{
			lives = lives - 1;
			setLocation(ball, WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS);
			velocityX = 2.0;
			velocityY = 2.0;	
		}
	  }
  }
  else if (god == 1)
  {
	  while (lives > 0 && bricks > 0)
	  {
		double x = getX(ball) + RADIUS- getWidth(paddle)/2;
		double y = HEIGHT - 5 - PadH;
		setLocation(paddle, x, y);
		if (detectCollision(window, ball) != NULL)
		{
			if (strcmp(getType(detectCollision(window, ball)),"GRect") == 0)
			{
				
					// Ball collisse with brick 
					if (getY(ball) < HEIGHT/2)
					{
						removeGWindow(window,detectCollision(window,ball));
						points = points+1;
						updateScoreboard(window,label,points);
						velocityY = -velocityY;
						setSize(paddle,getWidth(paddle)-getWidth(paddle)/40,getHeight(paddle)-getHeight(paddle)/30);

					}
					// Ball collise with pad
					else
					{
						if (timenew == timeold) 
							veloColis = 0;
						else
						{
							veloColis = (getX(paddle)-OldX)/(timenew - timeold)/20;
							OldX = getX(paddle);
						}
					}

			}
		}
		Ballmove(window, ball);
		timeold = timenew;
		veloColis = 0;
		if (getY(ball) > HEIGHT)
		{
			lives = lives - 1;
			setLocation(ball, WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS);
			velocityX = 2.0;
			velocityY = 2.0;	
		}
	}
} 
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
	
	int space = (WIDTH - COLS*BrickW -10)/9;
	int Xini = 5;
	int Yini = 40;
	char* color;
    for (int j = 0; j < ROWS; j++)
    {
		if (j == 0) 
			color = "RED";
		else if (j == 1)
			color = "BLUE";
		else if (j == 2)
			color = "YELLOW";
		else if (j == 3)
			color = "ORANGE";
		else  color = "CYAN";
		
		for (int i = 0; i < COLS; i++)
		{
			GRect rect = newGRect(Xini + i*(BrickW+space), Yini + j*(BrickH+space), BrickW, BrickH);
			setFilled(rect, true);
			setColor(rect, color);
			add(window, rect);
		}
	}
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    double velocityX = 2.0;
	double velocityY = 2.0;	
    GOval Ball = newGOval(WIDTH/2-RADIUS,HEIGHT/2-RADIUS,RADIUS*2,RADIUS*2);
    setFilled(Ball, true);
    setColor(Ball, "BLACK");
    add(window,Ball);
    return Ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect((WIDTH-PadW)/2,(HEIGHT - 5 - PadH),PadW,PadH);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
	setFont(label, "SansSerif-50");
	add(window, label);
	double x = WIDTH/2 - getWidth(label)/2;
	double y = HEIGHT/2 - getHeight(label)/2 ;
	setLocation(label,x,y);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
// init ball velocity

void Ballmove(GWindow window, GOval Ball)

{	
	if (getX(Ball) + getWidth(Ball) > WIDTH)
	{
		velocityX = -velocityX;
	}
	else if (getX(Ball) < 0)
	{
		velocityX = -velocityX;
	}
	else if (getY(Ball) < 0)
	{
		velocityY = -velocityY;
	}
	else if (detectCollision(window,Ball) != NULL)
	{
		if(strcmp(getType(detectCollision(window,Ball)),"GLabel") != 0)
		{
			
				velocityX = velocityX - veloColis;
				Collison(Ball,detectCollision(window,Ball));
		}
	}
	move(Ball, velocityX, velocityY);

	pause(10);
}

// init the collison 

void Collison(GOval Ball, GObject Object)
{
	double midXBall = getX(Ball) + RADIUS;
	double midYBall = getY(Ball) + RADIUS;
	// facesmash check 
	if (((midXBall > getX(Object)) && (midXBall < getX(Object) + getWidth(Object))) && (((midYBall  > getY(Object) - RADIUS) && (midYBall < getY(Object))) || ((midYBall < getY(Object) + getHeight(Object) + RADIUS) && (midYBall > getY(Object) + getHeight(Object)))))
	{
		velocityY = -velocityY;
	}
	else if (((midXBall < getX(Object)) && (getX(Object)-RADIUS < midXBall)) || ((midXBall > getX(Object) + getWidth(Object))&&(midXBall < getX(Object) + getWidth(Object) + RADIUS))) 
	{
		velocityX = -velocityX;
	}
	else
	{
		velocityX = -velocityX;
		velocityY = -velocityY;
	}
}

// init two canon
GObject initCanons(GWindow window, GObject paddle)
{
	double canonW = 2;
	double canonH = 10;
	GRect leftcanon = newGRect(getX(paddle),getY(paddle)-canonH,canonW,canonH);
	GRect rightcanon = newGRect(getX(paddle)+getWidth(paddle)-canonW,getY(paddle)-canonH,canonW,canonH);
	GObject canons = newGCompound();
	addGCompound(canons, leftcanon);
	addGCompound(canons, rightcanon);
	add(window,canons);
	return canons;
}
	
	
