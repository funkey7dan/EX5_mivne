// 315901173 Daniel Bronfman
#pragma GCC target("bmi,bmi2,popcnt,lzcnt")
#pragma GCC optimize ("Ofast,unroll-loops")
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include "writeBMP.h"
#define MULT_M(a) a*m
#define CALC_INDEX2 (ixm) + j
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define DIVIDE7(a) (a /= 7)
#define DIVIDE9(a) (a/=9)
#define MULT9(a) (a+a+a+a+a+a+a+a+a)
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;
typedef struct {
    int_fast16_t red;
    int_fast16_t green;
    int_fast16_t blue;
    // int num;
} pixel_sum;

void smoothSharpNoFilter(pixel *src)
{

    register int i, j;
    register char *pixelImage = image->data;
    register uint_fast16_t col1_sum_r, col1_sum_g, col1_sum_b, col2_sum_r, col2_sum_g, col2_sum_b, col3_sum_r, col3_sum_g,
            col3_sum_b;
    // inner matrix traversal
    for (i = m - 1; i > 0; --i)
    {
        int ixm = i * m;
        unsigned max_i = i - 1;
        register int calc1 = MULT_M(max_i);
        for (j = 1; j < m - 1; ++j)
        {
            // apply kernel
            register int min_intensity = 766, max_intensity = -1;
            int currRow, currCol, min_row, min_col, max_row, max_col, kRow, kCol;
            pixel_sum sum = {0, 0, 0};
            pixel current_pixel;
            // go over
            register pixel *pixel1 = (src + calc1), *pixel2 = pixel1 + 1, *pixel3 = pixel1 + 2, *pixel4 =
                    pixel1 + m, *pixel5 =
                    pixel4 + 1,
                    *pixel6 = pixel4 + 2,
                    *pixel7 = pixel4 + m, *pixel8 = pixel7 + 1, *pixel9 = pixel7 + 2;
            calc1++;
            if(i == m - 1 && j == 1)
            {
                col1_sum_r = pixel1->red + pixel4->red + pixel7->red;
                col1_sum_g = pixel1->green + pixel4->green + pixel7->green;
                col1_sum_b = pixel1->blue + pixel4->blue + pixel7->blue;
                col2_sum_r = pixel2->red + pixel5->red + pixel8->red;
                col2_sum_g = pixel2->green + pixel5->green + pixel8->green;
                col2_sum_b = pixel2->blue + pixel5->blue + pixel8->blue;
                col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
                col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
                col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;
            }
            if(!(i == m - 1 && j == 1))
            {
                col1_sum_r = col2_sum_r;
                col1_sum_g = col2_sum_g;
                col1_sum_b = col2_sum_b;
                col2_sum_r = col3_sum_r;
                col2_sum_g = col3_sum_g;
                col2_sum_b = col3_sum_b;
                col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
                col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
                col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;

            }
            sum.red =
                    MULT9(pixel5->red) - ((col1_sum_r + col3_sum_r + pixel2->red + pixel8->red));
            sum.green =
                    MULT9(pixel5->green) - ((col1_sum_g + col3_sum_g + pixel2->green + pixel8->green));
            sum.blue =
                    MULT9(pixel5->blue) - ((col1_sum_b + col3_sum_b + pixel2->blue + pixel8->blue));


// truncate each pixel's color values to match the range [0,255]
            /**/
            //for loop end
            // assign kernel's result to pixel at [i,j]

            *(pixelImage + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.red, 0), 255));
            *(pixelImage + 1 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.green, 0), 255));
            *(pixelImage + 2 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.blue, 0), 255));
        }
        // outer loop end
    }
}

