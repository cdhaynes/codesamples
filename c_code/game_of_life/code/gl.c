/**
 * @file gl.c
 *
 * @brief contains main logic for Conway's "Game of Life"
 *
 * @details takes in command line arguments and parses them to reflect changes in
 * the program. Uses mostly "If/Else" statements to do the job.
 *
 * @author Casey D. Haynes
 *
 * @date December 7, 2017
 *
 * @todo Add more error-checking and correct memory managment issues. Get the Klein Bottle working.
 *  Make code more modular--translate spaghetti to functions.
 *
 * @bug none
 *
 * @remark the valgrind command provided in the PDF does not show any memory leaks. However, I am sure they are present.
 */

#include <stdlib.h>
#include "SDL2/SDL.h"
#include "sdl.h"
#include "string.h"
#include "life.h"
#include <unistd.h>

#define LEN 1024

int main(int argc, char *argv[])
{

	int c;

	if (argc == 1) {
		printf("usage: life\n\n\n-w width of screen argument\n\n");
		printf("-h height of screen argument\n\n");
		printf("-e type of edge\n\n");
		printf("-r the red color value\n\n");
		printf("-g the green color value\n\n");
		printf("-b the blue color value\n\n");
		printf("-s size of the sprite\n\n");
		printf("-f filename (1.06)\n\n");
		printf("-o x,y initial x,y coordinate\n\n");
		printf("-H help\n\n");
		printf("-P filename(1.06)\n\n");
		printf("-Q filename(1.05)\n\n");
		printf("-p x,y initial coordinate of P\n\n");
		printf("-q x,y initial coordinate of Q\n\n");
		return 1;
	}


	int width = 600;
	int height = 800;
	int sprite_size = 8; /* either 2, 4, 8, or 16 */
	int x = 30;
	int y = 30;
	char *e = NULL;
	char *f = NULL;
	int i;
	int j;
 	char buf[1024];
        /* colors are RGB model valid values [0, 255] */
	unsigned char red = 140;
	unsigned char green = 145;
	unsigned char blue = 250;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */
	FILE *in;

	while((c = getopt(argc, argv, "::w:h:r:g:b:s:f:o:e:")) != -1) {
		switch(c) {
		case 'w':
			height = atoi(optarg);
			break;
		case 'h':
			width = atoi(optarg);
			break;
		case 'r':
			red = atoi(optarg);
			break;
		case 'g':
			green = atoi(optarg);
			break;
		case 'b':
			blue = atoi(optarg);
			break;
		case 's':
			sprite_size = atoi(optarg);
			break;
		case 'f':
			f = optarg;
			in = fopen(f, "r");
			if (in == NULL) {
				printf("Couldn't open file\n");
				return 1;
			}


			break;
		case 'o':
			x = atoi(strtok(optarg, ","));
			y = atoi(strtok(NULL, "\n"));
			break;
		case 'e':
			e = optarg;
			break;
		case 'H':
			printf("usage: life\n\n\n-w width of screen argument\n\n");
			printf("-h height of screen argument\n\n");
			printf("-e type of edge\n\n");
			printf("-r the red color value\n\n");
			printf("-g the green color value\n\n");
			printf("-b the blue color value\n\n");
			printf("-s size of the sprite\n\n");
			printf("-f filename (1.06)\n\n");
			printf("-o x,y initial x,y coordinate\n\n");
			printf("-H help\n\n");
			printf("-P filename(1.06)\n\n");
			printf("-Q filename(1.05)\n\n");
			printf("-p x,y initial coordinate of P\n\n");
			printf("-q x,y initial coordinate of Q\n\n");
			return 1;
			break;

		}
	}

        /* set up SDL -- works with SDL2 */
	init_sdl_info(&sdl_info, height, width, sprite_size, red, green, blue);

	/* your life initialization code here */
	unsigned char **a = NULL;
	unsigned char **b = NULL;
	int width_matrix = 200;
	int height_matrix = 150;
	width_matrix = (width/sprite_size);
	height_matrix = (height/sprite_size);


	a = init_matrix(height_matrix, width_matrix);
	b = init_matrix(height_matrix, width_matrix);


	int flag = 0;
	for (i = 0; i < height_matrix; i++) {
		for (j = 0; j < width_matrix; j++) {
			a[i][j] = 0;


		}
	}

	for (i = 0; i < height_matrix; i++) {
		for (j = 0; j < width_matrix; j++) {
			b[i][j] = 0;

		}
	}
        /* Main loop: loop forever. */
	while(fgets(buf, LEN, in))
	{
		if (buf[0] != '#') {
			int o = atoi(strtok(buf, " "));
			int p = atoi(strtok(NULL, " "));
			if (o+x > height_matrix) {
				continue;
			}
			if (o+x < 0){
				continue;
			}
			if (p+y > width_matrix) {
				continue;
			}
			if (p+y < 0) {
				continue;
			}
			b[o+x][p+y] = 1;


		}


	}

int hedge = strncmp(e, "hedge", LEN);
int torus = strncmp(e, "torus", LEN);
int klein = strncmp(e, "klein", LEN);


/*START OF LOGIC */
	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
			/* If escape is pressed, return (and thus, quit) */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_QUIT:
				return(0);
			}
		}


