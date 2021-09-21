#include "Images.h"

global_variable unsigned int bitdataheight;
global_variable unsigned int bitdatawidth;
global_variable unsigned int bitdatalength;
global_variable unsigned char bitdata[100000000];

internal void make_background(void) {
	int x0 = 0;
	int y0 = 0;
	for (int y = y0; y < 140; y++) {														//trident background
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + 1920; x++) {
			*pixel++ = 0x255A68;
		}
	}
	for (int y = 140; y < 396; y++) {														//shark and turtle background
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + 1920; x++) {
			*pixel++ = 0x2a6473;
			
		}
	}
	for (int y = 396; y < 460; y++) {														//smallship background														
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + 1920; x++) {
			*pixel++ = 0x357e91;
		}
	}
	for (int y = 460; y < 585; y++) {														//mediumship background
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + 1920; x++) {
			//*pixel++ = 0x357e91;
			*pixel++ = 0x3c8fa3;
		}
	}
	
	for (int y = 585; y < 830; y++) {														//bigship background
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + 1920; x++) {
			*pixel++ = 0x46A5BC;
		}
	}
	unsigned int color = 0xEC9F05;
	for (int y = 830; y < 915; y++) {														//sunset
		color = color + 1;
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + render_state.width; x++) {
			*pixel++ = color;
		}
	}
}


/*********************************************************
//Grabs bit data from image data without other bitmapheader information
*********************************************************/
internal unsigned char* readImagePixels(const unsigned char *image) {
	bitdataheight = (image[25] << 24) + (image[24] << 16) + (image[23] << 8) + image[22];
	bitdatawidth = (image[21]<<24) + (image[20]<<16) + (image[19]<<8) + image[18];
	bitdatalength = (image[37]<<24) + (image[36] << 16) + (image[35]<<8) + image[34] + 54;
	int j = 0;
	for (int i = 54; i < bitdatalength; i++) {
		bitdata[j] = image[i];
		j++;
	}
	return bitdata;
}


/*********************************************************
//Draws image in pixels straight to render_state memory
*********************************************************/
internal void draw_image_in_pixels(int x0, int y0, unsigned char bitdata[100000000]) {
	x0 = clamp(0, x0, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	int j = 0;
	for (int y = y0; y < y0 + bitdataheight; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x0 + bitdatawidth; x++) {
			*pixel++ = ((bitdata[j+2] << 16) + (bitdata[j+1] << 8) + bitdata[j]);
			j += 3;
		}
	}
}

/*********************************************************
//Inputs position and x and y half-sizes of image
*********************************************************/
internal void draw_image(float x, float y, const unsigned char *image, int tridentflag) {
	unsigned char *bitdata = readImagePixels(image);

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = x;
	int y0 = y;
	
	draw_image_in_pixels(x0, y0, bitdata);
}