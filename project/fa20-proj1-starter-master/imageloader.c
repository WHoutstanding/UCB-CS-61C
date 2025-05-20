/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename)
{
	// YOUR CODE HERE
	FILE *fp = fopen(filename, "r");

	char ppm[10];
	uint32_t cols, rows, scale;
	fscanf(fp, "%s %u %u %u", ppm, &cols, &rows, &scale);

	Color **img = (Color **)malloc(sizeof(Color *) * rows);

	uint8_t r, g, b;
	for (uint32_t i = 0; i < rows; i++)
	{
		img[i] = (Color *)malloc(sizeof(Color) * cols);
		for (uint32_t j = 0; j < cols; j++)
		{
			fscanf(fp, "%hhu %hhu %hhu", &r, &g, &b);
			Color rgb = {r, g, b};
			img[i][j] = rgb;
		}
	}

	Image *image = (Image *)malloc(sizeof(Image));
	image->image = img;
	image->cols = cols;
	image->rows = rows;

	fclose(fp);
	// free(img);

	return image;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	// YOUR CODE HERE
	printf("P3\n");
	uint32_t rows = image->rows, cols = image->cols;
	printf("%u %u\n", cols, rows);
	printf("255\n");

	uint8_t r, g, b;
	Color **img = image->image;
	for (uint32_t i = 0; i < rows; i++)
	{
		for (uint32_t j = 0; j < cols; j++)
		{
			Color rgb = img[i][j];
			r = rgb.R, g = rgb.G, b = rgb.B;
			if (j != cols - 1)
			{
				printf("%3u %3u %3u   ", r, g, b);
			}
			else
			{
				printf("%3u %3u %3u", r, g, b);
			}
		}
		printf("\n");
	}
}

// Frees an image
void freeImage(Image *image)
{
	// YOUR CODE HERE
	uint32_t rows = image->rows;
	Color **img = image->image;
	for (int i = 0; i < rows; i++)
	{
		free(*(img + i));
	}
	free(img);
	free(image);
}