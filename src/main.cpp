#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string.h>

#include "DoubleMario.h"
#include "RenderExample2D.h"
#include "utils/glErrorUtils.h"

void PrintHelp()
{
	printf("\nHow to use arguments:  ./app [Options] {Paths}\n");
	printf("Options:\n");
	printf("'-2D':\n");
	printf("    -  If you leave the path blank an image of mario will be rendered.\n");
	printf("    -  Insert a path to a given image you wish to have rendered.\n");
	printf("'-help':\n");
	printf("    -  Displays this message\n");
}

int main(int argc, char* argv[])
{
	Renderer renderer(30);

	GLenum err = glewInit();
	
	if (err != GLEW_OK) {
		//GLEW was not initialized stop the program!
		return 0;
	}
	
	//std::cout << glGetString(GL_VERSION) << std::endl;
	
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GlCall(glEnable(GL_BLEND));

	if (argc <= 1)
	{
		PrintHelp();
	}
	else if (argc == 2) 
	{
		if (strcmp(argv[1], "-help") == 0)
		{
			PrintHelp();
		}
		else if (strcmp(argv[1], "-2D") == 0)
		{
			const DoubleMario mario;

			mario.Run(renderer);
		}
		else 
		{
			printf("\n%s not a valid option\n", argv[1]);
			PrintHelp();
		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-2D") == 0)
		{
			const RenderExample2D example(argv[2]);

			example.Run(renderer);
		}
		else 
		{
			printf("\n%s not a valid option, when a path is given\n", argv[1]);
			PrintHelp();
		}
	}

    return 0;
}
