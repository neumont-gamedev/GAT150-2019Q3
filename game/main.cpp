#include "game.h"

#include <functional>
#include <iostream>

struct test
{
	bool display()
	{
		std::cout << "hello!\n";
		return true;
	}
};

int main(int argc, char* args[])
{
	int* p1 = new int(5);
	int* p2 = new int(10);

	(p1 < p2) ? std::cout << "p1" : std::cout << "p2";

	test t;
	std::function<bool()> fp;
	fp = std::bind(&test::display, &t);
	if (fp)
	{
		fp();
	}
	//OutputDebugStringW(L"hello");

	Engine* engine = new Engine();
	Game game(engine);

	game.Startup();
	while (!game.Quit())
	{
		game.Update();
	}
	game.Shutdown();

	return 0;
}

