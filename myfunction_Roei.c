#include <stdbool.h>

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

int min(int a, int b) { return (a < b ? a : b); }
int max(int a, int b) { return (a > b ? a : b); }
/*
 * assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
 */
//static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum, int kernelScale) {
//    int red = sum.red / kernelScale;
//    int green = sum.green / kernelScale;
//    int blue = sum.blue / kernelScale;
//    // divide by kernel's weight
////	sum.red = sum.red / kernelScale;
////	sum.green = sum.green / kernelScale;
////	sum.blue = sum.blue / kernelScale;
//    sum.red = red;
//    sum.blue = blue;
//    sum.green = green;
//
//    if(red <= 0) {
//        current_pixel->red = (unsigned char)0;
//    }
//    else if (red > 0 && red < 255) {
//        current_pixel->red = (unsigned char)(red);
//    } else if (red >= 255) {
//        current_pixel->red = (unsigned char)255;
//    }
//    if(green <= 0) {
//        current_pixel->green = (unsigned char)0;
//    }else if (green > 0 && green < 255) {
//        current_pixel->green = (unsigned char)(green);
//    } else if (green >= 255) {
//        current_pixel->green = (unsigned char)255;
//    }
//    if(blue <= 0) {
//        current_pixel->blue = (unsigned char)0;
//    } else if (blue > 0 && blue < 255) {
//        current_pixel->blue = (unsigned char)(blue);
//    } else if (blue >= 255) {
//        current_pixel->blue = (unsigned char)255;
//    }
//
//    // truncate each pixel's color values to match the range [0,255]
////	current_pixel->red = (unsigned char) (min(max(sum.red, 0), 255));
////	current_pixel->green = (unsigned char) (min(max(sum.green, 0), 255));
////	current_pixel->blue = (unsigned char) (min(max(sum.blue, 0), 255));
//    return;
//}

static pixel applyKernelnoFilterBlur(int dim, int i, int j, pixel *src) {
    pixel_sum sum;
    pixel current_pixel;
    //initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    int startI = 0;
    int startJ = 0;
    if (i-1 > 0) {
        startI = i-1;
    }
    if (j-1 > 0) {
        startJ = j-1;
    }
    int red = sum.red;
    int green = sum.green;
    int blue = sum.blue;
    int ni = startI * dim;
    int startJ2 = startJ;
    pixel p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    startJ2 = startJ;
    ni += dim;
    p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    startJ2 = startJ;
    ni += dim;
    p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    p = src[ni + startJ2];
    red += ((int) p.red);
    green += ((int) p.green);
    blue += ((int) p.blue);
    sum.red = red / 9;
    sum.blue = blue / 9;
    sum.green = green / 9;
    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
    //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
    return current_pixel;
}

static pixel applyKernelnoFilterSharp(int dim, int i, int j, pixel *src) {
    pixel_sum sum;
    pixel current_pixel;
    //initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    int red = sum.red;
    int green = sum.green;
    int blue = sum.blue;
    int startI = 0;
    int startJ = 0;
    if (i-1 > 0) {
        startI = i-1;
    }
    if (j-1 > 0) {
        startJ = j-1;
    }
    int ni = startI * dim;
    int startJ2 = startJ;
    pixel p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    p = src[ni + startJ2];
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    startJ2 = startJ;
    ni += dim;
    p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    // = kernel[1][1];
    red += ((int) p.red) * 9;
    green += ((int) p.green) * 9;
    blue += ((int) p.blue) * 9;
    p = src[ni + startJ2];
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    startJ2 = startJ;
    ni += dim;
    p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    p = src[ni + startJ2];
    startJ2 ++;
    red -= ((int) p.red);
    green -= ((int) p.green);
    blue -= ((int) p.blue);
    sum.red = red;
    sum.blue = blue;
    sum.green = green;
    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
    //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
    return current_pixel;
}




