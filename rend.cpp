/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#define PI (float) 3.14159265358979323846

static short matlvlNorm;
int Pop_Matrix(short& top, GzMatrix* Stack) {
	if (top > -1) top--;
	else return GZ_FAILURE;

	return GZ_SUCCESS;
}
int Push_Matrix(short& top, GzMatrix* Stack, GzMatrix Mat) {
	if (top < MATLEVELS) {
		if (top == -1) {
			int i = 0, j = 0;
			while (j < 4) {
				i = 0;
				while (i < 4) {
					Stack[0][i][j] = Mat[i][j];
					i++;
				}
				j++;
			}
		}
		else {
			float sum = 0;
			int i = 0, k = 0, j = 0;
			while (k < 4) {
				j = 0;
				while (j < 4) {
					sum = 0;i = 0;
					while (i < 4) {
						sum += Stack[top][k][i] * Mat[i][j];
						i++;
					}
					Stack[top + 1][k][j] = sum;
					j++;
				}
				k++;
			}
		}
		top++;
	}
	else
		return GZ_FAILURE;

	return GZ_SUCCESS;
}

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			mat[i][j] = 0;
			j++;
		}
		i++;
	}

	float Angle_in_Radian = (degree * PI) / 180.0f;

	mat[0][0] = 1.0;
	mat[3][3] = 1.0;
	mat[1][1] = (float)cos((double)Angle_in_Radian);
	mat[1][2] = -1.0f * (float)sin((double)Angle_in_Radian);
	mat[2][1] = (float)sin((double)Angle_in_Radian);
	mat[2][2] = (float)cos((double)Angle_in_Radian);

	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			mat[i][j] = 0;
			j++;
		}
		i++;
	}

	float Angle_in_Radian = (degree * PI) / 180.0f;

	mat[0][0] = (float)cos((double)Angle_in_Radian);
	mat[0][2] = (float)sin((double)Angle_in_Radian);
	mat[2][0] = -1.0f * (float)sin((double)Angle_in_Radian);
	mat[2][2] = (float)cos((double)Angle_in_Radian);
	mat[1][1] = 1.0;
	mat[3][3] = 1.0;

	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			mat[i][j] = 0;
			j++;
		}
		i++;
	}
	float Angle_in_Radian = (degree * PI) / 180.0f;

	mat[2][2] = 1.0;
	mat[3][3] = 1.0;
	mat[0][0] = (float)cos((double)Angle_in_Radian);
	mat[0][1] = -1.0f * (float)sin((double)Angle_in_Radian);
	mat[1][0] = (float)sin((double)Angle_in_Radian);
	mat[1][1] = (float)cos((double)Angle_in_Radian);

	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			mat[i][j] = 0;
			j++;
		}
		i++;
	}

	mat[0][0] = 1.0;
	mat[1][1] = 1.0;
	mat[2][2] = 1.0;
	mat[3][3] = 1.0;
	mat[0][3] = translate[0];
	mat[1][3] = translate[1];
	mat[2][3] = translate[2];

	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			mat[i][j] = 0;
			j++;
		}
		i++;
	}

	mat[3][3] = 1.0;
	mat[0][0] = scale[0];
	mat[1][1] = scale[1];
	mat[2][2] = scale[2];

	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	xres = (unsigned short)xRes;
	yres = (unsigned short)yRes;

	int total_resolution = xres * yres;
	int framebuffersize = 3 * total_resolution;
	pixelbuffer = new GzPixel[total_resolution];
	framebuffer = new char[framebuffersize];

/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
	int i = 0, j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			Xsp[i][j] = 0;
			j++;
		}
		i++;
	}
	Xsp[3][3] = 1.0;
	Xsp[2][2] = (float)MAXINT;
	Xsp[0][0] = (float)xres / 2.0f;
	Xsp[0][3] = (float)xres / 2.0f;
	Xsp[1][1] = (-1.0f * (float)yres) / 2.0f;
	Xsp[1][3] = (float)yres / 2.0f;


	i = 0;
	while (i < 3) {
		m_camera.lookat[i] = 0;
		m_camera.worldup[i] = 0;
		i++;
	}
	m_camera.FOV = DEFAULT_FOV;
	m_camera.worldup[1] = 1.0;

	m_camera.position[0] = DEFAULT_IM_X;
	m_camera.position[1] = DEFAULT_IM_Y;
	m_camera.position[2] = DEFAULT_IM_Z;

	matlevel = -1;
	matlvlNorm = -1;
	numlights = 0;
}

GzRender::~GzRender()
{
/* HW1.2 clean up, free buffer memory */
	delete[] pixelbuffer;
	delete[] framebuffer;
}

int GzRender::GzDefault()
{
/* HW1.3 set pixel buffer to some default values - start a new frame */
	GzPixel backgroundPixel = { 275, 575, 275, 1, MAXINT };

	int total_resolution = xres * yres;
	int i = 0;
	while (i < total_resolution) {
		framebuffer[3 * i] = (char)275;
		framebuffer[3 * i + 1] = (char)575;
		framebuffer[3 * i + 2] = (char)275;
		pixelbuffer[i] = backgroundPixel;
		i++;
	}
	return GZ_SUCCESS;
}

