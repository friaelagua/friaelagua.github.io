#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "common.h"

#include "gameboy_palette.h"

#define GRAPHICS_IMPLEMENTATION_H
#include "graphics.h"

#define UTIL_IMPLEMENTATION_H
#include "util.h"

static SDL_Texture *display;
static SDL_Event event;

SDL_Point touch;
bool touchDown = false;

typedef struct dial_t dial_t;

struct dial_t
{
	double x, y, r, a;
};

dial_t dialLeft, dialRight;

double x, y, t;

double dialLeftBefore, dialLeftAfter, dialLeftChange;
double dialRightBefore, dialRightAfter, dialRightChange;

bool rotateDialLeft, rotateDialRight;

int es, ex, ey;
int eraseCounter = 0;

double tx, ty;

bool hold = false;

void move(double d)
{
	double nx = d * cos(t * DEG2RAD) + x;
	double ny = d * sin(t * DEG2RAD) + y;

	if (nx < 0)
	{
		nx = 0;
	}

	if (ny < 0)
	{
		ny = 0;
	}

	if (nx > sw - 1)
	{
		nx = sw - 1;
	}

	if (ny > sh - 1)
	{
		ny = sh - 1;
	}

	SetDrawColor(renderer, gameboy_palette[1]);
	DrawLine(renderer, x + ox, y + oy, nx + ox, ny + oy);
	x = nx;
	y = ny;
}

void face(double a)
{
	t = a;
}