static pixel applyKernelWithFilterBlur(int dim, int i, int j, pixel *src) {
    pixel_sum sum;
    pixel current_pixel;
    int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
    int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
    int min_row, min_col, max_row, max_col;
    //initialize_pixel_sum(&sum);
    sum.red = sum.green = sum.blue = 0;
    int startI = 0;
    int startJ = 0;
    if (i-1 > 0) {
        startI = i-1;
    }
    if (j-1 > 0) {
        startJ = j-1;
    }
    int startI2 = startI;
    int ni = startI * dim;
        int startJ2 = startJ;
        pixel p = src[ni + startJ2];
        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        int sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];
        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];
        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }

        startJ2 = startJ;
        startI2 = startI+1;
        ni += dim;
        p = src[ni + startJ2];

        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];

        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];
        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 = startJ;
        startI2 = startI + 2;
        ni += dim;
        p = src[ni + startJ2];

        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];

        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        startJ2 ++;
        p = src[ni + startJ2];
        sum.red += ((int) p.red);
        sum.green += ((int) p.green);
        sum.blue += ((int) p.blue);
        sumP = (int) p.red + (int) p.green + (int) p.blue;
        if (sumP <= min_intensity) {
            min_intensity = sumP;
            min_row = startI2;
            min_col = startJ2;
        }
        if ((sumP) > max_intensity) {
            max_intensity = sumP;
            max_row = startI2;
            max_col = startJ2;
        }
        p = src[min_row*dim + min_col];
    pixel p2 = src[max_row*dim + max_col];
    sum.red -= ((int) p.red);
    sum.green -= ((int) p.green);
    sum.blue -= ((int) p.blue);
    sum.red -= ((int) p2.red);
    sum.green -= ((int) p2.green);
    sum.blue -= ((int) p2.blue);
    sum.red = sum.red / 7;
    sum.blue = sum.blue /7;
    sum.green = sum.green / 7;
    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
    //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
    return current_pixel;
}

//static pixel applyKernelWithFilterSharp(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {
//    int ii, jj;
//    int currRow, currCol;
//    pixel_sum sum;
//    pixel current_pixel;
//    int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
//    int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
//    int min_row, min_col, max_row, max_col;
//    pixel loop_pixel;
//    //initialize_pixel_sum(&sum);
//    sum.red = sum.green = sum.blue = 0;
//    int startI = 0;
//    int startJ = 0;
//    if (i-1 > 0) {
//        startI = i-1;
//    }
//    if (j-1 > 0) {
//        startJ = j-1;
//    }
//    int startI2 = startI;
//    int ni = startI * dim;
//        int startJ2 = startJ;
//        pixel p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        int sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//
//        startJ2 = startJ;
//        startI2 = startI+1;
//        ni += dim;
//        p = src[ni + startJ2];
//
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red += (((int) p.red) << 3) + ((int) p.red);
//        sum.green += (((int) p.green) << 3) +((int) p.green);
//        sum.blue += (((int) p.blue) << 3) +((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 = startJ;
//        startI2 = startI + 2;
//        ni += dim;
//        p = src[ni + startJ2];
//
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//        startJ2 ++;
//        p = src[ni + startJ2];
//        sum.red -= ((int) p.red);
//        sum.green -= ((int) p.green);
//        sum.blue -= ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = startI2;
//            min_col = startJ2;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = startI2;
//            max_col = startJ2;
//        }
//    p = src[min_row*dim + min_col];
//    pixel p2 = src[max_row*dim + max_col];
//    sum.red -= ((int) p.red);
//    sum.green -= ((int) p.green);
//    sum.blue -= ((int) p.blue);
//    sum.red -= ((int) p2.red);
//    sum.green -= ((int) p2.green);
//    sum.blue -= ((int) p2.blue);
//    sum.red = sum.red / kernelScale;
//    sum.blue = sum.blue / kernelScale;
//    sum.green = sum.green / kernelScale;
//    current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
//    current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
//    current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
//    //assign_sum_to_pixel(&current_pixel, sum, kernelScale);
//    return current_pixel;
//}





/*
 *  Applies kernel for pixel at (i,j)
 */
