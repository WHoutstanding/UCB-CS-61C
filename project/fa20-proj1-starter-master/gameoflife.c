/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
// Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
// and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	// YOUR CODE HERE
	Color **img = image->image;
	uint8_t b = img[row][col].B;
	uint8_t flag;
	// 判断当前像素的状态是0or255
	if (b % 2 != 0)
	{
		flag = 255;
	}
	else
	{
		flag = 0;
	}

	// 统计当前像素周围的像素状态是255的个数
	uint32_t rows = image->rows, cols = image->cols;
	int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1}, dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		uint8_t a = (row + dx[i] + rows) % rows, b = (col + dy[i] + cols) % cols;
		uint8_t bule = img[a][b].B;
		if (bule % 2 != 0)
		{
			sum++;
		}
	}

	// 计算当前像素下个周期像素的状态是255or0
	int shift_number = sum;
	if (flag == 255)
	{
		shift_number += 9;
	}

	rule >>= shift_number;
	int state = rule & 1;

	if (state == 1)
	{
		flag = 255;
	}
	else
	{
		flag = 0;
	}

	Color *color = (Color *)malloc(sizeof(Color));
	color->R = flag;
	color->G = flag;
	color->B = flag;

	return color;
}

// The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
// You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	// YOUR CODE HERE
	uint32_t rows = image->rows, cols = image->cols;
	Color **new_img = (Color **)malloc(sizeof(Color *) * rows);

	for (uint32_t i = 0; i < rows; i++)
	{
		new_img[i] = (Color *)malloc(sizeof(Color) * cols);
		for (uint32_t j = 0; j < cols; j++)
		{
			Color *p = evaluateOneCell(image, i, j, rule);
			new_img[i][j] = *p;
			free(p);
		}
		// printf("\n");
	}

	Image *new_image = (Image *)malloc(sizeof(Image));
	new_image->image = new_img;
	new_image->cols = cols;
	new_image->rows = rows;

	return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	Image *image = readData(argv[1]);

	// printf("%s", argv[2]);
	char *endptr;
	uint32_t rule = strtol(argv[2], &endptr, 16);
	// printf("rule: %d", rule);

	Image *new_image = life(image, rule);
	// Writes an image to stdout
	writeData(new_image);

	// Frees an image and all its associated data
	freeImage(image);
	freeImage(new_image);

	return 0;
}