int GzRender::GzBeginRender()
{
/* HW 3.7 
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 
	GzCoord  cameraX, cameraY, cameraZ, cl, newUp;
	int i = 0;
	while (i < 3) {
		cl[i] = m_camera.lookat[i] - m_camera.position[i];
		i++;
	}
	cameraZ[0] = cl[0] / (float)sqrt((double)((cl[0] * cl[0]) + (cl[1] * cl[1]) + (cl[2] * cl[2])));
	cameraZ[1] = cl[1] / (float)sqrt((double)((cl[0] * cl[0]) + (cl[1] * cl[1]) + (cl[2] * cl[2])));
	cameraZ[2] = cl[2] / (float)sqrt((double)((cl[0] * cl[0]) + (cl[1] * cl[1]) + (cl[2] * cl[2])));

	float upCrossZ = (m_camera.worldup[0] * cameraZ[0]) + (m_camera.worldup[1] * cameraZ[1]) + (m_camera.worldup[2] * cameraZ[2]);

	newUp[0] = m_camera.worldup[0] - (upCrossZ * cameraZ[0]);
	newUp[1] = m_camera.worldup[1] - (upCrossZ * cameraZ[1]);
	newUp[2] = m_camera.worldup[2] - (upCrossZ * cameraZ[2]);

	cameraY[0] = newUp[0] / (float)sqrt((double)((newUp[0] * newUp[0]) + (newUp[1] * newUp[1]) + (newUp[2] * newUp[2])));
	cameraY[1] = newUp[1] / (float)sqrt((double)((newUp[0] * newUp[0]) + (newUp[1] * newUp[1]) + (newUp[2] * newUp[2])));
	cameraY[2] = newUp[2] / (float)sqrt((double)((newUp[0] * newUp[0]) + (newUp[1] * newUp[1]) + (newUp[2] * newUp[2])));

	cameraX[0] = (cameraY[1] * cameraZ[2]) - (cameraY[2] * cameraZ[1]);
	cameraX[1] = (cameraY[2] * cameraZ[0]) - (cameraY[0] * cameraZ[2]);
	cameraX[2] = (cameraY[0] * cameraZ[1]) - (cameraY[1] * cameraZ[0]);

	m_camera.Xiw[3][0] = 0;
	m_camera.Xiw[3][1] = 0;
	m_camera.Xiw[3][2] = 0;
	m_camera.Xiw[3][3] = 1;
	m_camera.Xiw[0][3] = -1.0f * ((cameraX[0] * m_camera.position[0]) + (cameraX[1] * m_camera.position[1]) + (cameraX[2] * m_camera.position[2]));
	m_camera.Xiw[1][3] = -1.0f * ((cameraY[0] * m_camera.position[0]) + (cameraY[1] * m_camera.position[1]) + (cameraY[2] * m_camera.position[2]));
	m_camera.Xiw[2][3] = -1.0f * ((cameraZ[0] * m_camera.position[0]) + (cameraZ[1] * m_camera.position[1]) + (cameraZ[2] * m_camera.position[2]));
	m_camera.Xiw[0][0] = cameraX[0];
	m_camera.Xiw[0][1] = cameraX[1];
	m_camera.Xiw[0][2] = cameraX[2];
	m_camera.Xiw[1][0] = cameraY[0];
	m_camera.Xiw[1][1] = cameraY[1];
	m_camera.Xiw[1][2] = cameraY[2];
	m_camera.Xiw[2][0] = cameraZ[0];
	m_camera.Xiw[2][1] = cameraZ[1];
	m_camera.Xiw[2][2] = cameraZ[2];


	i = 0;int j = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			m_camera.Xpi[i][j] = 0;
			j++;
		}
		i++;
	}
	m_camera.Xpi[0][0] = 1;
	m_camera.Xpi[1][1] = 1;
	m_camera.Xpi[3][3] = 1;
	m_camera.Xpi[2][2] = (float)tan((double)((m_camera.FOV * 3.14159265358979323846) / 180.0) / 2.0f);
	m_camera.Xpi[3][2] = (float)tan((double)((m_camera.FOV * 3.14159265358979323846) / 180.0) / 2.0f);


	int status_update = 0;
	status_update |= GzPushMatrix(Xsp);
	status_update |= GzPushMatrix(m_camera.Xpi);
	status_update |= GzPushMatrix(m_camera.Xiw);

	if (status_update)
		return GZ_FAILURE;
	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/
	m_camera.FOV = camera.FOV;

	int i = 0, j = 0;

	while (i < 3) {

		m_camera.worldup[i] = camera.worldup[i];
		m_camera.position[i] = camera.position[i];
		m_camera.lookat[i] = camera.lookat[i];

		i++;
	}
	i = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			m_camera.Xpi[i][j] = camera.Xpi[i][j];
			m_camera.Xiw[i][j] = camera.Xiw[i][j];

			j++;
		}
		i++;
	}
	return GZ_SUCCESS;	
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	int status_update = 0;

	GzMatrix matrix_I;
	int i = 0, j = 0;
	while (j < 4) {
		i = 0;
		while (i < 4) {
			matrix_I[j][i] = 0;
			i++;
		}
		j++;
	}

	matrix_I[3][3] = 1.0f;
	matrix_I[2][2] = 1.0f;
	matrix_I[0][0] = 1.0f;
	matrix_I[1][1] = 1.0f;

	status_update |= Push_Matrix(matlevel, Ximage, matrix);


	if (matlvlNorm < 2) {
		status_update |= Push_Matrix(matlvlNorm, Xnorm, matrix_I);
	}
	else if (matlvlNorm == 2) {
		GzMatrix Xnorm_iw;
		i = 0;j = 0;
		while (j < 4) {
			i = 0;
			while (i < 4) {
				Xnorm_iw[j][i] = m_camera.Xiw[j][i];
				i++;
			}
			j++;
		}

		Xnorm_iw[2][3] = 0;
		Xnorm_iw[1][3] = 0;
		Xnorm_iw[0][3] = 0;

		status_update |= Push_Matrix(matlvlNorm, Xnorm, Xnorm_iw);
	}
	else {
		if (matrix[0][1] == 0 && matrix[0][2] == 0 && matrix[1][0] == 0
			&& matrix[1][2] == 0 && matrix[2][0] == 0 && matrix[2][1] == 0) {
			status_update |= Push_Matrix(matlvlNorm, Xnorm, matrix_I);
		}
		else {
			status_update |= Push_Matrix(matlvlNorm, Xnorm, matrix);
		}
	}

	if (status_update)
		return GZ_FAILURE;
	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if (Pop_Matrix(matlvlNorm, Xnorm)) return GZ_FAILURE;
	if (Pop_Matrix(matlevel, Ximage)) return GZ_FAILURE;


	return GZ_SUCCESS;
}

int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.4 write pixel values into the buffer */
	if ((i >= 0 && i < xres) && (j >= 0 && j < yres)) {
		int idx = ARRAY(i, j);
		if (z < pixelbuffer[idx].z) {
			GzPixel givenPixel = { r, g, b, a, z };
			pixelbuffer[idx] = givenPixel;
		}
	}
	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.5 retrieve a pixel information from the pixel buffer */
	if ((i >= 0 && i < xres) && (j >= 0 && j < yres)) {
		int idx = ARRAY(i, j);
		GzPixel givenPixel = pixelbuffer[idx];
		*a = givenPixel.alpha;
		*z = givenPixel.z;
		*r = givenPixel.red;
		*g = givenPixel.green;
		*b = givenPixel.blue;

	}
	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	int total_resolution = xres * yres;
	fprintf(outfile, "P6 %d %d 255\n", xres, yres);
	int i = 0;
	while (i < total_resolution) {

		GzPixel givenPixel = pixelbuffer[i];

		GzIntensity colorRed = givenPixel.red;
		GzIntensity colorGreen = givenPixel.green;
		GzIntensity colorBlue = givenPixel.blue;

		if (givenPixel.red > 4095)
			colorRed = 4095;
		else if (givenPixel.red < 0)
			colorRed = 0;
		if (givenPixel.green > 4095)
			colorGreen = 4095;
		else if (givenPixel.green < 0)
			colorGreen = 0;
		if (givenPixel.blue > 4095)
			colorBlue = 4095;
		else if (givenPixel.blue < 0)
			colorBlue = 0;


		char color_buffer[3];

		GzIntensity red_new = colorRed >> 4;
		char finalRed = (char)(red_new & 0xFF);
		GzIntensity green_new = colorGreen >> 4;
		char finalGreen = (char)(green_new & 0xFF);
		GzIntensity blue_new = colorBlue >> 4;
		char finalBlue = (char)(blue_new & 0xFF);


		color_buffer[0] = finalRed;
		color_buffer[1] = finalGreen;
		color_buffer[2] = finalBlue;

		fwrite(color_buffer, 1, 3, outfile);
		i++;
	}
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer()
{
/* HW1.7 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/
	int total_resolution = xres * yres;
	int i = 0;
	while (i < total_resolution) {
		GzPixel givenPixel = pixelbuffer[i];

		GzIntensity colorRed = givenPixel.red;
		GzIntensity colorGreen = givenPixel.green;
		GzIntensity colorBlue = givenPixel.blue;
		GzDepth depthZ = givenPixel.z;

		if (givenPixel.red > 4095)
			colorRed = 4095;
		else if (givenPixel.red < 0)
			colorRed = 0;
		if (givenPixel.green > 4095)
			colorGreen = 4095;
		else if (givenPixel.green < 0)
			colorGreen = 0;
		if (givenPixel.blue > 4095)
			colorBlue = 4095;
		else if (givenPixel.blue < 0)
			colorBlue = 0;

		GzIntensity blue_new = colorBlue >> 4;
		char finalBlue = (char)(blue_new & 0xFF);
		GzIntensity green_new = colorGreen >> 4;
		char finalGreen = (char)(green_new & 0xFF);
		GzIntensity red_new = colorRed >> 4;
		char finalRed = (char)(red_new & 0xFF);


		framebuffer[3 * i] = finalBlue;
		framebuffer[3 * i + 1] = finalGreen;
		framebuffer[3 * i + 2] = finalRed;

		i++;
	}
	return GZ_SUCCESS;
}


/***********************************************/
/* HW2 methods: implement from here */

int GzRender::GzPutAttribute(int numAttributes, GzToken	*nameList, GzPointer *valueList) 
{
/* HW 2.1
-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
-- In later homeworks set shaders, interpolaters, texture maps, and lights
*/

/*
- GzPutAttribute() must accept the following tokens/values:

- GZ_RGB_COLOR					GzColor		default flat-shade color
- GZ_INTERPOLATE				int			shader interpolation mode
- GZ_DIRECTIONAL_LIGHT			GzLight
- GZ_AMBIENT_LIGHT            	GzLight		(ignore direction)
- GZ_AMBIENT_COEFFICIENT		GzColor		Ka reflectance
- GZ_DIFFUSE_COEFFICIENT		GzColor		Kd reflectance
- GZ_SPECULAR_COEFFICIENT       GzColor		Ks coef's
- GZ_DISTRIBUTION_COEFFICIENT   float		spec power
*/
	for (int idx = 0; idx < numAttributes; idx++) {
		GzToken T = nameList[idx];
		if (T == GZ_TEXTURE_MAP) {
			GzTexture tex_function = (GzTexture)valueList[idx];
			if (tex_function != NULL) {
				tex_fun = tex_function;
			}
		}else if (T == GZ_AASHIFTY) {
			float* change_in_Y = (float*) valueList[idx];
			delta_y = *change_in_Y;

		}else if (T == GZ_AASHIFTX) {
			float* change_in_X = (float*) valueList[idx];
			delta_x = *change_in_X;

		}else if (T == GZ_AMBIENT_LIGHT) {
			GzLight* Ambient_light = (GzLight*)valueList[idx];
			ambientlight.color[0] = Ambient_light->color[0];
			ambientlight.color[1] = Ambient_light->color[1];
			ambientlight.color[2] = Ambient_light->color[2];
			ambientlight.direction[0] = Ambient_light->direction[0];
			ambientlight.direction[1] = Ambient_light->direction[1];
			ambientlight.direction[2] = Ambient_light->direction[2];
		}
		else if (T == GZ_AMBIENT_COEFFICIENT) {
			GzColor* color_Ambient = (GzColor*)valueList[idx];
			Ka[2] = (*color_Ambient)[2];
			Ka[1] = (*color_Ambient)[1];
			Ka[0] = (*color_Ambient)[0];
		}
		else if (T == GZ_DIFFUSE_COEFFICIENT) {
			GzColor* color_Diffusion = (GzColor*)valueList[idx];
			Kd[2] = (*color_Diffusion)[2];
			Kd[1] = (*color_Diffusion)[1];
			Kd[0] = (*color_Diffusion)[0];
		}
		else if (T == GZ_SPECULAR_COEFFICIENT) {
			GzColor* color_Specular = (GzColor*)valueList[idx];
			Ks[2] = (*color_Specular)[2];
			Ks[1] = (*color_Specular)[1];
			Ks[0] = (*color_Specular)[0];
		}
		else if (T == GZ_DISTRIBUTION_COEFFICIENT) {
			float* spec_power = (float*)valueList[idx];
			spec = *spec_power;
		}
		else if (T == GZ_RGB_COLOR) {
			GzColor* RGBcolor = (GzColor*)valueList[idx];
			flatcolor[2] = (*RGBcolor)[2];
			flatcolor[1] = (*RGBcolor)[1];
			flatcolor[0] = (*RGBcolor)[0];
		}
		else if (T == GZ_INTERPOLATE) {
			int* selected_mode = (int*)valueList[idx];
			interp_mode = *selected_mode;
		}
		else if (T == GZ_DIRECTIONAL_LIGHT) {
			GzLight* Directed_light = (GzLight*)valueList[idx];
			lights[numlights].color[0] = Directed_light->color[0];
			lights[numlights].color[1] = Directed_light->color[1];
			lights[numlights].color[2] = Directed_light->color[2];
			lights[numlights].direction[0] = Directed_light->direction[0];
			lights[numlights].direction[1] = Directed_light->direction[1];
			lights[numlights].direction[2] = Directed_light->direction[2];

			numlights++;
		}

	}
	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
/* HW 2.2
-- Pass in a triangle description with tokens and values corresponding to
      GZ_NULL_TOKEN:		do nothing - no values
      GZ_POSITION:		3 vert positions in model space
-- Return error code
*/
/*
-- Xform positions of verts using matrix on top of stack 
-- Clip - just discard any triangle with any vert(s) behind view plane 
		- optional: test for triangles with all three verts off-screen (trivial frustum cull)
-- invoke triangle rasterizer  
*/
	GzCoord mesh_vertices[3], mesh_normals[3];
	GzCoord* verticesP = (GzCoord*)valueList[0];
	GzCoord* verticesN = (GzCoord*)valueList[1];
	float transformedVertices4D[3][4], transformedNormals4D[3][4], verticesIn4D[3][4], normalsIn4D[3][4];
	GzTextureIndex* UVvector = (GzTextureIndex*)valueList[2];
	GzTextureIndex UVvec[3];

	int i = 0, j = 0;
	while (i < 3) {
		j = 0;
		while (j < 2) {
			UVvec[i][j] = UVvector[i][j];
			j++;
		}
		i++;
	}

	i = 0;
	j = 0;
	while (i < 3) {
		j = 0;
		while (j < 3) {
			verticesIn4D[i][j] = verticesP[i][j];
			normalsIn4D[i][j] = verticesN[i][j];
			j++;
		}
		verticesIn4D[i][3] = 1.0f;
		normalsIn4D[i][3] = 1.0f;
		i++;
	}

	int k = 0;i = 0;j = 0;
	while (k < 3) {
		j = 0;
		while (j < 4) {
			float Vsum = 0, Nsum = 0;i = 0;
			while (i < 4) {
				Vsum += Ximage[matlevel][j][i] * verticesIn4D[k][i];
				Nsum += Xnorm[matlvlNorm][j][i] * normalsIn4D[k][i];
				i++;
			}
			transformedVertices4D[k][j] = Vsum;
			transformedNormals4D[k][j] = Nsum;
			j++;
		}
		k++;
	}
	i = 0;j = 0;
	while (i < 3) {
		j = 0;
		while (j < 3) {
			mesh_vertices[i][j] = transformedVertices4D[i][j] / transformedVertices4D[i][3];
			mesh_normals[i][j] = transformedNormals4D[i][j] / transformedNormals4D[i][3];
			j++;
		}
		mesh_vertices[i][1] = mesh_vertices[i][1] - delta_y;
		mesh_vertices[i][0] = mesh_vertices[i][0] - delta_x;
		i++;
	}



	float tmp_X, tmp_Y, tmp_Z, tmp_U, tmp_V;
	if (mesh_vertices[0][1] > mesh_vertices[1][1]) {

		tmp_U = UVvec[0][0];
		tmp_V = UVvec[0][1];
		UVvec[0][0] = UVvec[1][0];
		UVvec[0][1] = UVvec[1][1];
		UVvec[1][0] = tmp_U;
		UVvec[1][1] = tmp_V;

		tmp_X = mesh_vertices[0][0];
		tmp_Y = mesh_vertices[0][1];
		tmp_Z = mesh_vertices[0][2];
		mesh_vertices[0][0] = mesh_vertices[1][0];
		mesh_vertices[0][1] = mesh_vertices[1][1];
		mesh_vertices[0][2] = mesh_vertices[1][2];
		mesh_vertices[1][0] = tmp_X;
		mesh_vertices[1][1] = tmp_Y;
		mesh_vertices[1][2] = tmp_Z;

		tmp_X = mesh_normals[0][0];
		tmp_Y = mesh_normals[0][1];
		tmp_Z = mesh_normals[0][2];
		mesh_normals[0][0] = mesh_normals[1][0];
		mesh_normals[0][1] = mesh_normals[1][1];
		mesh_normals[0][2] = mesh_normals[1][2];
		mesh_normals[1][0] = tmp_X;
		mesh_normals[1][1] = tmp_Y;
		mesh_normals[1][2] = tmp_Z;
	}
	if (mesh_vertices[0][1] > mesh_vertices[2][1]) {

		tmp_U = UVvec[0][0];
		tmp_V = UVvec[0][1];
		UVvec[0][0] = UVvec[2][0];
		UVvec[0][1] = UVvec[2][1];
		UVvec[2][0] = tmp_U;
		UVvec[2][1] = tmp_V;

		tmp_X = mesh_vertices[0][0];
		tmp_Y = mesh_vertices[0][1];
		tmp_Z = mesh_vertices[0][2];
		mesh_vertices[0][0] = mesh_vertices[2][0];
		mesh_vertices[0][1] = mesh_vertices[2][1];
		mesh_vertices[0][2] = mesh_vertices[2][2];
		mesh_vertices[2][0] = tmp_X;
		mesh_vertices[2][1] = tmp_Y;
		mesh_vertices[2][2] = tmp_Z;

		tmp_X = mesh_normals[0][0];
		tmp_Y = mesh_normals[0][1];
		tmp_Z = mesh_normals[0][2];
		mesh_normals[0][0] = mesh_normals[2][0];
		mesh_normals[0][1] = mesh_normals[2][1];
		mesh_normals[0][2] = mesh_normals[2][2];
		mesh_normals[2][0] = tmp_X;
		mesh_normals[2][1] = tmp_Y;
		mesh_normals[2][2] = tmp_Z;
	}
	if (mesh_vertices[1][1] > mesh_vertices[2][1]) {

		tmp_U = UVvec[1][0];
		tmp_V = UVvec[1][1];
		UVvec[1][0] = UVvec[2][0];
		UVvec[1][1] = UVvec[2][1];
		UVvec[2][0] = tmp_U;
		UVvec[2][1] = tmp_V;

		tmp_X = mesh_vertices[1][0];
		tmp_Y = mesh_vertices[1][1];
		tmp_Z = mesh_vertices[1][2];
		mesh_vertices[1][0] = mesh_vertices[2][0];
		mesh_vertices[1][1] = mesh_vertices[2][1];
		mesh_vertices[1][2] = mesh_vertices[2][2];
		mesh_vertices[2][0] = tmp_X;
		mesh_vertices[2][1] = tmp_Y;
		mesh_vertices[2][2] = tmp_Z;

		tmp_X = mesh_normals[1][0];
		tmp_Y = mesh_normals[1][1];
		tmp_Z = mesh_normals[1][2];
		mesh_normals[1][0] = mesh_normals[2][0];
		mesh_normals[1][1] = mesh_normals[2][1];
		mesh_normals[1][2] = mesh_normals[2][2];
		mesh_normals[2][0] = tmp_X;
		mesh_normals[2][1] = tmp_Y;
		mesh_normals[2][2] = tmp_Z;
	}


	if ((int)(mesh_vertices[0][1] + 0.5) == (int)(mesh_vertices[1][1] + 0.5)) {
		if (mesh_vertices[0][0] > mesh_vertices[1][0]) {

			tmp_U = UVvec[1][0];
			tmp_V = UVvec[1][1];
			UVvec[1][0] = UVvec[2][0];
			UVvec[1][1] = UVvec[2][1];
			UVvec[2][0] = tmp_U;
			UVvec[2][1] = tmp_V;

			tmp_X = mesh_vertices[1][0];
			tmp_Y = mesh_vertices[1][1];
			tmp_Z = mesh_vertices[1][2];
			mesh_vertices[1][0] = mesh_vertices[2][0];
			mesh_vertices[1][1] = mesh_vertices[2][1];
			mesh_vertices[1][2] = mesh_vertices[2][2];
			mesh_vertices[2][0] = tmp_X;
			mesh_vertices[2][1] = tmp_Y;
			mesh_vertices[2][2] = tmp_Z;

			tmp_X = mesh_normals[1][0];
			tmp_Y = mesh_normals[1][1];
			tmp_Z = mesh_normals[1][2];
			mesh_normals[1][0] = mesh_normals[2][0];
			mesh_normals[1][1] = mesh_normals[2][1];
			mesh_normals[1][2] = mesh_normals[2][2];
			mesh_normals[2][0] = tmp_X;
			mesh_normals[2][1] = tmp_Y;
			mesh_normals[2][2] = tmp_Z;
		}
	}
	else if ((int)(mesh_vertices[1][1] + 0.5) == (int)(mesh_vertices[2][1] + 0.5)) {
		if (mesh_vertices[2][0] > mesh_vertices[1][0]) {

			tmp_U = UVvec[1][0];
			tmp_V = UVvec[1][1];
			UVvec[1][0] = UVvec[2][0];
			UVvec[1][1] = UVvec[2][1];
			UVvec[2][0] = tmp_U;
			UVvec[2][1] = tmp_V;

			tmp_X = mesh_vertices[1][0];
			tmp_Y = mesh_vertices[1][1];
			tmp_Z = mesh_vertices[1][2];
			mesh_vertices[1][0] = mesh_vertices[2][0];
			mesh_vertices[1][1] = mesh_vertices[2][1];
			mesh_vertices[1][2] = mesh_vertices[2][2];
			mesh_vertices[2][0] = tmp_X;
			mesh_vertices[2][1] = tmp_Y;
			mesh_vertices[2][2] = tmp_Z;

			tmp_X = mesh_normals[1][0];
			tmp_Y = mesh_normals[1][1];
			tmp_Z = mesh_normals[1][2];
			mesh_normals[1][0] = mesh_normals[2][0];
			mesh_normals[1][1] = mesh_normals[2][1];
			mesh_normals[1][2] = mesh_normals[2][2];
			mesh_normals[2][0] = tmp_X;
			mesh_normals[2][1] = tmp_Y;
			mesh_normals[2][2] = tmp_Z;
		}
	}
	else {
		float slopeLongestEdge, midX;
		if ((int)(mesh_vertices[0][0] + 0.5) == (int)(mesh_vertices[2][0] + 0.5)) {
			slopeLongestEdge = mesh_vertices[0][0];
		}
		else {
			slopeLongestEdge = (mesh_vertices[0][1] - mesh_vertices[2][1]) / (mesh_vertices[0][0] - mesh_vertices[2][0]);
			midX = (mesh_vertices[1][1] - mesh_vertices[0][1]) / slopeLongestEdge + mesh_vertices[0][0];
		}

		if (midX > mesh_vertices[1][0]) {

			tmp_U = UVvec[1][0];
			tmp_V = UVvec[1][1];
			UVvec[1][0] = UVvec[2][0];
			UVvec[1][1] = UVvec[2][1];
			UVvec[2][0] = tmp_U;
			UVvec[2][1] = tmp_V;

			tmp_X = mesh_vertices[1][0];
			tmp_Y = mesh_vertices[1][1];
			tmp_Z = mesh_vertices[1][2];
			mesh_vertices[1][0] = mesh_vertices[2][0];
			mesh_vertices[1][1] = mesh_vertices[2][1];
			mesh_vertices[1][2] = mesh_vertices[2][2];
			mesh_vertices[2][0] = tmp_X;
			mesh_vertices[2][1] = tmp_Y;
			mesh_vertices[2][2] = tmp_Z;

			tmp_X = mesh_normals[1][0];
			tmp_Y = mesh_normals[1][1];
			tmp_Z = mesh_normals[1][2];
			mesh_normals[1][0] = mesh_normals[2][0];
			mesh_normals[1][1] = mesh_normals[2][1];
			mesh_normals[1][2] = mesh_normals[2][2];
			mesh_normals[2][0] = tmp_X;
			mesh_normals[2][1] = tmp_Y;
			mesh_normals[2][2] = tmp_Z;
		}
	}

	float diffX12 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float diffY12 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float diffX23 = mesh_vertices[2][0] - mesh_vertices[1][0];
	float diffY23 = mesh_vertices[2][1] - mesh_vertices[1][1];
	float diffX31 = mesh_vertices[0][0] - mesh_vertices[2][0];
	float diffY31 = mesh_vertices[0][1] - mesh_vertices[2][1];

	float a12 = diffY12;
	float b12 = -1.0f * diffX12;
	float c12 = diffX12 * mesh_vertices[0][1] - diffY12 * mesh_vertices[0][0];

	float a23 = diffY23;
	float b23 = -1.0f * diffX23;
	float c23 = diffX23 * mesh_vertices[1][1] - diffY23 * mesh_vertices[1][0];

	float a31 = diffY31;
	float b31 = -1.0f * diffX31;
	float c31 = diffX31 * mesh_vertices[2][1] - diffY31 * mesh_vertices[2][0];

	float x1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float z1 = mesh_vertices[1][2] - mesh_vertices[0][2];

	float x2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float z2 = mesh_vertices[2][2] - mesh_vertices[0][2];

	float plane_A = (y1 * z2) - (z1 * y2);
	float plane_B = -((x1 * z2) - (z1 * x2));
	float plane_C = (x1 * y2) - (y1 * x2);
	float plane_D = -1.0f * (plane_A * mesh_vertices[0][0] + plane_B * mesh_vertices[0][1] + plane_C * mesh_vertices[0][2]);

	GzColor Spec_Intensity[3], Diff_Intensity[3], Amb_Intensity[3], Final_Intensity[3];
	i = 0;j = 0;
	while (i < 3) {
		j = 0;
		while (j < 3) {
			Final_Intensity[i][j] = 0;
			Amb_Intensity[i][j] = 0;
			Spec_Intensity[i][j] = 0;
			Diff_Intensity[i][j] = 0;
			j++;

		}
		i++;
	}
	if(interp_mode == GZ_COLOR){
		i = 0;j = 0;
		while (j < 3) {
			i = 0;
			while (i < numlights) {
				GzCoord  E, R;
				E[2] = -1.0f;
				E[0] = 0;
				E[1] = 0;


				float NdL = mesh_normals[j][0] * (lights[i]).direction[0]
					+ mesh_normals[j][1] * (lights[i]).direction[1] + mesh_normals[j][2] * (lights[i]).direction[2];
				float NdE = mesh_normals[j][0] * E[0] + mesh_normals[j][1] * E[1] + mesh_normals[j][2] * E[2];

				if (NdE * NdL > 0) {
					for (int l = 0; l < 3; l++) {
						R[l] = (2.0f * NdL * mesh_normals[j][l])
							- (lights[i]).direction[l];
					}
					float len_R = (float)sqrt((double)((R[0] * R[0]) + (R[1] * R[1]) + (R[2] * R[2])));
					for (int l = 0; l < 3; l++) {
						R[l] /= len_R;
					}

					for (int l = 0; l < 3; l++) {
						float RdE = (R[0] * E[0]) + (R[1] * E[1]) + (R[2] * E[2]);

						if (tex_fun != NULL) {
							Ka[l] = 1.0f;
							Ks[l] = 1.0f;
							Kd[l] = 1.0f;
						}

						if (RdE > 1.0f) {
							RdE = 1.0f;
						}
						else if (RdE < 0) {
							RdE = 0;
						}
						

						Spec_Intensity[j][l] += Ks[l] * (float)pow((double)(RdE), (double)spec)
							* (lights[i]).color[l];
						if (NdL > 0 && NdE > 0) {
							Diff_Intensity[j][l] += Kd[l] * (mesh_normals[j][0] * (lights[i]).direction[0]
								+ mesh_normals[j][1] * (lights[i]).direction[1] + mesh_normals[j][2] * (lights[i]).direction[2]) * (lights[i]).color[l];
						}
						else {
							Diff_Intensity[j][l] += Kd[l] * (-1.0f * mesh_normals[j][0] * (lights[i]).direction[0]
								- 1.0f * mesh_normals[j][1] * (lights[i]).direction[1] - 1.0f * mesh_normals[j][2] * (lights[i]).direction[2]) * (lights[i]).color[l];
						}
					}
				}
				i++;
			}

			for (int l = 0; l < 3; l++) {
				Amb_Intensity[j][l] += (Ka[l] * ambientlight.color[l]);
			}
			j++;
		}
		i = 0;j = 0;
		while (j < 3) {
			i = 0;
			while (i < 3) {
				Final_Intensity[j][i] = Amb_Intensity[j][i] + Spec_Intensity[j][i] + Diff_Intensity[j][i];
				if (Final_Intensity[j][i] < 0) {
					Final_Intensity[j][i] = 0;
				}
				else if (Final_Intensity[j][i] > 1.0) {
					Final_Intensity[j][i] = 1.0;
				}

				i++;
			}
			j++;
		}
	}

	float red_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float red_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float red_Z2 = Final_Intensity[2][0] - Final_Intensity[0][0];
	float red_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float red_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float red_Z1 = Final_Intensity[1][0] - Final_Intensity[0][0];

	float red_PlaneA = (red_Y1 * red_Z2) - (red_Z1 * red_Y2);
	float red_PlaneB = -((red_X1 * red_Z2) - (red_Z1 * red_X2));
	float red_PlaneC = (red_X1 * red_Y2) - (red_Y1 * red_X2);
	float red_PlaneD = -1.0f * (red_PlaneA * mesh_vertices[0][0] + red_PlaneB * mesh_vertices[0][1] + red_PlaneC * Final_Intensity[0][0]);

	float green_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float green_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float green_Z2 = Final_Intensity[2][1] - Final_Intensity[0][1];
	float green_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float green_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float green_Z1 = Final_Intensity[1][1] - Final_Intensity[0][1];

	float green_PlaneA = (green_Y1 * green_Z2) - (green_Z1 * green_Y2);
	float green_PlaneB = -((green_X1 * green_Z2) - (green_Z1 * green_X2));
	float green_PlaneC = (green_X1 * green_Y2) - (green_Y1 * green_X2);
	float green_PlaneD = -1.0f * (green_PlaneA * mesh_vertices[0][0] + green_PlaneB * mesh_vertices[0][1] + green_PlaneC * Final_Intensity[0][1]);

	float blue_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float blue_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float blue_Z2 = Final_Intensity[2][2] - Final_Intensity[0][2];
	float blue_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float blue_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float blue_Z1 = Final_Intensity[1][2] - Final_Intensity[0][2];

	float blue_PlaneA = (blue_Y1 * blue_Z2) - (blue_Z1 * blue_Y2);
	float blue_PlaneB = -((blue_X1 * blue_Z2) - (blue_Z1 * blue_X2));
	float blue_PlaneC = (blue_X1 * blue_Y2) - (blue_Y1 * blue_X2);
	float blue_PlaneD = -1.0f * (blue_PlaneA * mesh_vertices[0][0] + blue_PlaneB * mesh_vertices[0][1] + blue_PlaneC * Final_Intensity[0][2]);

	float normal_X_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float normal_X_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float normal_X_Z2 = mesh_normals[2][0] - mesh_normals[0][0];
	float normal_X_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float normal_X_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float normal_X_Z1 = mesh_normals[1][0] - mesh_normals[0][0];

	float normal_X_PlaneA = (normal_X_Y1 * normal_X_Z2) - (normal_X_Z1 * normal_X_Y2);
	float normal_X_PlaneB = -((normal_X_X1 * normal_X_Z2) - (normal_X_Z1 * normal_X_X2));
	float normal_X_PlaneC = (normal_X_X1 * normal_X_Y2) - (normal_X_Y1 * normal_X_X2);
	float normal_X_PlaneD = -1.0f * (normal_X_PlaneA * mesh_vertices[0][0] + normal_X_PlaneB * mesh_vertices[0][1] + normal_X_PlaneC * mesh_normals[0][0]);

	float normal_Y_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float normal_Y_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float normal_Y_Z2 = mesh_normals[2][1] - mesh_normals[0][1];
	float normal_Y_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float normal_Y_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float normal_Y_Z1 = mesh_normals[1][1] - mesh_normals[0][1];

	float normal_Y_PlaneA = (normal_Y_Y1 * normal_Y_Z2) - (normal_Y_Z1 * normal_Y_Y2);
	float normal_Y_PlaneB = -((normal_Y_X1 * normal_Y_Z2) - (normal_Y_Z1 * normal_Y_X2));
	float normal_Y_PlaneC = (normal_Y_X1 * normal_Y_Y2) - (normal_Y_Y1 * normal_Y_X2);
	float normal_Y_PlaneD = -1.0f * (normal_Y_PlaneA * mesh_vertices[0][0] + normal_Y_PlaneB * mesh_vertices[0][1] + normal_Y_PlaneC * mesh_normals[0][1]);

	float normal_Z_X2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float normal_Z_Y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float normal_Z_Z2 = mesh_normals[2][2] - mesh_normals[0][2];
	float normal_Z_X1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float normal_Z_Y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float normal_Z_Z1 = mesh_normals[1][2] - mesh_normals[0][2];

	float normal_Z_PlaneA = (normal_Z_Y1 * normal_Z_Z2) - (normal_Z_Z1 * normal_Z_Y2);
	float normal_Z_PlaneB = -((normal_Z_X1 * normal_Z_Z2) - (normal_Z_Z1 * normal_Z_X2));
	float normal_Z_PlaneC = (normal_Z_X1 * normal_Z_Y2) - (normal_Z_Y1 * normal_Z_X2);
	float normal_Z_PlaneD = -1.0f * (normal_Z_PlaneA * mesh_vertices[0][0] + normal_Z_PlaneB * mesh_vertices[0][1] + normal_Z_PlaneC * mesh_normals[0][2]);

	GzTextureIndex screen_UVvec[3];
	float Vz;
	i = 0;
	while (i < 3) {
		Vz = mesh_vertices[i][2] / ((float)MAXINT - mesh_vertices[i][2]);
		screen_UVvec[i][0] = UVvec[i][0] / (1.0f + Vz);
		screen_UVvec[i][1] = UVvec[i][1] / (1.0f + Vz);

		i++;
	}

	float U_x1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float U_y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float U_z1 = screen_UVvec[1][0] - screen_UVvec[0][0];

	float U_x2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float U_y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float U_z2 = screen_UVvec[2][0] - screen_UVvec[0][0];

	float U_PlaneA = (U_y1 * U_z2) - (U_z1 * U_y2);
	float U_PlaneB = -((U_x1 * U_z2) - (U_z1 * U_x2));
	float U_PlaneC = (U_x1 * U_y2) - (U_y1 * U_x2);
	float U_PlaneD = -1.0f * (U_PlaneA * mesh_vertices[0][0] + U_PlaneB * mesh_vertices[0][1] + U_PlaneC * screen_UVvec[0][0]);

	float V_x1 = mesh_vertices[1][0] - mesh_vertices[0][0];
	float V_y1 = mesh_vertices[1][1] - mesh_vertices[0][1];
	float V_z1 = screen_UVvec[1][1] - screen_UVvec[0][1];

	float V_x2 = mesh_vertices[2][0] - mesh_vertices[0][0];
	float V_y2 = mesh_vertices[2][1] - mesh_vertices[0][1];
	float V_z2 = screen_UVvec[2][1] - screen_UVvec[0][1];

	float V_PlaneA = (V_y1 * V_z2) - (V_z1 * V_y2);
	float V_PlaneB = -((V_x1 * V_z2) - (V_z1 * V_x2));
	float V_PlaneC = (V_x1 * V_y2) - (V_y1 * V_x2);
	float V_PlaneD = -1.0f * (V_PlaneA * mesh_vertices[0][0] + V_PlaneB * mesh_vertices[0][1] + V_PlaneC * screen_UVvec[0][1]);

	float min_X = min(mesh_vertices[0][0], min(mesh_vertices[1][0], mesh_vertices[2][0]));
	float min_Y = min(mesh_vertices[0][1], min(mesh_vertices[1][1], mesh_vertices[2][1]));
	float max_X = max(mesh_vertices[0][0], max(mesh_vertices[1][0], mesh_vertices[2][0]));
	float max_Y = max(mesh_vertices[0][1], max(mesh_vertices[1][1], mesh_vertices[2][1]));


	int min_XPixel = (int)(min_X + 0.5);
	int max_XPixel = (int)(max_X + 0.5);
	int min_YPixel = (int)(min_Y + 0.5);
	int max_YPixel = (int)(max_Y + 0.5);

	for (int i = min_XPixel; i <= max_XPixel; i++) {
		for (int j = min_YPixel; j <= max_YPixel; j++) {
			float lee31 = a31 * (float)i + b31 * (float)j + c31;
			float lee12 = a12 * (float)i + b12 * (float)j + c12;
			float lee23 = a23 * (float)i + b23 * (float)j + c23;


			if (((lee23 == 0 || lee12 == 0 || lee31 == 0)) || (lee23 < 0 && lee12 < 0 && lee31 < 0 && plane_C != 0)
				|| (lee23 > 0 && lee12 > 0 && lee31 > 0 && plane_C != 0) && green_PlaneC * blue_PlaneC * red_PlaneC != 0
				&& normal_X_PlaneC * normal_Y_PlaneC * normal_Z_PlaneC != 0) {
				float interpolated_Z = -1.0f * (plane_A * (float)i + plane_B * (float)j + plane_D) / plane_C;
				int currZ = (int)(interpolated_Z + 0.5);
				if (currZ >= 0) {

					GzIntensity redColor = 0, greenColor = 0, blueColor = 0;
					if (interp_mode == GZ_FLAT) {

						blueColor = ctoi(flatcolor[2]);
						greenColor = ctoi(flatcolor[1]);
						redColor = ctoi(flatcolor[0]);
					}
					else if (interp_mode == GZ_COLOR) {
						GzColor total_intensity;
						GzColor tex_RGB; GzTextureIndex pixelUV;
						float Vz2;

						total_intensity[1] = -1.0f * (green_PlaneA * (float)i + green_PlaneB * (float)j + green_PlaneD) / green_PlaneC;
						total_intensity[2] = -1.0f * (blue_PlaneA * (float)i + blue_PlaneB * (float)j + blue_PlaneD) / blue_PlaneC;
						total_intensity[0] = -1.0f * (red_PlaneA * (float)i + red_PlaneB * (float)j + red_PlaneD) / red_PlaneC;

						if (tex_fun != NULL) {
							Vz2 = ((float)currZ) / ((float)MAXINT - (float)currZ);
							pixelUV[0] = -1.0f * (((float)i) * U_PlaneA + ((float)j) * U_PlaneB + U_PlaneD) / U_PlaneC;
							pixelUV[1] = -1.0f * (((float)i) * V_PlaneA + ((float)j) * V_PlaneB + V_PlaneD) / V_PlaneC;

							pixelUV[0] = pixelUV[0] * (1.0f + Vz2);
							pixelUV[1] = pixelUV[1] * (1.0f + Vz2);

							int status_update = tex_fun(pixelUV[0], pixelUV[1], tex_RGB);
							if (status_update) return GZ_FAILURE;
							for (int t = 0;t < 3;t++) {
								total_intensity[t] *= tex_RGB[t];
							}
						}

						blueColor = ctoi(total_intensity[2]);
						greenColor = ctoi(total_intensity[1]);
						redColor = ctoi(total_intensity[0]);

					}
					else if (interp_mode == GZ_NORMALS) {
						GzCoord interpolatedNorm;GzColor total_intensity;
						GzColor spec_I, amb_I, diff_I;
						GzColor tex_RGB; GzTextureIndex pixelUV;
						float Vz2;

						interpolatedNorm[1] = -1.0f * (normal_Y_PlaneA * (float)i + normal_Y_PlaneB * (float)j + normal_Y_PlaneD) / normal_Y_PlaneC;
						interpolatedNorm[2] = -1.0f * (normal_Z_PlaneA * (float)i + normal_Z_PlaneB * (float)j + normal_Z_PlaneD) / normal_Z_PlaneC;
						interpolatedNorm[0] = -1.0f * (normal_X_PlaneA * (float)i + normal_X_PlaneB * (float)j + normal_X_PlaneD) / normal_X_PlaneC;

						if (tex_fun != NULL) {
							Vz2 = ((float)currZ) / ((float)MAXINT - (float)currZ);
							pixelUV[0] = -1.0f * (((float)i) * U_PlaneA + ((float)j) * U_PlaneB + U_PlaneD) / U_PlaneC;
							pixelUV[1] = -1.0f * (((float)i) * V_PlaneA + ((float)j) * V_PlaneB + V_PlaneD) / V_PlaneC;

							pixelUV[0] = pixelUV[0] * (1.0f + Vz2);
							pixelUV[1] = pixelUV[1] * (1.0f + Vz2);

							int status_update = tex_fun(pixelUV[0], pixelUV[1], tex_RGB);
							if (status_update) return GZ_FAILURE;
							for (int t = 0;t < 3;t++) {
								Ka[t] = tex_RGB[t];
								Kd[t] = tex_RGB[t];
							}
						}

						int t = 0;
						while (t < 3) {
							spec_I[t] = 0;
							amb_I[t] = 0;
							diff_I[t] = 0;
							t++;

						}
						int m = 0;
						while (m < numlights) {
							GzCoord R, E;
							E[2] = -1.0f;
							E[0] = 0;
							E[1] = 0;

							float NdE = (interpolatedNorm[0] * E[0]) + (interpolatedNorm[1] * E[1]) + (interpolatedNorm[2] * E[2]);
							float NdL = interpolatedNorm[0] * (lights[m]).direction[0] + interpolatedNorm[1] * (lights[m]).direction[1]
								+ interpolatedNorm[2] * (lights[m]).direction[2];

							if (NdE * NdL > 0) {
								for (int l = 0; l < 3; l++) {
									R[l] = 2.0f * NdL * interpolatedNorm[l] - (lights[m]).direction[l];
								}
								float len_R = (float)sqrt((double)((R[0] * R[0]) + (R[1] * R[1]) + (R[2] * R[2])));
								for (int l = 0; l < 3; l++) {
									R[l] /= len_R;
								}

								for (int l = 0; l < 3; l++) {
									float RdE = (R[0] * E[0]) + (R[1] * E[1]) + (R[2] * E[2]);
									if (RdE > 1.0f) {
										RdE = 1.0f;
									}
									else if (RdE < 0) {
										RdE = 0;
									}


									spec_I[l] += Ks[l] *
										(float)pow((double)(RdE), (double)spec)
										* (lights[m]).color[l];
									if (NdL > 0 && NdE > 0) {
										diff_I[l] += Kd[l] * (interpolatedNorm[0] * (lights[m]).direction[0]
											+ interpolatedNorm[1] * (lights[m]).direction[1]
											+ interpolatedNorm[2] * (lights[m]).direction[2]) * (lights[m]).color[l];
									}
									else {
										diff_I[l] += Kd[l] * (-1.0f * interpolatedNorm[0] * (lights[m]).direction[0]
											- 1.0f * interpolatedNorm[1] * (lights[m]).direction[1]
											- 1.0f * interpolatedNorm[2] * (lights[m]).direction[2]) * (lights[m]).color[l];
									}
								}
							}
							m++;
						}
						int l = 0;
						while (l < 3) {
							amb_I[l] += (Ka[l] * ambientlight.color[l]);
							l++;
						}

						l = 0;
						while (l < 3) {
							total_intensity[l] = amb_I[l] + spec_I[l] + diff_I[l];
							if (total_intensity[l] < 0) {
								total_intensity[l] = 0;
							}
							else if (total_intensity[l] > 1.0) {
								total_intensity[l] = 1.0;
							}
							l++;

						}



						blueColor = ctoi(total_intensity[2]);
						greenColor = ctoi(total_intensity[1]);
						redColor = ctoi(total_intensity[0]);
					}


					GzPut(i, j, redColor, greenColor, blueColor, 1, currZ);
				}
			}
		}
	}
	return GZ_SUCCESS;
}

