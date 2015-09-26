/*
 * dump1.c
 * based on example1.c                                                         
 *                                                                  
 * This small program shows how to print a one char with the FreeType 2 library.
 */                                               

/* dump1 0x6c38 36 simhei.ttf 0
 * ^      ^      ^   ^        ^
 * |      |      |   |        |
 *
 * 1      2      3   4        5
 *
 * 1. the name of this program.
 * 2. unicode of the char you want to display, in hex or dec.
 * 3. size of font.
 * 4. font file.
 * 5. human/machine readable.
 */


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <ft2build.h>
#include FT_FREETYPE_H



int fontsize = 24;

/* wasting memory... */
unsigned char image[1920][1080];

int view = 0;

/* Replace this function with something useful. */

void draw_bitmap( FT_Bitmap* bitmap, FT_Int x, FT_Int y)
{
	FT_Int  i, j, p, q;
	FT_Int  x_max = x + bitmap->width;
	FT_Int  y_max = y + bitmap->rows;
  
	for ( i = x, p = 0; i < x_max; i++, p++ ) {
		for ( j = y, q = 0; j < y_max; j++, q++ ) {
		      if ( i < 0 || j < 0 || 
			i >= fontsize || j >= fontsize )
		continue;

		image[j][i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}


void show_point(unsigned char ch)
{
        if(!view) {
                unsigned int c;
                c = ch;
                if(c == 0) printf("____, ");
                else printf("0x%02x, ", c);
        }
        else {
                if(ch == 0) putchar(' ');
                else if(ch <  31) putchar('.');
                else if(ch <  63) putchar('o');
                else if(ch < 127) putchar('O');
                else              putchar('@'); 
        }
}


void LEFT_PAD(int n)
{
        int i;
        for(i=0; i<n; i++)
                putchar(' ');
}

void dump_bitmap( FT_Bitmap*  bitmap)
{
        FT_Int  p, q;
        FT_Int  x_max = bitmap->width;
        FT_Int  y_max = bitmap->rows;
        static int x_prev = -1;
        unsigned char ch;


        if(view) {     
                LEFT_PAD(10);
                putchar('*');
        }
  
        for ( q = 0; q < x_max || q<x_prev; q++ )
                if(view) {
                        if(q!=x_max && q!=x_prev) putchar('-');
                else 
                        putchar('*');
        }

        putchar('*');
        putchar('\n');
        
        x_prev = x_max;

        for ( q = 0; q < y_max; q++ ) {
                if(view) {
                        LEFT_PAD(10);
                        printf("|");
                }
        for ( p = 0; p < x_max; p++ ) {
                ch = bitmap->buffer[q * bitmap->width + p];
                show_point(ch);
        }
        if(view) putchar('|');
                printf("\n");
        }
}

        
void show_image( void )
{
        int  i, j;
        
        for ( i = 0; i < fontsize; i++ ) {
                for ( j = 0; j < fontsize; j++ ) {
                        show_point(image[i][j]);
                }
                putchar( '\n' );
        }
}


int main( int argc, char *argv[])
{
        FT_Library    library;
        FT_Face       face;
        FT_GlyphSlot  slot;
        FT_Error      error;

        char    filename[255];
        double  angle;
        int     ch;

        if(argc > 1) {
                if(argv[1][0] == '0' && (argv[1][1] == 'x' || argv[1][1] == 'X')) 
                        ch = strtol(argv[1], NULL, 16);
                else
                        ch = atoi(argv[1]);

        if(ch == 0) {
                strncpy((char *)&ch, argv[1], 2);
        }
        }
        else {
                ch = 0x6C38; /* 永 */
                ch = 27704;  /* also 永 */
        }
  
        if(argc > 2) {
                fontsize = atoi(argv[2]);
                if(fontsize == 0) fontsize = 24;
        }
        else {
                fontsize = 36;
        }

        if(argc > 3) {
                strcpy(filename, argv[3]);
        }
        else {
                strcpy(filename, "DroidSansFallback.ttf");
        }
        
        if(argc > 4 && argv[4][0]!='0') { 
                view = 0;
        }
        else {
                view = 0xdead;
        }
  
        error = FT_Init_FreeType( &library );
        error = FT_New_Face( library, filename, 0, &face );  
        error = FT_Set_Pixel_Sizes( face, 0, fontsize);

        slot = face->glyph;

for(ch=0x6c38; ch ;ch=0){
        error = FT_Load_Char( face, ch, FT_LOAD_RENDER );
        dump_bitmap( &slot->bitmap);
        if(!view) putchar('\n');
}
        FT_Done_Face    ( face );
        FT_Done_FreeType( library );
        return 0;
}

/* EOF */