int main(int argc, char *args[])
{
	bool quit = false;

	pixelSize = 4;

	w = sw;
	h = sh;
	
	pw=768;
	ph=1024;

	srand(time(NULL));

	SDL_Init(SDL_INIT_VIDEO);

	SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
	SDL_GetWindowSize(window, &w, &h);

	display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	pox = (w - pw) / 2;
	poy = (h - ph) / 2;

	ox = (w - sw * pixelSize) / 2 / pixelSize;
	oy = poy / pixelSize;

	x = sw / 2;
	y = sh / 2;
	t = 0;

	dialLeft.x = (192 + pox) / pixelSize;
	dialLeft.y = (ph - 256 + poy) / pixelSize;
	dialLeft.r = 128 / pixelSize;
	dialLeft.a = 0;

	dialRight.x = (pw - 192 + pox) / pixelSize;
	dialRight.y = (ph - 256 + poy) / pixelSize;
	dialRight.r = 128 / pixelSize;
	dialRight.a = 0;

	SDL_SetRenderTarget(renderer, display);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SetDrawColor(renderer, gameboy_palette[5]);

	SDL_RenderFillRect(renderer, &(SDL_Rect){ox * pixelSize, oy * pixelSize, sw * pixelSize, sh * pixelSize});

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_FINGERDOWN)
			{
				touch.x = event.tfinger.x * w;
				touch.y = event.tfinger.y * h;
				touchDown = true;
			}
			else if (event.type == SDL_FINGERMOTION)
			{
				touch.x = event.tfinger.x * w;
				touch.y = event.tfinger.y * h;
				touchDown = true;
			}
			else if (event.type == SDL_FINGERUP)
			{
				touch.x = event.tfinger.x * w;
				touch.y = event.tfinger.y * h;
				touchDown = false;
			}
		}

		SDL_SetRenderTarget(renderer, display);

		{
			int numTouchDevices = SDL_GetNumTouchDevices();
			for (int i = 0; i < numTouchDevices; i++)
			{
				SDL_TouchID touchId = SDL_GetTouchDevice(i);
				int numTouchFingers = SDL_GetNumTouchFingers(touchId);
				for (int j = 0; j < numTouchFingers; j++)
				{
					SDL_Finger *finger = SDL_GetTouchFinger(touchId, j);

					if (finger)
					{
						tx = finger->x * w / pixelSize;
						ty = finger->y * h / pixelSize;

						if (touchDown)
						{
							if (incirc(tx, ty, dialLeft.x, dialLeft.y, dialLeft.r))
							{
								if (rotateDialLeft)
								{
									dialLeftAfter = atan2(ty - dialLeft.y, tx - dialLeft.x);
									dialLeftChange = sgn(dialLeftAfter - dialLeftBefore) / pixelSize;

									dialLeft.a += dialLeftChange;
									face(0);
									move(dialLeftChange);
									dialLeftBefore = dialLeftAfter;
								}
								else
								{
									dialLeftBefore = dialLeft.a;
									rotateDialLeft = true;
								}
							}

							if (incirc(tx, ty, dialRight.x, dialRight.y, dialRight.r))
							{
								if (rotateDialRight)
								{
									dialRightAfter = atan2(ty - dialRight.y, tx - dialRight.x);
									dialRightChange = sgn(dialRightAfter - dialRightBefore) / pixelSize;

									dialRight.a += dialRightChange;
									face(-90);
									move(dialRightChange);
									dialRightBefore = dialRightAfter;
								}
								else
								{
									dialRightBefore = dialRight.a;
									rotateDialRight = true;
								}
							}
						}
					}
				}
			}
		}

		SetDrawColor(renderer, gameboy_palette[3]);

		DrawPoint(renderer, x + ox, y + oy);

		SDL_SetRenderTarget(renderer, NULL);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, display, NULL, NULL);

		SetDrawColor(renderer, gameboy_palette[5]);

		DrawCircle(renderer, dialLeft.x, dialLeft.y, dialLeft.r);

		DrawCircle(renderer, dialLeft.x + (dialLeft.r - 8) * cos(dialLeft.a - 90 * DEG2RAD), dialLeft.y + (dialLeft.r - 8) * sin(dialLeft.a - 90 * DEG2RAD), 4);

		DrawCircle(renderer, dialRight.x, dialRight.y, dialRight.r);

		DrawCircle(renderer, dialRight.x + (dialRight.r - 8) * cos(dialRight.a - 90 * DEG2RAD), dialRight.y + (dialRight.r - 8) * sin(dialRight.a - 90 * DEG2RAD), 4);

		es = 32;
		ex = ((pw - es * pixelSize) / 2 + pox) / pixelSize;
		ey = ((ph - es * pixelSize) + poy) / pixelSize;

		SetDrawColor(renderer, gameboy_palette[5]);

		DrawRect(renderer, ex, ey, es, es);

		if (touchDown)
		{
			if (inrect(touch.x / pixelSize, touch.y / pixelSize, ex, ey, es, es))
			{
				hold = true;
			}

			if (hold)
			{
				FillRect(renderer, ex, ey, es, es);

				eraseCounter++;
				if (eraseCounter == 100)
				{
					eraseCounter = 0;

					SDL_SetRenderTarget(renderer, display);
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
					SDL_RenderClear(renderer);

					SetDrawColor(renderer, gameboy_palette[5]);
					SDL_RenderFillRect(renderer, &(SDL_Rect){ox * pixelSize, oy * pixelSize, sw * pixelSize, sh * pixelSize});

					SDL_SetRenderTarget(renderer, NULL);
					SDL_RenderCopy(renderer, display, NULL, NULL);
				}
			}
			else
			{
				eraseCounter = 0;
			}
		}
		else
		{
			hold = false;
		}

		{
			int numTouchDevices = SDL_GetNumTouchDevices();
			for (int i = 0; i < numTouchDevices; i++)
			{
				SDL_TouchID touchId = SDL_GetTouchDevice(i);
				int numTouchFingers = SDL_GetNumTouchFingers(touchId);
				for (int j = 0; j < numTouchFingers; j++)
				{
					SDL_Finger *finger = SDL_GetTouchFinger(touchId, j);

					tx = finger->x * w / pixelSize;
					ty = finger->y * h / pixelSize;

					if (touchDown)
					{
						SetDrawColor(renderer, gameboy_palette[3]);
						DrawCircle(renderer, tx, ty, 4);
					}
				}
			}
		}
		SetDrawColor(renderer, gameboy_palette[1]);
		  SDL_RenderDrawRect(renderer, &(SDL_Rect){pox, poy, pw, ph});

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(display);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
