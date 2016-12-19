/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./resize infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];
            
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // set info and header file
	BITMAPFILEHEADER newbf;
	newbf.bfType = 0x4d42;
	if (bi.biHeight < 0)
		newbf.bfSize = 54 - 1 * -1 * 3 ;
	else
		newbf.bfSize = 54 + 1 * 1 * 3 ;
	newbf.bfReserved1 = 0;
	newbf.bfReserved2 = 0;
	newbf.bfOffBits = 54;
	BITMAPINFOHEADER newbi;
	newbi.biSize = 40;
	newbi.biWidth = 1;
	newbi.biHeight = -1;
	newbi.biPlanes = bi.biPlanes;
	newbi.biBitCount = bi.biBitCount;
	newbi.biCompression = bi.biCompression;
	newbi.biSizeImage = 1*abs(-1)*3;
	newbi.biXPelsPerMeter = bi.biXPelsPerMeter;
	newbi.biYPelsPerMeter = bi.biYPelsPerMeter;
	newbi.biClrUsed = bi.biClrUsed;
	newbi.biClrImportant = bi.biClrImportant;
	
    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4)%4;

    // iterate over infile's scanlines

				// temporary storage
				RGBTRIPLE triple;
				triple.rgbtRed =0;
				triple.rgbtBlue =0;
				triple.rgbtGreen =0;
				// write RGB triple to outfile
				fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
			        
				
			// then add it back (to demonstrate how)
			for (int k = 0; k < padding; k++)
			{
				fputc(0x00, outptr);
			}
			
		
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