if (hedge == 0) {
		for (i = 0; i < height_matrix; i++) {
			for (j = 0; j < width_matrix; j++) {
				/* hedge boundaries */
			int count = 0;
			if (flag == 0) {

				if (i-1 >= 0 && j-1 >= 0 && b[i-1][j-1] == 1) {
					count++;
					}
				if (i-1 >= 0 && b[i-1][j] == 1) {
					count++;
					}
				if (i-1 >= 0 && j+1 < height_matrix && b[i-1][j+1] == 1) {
					count++;
					}
				if (j-1 >= 0 && b[i][j-1] == 1) {
					count++;
					}
				if (j+1 < height_matrix && b[i][j+1] == 1) {
					count++;
					}
				if (i+1 < width_matrix && j-1 >= 0 && b[i+1][j-1] == 1) {
					count++;
					}
				if (i+1 < width_matrix && b[i+1][j] == 1) {
					count++;
					}
				if (i+1 < width_matrix && j+1 < height_matrix && b[i+1][j+1] == 1) {
					count++;
					}


			/*Use two arrays, set flags, alternate*/
				if (b[i][j] == 1 && count < 2) {
					a[i][j] = 0;
				} else if (b[i][j] == 1 && (count == 2 || count == 3)) {
					a[i][j] = 1;
				} else if (b[i][j] == 1 && count > 3) {
					a[i][j] = 0;
				} else if (b[i][j] == 0 && count == 3) {
					a[i][j] = 1;
				} else {
					a[i][j] = 0;
				}

}                   else if (flag == 1) {
		if (i-1 >= 0 && j-1 >= 0 && a[i-1][j-1] == 1) {
			count++;
			}
			if (i-1 >= 0 && a[i-1][j] == 1) {
				count++;
			}
			if (i-1 >= 0 && j+1 < height_matrix && a[i-1][j+1] == 1) {
				count++;
			}
			if (j-1 >= 0 && a[i][j-1] == 1) {
				count++;
			}
			if (j+1 < height_matrix && a[i][j+1] == 1) {
				count++;
			}
			if (i+1 < width_matrix && j-1 >= 0 && a[i+1][j-1] == 1) {
				count++;
			}
			if (i+1 < width_matrix && a[i+1][j] == 1) {
				count++;
			}
			if (i+1 < width_matrix && j+1 < height_matrix && a[i+1][j+1] == 1) {
				count++;
			}


			/*Use two arrays, set flags, alternate*/
			if (a[i][j] == 1 && count < 2) {
				b[i][j] = 0;
			} else if (a[i][j] == 1 && (count == 2 || count == 3)) {
				b[i][j] = 1;
			} else if (a[i][j] == 1 && count > 3) {
				b[i][j] = 0;
			} else if (a[i][j] == 0 && count == 3) {
				b[i][j] = 1;
			} else {
				b[i][j] = 0;
			}



		}


	}/*end inner for*/

}/*end outer for*/
}/*end hedge statement*/

if (torus == 0) {
	for (i = 0; i < height_matrix; i++) {
		for (j = 0; j < width_matrix; j++) {

		int count = 0;
		if (flag == 0) {


			if (b[(i-1+height_matrix)%height_matrix][(j-1+width_matrix)%width_matrix] == 1) {
				count++;
				}
			if (b[(i-1+height_matrix)%height_matrix][j] == 1) {
				count++;
				}
			if (b[(i-1+height_matrix)%height_matrix][(j+1)%width_matrix] == 1) {
				count++;
				}
			if (b[i][(j-1+width_matrix)%width_matrix] == 1) {
				count++;
				}
			if (b[i][(j+1)%width_matrix] == 1) {
				count++;
				}
			if (b[(i+1)%height_matrix][(j-1+width_matrix)%width_matrix] == 1) {
				count++;
				}
			if (b[(i+1)%height_matrix][j] == 1) {
				count++;
				}
			if (b[(i+1)%height_matrix][(j+1)%width_matrix] == 1) {
				count++;
				}


		/*Use two arrays, set flags, alternate*/
			if (b[i][j] == 1 && count < 2) {
				a[i][j] = 0;
			} else if (b[i][j] == 1 && (count == 2 || count == 3)) {
				a[i][j] = 1;
			} else if (b[i][j] == 1 && count > 3) {
				a[i][j] = 0;
			} else if (b[i][j] == 0 && count == 3) {
				a[i][j] = 1;
			} else {
				a[i][j] = 0;
			}

}                   else if (flag == 1) {
	if (a[(i-1+height_matrix)%height_matrix][(j-1+width_matrix)%width_matrix] == 1) {
		count++;
		}
		if (a[(i-1+height_matrix)%height_matrix][j] == 1) {
			count++;
		}
		if (a[(i-1+height_matrix)%height_matrix][(j+1)%width_matrix] == 1) {
			count++;
		}
		if (a[i][(j-1+width_matrix)%width_matrix] == 1) {
			count++;
		}
		if (a[i][(j+1)%width_matrix] == 1) {
			count++;
		}
		if (a[(i+1)%height_matrix][(j-1+width_matrix)%width_matrix] == 1) {
			count++;
		}
		if (a[(i+1)%height_matrix][j] == 1) {
			count++;
		}
		if (a[(i+1)%height_matrix][(j+1)%width_matrix] == 1) {
			count++;
		}


		/*Use two arrays, set flags, alternate*/
		if (a[i][j] == 1 && count < 2) {
			b[i][j] = 0;
		} else if (a[i][j] == 1 && (count == 2 || count == 3)) {
			b[i][j] = 1;
		} else if (a[i][j] == 1 && count > 3) {
			b[i][j] = 0;
		} else if (a[i][j] == 0 && count == 3) {
			b[i][j] = 1;
		} else {
			b[i][j] = 0;
		}



	}


}/*end inner for*/

}/*end outer for*/


}

if (klein == 0) {
	printf("The Klein Bottle Function is not operable, sorry.\n");
	return 1;
}
/*torus if END*/


if (flag == 0) {
	flag = 1;
	sdl_render_life(&sdl_info, a);
} else if (flag == 1) {
	flag = 0;
	sdl_render_life(&sdl_info, b);
}

}/*while END*/






	}
