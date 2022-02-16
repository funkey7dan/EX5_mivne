#include <stdbool.h>
#include <malloc.h>
#include "readBMP.h"
#include "writeBMP.h"
typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    // int num;
} pixel_sum;


/* Compute min and max of two integers, respectively */
int min(int a, int b) { return (a < b ? a : b); }
int max(int a, int b) { return (a > b ? a : b); }



/*
 *  Applies kernel for pixel at (i,j)
 */
static pixel applyKernel(int dim, int i, int j, pixel *src, int 3, int kernel[3][3], int kernelScale, bool filter) {

	int ii = max(i-1, 0), jj;
	int currRow, currCol;
	pixel_sum sum;
	pixel current_pixel;
	int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
	int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
	int min_row, min_col, max_row, max_col,kRow,kCol;
	pixel loop_pixel;
    int ii_min = min(i+1, dim-1),jj_min=min(j+1, dim-1);

	//initialize_pixel_sum(&sum);
    // Initialize inlined
    //void initialize_pixel_sum(pixel_sum *sum)
    sum.red = sum.green = sum.blue = 0;

	for(; ii <= ii_min; ii++) {
        int jj = max(j-1, 0);
		for(; jj <= jj_min; jj++) {

			// compute row index in kernel
			if (ii < i) {
				kRow = 0;
			} else if (ii > i) {
				kRow = 2;
			} else {
				kRow = 1;
			}

			// compute column index in kernel
			if (jj < j) {
				kCol = 0;
			} else if (jj > j) {
				kCol = 2;
			} else {
				kCol = 1;
			}
			// apply kernel on pixel at [ii,jj]
            // TODO: maybe unwrap kernel to 1d array?
			//sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
            // sum_pixels_unrolled:
            //static void sum_pixels_by_weight(pixel_sum *sum, pixel p, int weight)
            // inlining calc index
//            int calcIndex(int i, int j, int n) {
//                return ((i)*(n)+(j));
//            }
            pixel p  = src[ii*dim+jj];
            p.red = (int)p.red;
            p.blue = (int)p.blue;
            p.green = (int)p.green;
            int weight = kernel[kRow][kCol];
            sum.red += ((int) p.red) * weight;
            sum.green += ((int) p.green) * weight;
            sum.blue += ((int) p.blue) * weight;
		}
	}
	if (filter) {
		// find min and max coordinates
        ii = max(i-1, 0);
        jj = max(j-1, 0);
		for(; ii <= min(i+1, dim-1); ii++) {
			for(; jj <= min(j+1, dim-1); jj++) {
				// check if smaller than min or higher than max and update
				loop_pixel = src[ii*dim+jj];
                loop_pixel.red = (int)loop_pixel.red;
                loop_pixel.blue = (int)loop_pixel.blue;
                loop_pixel.green = (int)loop_pixel.green;
				if (((loop_pixel.red) + (loop_pixel.green) + (loop_pixel.blue)) <= min_intensity) {
					min_intensity = (( loop_pixel.red) + ( loop_pixel.green) + ( loop_pixel.blue));
					min_row = ii;
					min_col = jj;
				}
				if ((( loop_pixel.red) + ( loop_pixel.green) + ( loop_pixel.blue)) > max_intensity) {
					max_intensity = ((( loop_pixel.red) + ( loop_pixel.green) + ( loop_pixel.blue)));
					max_row = ii;
					max_col = jj;
				}
			}
		}
        // inlining the function twice.
		// filter out min and max
		//sum_pixels_by_weight(&sum, src[calcIndex(min_row, min_col, dim)], -1);
        pixel p  = src[min_row*dim+min_col];
        sum.red += -( p.red);
        sum.green += -(p.green);
        sum.blue += -(p.blue);
		//sum_pixels_by_weight(&sum, src[calcIndex(max_row, max_col, dim)], -1);
        sum.red += -(p.red);
        sum.green += -(p.green);
        sum.blue += -( p.blue);
	}

	// assign kernel's result to pixel at [i,j]
	//assign_sum_to_pixel(&current_pixel, sum, kernelScale);
    // divide by kernel's weight
    sum.red = sum.red / kernelScale;
    sum.green = sum.green / kernelScale;
    sum.blue = sum.blue / kernelScale;

    // truncate each pixel's color values to match the range [0,255]
    current_pixel.red = (unsigned int) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned int) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned int) (min(max(sum.blue, 0), 255));
	return current_pixel;
}

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than 3/2 and/or
* column index smaller than 3/2
*/
void smooth(int dim, pixel *src, pixel *dst, int 3, int kernel[3][3], int kernelScale, bool filter) {

	int i, j;
	for (i = 3 / 2 ; i < dim - 3 / 2; i++) {
		for (j =  3 / 2 ; j < dim - 3 / 2 ; j++) {
			//dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, 3, kernel, kernelScale, filter);
            dst[i*dim+j] = applyKernel(dim, i, j, src, 3, kernel, kernelScale, filter);
		}
	}
}