//alt2 - BEST
void smoothBlurNoFilter(pixel *src)
{

    int_fast8_t currRow, currCol, min_row, min_col, max_row, max_col, kRow, kCol;
    pixel_sum sum = {0, 0, 0};
    pixel current_pixel;
    register uint_fast16_t i, j;
    char *pixelImage = image->data;
    register pixel *pixel1 = (src), *pixel2 = pixel1 + 1, *pixel3 = pixel1 + 2, *pixel4 = pixel1 + m, *pixel5 =
            pixel4 + 1,
            *pixel6 = pixel4 + 2,
            *pixel7 = pixel4 + m, *pixel8 = pixel7 + 1, *pixel9 = pixel7 + 2;
    register int col1_sum_r, col1_sum_g, col1_sum_b, col2_sum_r, col2_sum_g, col2_sum_b, col3_sum_r, col3_sum_g, col3_sum_b;
    col1_sum_r = pixel1->red + pixel4->red + pixel7->red;
    col1_sum_g = pixel1->green + pixel4->green + pixel7->green;
    col1_sum_b = pixel1->blue + pixel4->blue + pixel7->blue;
    col2_sum_r = pixel2->red + pixel5->red + pixel8->red;
    col2_sum_g = pixel2->green + pixel5->green + pixel8->green;
    col2_sum_b = pixel2->blue + pixel5->blue + pixel8->blue;
    col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
    col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
    col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;
    sum.red = col1_sum_r + col2_sum_r + col3_sum_r;
    sum.green = col1_sum_g + col2_sum_g + col3_sum_g;
    sum.blue = col1_sum_b + col2_sum_b + col3_sum_b;
    DIVIDE9(sum.red);
    DIVIDE9(sum.green);
    DIVIDE9(sum.blue);
// truncate each pixel's color values to match the range [0,255]
    current_pixel.red = (MIN(MAX(sum.red, 0), 255));
    current_pixel.green = (MIN(MAX(sum.green, 0), 255));
    current_pixel.blue = (MIN(MAX(sum.blue, 0), 255));
    //for loop end
    // assign kernel's result to pixel at [i,j]

    *(pixelImage) = (MIN(MAX(sum.red, 0), 255));
    *(pixelImage + 1) = (MIN(MAX(sum.green, 0), 255));
    *(pixelImage + 2) = (MIN(MAX(sum.blue, 0), 255));
    // inner matrix traversal
    for (i = 2; i < m - 1; ++i)
    {
        int ixm = i * m;
        int max_i = i - 1;
        int calc1 = MULT_M(max_i);
        for (j = 1; j < m - 1; ++j)
        {
            // apply kernel
            register int min_intensity = 766, max_intensity = -1;

            // go over
            pixel1 = (src + calc1);
            pixel2 = pixel1 + 1;
            pixel3 = (src + calc1) + 2;
            pixel4 = (src + calc1) + m;
            pixel5 = pixel4 + 1;
            pixel6 = pixel4 + 2;
            pixel7 = (src + calc1) + m + m;
            pixel8 = pixel7 + 1;
            pixel9 = (src + calc1) + m + m + 2;
            col1_sum_r = col2_sum_r;
            col1_sum_g = col2_sum_g;
            col1_sum_b = col2_sum_b;
            col2_sum_r = col3_sum_r;
            col2_sum_g = col3_sum_g;
            col2_sum_b = col3_sum_b;
            col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
            col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
            col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;
            calc1++;
            sum.red = col1_sum_r + col2_sum_r + col3_sum_r;
            sum.green = col1_sum_g + col2_sum_g + col3_sum_g;
            sum.blue = col1_sum_b + col2_sum_b + col3_sum_b;
            DIVIDE9(sum.red);
            DIVIDE9(sum.green);
            DIVIDE9(sum.blue);
// truncate each pixel's color values to match the range [0,255]

            //for loop end
            // assign kernel's result to pixel at [i,j]

            *(pixelImage + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.red, 0), 255));
            *(pixelImage + 1 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.green, 0), 255));
            *(pixelImage + 2 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.blue, 0), 255));
        }
        // outer loop end
    }
}

