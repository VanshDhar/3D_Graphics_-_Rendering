/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */

  GzColor A;
  GzColor B;
  GzColor C;
  GzColor D;

  if (u < 0) {
	  u = 0;
  }
  else if (u > 1.0f) {
	  u = 1.0f;
  }
  if (v < 0){
	  v = 0;
  }else if (v > 1.0f) {
	  v = 1.0f;
  }
  

  float U_val = ((float)(xs - 1))*u;
  float V_val = ((float)(ys - 1))*v;
  int higher_X = (int) ceil(U_val);
  int higher_Y = (int) ceil(V_val);
  int lower_Y = (int) floor(V_val);
  int lower_X = (int) floor(U_val);
  float g = U_val - (float)lower_X;
  float h = V_val - (float)lower_Y;


  A[2] = image[( lower_Y * xs ) + lower_X][2];
  A[1] = image[( lower_Y * xs ) + lower_X][1];
  A[0] = image[( lower_Y * xs ) + lower_X][0];
  D[2] = image[(higher_Y * xs) + lower_X][2];
  D[1] = image[(higher_Y * xs) + lower_X][1];
  D[0] = image[(higher_Y * xs) + lower_X][0];
  B[2] = image[( lower_Y * xs ) + higher_X][2];
  B[1] = image[( lower_Y * xs ) + higher_X][1];
  B[0] = image[( lower_Y * xs ) + higher_X][0];
  C[2] = image[( higher_Y * xs ) + higher_X][2];
  C[1] = image[( higher_Y * xs ) + higher_X][1];
  C[0] = image[( higher_Y * xs ) + higher_X][0];

  color[2] = ( g * h * C[2] ) + ( (1.0f - g) * h * D[2] ) + ( g * (1.0f - h) * B[2] ) + ( (1.0f - g) * (1.0f - h) * A[2] );
  color[1] = (g * h * C[1]) + ((1.0f - g) * h * D[1]) + (g * (1.0f - h) * B[1]) + ((1.0f - g) * (1.0f - h) * A[1]);
  color[0] = (g * h * C[0]) + ((1.0f - g) * h * D[0]) + (g * (1.0f - h) * B[0]) + ((1.0f - g) * (1.0f - h) * A[0]);

  return GZ_SUCCESS;
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{

	if (u < 0) {
		u = 0;
	}
	else if (u > 1.0f) {
		u = 1.0f;
	}
	if (v < 0) {
		v = 0;
	}
	else if (v > 1.0f) {
		v = 1.0f;
	}

	float U_val = 6.0f * u;
	float V_val = 6.0f * v;
	int higher_X = (int)ceil(U_val);
	int higher_Y = (int)ceil(V_val);

	

	if (((higher_X%2==0)&&(higher_Y%2==0))||((higher_X % 2 != 0) && (higher_Y % 2 != 0))) {
		color[2] = 0.0f;
		color[1] = 0.0f;
		color[0] = 0.0f;
	}
	else {
		color[2] = 1.0f;
		color[1] = 1.0f;
		color[0] = 1.0f;
	}

	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