void charsToPixels(Image *charsImg, pixel* pixels) {

	unsigned row, col;

	for (row = 0 ; row < m ; row++) {
        int rowMult = row*n;
		for (col = 0 ; col < n ; col+=4) {
            //1
            int rowColSum = rowMult + col;
            int mult3 = rowColSum+rowColSum+rowColSum;
            pixel pixel1 = pixels[rowColSum];
			pixels[rowColSum].red = image->data[mult3];
			pixels[rowColSum].green = image->data[mult3 + 1];
			pixels[rowColSum].blue = image->data[mult3 + 2];
            //2
            rowColSum += 1;
            mult3 += 3;
            pixels[rowColSum].red = image->data[mult3];
            pixels[rowColSum].green = image->data[mult3 + 1];
            pixels[rowColSum].blue = image->data[mult3 + 2];
            //3
            rowColSum += 1;
            mult3 += 3;
            pixels[rowColSum].red = image->data[mult3];
            pixels[rowColSum].green = image->data[mult3 + 1];
            pixels[rowColSum].blue = image->data[mult3 + 2];
            //4
            rowColSum += 1;
            mult3 += 3;
            pixels[rowColSum].red = image->data[mult3];
            pixels[rowColSum].green = image->data[mult3 + 1];
            pixels[rowColSum].blue = image->data[mult3 + 2];

		}
	}
}

void pixelsToChars(pixel* pixels, Image *charsImg) {

	int row, col;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {

			image->data[3*row*n + 3*col] = pixels[row*n + col].red;
			image->data[3*row*n + 3*col + 1] = pixels[row*n + col].green;
			image->data[3*row*n + 3*col + 2] = pixels[row*n + col].blue;
		}
	}
}

void copyPixels(pixel* src, pixel* dst) {

	int row, col;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {

			dst[row*n + col].red = src[row*n + col].red;
			dst[row*n + col].green = src[row*n + col].green;
			dst[row*n + col].blue = src[row*n + col].blue;
		}
	}
}

void doConvolution(Image *image, int 3, int kernel[3][3], int kernelScale, bool filter) {

	pixel* pixelsImg = malloc(m*n*sizeof(pixel));
	pixel* backupOrg = malloc(m*n*sizeof(pixel));

	charsToPixels(image, pixelsImg);
	copyPixels(pixelsImg, backupOrg);

	smooth(m, backupOrg, pixelsImg, 3, kernel, kernelScale, filter);

	pixelsToChars(pixelsImg, image);

	free(pixelsImg);
	free(backupOrg);
}

void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {

	/*
	* [1, 1, 1]
	* [1, 1, 1]
	* [1, 1, 1]
	*/
	int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	/*
	* [-1, -1, -1]
	* [-1, 9, -1]
	* [-1, -1, -1]
	*/
	int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

	if (flag == '1') {	
		// blur image
		doConvolution(image, 3, blurKernel, 9, false);

		// write result image to file
		writeBMP(image, srcImgpName, blurRsltImgName);	

		// sharpen the resulting image
		doConvolution(image, 3, sharpKernel, 1, false);
		
		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);	
	} else {
		// apply extermum filtered kernel to blur image
		doConvolution(image, 3, blurKernel, 7, true);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		doConvolution(image, 3, sharpKernel, 1, false);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}
}

