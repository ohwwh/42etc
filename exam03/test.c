#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct canvas
{
	int	width;
	int	height;
	char	c;
	char	*canvas;
}canvas;

typedef struct figure
{
	char	filled;
	float	x;
	float	y;
	float	width;
	float	height;
	char	c;
}figure;

int	get_info(FILE *file, canvas *can)
{
	int	i;

	i = 0;
	if (3 == fscanf(file, "%d %d %c\n", &can->width, &can->height, &can->c))
	{
		if (can->width < 1 || can -> width > 300 || can->height < 1 || can->height > 300)
			return (1);
		can->canvas = (char *)malloc(sizeof(char) * ((can->width + 1) * can->height + 1));
		if (!can->canvas)
			return (1);
		while (i < ((can->width + 1) * can->height))
		{
			if ((i + 1) % (can->width + 1))
				can->canvas[i] = can->c;
			else
				can->canvas[i] = '\n';
			i ++;
		}
		can->canvas[i] = 0;
		return (0);
	}
	else
		return (1);
}

int	in_fig(figure *fig, float i, float j)
{
	if (i < fig->x || i > fig->x + fig->width || j < fig->y || j > fig->y + fig->height)
		return (0);
	else if (i - fig->x < 1.000000 || fig->x + fig->width - i < 1.000000 || 
	j - fig->y < 1.000000 || fig->y + fig->height - j < 1.000000)
		return (2);
	return (1);
}

void	paint_pixel(figure *fig, canvas *can, int i, int j)
{
	const int	ret = in_fig(fig, (float)i, (float)j);
	if (ret == 2 || (ret == 1 && fig->filled == 'R'))
		can->canvas[i + ((can->width + 1) * j)] = fig->c;
}

int	execute_fig(figure *fig, canvas* can)
{
	int	i;
	int	j;

	i = 0;
	if (fig->width <= 0.000000 || fig->height <= 0.000000 || (fig->filled != 'r' && fig->filled != 'R'))
		return (1);
	while (i < can->width)
	{
		j = 0;
		while (j < can->height)
		{
			paint_pixel(fig, can, i, j);
			j ++;
		}
		i ++;
	}
	return (0);
}

void	print_canvas(canvas can)
{
	int	i;

	i = 0;
	while (can.canvas[i])
		write(1, &can.canvas[i ++], 1);
}

int	execute(FILE *file)
{
	canvas can;
	figure fig;
	int		f;

	if (!get_info(file, &can))
	{
		f = fscanf(file, "%c %f %f %f %f %c\n", &fig.filled, &fig.x, &fig.y, &fig.width, &fig.height, &fig.c);
		while (f == 6)
		{
			if (!execute_fig(&fig, &can))
				f = fscanf(file, "%c %f %f %f %f %c\n", &fig.filled, &fig.x, &fig.y, &fig.width, &fig.height, &fig.c);
			else
				return (1);
		}
		if (f != -1)
			return (1);
		else
		{
			print_canvas(can);
			return (0);
		}
	}
	else
		return (1);
}

int main(int argc, char *argv[]){
	FILE *file;
	
	if (argc != 2)
		write(1, "Error: argument\n", 16);
	file = fopen(argv[1], "r");
	if (file && !execute(file))
		return (0);
	write(1, "Error: Operation file corrupted\n", 32);
}

/*
execute
execute_fig
paint_pixel
in_fig
*/