//static pixel applyKernel(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {
//
//    int ii, jj;
//    int currRow, currCol;
//    pixel_sum sum;
//    pixel current_pixel;
//    int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
//    int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
//    int min_row, min_col, max_row, max_col;
//    pixel loop_pixel;
//
//    //initialize_pixel_sum(&sum);
//    sum.red = sum.green = sum.blue = 0;
//    int startI = 0;
//    int startJ = 0;
//    int endI = i + 1;
//    int endJ = j + 1;
//    if (i-1 > 0) {
//        startI = i-1;
//    }
//    if (j-1 > 0) {
//        startJ = j-1;
//    }
//    if (endI > dim - 1) {
//        endI = dim - 1;
//    }
//    if (endJ > dim -1) {
//        endJ = dim -1;
//    }
//    int ni = startI * dim;
//
//    if(kernel[0][0] == 1) {
//        int startJ2 = startJ;
//        pixel p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        int sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        startJ2 = startJ;
//        ni += dim;
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        startJ2 = startJ;
//        ni += dim;
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        sum.red += ((int) p.red);
//        sum.green += ((int) p.green);
//        sum.blue += ((int) p.blue);
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//    }
//    else {
//        int startJ2 = startJ;
//        pixel p = src[ni + startJ2];
//        startJ2 ++;
//        int weight = kernel[0][0];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        int sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[0][1];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[0][2];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        startJ2 = startJ;
//        ni += dim;
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[1][0];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[1][1];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[1][2];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//
//        startJ2 = startJ;
//        ni += dim;
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[2][0];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[2][1];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//
//        p = src[ni + startJ2];
//        startJ2 ++;
//        weight = kernel[2][2];
//        sum.red += ((int) p.red) * weight;
//        sum.green += ((int) p.green) * weight;
//        sum.blue += ((int) p.blue) * weight;
//        sumP = (int) p.red + (int) p.green + (int) p.blue;
//        if (sumP <= min_intensity) {
//            min_intensity = sumP;
//            min_row = ii;
//            min_col = jj;
//        }
//        if ((sumP) > max_intensity) {
//            max_intensity = sumP;
//            max_row = ii;
//            max_col = jj;
//        }
//    }
//    pixel p = src[min_row*dim + min_col];
//    pixel p2 = src[max_row*dim + max_col];
//    sum.red -= ((int) p.red);
//    sum.green -= ((int) p.green);
//    sum.blue -= ((int) p.blue);
//    sum.red -= ((int) p2.red);
//    sum.green -= ((int) p2.green);
//    sum.blue -= ((int) p2.blue);
//
//
////    if (filter) {
////        int n2 = startI * dim;
////        // find min and max coordinates
////        for (ii = startI; ii <= endI; ii++) {
////            for (jj = startJ; jj <= endJ; jj++) {
////                // check if smaller than min or higher than max and update
////                loop_pixel = src[n2 + jj];
////                int sum = (int) loop_pixel.red + (int) loop_pixel.green + (int) loop_pixel.blue;
////                if (sum <= min_intensity) {
////                    min_intensity = sum;
////                    min_row = ii;
////                    min_col = jj;
////                }
////                if ((sum) > max_intensity) {
////                    max_intensity = sum;
////                    max_row = ii;
////                    max_col = jj;
////                }
////            }
////            n2 += dim;
////        }
////        pixel p = src[min_row*dim + min_col];
////        pixel p2 = src[max_row*dim + max_col];
////        sum.red -= ((int) p.red);
////        sum.green -= ((int) p.green);
////        sum.blue -= ((int) p.blue);
////        sum.red -= ((int) p2.red);
////        sum.green -= ((int) p2.green);
////        sum.blue -= ((int) p2.blue);
//        // filter out min and max
//    //}
//
//    // assign kernel's result to pixel at [i,j]
//    assign_sum_to_pixel(&current_pixel, sum, kernelScale);
//    return current_pixel;
//}

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
//void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {
//
//    int i, j;
//    int start = kernelSize / 2;
//    int end = dim - kernelSize / 2;
//    int ni = start * dim;
//    if (filter) {
//        if (kernel[0][0] == 1) {
//            for (i = start ; i < end; i++) {
//                for (j =  start ; j < end ; j++) {
//                    dst[ni + j] = applyKernelWithFilterBlur(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
//                }
//                ni += dim;
//            }
//        } else {
//            for (i = start ; i < end; i++) {
//                for (j =  start ; j < end ; j++) {
//                    dst[ni + j] = applyKernelWithFilterSharp(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
//                }
//                ni += dim;
//            }
//        }
//
//    } else {
//        if (kernel[0][0] == 1) {
//            for (i = start ; i < end; i++) {
//                for (j =  start ; j < end ; j++) {
//                    dst[ni + j] = applyKernelnoFilterBlur(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
//                }
//                ni += dim;
//            }
//        } else {
//            for (i = start ; i < end; i++) {
//                for (j =  start ; j < end ; j++) {
//                    dst[ni + j] = applyKernelnoFilterSharp(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
//                }
//                ni += dim;
//            }
//        }
//    }
//
//}

