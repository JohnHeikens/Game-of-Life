// Engine3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Window3D.h"
constexpr int checkx[8]{ -1, 0, 1,-1,1,-1,0,1 };
constexpr int checky[8]{ -1,-1,-1, 0,0, 1,1,1 };

int main()
{
	HINSTANCE Current = GetModuleHandle(NULL);
	int w = 0, h = 0;
	GetDesktopResolution(w, h);
	Window3D* window = new Window3D(Current, w, h);
	window->Show();
	int length = w * h;
	bool* Grid = (bool*)calloc(length, sizeof(bool));
	bool* NewGrid = (bool*)calloc(length, sizeof(bool));
	color AliveColor = color((byte)rand(), (byte)rand(), (byte)rand());
	color DeathColor = color(1 - AliveColor.R, 1 - AliveColor.G, 1 - AliveColor.B);
	bool* GridPtr = Grid;
	for (int i = 0; i < length; i++)//fill grid with randomness
	{
		*GridPtr++ = rand() % 3 == 0;//1 out of 3 chance that it is alive
		//*GridPtr++ = rand() % 50 == 0;//switch this line with the line above and see what happens!
	}
	int first = 1;//does not check the borders
	int lasti = w - 1;	
	int lastj = h - 1;
	while (true)
	{
		fp f = (fp)rand() / RAND_MAX;
		color* ptr = window->colors;
		//process and draw
		for (int j = first; j < lastj; j++) {
			int plusj = j * w;
			for (int i = first; i < lasti; i++)
			{
				int plusi = plusj + i;
				//count neighbors
				int count = 0;
				for (int k = 0; k < 8; k++)
				{
					int plus = plusi + checkx[k] + checky[k] * w;
					if (*(Grid + plus))
					{
						count++;
					}
				}
				if (count < 2 || count > 3) {
						*(NewGrid + plusi) = false;//certain death

					}
				if (count == 3) 
				{
					*(NewGrid + plusi) = true;//certain, alive
				}
				else {
					*(NewGrid + plusi) = *(Grid + plusi);//remains what it is
				}
				//fill pixel
				if (*(Grid + plusi))
				{
					*(window->colors + plusi) = AliveColor;
				}
				else 
				{
					*(window->colors + plusi) = DeathColor;
				}

			}
		}
		Grid = NewGrid;
		window->Update();
	}
	delete window;
}