void smoothBlur(pixel *src)
{

    register uint_fast16_t i, j;
    register char *pixelImage = image->data;
    register uint_fast16_t col1_sum_r, col1_sum_g, col1_sum_b, col2_sum_r, col2_sum_g, col2_sum_b, col3_sum_r, col3_sum_g,
            col3_sum_b;
    pixel current_pixel, p, p2;
    // inner matrix traversal
    for (i = 1; i < m - 1; ++i)
    {
        int ixm = i * m;
        int calc1 = (i - 1) * m;
        for (j = 1; j < m - 1; ++j)
        {
            // apply kernel
            register int min_intensity = 766, max_intensity = -1;
            pixel *pixel1 = (src + calc1), *pixel2 = pixel1 + 1, *pixel3 = pixel1 + 2, *pixel4 = pixel1 + m, *pixel5 =
                    pixel4 + 1, *pixel6 = pixel4 + 2,
                    *pixel7 = pixel4 + m, *pixel8 = pixel7 + 1, *pixel9 = pixel7 + 2;
            int currRow, currCol, min_row, min_col, max_row, max_col, kRow, kCol,
                    pix_sum1, pix_sum2, pix_sum3, pix_sum4, pix_sum5, pix_sum6, pix_sum7, pix_sum8, pix_sum9;
            pixel_sum sum = {0, 0, 0};

            // go over

            if(i == 1 && j == 1)
            {
                pix_sum1 = pixel1->red + pixel1->blue + pixel1->green;
                pix_sum2 = pixel2->red + pixel2->blue + pixel2->green;
                pix_sum4 = pixel4->red + pixel4->blue + pixel4->green;
                pix_sum5 = pixel5->red + pixel5->blue + pixel5->green;
                pix_sum7 = pixel7->red + pixel7->blue + pixel7->green;
                pix_sum8 = pixel8->red + pixel8->blue + pixel8->green;
                col1_sum_r = pixel1->red + pixel4->red + pixel7->red;
                col1_sum_g = pixel1->green + pixel4->green + pixel7->green;
                col1_sum_b = pixel1->blue + pixel4->blue + pixel7->blue;
                col2_sum_r = pixel2->red + pixel5->red + pixel8->red;
                col2_sum_g = pixel2->green + pixel5->green + pixel8->green;
                col2_sum_b = pixel2->blue + pixel5->blue + pixel8->blue;
                col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
                col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
                col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;
            }
            if(!(i == 1 && j == 1))
            {
                pix_sum1 = pix_sum2;
                pix_sum2 = pix_sum3;
                pix_sum4 = pix_sum5;
                pix_sum5 = pix_sum6;
                pix_sum7 = pix_sum8;
                pix_sum8 = pix_sum9;
                col1_sum_r = col2_sum_r;
                col1_sum_g = col2_sum_g;
                col1_sum_b = col2_sum_b;
                col2_sum_r = col3_sum_r;
                col2_sum_g = col3_sum_g;
                col2_sum_b = col3_sum_b;
            }
            pix_sum3 = pixel3->red + pixel3->blue + pixel3->green;
            pix_sum6 = pixel6->red + pixel6->blue + pixel6->green;
            pix_sum9 = pixel9->red + pixel9->blue + pixel9->green;
            col3_sum_r = pixel3->red + pixel6->red + pixel9->red;
            col3_sum_g = pixel3->green + pixel6->green + pixel9->green;
            col3_sum_b = pixel3->blue + pixel6->blue + pixel9->blue;
            if(pix_sum1 <= min_intensity)
            {
                min_intensity = pix_sum1;
                min_row = i - 1;
                min_col = j - 1;
            }
            if(pix_sum1 > max_intensity)
            {
                max_intensity = pix_sum1;
                max_row = i - 1;
                max_col = j - 1;
            }
            if(pix_sum2 <= min_intensity)
            {
                min_intensity = pix_sum2;
                min_row = i - 1;
                min_col = j;
            }
            if(pix_sum2 > max_intensity)
            {
                max_intensity = pix_sum2;
                max_row = i - 1;
                max_col = j;
            }
            if(pix_sum3 <= min_intensity)
            {
                min_intensity = pix_sum3;
                min_row = i - 1;
                min_col = j + 1;
            }
            if(pix_sum3 > max_intensity)
            {
                max_intensity = pix_sum3;
                max_row = i - 1;
                max_col = j + 1;
            }
            if(pix_sum4 <= min_intensity)
            {
                min_intensity = pix_sum4;
                min_row = i;
                min_col = j - 1;
            }
            if(pix_sum4 > max_intensity)
            {
                max_intensity = pix_sum4;
                max_row = i;
                max_col = j - 1;
            }
            if(pix_sum5 <= min_intensity)
            {
                min_intensity = pix_sum5;
                min_row = i;
                min_col = j;
            }
            if(pix_sum5 > max_intensity)
            {
                max_intensity = pix_sum5;
                max_row = i;
                max_col = j;
            }
            if(pix_sum6 <= min_intensity)
            {
                min_intensity = pix_sum6;
                min_row = i;
                min_col = j + 1;
            }
            if(pix_sum6 > max_intensity)
            {
                max_intensity = pix_sum6;
                max_row = i;
                max_col = j + 1;
            }
            if(pix_sum7 <= min_intensity)
            {
                min_intensity = pix_sum7;
                min_row = i + 1;
                min_col = j - 1;
            }
            if(pix_sum7 > max_intensity)
            {
                max_intensity = pix_sum7;
                max_row = i + 1;
                max_col = j - 1;
            }
            if(pix_sum8 <= min_intensity)
            {
                min_intensity = pix_sum8;
                min_row = i + 1;
                min_col = j;
            }
            if(pix_sum8 > max_intensity)
            {
                max_intensity = pix_sum8;
                max_row = i + 1;
                max_col = j;
            }
            if(pix_sum9 <= min_intensity)
            {
                min_intensity = pix_sum9;
                min_row = i + 1;
                min_col = j + 1;
            }
            if(pix_sum9 > max_intensity)
            {
                max_intensity = pix_sum9;
                max_row = i + 1;
                max_col = j + 1;
            }
            calc1++;
            sum.red = col1_sum_r + col2_sum_r + col3_sum_r;
            sum.green = col1_sum_g + col2_sum_g + col3_sum_g;
            sum.blue = col1_sum_b + col2_sum_b + col3_sum_b;
            p = *(src + m * (min_row) + min_col), p2 = *(src + m * (max_row) + max_col);
            sum.red -= (p.red) + (p2.red);
            sum.green -= (p.green) + (p2.green);
            sum.blue -= (p.blue) + (p2.blue);
            DIVIDE7(sum.red);
            DIVIDE7(sum.green);
            DIVIDE7(sum.blue);
// truncate each pixel's color values to match the range [0,255]

            //for loop end
            // assign kernel's result to pixel at [i,j]

            *(pixelImage + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.red, 0), 255));
            *(pixelImage + 1 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.green, 0), 255));
            *(pixelImage + 2 + (CALC_INDEX2) + (CALC_INDEX2) + (CALC_INDEX2)) = (MIN(MAX(sum.blue, 0), 255));
        }
        // outer loop end
    }
}