void smoothBlur(int dim, pixel *src, pixel *dst) {
    int i, j;
    //int start = kernelSize / 2;
    int end = dim - 4;
    int ni = 4 * dim;
    for (i = 4; i < end; i++) {
        for (j = 4; j < end; j++) {
            dst[ni + j] = applyKernelnoFilterBlur(dim, i, j, src);
        }
        ni += dim;
    }
}
void smoothSharp(int dim, pixel *src, pixel *dst) {
    int i, j;
    //int start = kernelSize / 2;
    //int end = dim;
    int ni = 0;
    for (i = 0 ; i < dim; i++) {
        for (j =  0 ; j < dim ; j++) {
            dst[ni + j] = applyKernelnoFilterSharp(dim, i, j, src);
        }
        ni += dim;
    }
}

void smoothFilterBlur(int dim, pixel *src, pixel *dst) {
    int i, j;
    //int start = kernelSize / 2;
    int end = dim - 3;
    int ni = 3 * dim;
    for (i = 3 ; i < end; i++) {
        for (j =  3 ; j < end ; j++) {
            dst[ni + j] = applyKernelWithFilterBlur(dim, i, j, src);
        }
        ni += dim;
    }
}

//void smoothFilterSharp(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {
//    int i, j;
//    int start = kernelSize / 2;
//    int end = dim - kernelSize / 2;
//    int ni = start * dim;
//    for (i = start ; i < end; i++) {
//        for (j =  start ; j < end ; j++) {
//            dst[ni + j] = applyKernelWithFilterSharp(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
//        }
//        ni += dim;
//    }
//}




void charsToPixels(Image *charsImg, pixel* pixels) {

    int row, col;
    int rowN = 0;
    for (row = 0 ; row < m ; row++) {
        //int rowN = row * n;
        int rowN3 = 3 * rowN;
        for (col = 0 ; col < n ; col++) {
            int rowCol = rowN3 + 3*col;
            int r = rowN + col;
            pixels[r].red = image->data[rowCol];
            pixels[r].green = image->data[rowCol+ 1];
            pixels[r].blue = image->data[rowCol + 2];
        }
        rowN += n;
    }
}

void pixelsToChars(pixel* pixels, Image *charsImg) {

    int row, col;
    int rowN = 0;
    for (row = 0 ; row < m ; row++) {
        //int rowN = row * n;
        int rowN3 = 3 * rowN;
        for (col = 0 ; col < n ; col++) {
            int rowCol = rowN3 + 3*col;
            int r = rowN + col;

            image->data[rowCol] = pixels[r].red;
            image->data[rowCol + 1] = pixels[r].green;
            image->data[rowCol + 2] = pixels[r].blue;
        }
        rowN += n;
    }
}

