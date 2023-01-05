#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include "template.h"
#include <math.h>
#include <cstring>
#include <iostream>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	
	//VARIABLES
	static Sprite theSprite(new Surface("assets/ninja.png"), 1);
	static Sprite theSpriteS(new Surface("assets/ninjaS.png"), 1);

	vec2 playerPos{ 0, 0 };

	vec2 pivotPos{ 350, 350 };

	int bx1 = 0, bx2 = 750;

	int speed = 1;

	bool isGrounded = false, rWall = false;

	int xDiff = 360 - playerPos.x;
	int yDiff = playerPos.y - 200;


	//METHODS
	void Circle(Surface* s, float x, float y, float r)
	{
		for (int i = 0; i < 64; i++)
		{
			float r1 = (float)i * PI / 32, r2 = (float)(i + 1) * PI / 32;
			s->Line(x - r * sinf(r1), y - r * cosf(r1),
				x - r * sinf(r2), y - r * cosf(r2), 0xff0000);
		}
	}

	void Square(Surface* s, int x, int y, int init1, int init2)
	{
		s->Line(x - init1, y - init1, x - init1, y + init1, 0xffffff);//left
		s->Line(x - init1, y + init1, x + init2, y + init1, 0xffffff);//top
		s->Line(x + init2, y - init1, x + init2, y + init1, 0xffffff);//right
		s->Line(x - init1, y - init1, x + init2, y - init1, 0xffffff);//down

		if (playerPos.x <= x + init2 && playerPos.x + 50 >= x - init1 && playerPos.y <= y + init1 && playerPos.y + 50 >= y - init1)
		{
			speed = -speed * 0.9f;
			isGrounded = true;
			
		}
		if (playerPos.x <= x + init2 && playerPos.x + 50 >= x - init1 && playerPos.y == y + init1)
		{
			playerPos.y = y + init1 + 5;
		}
		if (playerPos.x == x - (init1 + 50) && playerPos.y <= y + init1 && playerPos.y + 50 >= y - init1)
		{
			playerPos.x = x - (init1 + 55);
			rWall = true;
		}
		if (playerPos.x == x + init2 && playerPos.y <= y + init1 && playerPos.y + 50 >= y - init1)
		{
			playerPos.x = x + init2 + 5;
			rWall = true;
		}
		

	}

	void Tunnel(Surface* s, int x, int y, int init1, int init2)
	{
		//s->Line(x - init1, y - init1, x - init1, y + init1, 0xffffff);//left
		s->Line(x - init1, y + init1, x + init2, y + init1, 0xffffff);//top
		//s->Line(x + init2, y - init1, x + init2, y + init1, 0xffffff);//right
		s->Line(x - init1, y - init1, x + init2, y - init1, 0xffffff);//down

		if (playerPos.x <= x + init2 && playerPos.x + 50 >= x - init1 && playerPos.y <= y + init1 && playerPos.y + 50 >= y - init1)
		{
			speed = -speed * 0.9f;
			isGrounded = true;
			rWall = true;

		}
		if (playerPos.x <= x + init2 && playerPos.x + 50 >= x - init1 && playerPos.y == y + init1)
		{
			playerPos.y = y + init1 + 5;
		}


	}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		//PLAYER LOGIC

		playerPos.y += speed;
		speed += 1.0f;

		//sprite conditions
		if (isGrounded == false)
		{
			theSprite.Draw(screen, playerPos.x, playerPos.y);
		}
		else
		{
			theSpriteS.Draw(screen, playerPos.x, playerPos.y);
		}

		//GENERATE BORDERS
		DrawBorders(bx1, bx2, playerPos.y, playerPos.y);

		//GENERATE CURRENT COLLIDERS
		Circle(screen, playerPos.x + 25 , playerPos.y + 25, 25);
		Square(screen, pivotPos.x, pivotPos.y, 75, 360);
		Square(screen, pivotPos.x + 450, pivotPos.y, 75, 300);
		//Tunnel(screen, pivotPos.x + 150, pivotPos.y - 100, 75, 360);
		//Tunnel(screen, pivotPos.x + 550, pivotPos.y - 70, 75, 360);
		//Tunnel(screen, pivotPos.x + 950, pivotPos.y - 50, 75, 360);

		//input controls
		
		if (GetAsyncKeyState(VK_LEFT)) playerPos.x -= 5;
		if (GetAsyncKeyState(VK_RIGHT)) playerPos.x += 5;
		if (GetAsyncKeyState(VK_UP) && rWall == true) playerPos.y -= 3;
		if (GetAsyncKeyState(VK_DOWN) && rWall == true) playerPos.y += 3;
		if (GetAsyncKeyState(VK_SPACE) && isGrounded == true) speed *= 1.25f;


		////debug values
		printf("x: %d ", (int)playerPos.x);
		printf("y: %d \n", (int)playerPos.y);
		printf("Speed: %d \n", speed);
		screen->Print("Left/Right arrow keys to move.", 20, 20, 0xffffff);
		screen->Print("Hold space to progressively gain bounce force", 20, 40, 0xffffff);
	}


	void Game::DrawBorders(int xMin, int xMax, int yMin, int yMax)
	{
		if (playerPos.x < (xMin))
		{
			playerPos.x = xMin;

		}
		/*if (playerPos.x >(xMax))
		{
			playerPos.x = xMax;

		}*/
		if (playerPos.y > (512 - 50))
		{
			playerPos.y = 512 - 50;
			speed = -speed * 0.8f;
			isGrounded = true;
		}
		else
		{
			isGrounded = false;
		}
		if (playerPos.y < (0))
		{
			playerPos.y = 0;
		}
	}
};