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
    if (argc != 4)
    {
        printf("Usage: ./resize ratio infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int ratio = atoi(argv[1]);
            
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
	newbf.bfReserved1 = 0;
	newbf.bfReserved2 = 0;
	newbf.bfOffBits = 54;
	BITMAPINFOHEADER newbi;
	newbi.biSize = 40;
	newbi.biWidth = bi.biWidth *ratio;
	newbi.biHeight = bi.biHeight *ratio;
	newbi.biPlanes = bi.biPlanes;
	newbi.biBitCount = bi.biBitCount;
	newbi.biCompression = bi.biCompression;
	newbi.biXPelsPerMeter = bi.biXPelsPerMeter;
	newbi.biYPelsPerMeter = bi.biYPelsPerMeter;
	newbi.biClrUsed = bi.biClrUsed;
	newbi.biClrImportant = bi.biClrImportant;
	
	// determine padding for scanlines
    int padding =  (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    newbi.biSizeImage = (newbi.biWidth*3+ padding)*abs(newbi.biHeight);
	newbf.bfSize = 54 + newbi.biSizeImage;


    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

		for (int k = 0; k < ratio; k++)
		{
			// iterate over pixels in scanline
			for (int j = 0; j < bi.biWidth; j++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
				for (int n = 0; n < ratio; n++)
				{
					// write RGB triple to outfile
					fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				}
			}
			fseek(inptr, -sizeof(RGBTRIPLE) * bi.biWidth, SEEK_CUR);
			        
				
			// then add it back (to demonstrate how)
			for (int k = 0; k < padding; k++)
			{
				fputc(0x00, outptr);
			}
			
		}
		// skip over padding, if any
		fseek(inptr, padding + sizeof(RGBTRIPLE)*bi.biWidth, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
