#include <stdio.h>
#include <error.h>
#include <gd.h>
#include <string.h>
#include <omp.h>
// image size vs scheduling technique

int main(int argc, char **argv) 
{
	FILE *fp = {0}; 
	gdImagePtr img;
	char *iname = NULL; // input file name
	char *oname = NULL; // output file name
	int color, x, y, w, h,i=0;
	int red, green, blue;
	color = x = y = w = h = 0;
	red = green = blue = 0;
	int mean = 0, thresh = 100; 
	int threadid = 0;
	if(argc != 3)
		error(1, 0, "Usage: gdnegat input.png output.png");
	else{
		iname = argv[1];
		oname = argv[2];
	}
	if((fp = fopen(iname, "r")) == NULL)
		// cannot open input file 
		error(1, 0, "Error - fopen(): %s", iname);
	else
		img = gdImageCreateFromPng(fp);
	// image width
	w = gdImageSX(img);
	// image height
	h = gdImageSY(img);
	double t = omp_get_wtime();
#pragma omp parallel for private(y, color, red, green, blue) schedule(dynamic,4)
	for(x = 0; x < w; x++) {
		for(y = 0; y < h; y++) {
			// color = x+0;
			threadid = omp_get_thread_num();
			color = gdImageGetPixel(img, x, y);
			red   = gdImageRed(img, color);
			green = gdImageGreen(img, color);
			blue  = gdImageBlue(img, color);
			mean = (red + green + blue)/3;
			red = blue = green = mean;
			color = gdImageColorAllocate(img, red, green, blue);
			gdImageSetPixel(img, x, y, color);
		}
	}
	if((fp = fopen(oname, "w")) == NULL)
		error(1, 0, "Error - fopen(): %s", oname);
	else{
		gdImagePng(img, fp);
		fclose(fp);
	}
	t = omp_get_wtime() - t;
	gdImageDestroy(img);
	printf("Time taken = %.10f\n",t);
	return 0;
}