void myfunction(Image *image, const char *srcImgpName, const char *blurRsltImgName, const char *sharpRsltImgName,
                const char *filteredBlurRsltImgName, const char *filteredSharpRsltImgName, char flag)
{

    /*
    * [-1, -1, -1]
    * [-1, 9, -1]
    * [-1, -1, -1]
    */
    register int size_of_matrix = MULT_M(MULT_M(sizeof(pixel)));
    if(flag == '1')
    {
        // blur image
        register pixel *backupOrg = malloc(size_of_matrix);
        memcpy(backupOrg, image->data, size_of_matrix);
        smoothBlurNoFilter(backupOrg);


        // write result image to file
        /*FILE *bmpfile;
        // open the file to be written
        bmpfile = fopen(blurRsltImgName, "wb");
        if(bmpfile == NULL)
        {
            printf("Error opening output file\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // open BMP file of original image
        FILE *srcFile;
        if((srcFile = fopen(srcImgpName, "rb")) == NULL)
        {
            printf("File Not Found : %s\n", srcImgpName);
            exit(1);
        }

        // read header of original image
        char originalHeader[54];
        fread(&originalHeader, 1, 54, srcFile);

        // write the BMP file header
        fwrite(&originalHeader, 1, 54, bmpfile);

        // close BMP file of original image
        fclose(srcFile);

        // calculate number of bytes per each line
        int bytesPerLine;
        bytesPerLine = image->sizeX + image->sizeX + image->sizeX;  // for 24 bit images
        // round up to a dword boundary
        if(bytesPerLine & 0x0003)
        {
            bytesPerLine |= 0x0003;
            ++bytesPerLine;
        }

        // allocate buffer to hold one line of the image
        char *linebuf;
        linebuf = (char *) calloc(1, bytesPerLine);
        if(linebuf == NULL)
        {
            printf("Error allocating memory\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // write the image line by line - start with the lowest line
        int line;
        int i;
        char *iData = image->data;
        for (line = 0; line <= image->sizeY; ++line)
        {

            *//*
            * fill line linebuf with the image data for that line
            * remember that the order is BGR
            *//*
            for (i = bytesPerLine; i >= 0; i -= 3)
            {
                int lineMult = line * bytesPerLine + i;
                *(linebuf + i) = *(iData + lineMult + 2);
                *(linebuf + i + 1) = *(iData + lineMult + 1);
                *(linebuf + i + 2) = *(iData + lineMult);
            }

            *//*
            * remember that the order is BGR and if width is not a multiple
            * of 4 then the last few bytes may be unused
            *//*
            fwrite(linebuf, 1, bytesPerLine, bmpfile);
        }

        // close the image file
        fclose(bmpfile);*/
        writeBMP(image, srcImgpName, blurRsltImgName);

        // sharpen the resulting image
        memcpy(backupOrg, image->data, size_of_matrix);
        smoothSharpNoFilter(backupOrg);
        free(backupOrg);

        // write result image to file
        /*bmpfile = fopen(sharpRsltImgName, "wb");
        if(bmpfile == NULL)
        {
            printf("Error opening output file\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // open BMP file of original image
        if((srcFile = fopen(srcImgpName, "rb")) == NULL)
        {
            printf("File Not Found : %s\n", srcImgpName);
            exit(1);
        }

        // read header of original image
        fread(&originalHeader, 1, 54, srcFile);

        // write the BMP file header
        fwrite(&originalHeader, 1, 54, bmpfile);

        // close BMP file of original image
        fclose(srcFile);

        // calculate number of bytes per each line
        unsigned long temp = image->sizeX;
        bytesPerLine = temp + temp + temp;  // for 24 bit images
        // round up to a dword boundary
        if(bytesPerLine & 0x0003)
        {
            bytesPerLine |= 0x0003;
            ++bytesPerLine;
        }

        // allocate buffer to hold one line of the image
        linebuf = (char *) calloc(1, bytesPerLine);
        if(linebuf == NULL)
        {
            printf("Error allocating memory\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // write the image line by line - start with the lowest line
        iData = image->data;
        for (line = 0; line <= image->sizeY; ++line)
        {

            *//*
            * fill line linebuf with the image data for that line
            * remember that the order is BGR
            *//*
            for (i = bytesPerLine; i >= 0; i -= 3)
            {
                int lineMult = line * bytesPerLine + i;
                *(linebuf + i) = *(iData + lineMult + 2);
                *(linebuf + i + 1) = *(iData + lineMult + 1);
                *(linebuf + i + 2) = *(iData + lineMult);
            }

            *//*
            * remember that the order is BGR and if width is not a multiple
            * of 4 then the last few bytes may be unused
            *//*
            fwrite(linebuf, 1, bytesPerLine, bmpfile);
        }

        // close the image file
        fclose(bmpfile);*/
        writeBMP(image, srcImgpName, sharpRsltImgName);
    }
    else
    {
        // apply extermum filtered kernel to blur image
        pixel *backupOrg = malloc(size_of_matrix);
        // copy pixels embedded in chars to pixels
        memcpy(backupOrg, image->data, size_of_matrix);
        smoothBlur(backupOrg);

        // write result image to file
        /*FILE *bmpfile;
        // open the file to be written
        bmpfile = fopen(filteredBlurRsltImgName, "wb");
        if(bmpfile == NULL)
        {
            printf("Error opening output file\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // open BMP file of original image
        FILE *srcFile;
        if((srcFile = fopen(srcImgpName, "rb")) == NULL)
        {
            printf("File Not Found : %s\n", srcImgpName);
            exit(1);
        }

        // read header of original image
        char originalHeader[54];
        fread(&originalHeader, 1, 54, srcFile);

        // write the BMP file header
        fwrite(&originalHeader, 1, 54, bmpfile);

        // close BMP file of original image
        fclose(srcFile);

        // calculate number of bytes per each line
        int bytesPerLine;
        bytesPerLine = image->sizeX + image->sizeX + image->sizeX;  // for 24 bit images)
        // round up to a dword boundary
        if(bytesPerLine & 0x0003)
        {
            bytesPerLine |= 0x0003;
            ++bytesPerLine;
        }

        // allocate buffer to hold one line of the image
        char *linebuf;
        linebuf = (char *) calloc(1, bytesPerLine);
        if(linebuf == NULL)
        {
            puts("Error allocating memory\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // write the image line by line - start with the lowest line
        int line;
        int i;
        char *iData = image->data;
        for (line = 0; line <= image->sizeY; ++line)
        {

            *//*
            * fill line linebuf with the image data for that line
            * remember that the order is BGR
            *//*
            int lineXbytes = line * bytesPerLine;
            for (i = bytesPerLine; i >= 0; i -= 3)
            {
                int lineMult = line * bytesPerLine + i;
                *(linebuf + i) = *(iData + lineMult + 2);
                *(linebuf + i + 1) = *(iData + lineMult + 1);
                *(linebuf + i + 2) = *(iData + lineMult);
            }

            *//*
            * remember that the order is BGR and if width is not a multiple
            * of 4 then the last few bytes may be unused
            *//*
            fwrite(linebuf, 1, bytesPerLine, bmpfile);
        }

        // close the image file
        fclose(bmpfile);*/
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);
        // sharpen the resulting image
        memcpy(backupOrg, image->data, size_of_matrix);
        //smooth(backupOrg, sharpKernel, 1, false);
        smoothSharpNoFilter(backupOrg);
        free(backupOrg);
        // write result image to file
        /*bmpfile = fopen(filteredSharpRsltImgName, "wb");
        if(bmpfile == NULL)
        {
            printf("Error opening output file\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // open BMP file of original image
        if((srcFile = fopen(srcImgpName, "rb")) == NULL)
        {
            printf("File Not Found : %s\n", srcImgpName);
            exit(1);
        }

        // read header of original image
        fread(&originalHeader, 1, 54, srcFile);

        // write the BMP file header
        fwrite(&originalHeader, 1, 54, bmpfile);

        // close BMP file of original image
        fclose(srcFile);

        // calculate number of bytes per each line
        bytesPerLine = image->sizeX + image->sizeX + image->sizeX;  // for 24 bit images)
        // round up to a dword boundary
        if(bytesPerLine & 0x0003)
        {
            bytesPerLine |= 0x0003;
            ++bytesPerLine;
        }

        // allocate buffer to hold one line of the image
        linebuf = (char *) calloc(1, bytesPerLine);
        if(linebuf == NULL)
        {
            printf("Error allocating memory\n");
            // close all open files and free any allocated memory
            exit(1);
        }

        // write the image line by line - start with the lowest line
        iData = image->data;
        for (line = 0; line <= image->sizeY; ++line)
        {

            *//*
            * fill line linebuf with the image data for that line
            * remember that the order is BGR
            *//*
            int lineXbytes = line * bytesPerLine;
            for (i = bytesPerLine; i >= 0; i -= 3)
            {
                int lineMult = line * bytesPerLine + i;
                *(linebuf + i) = *(iData + lineMult + 2);
                *(linebuf + i + 1) = *(iData + lineMult + 1);
                *(linebuf + i + 2) = *(iData + lineMult);
            }

            *//*
            * remember that the order is BGR and if width is not a multiple
            * of 4 then the last few bytes may be unused
            *//*
            fwrite(linebuf, 1, bytesPerLine, bmpfile);
        }

        // close the image file
        fclose(bmpfile);*/
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}