void copyPixels(pixel* src, pixel* dst) {

    int limit = n -10;

    int row, col;
    int rowN = 0;
    for (row = 0 ; row < m ; row++) {
        for (col = 0 ; col < limit ; col+=11) {
            int r = rowN + col;
            dst[r].red = src[r].red;
            dst[r].green = src[r].green;
            dst[r].blue = src[r].blue;
            int r1 = r + 1;
            dst[r1].red = src[r1].red;
            dst[r1].green = src[r1].green;
            dst[r1].blue = src[r1].blue;
            int r2 = r + 2;
            dst[r2].red = src[r2].red;
            dst[r2].green = src[r2].green;
            dst[r2].blue = src[r2].blue;
            int r3 = r + 3;
            dst[r3].red = src[r3].red;
            dst[r3].green = src[r3].green;
            dst[r3].blue = src[r3].blue;
            int r4 = r + 4;
            dst[r4].red = src[r4].red;
            dst[r4].green = src[r4].green;
            dst[r4].blue = src[r4].blue;
            int r5 = r + 5;
            dst[r5].red = src[r5].red;
            dst[r5].green = src[r5].green;
            dst[r5].blue = src[r5].blue;
            int r6 = r + 6;
            dst[r6].red = src[r6].red;
            dst[r6].green = src[r6].green;
            dst[r6].blue = src[r6].blue;
            int r7 = r + 7;
            dst[r7].red = src[r7].red;
            dst[r7].green = src[r7].green;
            dst[r7].blue = src[r7].blue;
            int r8 = r + 8;
            dst[r8].red = src[r8].red;
            dst[r8].green = src[r8].green;
            dst[r8].blue = src[r8].blue;
            int r9 = r + 9;
            dst[r9].red = src[r9].red;
            dst[r9].green = src[r9].green;
            dst[r9].blue = src[r9].blue;
            int r10 = r + 10;
            dst[r10].red = src[r10].red;
            dst[r10].green = src[r10].green;
            dst[r10].blue = src[r10].blue;
        }
        for (; col < n; col++) {
            int r = rowN + col;
            dst[r].red = src[r].red;
            dst[r].green = src[r].green;
            dst[r].blue = src[r].blue;
        }
        rowN += n;
    }
}

void doConvolutionBlur(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

    int mn = m * n * sizeof(pixel);
    pixel* pixelsImg = malloc(mn);
    pixel* backupOrg = malloc(mn);

    charsToPixels(image, pixelsImg);
    copyPixels(pixelsImg, backupOrg);

    smoothBlur(m, backupOrg, pixelsImg);

    pixelsToChars(pixelsImg, image);

    free(pixelsImg);
    free(backupOrg);
}

void doConvolutionSharp(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

    int mn = m * n * sizeof(pixel);
    pixel* pixelsImg = malloc(mn);
    pixel* backupOrg = malloc(mn);

    charsToPixels(image, pixelsImg);
    copyPixels(pixelsImg, backupOrg);

    smoothSharp(m, backupOrg, pixelsImg);

    pixelsToChars(pixelsImg, image);

    free(pixelsImg);
    free(backupOrg);
}
void doConvolutionFilterBlur(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

    int mn = m * n * sizeof(pixel);
    pixel* pixelsImg = malloc(mn);
    pixel* backupOrg = malloc(mn);

    charsToPixels(image, pixelsImg);
    copyPixels(pixelsImg, backupOrg);

    smoothFilterBlur(m, backupOrg, pixelsImg);

    pixelsToChars(pixelsImg, image);

    free(pixelsImg);
    free(backupOrg);
}

//void doConvolutionFilterSharp(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {
//
//    int mn = m * n * sizeof(pixel);
//    pixel* pixelsImg = malloc(mn);
//    pixel* backupOrg = malloc(mn);
//
//    charsToPixels(image, pixelsImg);
//    copyPixels(pixelsImg, backupOrg);
//
//    smoothFilterSharp(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);
//
//    pixelsToChars(pixelsImg, image);
//
//    free(pixelsImg);
//    free(backupOrg);
//}


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
        doConvolutionBlur(image, 3, blurKernel, 9, false);

        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);

        // sharpen the resulting image
        doConvolutionSharp(image, 3, sharpKernel, 1, false);

        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);
    } else {
        // apply extermum filtered kernel to blur image
        doConvolutionFilterBlur(image, 3, blurKernel, 7, true);

        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);

        // sharpen the resulting image
        doConvolutionSharp(image, 3, sharpKernel, 1, false);

        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}


