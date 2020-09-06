
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstdlib>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

GLUquadricObj* mqo = gluNewQuadric();

int slices = 50, stacks = 50;
float camX = 0.5, camY = 12.0, camZ = 26.0;
float lookX = 0.0, lookY = 10, lookZ = 0.0;
float rotateX = 0.0, rotateY = 0.0, rotateZ = 0.0;
float translateX = 0.0, translateY = 0.0, translateZ = 0.0;
float lightX = 0.0, lightY = -2.0, lightZ = 5.0;

float zoom = 1.0;

GLuint LoadTexture(char* fileName);

void setPerspective(), drawBg(), drawCube(), drawRobot(), drawSpike(), drawBolt();
void drawSkeleton(float radius, float skeletonLength), drawBallJoint(float radius), drawHingeJoint(float radius), drawPlate();
void drawHead(), drawNeck(), drawTurbo(), drawChest(), drawBackArmor(), drawInnerBody(), drawPelvic();
void drawArmLeft(), drawArmRight(), drawLowerArmCover(), drawLeftHand(), drawRightHand(), drawFinger(float fingersAngle);
void drawLegs(), drawOneLeg(int rotateLowerLegX);
void drawSword(), drawSwordBlade(), drawSword2(), drawShield();

GLuint skyTexture, earthTexture, boltTexture, blueFlameTexture, redFlameTexture, shieldStarTexture;
GLuint eyesTexture, redTexture, turboTexture, turboOuterTexture, swordTexture;
GLuint armourTexture, armourTexture1, armourTexture2, bodyTexture;
GLuint skeletonTexture, skeletonTexture1, skeletonTexture2;
GLuint armourTextureArr[3], skeletonTextureArr[3];
int texCount = 2;

BITMAP BMP;
HBITMAP hBMP = NULL;

boolean draw_spike = false, draw_bolt = false, draw_sword = false, draw_sword2 = false, draw_shield = false, walking = false, stab = false, chop = false;
boolean switch_perspective = false, switch_viewpoint = false, assing = false, jumping = false, flying = false;

float raise_Spike = -9.0, boltheight = 0.0, boltradius = 0.74, scaleWeapon2 = 0.0;
float headAngle = 180.0f;
float fingersAngle = 150.0f;
int boltRotate = 0, turboRotate = 0;
int rotateArmLX = 0, rotateForeArmLX = 0, rotateArmLZ = 0, rotateArmRX = 0, rotateForeArmRX = 0, rotateArmRZ = 0;
int rotateLegLX = 0, rotateLowerLegLX = 0, rotateLegRX = 0, rotateLowerLegRX = 0;
int stepRotateArmLX = 10, stepRotateForeArmLX = 10, stepRotateArmLZ = 10, stepRotateArmRX = 10, stepRotateForeArmRX = 10, stepRotateArmRZ = 10;
int stepRotateLegLX = 10, stepRotateLowerLegLX = 10, stepRotateLegRX = 10, stepRotateLowerLegRX = 10;
int stepStab = 3, stepChop = 3;
float rotateBodyY = 0, stepRotateBodyY = 0.25, rotateAss = 0.0, stepRotateAss = 0.20, translateJumping = 0.0, stepJumping = 0.50, translateFlying = 0;
int stepWalking = 2;
int swordLength = 0;

void reset()
{
	draw_spike = false, draw_bolt = false, draw_sword = false, draw_sword2 = false, draw_shield = false, walking = false, stab = false, chop = false;
	assing = false, jumping = false, flying = false;
	raise_Spike = -9.0, boltheight = 0.0, boltradius = 0.74;
	headAngle = 180.0f;
	fingersAngle = 150.0f;
	boltRotate = 0, turboRotate = 0;
	rotateArmLX = 0, rotateForeArmLX = 0, rotateArmLZ = 0, rotateArmRX = 0, rotateForeArmRX = 0, rotateArmRZ = 0;
	rotateLegLX = 0, rotateLowerLegLX = 0, rotateLegRX = 0, rotateLowerLegRX = 0;
	stepRotateArmLX = 10, stepRotateForeArmLX = 10, stepRotateArmLZ = 10, stepRotateArmRX = 10, stepRotateForeArmRX = 10, stepRotateArmRZ = 10;
	stepRotateLegLX = 10, stepRotateLowerLegLX = 10, stepRotateLegRX = 10, stepRotateLowerLegRX = 10;
	stepStab = 3, stepChop = 3;
	rotateBodyY = 0, stepRotateBodyY = 0.25, rotateAss = 0.0, stepRotateAss = 0.20, translateJumping = 0.0, stepJumping = 0.50, translateFlying = 0;
	stepWalking = 2;
}

void resetCam()
{
	camX = 0.5, camY = 12.0, camZ = 25.0;
	lookX = 0.0, lookY = 10, lookZ = 0.0;
	rotateX = 0.0, rotateY = 0.0, rotateZ = 0.0;
	translateX = 0.0, translateY = 0.0, translateZ = 0.0;
	lightX = 0.0, lightY = -2.0, lightZ = 5.0;
	zoom = 1.0;
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			PostQuitMessage(0);
			break;
		}
		case 0x41: // A
		{
			camX -= 0.3;
			break;
		}
		case 0x44: // D
		{
			camX += 0.3;
			break;
		}
		case 0x57: // W
		{
			camY += 0.3;
			break;
		}
		case 0x53: // S
		{
			camY -= 0.3;
			break;
		}
		case 0x51:  // Q
		{
			camZ -= 0.3;
			break;
		}
		case 0x45: // E
		{
			camZ += 0.3;
			break;
		}
		case 0x4A: // J
		{
			lookX -= 0.3;
			break;
		}
		case 0x4C: // L
		{
			lookX += 0.3;
			break;
		}
		case 0x49: // I
		{
			lookY += 0.3;
			break;
		}
		case 0x4B: // K
		{
			lookY -= 0.3;
			break;
		}
		case 0x55: // U
		{
			//lookZ += 0.1;
			if (zoom < 4.0)
			{
				zoom += 0.05;
				setPerspective();
			}
			break;
		}
		case 0x4F: // O
		{
			//lookZ -= 0.1;
			if (zoom >= 0.25)
			{
				zoom -= 0.05;
				setPerspective();
			}
			break;
		}
		case VK_LEFT: // LEFT
		{
			translateX += 0.3;
			break;
		}
		case VK_RIGHT: // RIGHT
		{
			translateX -= 0.3;
			break;
		}
		case VK_UP: // UP
		{
			translateZ += 0.3;
			break;
		}
		case VK_DOWN: // DOWN
		{
			translateZ -= 0.3;
			break;
		}
		case VK_OEM_COMMA: // ,
		{
			translateY += 0.3;
			break;
		}
		case VK_OEM_PERIOD: // .
		{
			translateY -= 0.3;
			break;
		}
		case VK_NUMPAD1: // 1
		{
			//lightX += 0.1;
			rotateY += 3;
			break;
		}
		case VK_NUMPAD3: // 3
		{
			//lightX -= 0.1;
			rotateY -= 3;
			break;
		}
		case VK_NUMPAD5: // 5
		{
			//lightY -= 0.1;
			rotateX += 3;
			break;
		}
		case VK_NUMPAD2: // 2
		{
			//lightY += 0.1;
			rotateX -= 3;
			break;
		}
		case VK_NUMPAD4: // 4
		{
			//lightZ -= 0.1;
			rotateZ += 0.3;
			break;
		}
		case VK_NUMPAD6: // 6
		{
			//lightZ += 0.1;
			rotateZ -= 0.3;
			break;
		}
		case VK_SPACE:
		{
			resetCam();
			reset();
			break;
		}
		case 0x31:
		{
			draw_spike = !draw_spike;
			if (draw_spike)
			{
				reset();
				draw_spike = true;
			}
			break;
		}
		case 0x32:
		{
			draw_bolt = !draw_bolt;
			if (draw_bolt)
			{
				reset();
				draw_bolt = true;
			}
			break;
		}
		case 0x34:
		{
			draw_shield = !draw_shield;
			draw_sword2 = !draw_sword2;
			if (draw_shield || draw_sword2)
			{
				reset();
				draw_shield = true;
				draw_sword2 = true;
			}
			break;
		}
		case 0x35:
		{
			draw_sword = !draw_sword;
			if (draw_sword)
			{
				reset();
				draw_sword = true;
			}
			break;
		}
		case 0x37:
		{
			if (rotateArmLX > 160 || rotateArmLX < -60)
				stepRotateArmLX = -stepRotateArmLX;
			if (rotateArmRX > 160 || rotateArmRX < -60)
				stepRotateArmRX = -stepRotateArmRX;
			rotateArmLX += stepRotateArmLX;
			rotateArmRX += stepRotateArmRX;
			break;
		}
		case 0x38:
		{
			if (rotateForeArmLX > 130 || rotateForeArmLX < 0)
				stepRotateForeArmLX = -stepRotateForeArmLX;
			if (rotateForeArmRX > 130 || rotateForeArmRX < 0)
				stepRotateForeArmRX = -stepRotateForeArmRX;
			rotateForeArmLX += stepRotateForeArmLX;
			rotateForeArmRX += stepRotateForeArmRX;
			break;
		}
		case 0x39:
		{
			if (rotateArmLZ > 100 || rotateArmLZ < 0)
				stepRotateArmLZ = -stepRotateArmLZ;
			rotateArmLZ += stepRotateArmLZ;
			if (rotateArmRZ > 100 || rotateArmRZ < 0)
				stepRotateArmRZ = -stepRotateArmRZ;
			rotateArmRZ += stepRotateArmRZ;
			break;
		}
		case '0':
		{
			if (rotateLegLX > 70 || rotateLegLX < -20)
				stepRotateLegLX = -stepRotateLegLX;
			if (rotateLegRX > 70 || rotateLegRX < -20)
				stepRotateLegRX = -stepRotateLegRX;
			rotateLegLX += stepRotateLegLX;
			rotateLegRX += stepRotateLegRX;
			break;
		}
		case VK_OEM_MINUS:
		{
			if (rotateLowerLegLX > 60 || rotateLowerLegLX < 0)
				stepRotateLowerLegLX = -stepRotateLowerLegLX;
			rotateLowerLegLX += stepRotateLowerLegLX;
			if (rotateLowerLegRX > 60 || rotateLowerLegRX < 0)
				stepRotateLowerLegRX = -stepRotateLowerLegRX;
			rotateLowerLegRX += stepRotateLowerLegRX;
			break;
		}
		case VK_OEM_PLUS:
		{
			//rotateArmZ -= 10;
			break;
		}
		case VK_RETURN:
		{
			walking = !walking;
			if (walking)
			{
				reset();
				walking = true;
			}
			break;
		}
		break;
		case 'R':
		{
			texCount = (texCount + 1) % 3;
			break;
		}
		case 'T':
		{
			stab = !stab;
			if (stab)
			{
				reset();
				stab = true;
				draw_sword = true;
				rotateForeArmLX = 90;
			}
			else
				draw_sword = false;
			rotateArmLZ = 0;
			rotateArmLX = 0;
			stepStab = 2;
			break;
		}
		case 'Y':
		{
			chop = !chop;
			if (chop)
			{
				reset();
				chop = true;
				draw_sword2 = true;
				draw_shield = true;
				rotateForeArmLX = 110;
				rotateArmLX = 45;
			}
			else
				draw_sword = false;
			break;
		}
		case VK_OEM_3: // `
		{
			switch_perspective = !switch_perspective;
			setPerspective();
			break;
		}
		case VK_TAB:
		{
			switch_viewpoint = !switch_viewpoint;
			if (switch_viewpoint)
			{
				camX = -4.5;
				camY = 16.0;
				camZ = -8.0;
				lookX = 0.0;
				lookY = 10.0;
				lookZ = 25.0;
			}
			else
			{
				camX = 0.5;
				camY = 12.0;
				camZ = 26.0;
				lookX = 0.0;
				lookY = 10.0;
				lookZ = 0.0;
			}
			break;
		}
		case 'Z':
		{
			assing = !assing;
			if (assing)
			{
				reset();
				assing = true;
				rotateForeArmLX = 90;
				rotateForeArmRX = 90;
				rotateArmLX = 90;
				rotateArmRX = 90;
				rotateArmLZ = 90;
				rotateArmRZ = 90;
			}
			break;
		}
		case 'X':
		{
			jumping = !jumping;
			if (jumping)
			{
				reset();
				jumping = true;
			}
			break;
		}
		case 'C':
		{
			flying = !flying;
			if (flying)
			{
				reset();
				flying = true;
				rotateArmLZ = 70;
				rotateArmRZ = 70;
			}
			break;
		}
		case 'V':
		{
			if (flying)
				translateFlying += 0.1;
			break;
		}
		case 'B':
		{
			if (flying && translateFlying >= 2.0)
				translateFlying -= 0.1;
			break;
		}
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(camX, camY, camZ, lookX, lookY + translateFlying, lookZ, 0.0, 1.0, 0.0);

	glRotatef(rotateX, 1, 0, 0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);

	GLfloat lightposition[] = { lightX, lightY, lightZ, 0.1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
	GLfloat disfuse[] = { 0.7, 0.7, 0.7, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, disfuse);
	GLfloat ambient0[] = { 0.7, 0.7, 0.7, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);

	gluQuadricDrawStyle(mqo, GLU_FILL);
	gluQuadricNormals(mqo, GLU_SMOOTH);
	gluQuadricOrientation(mqo, GLU_INSIDE);
	gluQuadricTexture(mqo, GL_TRUE);

	drawRobot();

	//--------------------------------
	//
	//	Draw Here
	//
	//--------------------------------

	glTranslatef(translateX, translateY, translateZ);

	drawBg();

	// glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);


	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

void drawRobot()
{
	glEnable(GL_TEXTURE_2D);

	if (walking)
	{
		translateZ -= 0.1;

		if (rotateArmLX > 30 || rotateArmLX < -30)
		{
			stepWalking = -stepWalking;
			stepRotateBodyY = -stepRotateBodyY;
		}

		rotateBodyY -= stepRotateBodyY;
		rotateArmLX += stepWalking;
		rotateArmRX -= stepWalking;
		rotateLegLX += stepWalking;
		rotateLegRX -= stepWalking;
		rotateLowerLegLX = abs(rotateLegLX);
		rotateLowerLegRX = abs(rotateLegRX);
		if (rotateArmLX > 0)
		{
			rotateForeArmLX += stepWalking;
		}
		if (rotateArmRX > 0)
		{
			rotateForeArmRX -= stepWalking;
		}
		else if (rotateArmLX == 0)
		{
			rotateForeArmLX = 0;
			rotateForeArmRX = 0;
		}
	}

	if (stab)
	{
		if (rotateArmLZ > 15)
		{
			stepStab = -stepStab;
		}
		if (rotateArmLZ >= 0)
		{
			rotateArmLZ += stepStab;
			rotateBodyY -= stepRotateBodyY;
		}

		if (rotateArmLX < 90)
		{
			rotateArmLX += 5;
			rotateForeArmLX -= 5;
		}
	}
	else
	{
		if (rotateBodyY < 0)
		{
			rotateBodyY += stepRotateBodyY;
		}
	}

	if (chop)
	{
		if (rotateForeArmLX > 0)
		{
			rotateForeArmLX -= stepChop;
			rotateBodyY -= stepRotateBodyY * 2;
		}
	}

	if (draw_shield && draw_sword2)
	{
		if (scaleWeapon2 < 1.0)
		{
			scaleWeapon2 += 0.05;
		}
	}
	else if (scaleWeapon2 > 0.0)
	{
		scaleWeapon2 -= 0.05;
	}

	if (assing)
	{
		if (rotateAss > 3 || rotateAss < -3)
		{
			stepRotateAss = -stepRotateAss;
		}
		rotateAss += stepRotateAss;
		if (rotateForeArmLX > 120 || rotateForeArmLX < 60)
		{
			stepRotateForeArmLX = -stepRotateForeArmLX;
			stepRotateForeArmRX = -stepRotateForeArmRX;
		}
		rotateForeArmLX += stepRotateForeArmLX / 3;
		rotateForeArmRX += stepRotateForeArmRX / 3;
	}

	if (jumping)
	{
		if (rotateLegLX > 90 || rotateLegLX < 0)
		{
			stepRotateArmLZ = -stepRotateArmLZ;
			stepRotateArmRZ = -stepRotateArmRZ;
			stepRotateLegLX = -stepRotateLegLX;
			stepRotateLegRX = -stepRotateLegRX;
			stepRotateLowerLegLX = -stepRotateLowerLegLX;
			stepRotateLowerLegRX = -stepRotateLowerLegRX;
			stepJumping = -stepJumping;
		}
		rotateArmLZ += stepRotateArmLZ / 2;
		rotateArmRZ += stepRotateArmRZ / 2;
		rotateLegLX += stepRotateLegLX / 2;
		rotateLegRX += stepRotateLegRX / 2;
		rotateLowerLegLX += stepRotateLowerLegLX / 2;
		rotateLowerLegRX += stepRotateLowerLegRX / 2;
		translateJumping += stepJumping;
	}

	if (flying)
	{
		if (translateFlying < 2.0)
			translateFlying += 0.1;
	}
	else if (translateFlying > 0)
	{
		translateFlying -= 0.1;
		if (rotateArmLZ > 0 || rotateArmRZ > 0)
		{
			rotateArmLZ -= 2;
			rotateArmRZ -= 2;
		}
	}

	glPushMatrix();
	{
		if (jumping)
			glTranslatef(0.0, -translateJumping + 4.2, -translateJumping / 3);
		if (flying || translateFlying > 0)
			glTranslatef(0.0, translateFlying, 0.0);
		glRotatef(rotateBodyY, 0, 1, 0);

		glPushMatrix();
		{
			glTranslatef(0, 3.0, 0);
			glRotatef(-rotateAss / 3, 0, 0, 1);
			glTranslatef(0, -3.0, 0);
			glScalef(1.1, 1.2, 1.1);
			drawLegs();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0, 1.0, 0.0);

			glPushMatrix();
			{
				glTranslatef(0, 9.0, 0);
				glRotatef(rotateAss, 0, 0, 1);
				glTranslatef(0, -9.0, 0);
				glPushMatrix();
				{
					glTranslatef(0, 1.2, 0);

					drawHead();

					drawNeck();

					drawTurbo();

					drawChest();

					drawBackArmor();

					drawInnerBody();
				}
				glPopMatrix();

				drawPelvic();

				glPushMatrix();
				{
					glTranslatef(4.9, 0.0, -2.7);
					glRotatef(10, 0, 0, 1);
					glScalef(1.0, 1.2, 1.0);
					drawArmLeft();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(-4.9, 0.0, 1.0);
					glRotatef(-10, 0, 0, 1);
					glScalef(1.0, 1.2, 1.0);
					drawArmRight();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	if (draw_spike || raise_Spike > -9.0)
		drawSpike();

	if (draw_bolt || boltheight > 0.0)
		drawBolt();

}

void drawHead()
{
	// draw head
	glPushMatrix();
	{
		glTranslatef(0.0, 12.0, 0.0);
		glScalef(5.0, 5.0, 5.0);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		drawBallJoint(1.0f);

		// draw eyes
		glPushMatrix();
		{
			glColor3f(0.8f, 0.7f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, eyesTexture);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluCylinder(mqo, 1.0f / 7.0f, 1.0f / 9.0f, 0.15f, slices, stacks);
		}
		glPopMatrix();

		//draw helmet top
		glPushMatrix();
		{
			glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

			glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
			glTranslatef(0.0f, 0.07f, 0.10f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(1.2f, 1.4f, 1.0f);
			gluSphere(mqo, 1.0f / 9.0f, slices, stacks);
		}
		glPopMatrix();

		//draw helmet cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.14f, -0.225f);
			glRotatef(-30.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
			{
				glTranslatef(0.08f, -0.10f, 0.26f);
				glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.12f, 0.01f, 0.015f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.08f, -0.10f, 0.26f);
				glRotatef(-50.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.12f, 0.01f, 0.015f);
				drawPlate();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.025f, 0.0485f, 0.07f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glColor3f(105 / 255.0f, 33 / 255.0f, 47 / 255.0f);
			glBindTexture(GL_TEXTURE_2D, redTexture);
			gluCylinder(mqo, 1.0f / 6.0f, 1.0f / 6.0f, 0.05f, 20, stacks);
			gluDisk(mqo, 0.0f, 1.0f / 6.0f, 20, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.05f);
				gluDisk(mqo, 0.0f, 1.0f / 6.0f, 20, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw chin cover
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.15f, -0.12f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
			glScalef(0.05f, 0.01f, 0.05f);
			drawPlate();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.16f, -0.16f);
			glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);
			glScalef(0.07f, 0.01f, 0.04f);
			drawPlate();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.13f, 0.10f, -0.06f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.12f, 0.02f, 0.06f);
			drawPlate();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(0.13f, 0.10f, -0.06f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-65.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.12f, 0.02f, 0.06f);
			drawPlate();
		}
		glPopMatrix();

		//draw back cover
		glPushMatrix();
		{
			glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -0.12f, 0.06f);
			glScalef(0.15f, 0.07f, 0.10f);
			drawPlate();
		}
		glPopMatrix();

		// draw ear cover
		glPushMatrix();
		{
			glTranslatef(0.17f, 0.05f, 0.05f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.06f, 0.03f, 0.08f);
			drawPlate();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glScalef(-1.0f, 1.0f, 1.0f);
			glTranslatef(0.17f, 0.05f, 0.05f);
			glRotatef(-55.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			glScalef(0.06f, 0.03f, 0.08f);
			drawPlate();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// draw back head cover
	glPushMatrix();
	{
		glTranslatef(0, 12.3, -0.9);
		glScalef(1.9, 2.0, 1);
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
		{
			glTranslatef(0.0, 0, 0.1);
			glScalef(0.2, 0.5, 0.1);
			drawCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.34, 0, 0);
			glRotatef(25, 0, 1, 0);
			glScalef(0.2, 0.5, 0.1);
			drawCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.34, 0, 0);
			glRotatef(-25, 0, 1, 0);
			glScalef(0.2, 0.5, 0.1);
			drawCube();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawNeck()
{
	glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
	glPushMatrix();
	{
		glTranslatef(0.0, 11.2, -0.4);

		// Draw throat
		glPushMatrix();
		{
			glRotatef(25, 1, 0, 0);

			glPushMatrix();
			{
				glRotatef(-90, 1, 0, 0);
				gluCylinder(mqo, 0.35, 0.35, 0.6, 4, stacks);
				gluDisk(mqo, 0.0, 0.35, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, -0.5, 0.0);
				glRotatef(-90, 1, 0, 0);
				gluCylinder(mqo, 0.30, 0.30, 0.5, 4, stacks);
				gluDisk(mqo, 0.0, 0.30, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, -0.9, 0.0);
				glRotatef(-90, 1, 0, 0);
				gluCylinder(mqo, 0.25, 0.25, 0.4, 4, stacks);
				gluDisk(mqo, 0.0, 0.25, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, -1.2, 0.0);
				glRotatef(-90, 1, 0, 0);
				gluCylinder(mqo, 0.21, 0.21, 0.3, 4, stacks);
				gluDisk(mqo, 0.0, 0.21, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		// draw left shoulder
		glPushMatrix();
		{
			glTranslatef(1.1, -0.28, -0.3);
			glTranslatef(-0.15, 0.0, 0.0);
			glScalef(1.8, 1.4, 1.4);
			glRotatef(90, 0, 1, 0);

			glPushMatrix();
			{
				gluCylinder(mqo, 0.5, 0.5, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.5, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.5, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.3);
				gluCylinder(mqo, 0.35, 0.35, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.35, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.35, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -0.3);
				gluCylinder(mqo, 0.35, 0.35, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.35, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.35, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// draw right shoulder
		glPushMatrix();
		{
			glTranslatef(-1.6, -0.28, -0.3);
			glTranslatef(0.15, 0.0, 0.0);
			glScalef(1.8, 1.4, 1.4);
			glRotatef(90, 0, 1, 0);

			glPushMatrix();
			{
				gluCylinder(mqo, 0.5, 0.5, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.5, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.5, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 0.3);
				gluCylinder(mqo, 0.35, 0.35, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.35, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.35, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -0.3);
				gluCylinder(mqo, 0.35, 0.35, 0.3, 6, stacks);
				gluDisk(mqo, 0.0, 0.35, 6, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.3);
					gluDisk(mqo, 0.0, 0.35, 6, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawTurbo()
{
	// draw turbo reactor in the chest
	turboRotate = turboRotate + 1;
	glPushMatrix();
	{
		glTranslatef(0.0f, 9.0f, 1.5f);
		glScalef(3.5, 3.5, 3.5);
		glRotatef(-100, 1, 0, 0);
		glRotatef(-67.0f, 1.0f, 0.0f, 0.0f);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
			gluCylinder(mqo, 1.0f / 4, 1.0f / 3, 0.1f, slices, stacks);
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluCylinder(mqo, 1.0f / 3, 1.0f / 4, 0.1f, slices, stacks);
				glTranslatef(0.0f, 0.0f, 0.1f);
				gluDisk(mqo, 0, 1.0f / 4, slices, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, turboOuterTexture);
			gluCylinder(mqo, 1.0f / 5, 1.0f / 4, 0.02f, slices, stacks);
		}
		glPopMatrix();

		glPushMatrix(); {
			glRotatef(-turboRotate, 0.0f, 0.0f, 1.0f);
			glBindTexture(GL_TEXTURE_2D, turboTexture);
			gluCylinder(mqo, 1.0f / 5, 0.07, 0.1f, slices, stacks);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, 0.1f);
			glBindTexture(GL_TEXTURE_2D, turboOuterTexture);
			gluSphere(mqo, 0.07, slices, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();

	// turbo connector
	glPushMatrix();
	{
		glTranslatef(0.0f, 9.5f, 1.2f);
		glScalef(2.5, 2.5, 2.5);
		glRotatef(-110, 1, 0, 0);
		glRotatef(-67.0f, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
		glPushMatrix();
		{
			glTranslatef(0.0f, -0.39f, 0.25f);
			glRotatef(33.0f, 1.0f, 0.0f, 0.0f);

			glPushMatrix();
			{
				glScalef(0.08f, 0.05f, 0.26f);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(0, 9.2, 0.85);
		glRotatef(14, 1, 0, 0);
		glRotatef(180, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
		gluCylinder(mqo, 0.88, 0.62, 1.1, slices, stacks);
		glPushMatrix();
		{
			glTranslatef(0, 0, 1.1);
			gluDisk(mqo, 0, 0.62, slices, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawChest()
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			// draw leg front chest plate
			glTranslatef(1.3, 9.9, 0.4);
			glRotatef(8, 0, 0, 1);
			glRotatef(25, 0, 1, 0);
			glRotatef(10, 1, 0, 0);
			glScalef(1.2, 0.6, 0.1);
			drawPlate();
		}
		glPopMatrix();

		glPushMatrix();
		{
			// draw right front chest plate
			glTranslatef(-1.3, 9.9, 0.4);
			glRotatef(-8, 0, 0, 1);
			glRotatef(-25, 0, 1, 0);
			glRotatef(10, 1, 0, 0);
			glScalef(1.2, 0.6, 0.1);
			drawPlate();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawBackArmor() {
	glPushMatrix();
	{
		glTranslatef(0, 6, -0.7);
		glScalef(2.5, 2.5, 2.5);
		glRotatef(-90, 1, 0, 0);
		//draw head cover
		glPushMatrix();
		{
			glPushMatrix(); {
				glTranslatef(-0.08f, 0.35f, 2.4f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.20f, 0.025f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix(); {
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.08f, 0.35f, 2.4f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-20.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.20f, 0.025f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.55f, 2.0f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.025f, 0.30f);
				drawPlate();
				glPushMatrix();
				{
					glTranslatef(-1.0f, 0.0f, 0.0f);
					glScalef(0.50f, 1.0f, 0.60f);
					drawPlate();

				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(-1.0f, 1.0f, 1.0f);
					glTranslatef(-1.0f, 0.0f, 0.0f);
					glScalef(0.50f, 1.0f, 0.60f);
					drawPlate();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw shoulder cover
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(-0.80f, 0.10f, 2.3f);
				glRotatef(87.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.30f, 0.025f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.40f, 0.45f, 2.0f);
				glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.13f, 0.025f, 0.38f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glPushMatrix(); {
					glTranslatef(-0.80f, 0.10f, 2.3f);
					glRotatef(87.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
					glRotatef(10.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.30f, 0.025f, 0.30f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(-0.40f, 0.45f, 2.0f);
					glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
					glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.13f, 0.025f, 0.38f);
					drawPlate();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//draw back booster
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(-0.55f, 0.5f, 1.3f);
				glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
				glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

				glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
				gluCylinder(mqo, 1.0f / 8.0f, 1.0f / 6.0f, 0.5f, 7, stacks * 2);
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
				glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.1f);
					gluDisk(mqo, 0.0f, 1.0f / 8.0f, 7, 20);
				}
				glPopMatrix();

				glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

				glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.1f);
					gluCylinder(mqo, 1.0f / 6.5f, 1.0f / 5.8f, 0.45f, 7, stacks * 2);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(-0.1f, 0.15f, 0.50f);
					glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.1f, 0.01f, 0.15f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0.0f, 0.15f, 0.60f);
					glRotatef(80.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.05f, 0.01f, 0.15f);
					drawPlate();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glPushMatrix();
				{
					glTranslatef(-0.55f, 0.5f, 1.3f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

					glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
					gluCylinder(mqo, 1.0f / 8.0f, 1.0f / 6.0f, 0.5f, 7, stacks * 2);

					glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
					glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.1f);
						gluDisk(mqo, 0.0f, 1.0f / 8.0f, 7, 20);
					}
					glPopMatrix();
					glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

					glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.1f);
						gluCylinder(mqo, 1.0f / 6.5f, 1.0f / 5.8f, 0.45f, 7, stacks * 2);
					}
					glPopMatrix();
					glPushMatrix();
					{
						glTranslatef(-0.1f, 0.15f, 0.50f);
						glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
						glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
						glScalef(0.1f, 0.01f, 0.15f);
						drawPlate();
					}
					glPopMatrix();
					glPushMatrix(); {
						glTranslatef(0.0f, 0.15f, 0.60f);
						glRotatef(80.0f, 0.0f, 1.0f, 0.0f);
						glScalef(0.05f, 0.01f, 0.15f);
						drawPlate();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();

		}
		glPopMatrix();

		//draw back connector
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(-0.3f, 0.7f, 1.3f);
				glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
				glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
				glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
				glScalef(0.5f, 1.5f, 1.0f);
				gluCylinder(mqo, 1.0f / 6.0f, 1.0f / 4.5f, 0.3f, 10, stacks * 5);

				glPushMatrix();
				{

					glColor3f(119 / 255.0f, 99 / 255.0f, 94 / 255.0f);
					glTranslatef(0.0f, 0.0f, 0.05f);
					gluDisk(mqo, 0.0f, 1.0f / 6.0f, 10, 20);
				}
				glPopMatrix();

			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glPushMatrix();
				{
					glTranslatef(-0.3f, 0.7f, 1.3f);
					glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
					glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
					glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
					glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
					glScalef(0.5f, 1.5f, 1.0f);
					gluCylinder(mqo, 1.0f / 6.0f, 1.0f / 4.5f, 0.3f, 10, stacks * 5);

					glPushMatrix();
					{

						glColor3f(119 / 255.0f, 99 / 255.0f, 94 / 255.0f);
						glTranslatef(0.0f, 0.0f, 0.05f);
						gluDisk(mqo, 0.0f, 1.0f / 6.0f, 10, 20);
					}
					glPopMatrix();

				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

	}
	glPopMatrix();
}

void drawInnerBody()
{
	glPushMatrix();
	{
		glTranslatef(0.0, 10.5, -0.76);
		glPushMatrix();
		{
			//glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
			glScalef(9.5f, 4.5f, 5.2f);
			glRotatef(90, 1, 0, 0);

			gluCylinder(mqo, 0.28f, 0.20f, 0.5f, 7, stacks * 5);

			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			gluDisk(mqo, 0.0f, 0.28f, 7, 20);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.3);
				gluDisk(mqo, 0.0f, 0.20f, 6, 20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glTranslatef(0.0, -2.22, 0.0);
			glScalef(7.0f, 1.5f, 5.0f);
			glRotatef(90, 1, 0, 0);

			gluCylinder(mqo, 0.27f, 0.20f, 0.45f, 7, stacks * 5);

			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			gluDisk(mqo, 0.0f, 0.27f, 7, 20);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.3);
				gluDisk(mqo, 0.0f, 0.20f, 6, 20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0.0, -2.895, 0.0);
			glScalef(7.0f, 1.5f, 5.0f);
			glRotatef(90, 1, 0, 0);

			gluCylinder(mqo, 0.22f, 0.18f, 0.3f, 7, stacks * 5);

			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			gluDisk(mqo, 0.0f, 0.22f, 7, 20);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.3);
				gluDisk(mqo, 0.0f, 0.18f, 6, 20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0.0, -3.345, 0.0);
			glScalef(7.0f, 1.5f, 5.0f);
			glRotatef(90, 1, 0, 0);

			gluCylinder(mqo, 0.22f, 0.18f, 0.3f, 7, stacks * 5);

			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			gluDisk(mqo, 0.0f, 0.22f, 7, 20);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.3);
				gluDisk(mqo, 0.0f, 0.18f, 6, 20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0.0, -3.795, 0.0);
			glScalef(7.0f, 1.5f, 5.0f);
			glRotatef(90, 1, 0, 0);

			gluCylinder(mqo, 0.22f, 0.18f, 0.3f, 7, stacks * 5);

			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			gluDisk(mqo, 0.0f, 0.22f, 7, 20);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.3);
				gluDisk(mqo, 0.0f, 0.18f, 6, 20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, bodyTexture);
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0.0, -4.5, 0.0);
			glScalef(5.4, 4.0, 4.0);
			glRotatef(90, 1, 0, 0);

			gluSphere(mqo, 0.22f, 5, 5);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawPelvic()
{
	glPushMatrix();
	{
		glTranslatef(0.0, 6.7, 0.35);
		glRotatef(-90, 1, 0, 0);
		glScalef(3.0, 3.0, 3.0);

		// drawFront
		glPushMatrix();
		{
			glScalef(1.0, 1.2, 0.8);
			glPushMatrix();
			{
				glScalef(0.15f, 0.10f, 0.10f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.15f, -0.25f);
				glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.35f, -0.50f);
				glRotatef(110.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// drawSide
		glPushMatrix();
		{
			glScalef(1.2, 1.0, 0.7);
			glPushMatrix();
			{
				glTranslatef(0.25f, 0.1f, 0.20f);
				glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.05f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.25f, 0.1f, 0.20f);
				glRotatef(35.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.05f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.50f, 0.3f, 0.40f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.025f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.50f, 0.3f, 0.40f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.05f, 0.025f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.40f, 0.53f, 0.40f);
				glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(0.40f, 0.53f, 0.40f);
				glRotatef(-25.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.10f, 0.08f, 0.30f);
				drawPlate();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// drawBack
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(-0.40f, 0.55f, 0.1f);
				glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.05f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.40f, 0.55f, 0.1f);
				glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.15f, 0.05f, 0.20f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.40f, 0.25f, 0.2f);
				glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.10f);
				drawPlate();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(-1.0f, 1.0f, 1.0f);
				glTranslatef(-0.40f, 0.25f, 0.2f);
				glRotatef(-70.0f, 1.0f, 0.0f, 0.0f);
				glScalef(0.10f, 0.05f, 0.10f);
				drawPlate();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// buttock plate
	glPushMatrix();
	{
		glScalef(2.2, 1.2, 1);
		glTranslatef(0, 5.7, -1.9);
		glRotatef(180, 0, 1, 0);
		glPushMatrix();
		{
			glTranslatef(0.312, 0, 0);
			glRotatef(25, 0, 1, 0);
			glScalef(0.4, 0.5, 0.1);
			drawCube();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.312, 0, 0);
			glRotatef(-25, 0, 1, 0);
			glScalef(0.4, 0.5, 0.1);
			drawCube();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawArmLeft()
{
	// fore arm
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
		float adjustX = 0.7, adjustY = -3.0;

		glTranslatef(0 - adjustX, 7.5 - adjustY, 2);

		// fore arm
		glRotatef(-rotateArmLX, 1, 0, 0);
		glRotatef(rotateArmLZ, 0, 0, 1);

		glTranslatef(adjustX, adjustY, 0);

		glPushMatrix();
		{
			glRotatef(-rotateForeArmLX, 1, 0, 0);

			// fore arm ankle
			glPushMatrix();
			{
				glTranslatef(-0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.4, 0.4, 0.6, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.6);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.65, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// fore arm bone
			glPushMatrix();
			{
				glTranslatef(0, 0, 0);
				glRotatef(-5, 1, 0, 0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(mqo, 0.15, 0.15, 2.4, slices, stacks);
			}
			glPopMatrix();

			//fore arm armour
			glPushMatrix();
			{
				glRotatef(86, 1, 0, 0);
				drawLowerArmCover();
			}
			glPopMatrix();

			// wrist
			glPushMatrix();
			{
				glTranslatef(0, -2.4, 0);
				glRotatef(-5, 1, 0, 0);
				gluCylinder(mqo, 0.25, 0.25, 0.5, slices, stacks);
				gluDisk(mqo, 0, 0.25, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.5);
					gluDisk(mqo, 0, 0.25, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// left hand
			glPushMatrix();
			{
				glTranslatef(0, -2.8, 0.25);
				glScalef(2.0, 2.0, 2.0);
				drawLeftHand();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// upper arm bone
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0, 2.5, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(mqo, 0.15, 0.15, 2.8, slices, stacks);
		}
		glPopMatrix();

		// upper arm armour
		glPushMatrix();
		{
			glTranslatef(0, 3.0, 0);
			glScalef(1.2, 1.2, 1.2);
			glRotatef(90, 1, 0, 0);
			drawLowerArmCover();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0, 2.9, 0);
			glPushMatrix();
			{
				glTranslatef(-0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.4, 0.4, 0.6, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.6);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.65, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
					glPushMatrix();
					{
						glTranslatef(0, 0, -0.35);
						gluSphere(mqo, 0.28, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

}

void drawLeftHand() {
	glPushMatrix();
	{
		glRotatef(90, 1, 0, 0);
		glScalef(-1.0f, 1.0f, 1.0f);
		glPushMatrix();
		{
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			//draw palm details
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.1f, 0.05f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(mqo, 1.0f / 8.0f, 0.0f, 0.05f, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.1f, 0.05f);
				glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(mqo, 1.0f / 8.0f, 0.0f, 0.05f, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.1f, -0.2f, 0.05f);
				glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(mqo, 1.0f / 16.0f, 1.0f / 16.0f, 0.40f, 3, stacks);
				gluDisk(mqo, 0.0f, 1.0f / 16.0f, 3, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);
					gluDisk(mqo, 0.0f, 1.0f / 16.0f, 3, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// draw hand back details
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.09f);
				glPushMatrix(); {
					glTranslatef(0.10f, -0.07f, -0.05f);
					glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.08f, 0.01f, 0.05f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix(); {
					glScalef(1.0f, -1.0f, 1.0f);
					glTranslatef(0.10f, -0.07f, -0.05f);
					glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.08f, 0.01f, 0.05f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.13f, 0.0f, -0.05f);
					glScalef(0.025f, 0.07f, 0.05f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.05f, 0.0f, -0.03f);
					glScalef(0.06f, 0.06f, 0.02f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix(); {
					glTranslatef(0.0f, -0.15f, -0.05f);
					glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.16f, 0.02f, 0.07f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix(); {
					glScalef(1.0f, -1.0f, 1.0f);
					glTranslatef(0.0f, -0.15f, -0.05f);
					glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.16f, 0.02f, 0.07f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(-0.1f, 0.0f, -0.08f);
					glScalef(0.10f, 0.10f, 0.02f);
					drawPlate();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glScalef(0.05f, 0.17f, 0.17f);
			drawPlate();
		}
		glPopMatrix();

		// draw finger
		glPushMatrix();
		{
			//draw middle finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.1f, -0.9f);

				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);

				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);

				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -0.9f);

				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.28f);
				glTranslatef(0.0f, 0.8f, -0.3f);
				glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);

				drawFinger(fingersAngle);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// draw sword
	drawSword();

	// draw sword 2
	glPushMatrix();
	{
		glDisable(GL_TEXTURE_2D);
		glTranslatef(-0.15, 0.18, 2.4);
		glRotatef(86, 1, 0, 0);
		glRotatef(90, 0, 1, 0);
		glScalef(scaleWeapon2, scaleWeapon2, scaleWeapon2);
		glScalef(0.3, 0.6, 0.3);
		drawSword2();
		glEnable(GL_TEXTURE_2D);
	}
	glPopMatrix();


	if (flying)
	{
		glPushMatrix();
		{
			glTranslatef(-1.1, 0.0, 0.0);
			glRotatef(90, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, blueFlameTexture);
			gluCylinder(mqo, 0.0, 0.2, 1.0, slices, stacks);
		}
		glPopMatrix();
	}
}

void drawSword() {
	glBindTexture(GL_TEXTURE_2D, swordTexture);

	if (draw_sword || swordLength > 0) {
		if (draw_sword && swordLength < 18)
			swordLength += 1;
		else if (!draw_sword && swordLength > 0)
			swordLength -= 1;

		glPushMatrix();
		{
			glTranslatef(-0.13, 0.12, 0.00);
			glRotatef(5, 0, 0, 1);
			glRotatef(85, 1, 0, 0);
			glScalef(1.5, 1.4, 1.0);
			glPushMatrix();
			{
				glTranslatef(0.25f, 0.0f, 0.0f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

				for (int i = 0; i < swordLength; i++) {
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, i / 7.0f);
						drawSwordBlade();
					}
					glPopMatrix();
				}
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.25f, 0.05f, 0.02f * swordLength * 2 - 0.675 / 18 * swordLength);
				gluCylinder(mqo, 1.0f / 50.0f, 1.0f / 50.0f, 0.14f * swordLength, slices, stacks);
				glTranslatef(0.0f, -0.10f, 0.0f);
				gluCylinder(mqo, 1.0f / 50.0f, 1.0f / 50.0f, 0.14f * swordLength, slices, stacks);
				glTranslatef(0.0f, 0.05f, 0.0f);
				gluCylinder(mqo, 1.0f / 50.0f, 1.0f / 50.0f, 0.14f * swordLength, slices, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[2]);
				glTranslatef(0.25f, 0.0f, 0.16f * swordLength - 0.35 / 18 * swordLength);
				glScalef(0.2f, 0.7f, 1.0f);
				gluCylinder(mqo, 1.2f / 5.0f, 0.0f, 0.35f, 4, stacks);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	else {
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[2]);
			glTranslatef(-0.13, 0.12, 0.00);
			glRotatef(5, 0, 0, 1);
			glRotatef(85, 1, 0, 0);
			glScalef(1.5, 1.4, 1.0);
			glTranslatef(0.25f, 0.0f, 0.0f);
			glScalef(0.2f, 0.7f, 1.0f);
			gluCylinder(mqo, 1.2f / 5.0f, 0.0f, 0.35f, 4, stacks);
		}
		glPopMatrix();
	}
}

void drawSwordBlade()
{
	glPushMatrix();
	{
		glScalef(0.08f, 0.005f, 0.05f);
		drawCube();
	}
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, 0.08f);
		glScalef(0.10f, 0.025f, 0.03f);
		drawCube();
	}
	glPopMatrix();
}

void drawSword2()
{
	glLineWidth(1.0f);
	// draw sword head
	glPushMatrix();
	{
		glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, -0.1);
		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(0.4, 0.1, -0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, 0.1);
		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(0.4, 0.1, 0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(0.4, 0.1, 0.1);
		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(0.4, 0.1, -0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, 0.1);
		glVertex3f(0.0, 0.7, 0.0);
		glVertex3f(-0.4, 0.1, -0.1);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.1, 0.1, -0.11);
		glVertex3f(0.0, 0.7, -0.015);
		glVertex3f(0.1, 0.1, -0.11);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(0.1, 0.1, 0.11);
		glVertex3f(0.0, 0.7, 0.015);
		glVertex3f(-0.1, 0.1, 0.11);
		glEnd();
	}
	glPopMatrix();

	// sword body
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, -0.1);
		glVertex3f(-0.4, 0.1, 0.1);
		glVertex3f(-0.7, -3.3, 0.1);
		glVertex3f(-0.7, -3.3, -0.1);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(0.4, 0.1, -0.1);
		glVertex3f(0.4, 0.1, 0.1);
		glVertex3f(0.7, -3.3, 0.1);
		glVertex3f(0.7, -3.3, -0.1);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, 0.1);
		glVertex3f(-0.7, -3.3, 0.1);
		glVertex3f(0.7, -3.3, 0.1);
		glVertex3f(0.4, 0.1, 0.1);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(-0.4, 0.1, -0.1);
		glVertex3f(-0.7, -3.3, -0.1);
		glVertex3f(0.7, -3.3, -0.1);
		glVertex3f(0.4, 0.1, -0.1);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.41, 0.11, -0.11);
		glVertex3f(-0.71, -3.31, -0.11);
		glVertex3f(-0.71, -3.31, 0.11);

		glVertex3f(-0.41, 0.11, 0.11);
		glVertex3f(0.0, 0.7, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.41, 0.11, -0.11);
		glVertex3f(0.71, -3.31, -0.11);
		glVertex3f(0.71, -3.31, 0.11);

		glVertex3f(0.41, 0.11, 0.11);
		glVertex3f(0.0, 0.7, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.41, 0.11, 0.11);
		glVertex3f(-0.71, -3.31, 0.11);
		glVertex3f(0.71, -3.31, 0.11);
		glVertex3f(0.41, 0.11, 0.11);
		glVertex3f(0.0, 0.7, 0.0);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.41, 0.11, -0.11);
		glVertex3f(-0.71, -3.31, -0.11);
		glVertex3f(0.71, -3.31, -0.11);
		glVertex3f(0.41, 0.11, -0.11);
		glVertex3f(0.0, 0.7, 0.0);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.08, 0.1, -0.12);
		glVertex3f(-0.2, -3.3, -0.12);
		glVertex3f(0.2, -3.3, -0.12);
		glVertex3f(0.1, 0.1, -0.12);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.08, 0.1, 0.12);
		glVertex3f(-0.2, -3.3, 0.12);
		glVertex3f(0.2, -3.3, 0.12);
		glVertex3f(0.08, 0.1, 0.12);
		glEnd();
	}
	glPopMatrix();

	// sword upper handle
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(-0.8, -3.3, -0.2);
		glVertex3f(-0.8, -3.3, 0.2);
		glVertex3f(0.8, -3.3, 0.2);
		glVertex3f(0.8, -3.3, -0.2);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(-0.8, -3.5, -0.2);
		glVertex3f(-0.8, -3.5, 0.2);
		glVertex3f(0.8, -3.5, 0.2);
		glVertex3f(0.8, -3.5, -0.2);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(-0.8, -3.3, 0.2);
		glVertex3f(-0.8, -3.3, -0.2);
		glVertex3f(-0.8, -3.5, -0.2);
		glVertex3f(-0.8, -3.5, 0.2);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(0.8, -3.3, 0.2);
		glVertex3f(0.8, -3.3, -0.2);
		glVertex3f(0.8, -3.5, -0.2);
		glVertex3f(0.8, -3.5, 0.2);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(0.8, -3.3, 0.2);
		glVertex3f(-0.8, -3.3, 0.2);
		glVertex3f(-0.8, -3.5, 0.2);
		glVertex3f(0.8, -3.5, 0.2);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.8, 0.7, 0.0);
		glVertex3f(0.8, -3.3, -0.2);
		glVertex3f(-0.8, -3.3, -0.2);
		glVertex3f(-0.8, -3.5, -0.2);
		glVertex3f(0.8, -3.5, -0.2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.81, -3.31, -0.21);
		glVertex3f(-0.81, -3.31, 0.21);
		glVertex3f(0.81, -3.31, 0.21);
		glVertex3f(0.81, -3.31, -0.21);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.81, -3.51, -0.21);
		glVertex3f(-0.81, -3.51, 0.21);
		glVertex3f(0.81, -3.51, 0.21);
		glVertex3f(0.81, -3.51, -0.21);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(-0.81, -3.31, 0.21);
		glVertex3f(-0.81, -3.31, -0.21);
		glVertex3f(-0.81, -3.51, -0.21);
		glVertex3f(-0.81, -3.51, 0.21);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.81, -3.31, 0.21);
		glVertex3f(0.81, -3.31, -0.21);
		glVertex3f(0.81, -3.51, -0.21);
		glVertex3f(0.81, -3.51, 0.21);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.81, -3.31, 0.21);
		glVertex3f(-0.81, -3.31, 0.21);
		glVertex3f(-0.81, -3.51, 0.21);
		glVertex3f(0.81, -3.51, 0.21);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.81, -3.31, -0.21);
		glVertex3f(-0.81, -3.31, -0.21);
		glVertex3f(-0.81, -3.51, -0.21);
		glVertex3f(0.81, -3.51, -0.21);
		glEnd();
	}
	glPopMatrix();

	// sword handle
	glPushMatrix();
	{
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslated(0.0, 0.0, 3.5);
		glColor3f(0.2, 0.1, 0.0);
		gluCylinder(mqo, 0.1f, 0.1f, 0.8f, 32, 32);

		glColor3f(0.0, 0.0, 0.3);
		gluCylinder(mqo, 0.15f, 0.15f, 0.2f, 32, 32);

		glColor3f(1.0, 0.7, 0.0);
		glTranslated(0.0, 0.0, 0.75);
		gluCylinder(mqo, 0.15f, 0.1f, 0.2f, 32, 32);
	}
	glPopMatrix();
}

void drawArmRight()
{
	// fore arm
	glPushMatrix();
	{
		glRotatef(180, 0, 1, 0);

		glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
		float adjustX = 0.7, adjustY = -3.0;

		glTranslatef(0 - adjustX, 7.5 - adjustY, 2);

		// fore arm
		glRotatef(rotateArmRX, 1, 0, 0);
		glRotatef(rotateArmRZ, 0, 0, 1);

		glTranslatef(adjustX, adjustY, 0);

		glPushMatrix();
		{
			glRotatef(rotateForeArmRX, 1, 0, 0);

			// fore arm ankle
			glPushMatrix();
			{
				glTranslatef(-0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.4, 0.4, 0.6, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.6);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.65, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// fore arm bone
			glPushMatrix();
			{
				glTranslatef(0, 0, 0);
				glRotatef(5, 1, 0, 0);
				glRotatef(90, 1, 0, 0);
				gluCylinder(mqo, 0.15, 0.15, 2.4, slices, stacks);
			}
			glPopMatrix();

			//fore arm armour
			glPushMatrix();
			{
				glRotatef(94, 1, 0, 0);
				drawLowerArmCover();
			}
			glPopMatrix();

			// wrist
			glPushMatrix();
			{
				glTranslatef(0, -2.4, -0.5);
				glRotatef(5, 1, 0, 0);
				gluCylinder(mqo, 0.25, 0.25, 0.5, slices, stacks);
				gluDisk(mqo, 0, 0.25, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.5);
					gluDisk(mqo, 0, 0.25, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// right hand
			glPushMatrix();
			{
				glTranslatef(0, -2.8, -0.25);
				glRotatef(180, 0, 1, 0);
				glScalef(2.0, 2.0, 2.0);
				drawRightHand();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// upper arm bone
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0, 2.5, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(mqo, 0.15, 0.15, 2.8, slices, stacks);
		}
		glPopMatrix();

		// upper arm armour
		glPushMatrix();
		{
			glTranslatef(0, 3.0, 0);
			glScalef(1.2, 1.2, 1.2);
			glRotatef(90, 1, 0, 0);
			drawLowerArmCover();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glTranslatef(0, 2.9, 0);
			glPushMatrix();
			{
				glTranslatef(-0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.4, 0.4, 0.6, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.6);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.3, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.65, 0, 0);
				glRotatef(90, 0, 1, 0);
				gluCylinder(mqo, 0.28, 0.28, 0.35, slices, stacks);
				gluDisk(mqo, 0, 0.28, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.35);
					gluDisk(mqo, 0, 0.28, slices, stacks);
					glPushMatrix();
					{
						glTranslatef(0, 0, -0.35);
						gluSphere(mqo, 0.28, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawRightHand() {
	glPushMatrix();
	{
		glRotatef(90, 1, 0, 0);
		glScalef(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		{
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			//draw palm details
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.1f, 0.05f);
				glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(mqo, 1.0f / 8.0f, 0.0f, 0.05f, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.1f, 0.05f);
				glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(mqo, 1.0f / 8.0f, 0.0f, 0.05f, 4, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.1f, -0.2f, 0.05f);
				glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				gluCylinder(mqo, 1.0f / 16.0f, 1.0f / 16.0f, 0.40f, 3, stacks);
				gluDisk(mqo, 0.0f, 1.0f / 16.0f, 3, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);
					gluDisk(mqo, 0.0f, 1.0f / 16.0f, 3, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// draw hand back details
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, -0.09f);
				glPushMatrix();
				{
					glTranslatef(0.10f, -0.07f, -0.05f);
					glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.08f, 0.01f, 0.05f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(1.0f, -1.0f, 1.0f);
					glTranslatef(0.10f, -0.07f, -0.05f);
					glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
					glScalef(0.08f, 0.01f, 0.05f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.13f, 0.0f, -0.05f);
					glScalef(0.025f, 0.07f, 0.05f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.05f, 0.0f, -0.03f);
					glScalef(0.06f, 0.06f, 0.02f);
					drawPlate();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.0f, -0.15f, -0.05f);
					glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.16f, 0.02f, 0.07f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(1.0f, -1.0f, 1.0f);
					glTranslatef(0.0f, -0.15f, -0.05f);
					glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
					glRotatef(-15.0f, 0.0f, 1.0f, 0.0f);
					glScalef(0.16f, 0.02f, 0.07f);
					drawPlate();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(-0.1f, 0.0f, -0.08f);
					glScalef(0.10f, 0.10f, 0.02f);
					drawPlate();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(0.05f, 0.17f, 0.17f);
			drawPlate();
		}
		glPopMatrix();
		glPushMatrix();
		{
			//draw middle finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.1f, -0.9f);
				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw index finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, 0.5f, -0.9f);
				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw ring finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.3f);
				glTranslatef(0.0f, -0.3f, -0.9f);
				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw little finger
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.25f);
				glTranslatef(0.0f, -0.6f, -0.9f);
				drawFinger(fingersAngle);
			}
			glPopMatrix();
			//draw thumb
			glPushMatrix();
			{
				glScalef(0.3f, 0.3f, -0.28f);
				glTranslatef(0.0f, 0.8f, -0.3f);
				glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
				glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
				drawFinger(fingersAngle);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glDisable(GL_TEXTURE_2D);
		glTranslatef(-0.2, 0.0, 0.0);
		glRotatef(100, 0, 1, 0);
		glRotatef(-5, 1, 0, 0);
		glScalef(scaleWeapon2, scaleWeapon2, scaleWeapon2);
		glScalef(0.7, 0.7, 0.7);
		glScalef(1.16, 1.0, 1.1);
		drawShield();
		glEnable(GL_TEXTURE_2D);
	}
	glPopMatrix();


	if (flying)
	{
		glPushMatrix();
		{
			glTranslatef(1.1, 0.0, 0.0);
			glRotatef(-90, 0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, blueFlameTexture);
			gluCylinder(mqo, 0.0, 0.2, 1.0, slices, stacks);
		}
		glPopMatrix();
	}
}

void drawShield()
{
	glPushMatrix();
	{
		GLdouble eqn[4] = { 0.0,0.0,-1.0,0.0 };
		glPushMatrix();
		{
			glClipPlane(GL_CLIP_PLANE2, eqn);
			glEnable(GL_CLIP_PLANE2);
			glColor3f(0.5, 0.5, 0.5);
			glScalef(1.0f, 1.0f, 0.02f);
			gluSphere(mqo, 2.0f, 32, 32);
			glDisable(GL_CLIP_PLANE2);
		}
		glPopMatrix();
		glClipPlane(GL_CLIP_PLANE0, eqn);
		glEnable(GL_CLIP_PLANE0);
		glColor3f(1.0, 0.0, 0.0);
		glScalef(1.0f, 1.0f, 0.3f);
		gluSphere(mqo, 2.0f, 32, 32);
		glDisable(GL_CLIP_PLANE0);

		glClipPlane(GL_CLIP_PLANE1, eqn);
		glEnable(GL_CLIP_PLANE1);
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0f, 0.0f, -0.2f);
		gluSphere(mqo, 1.9f, 32, 32);
		glDisable(GL_CLIP_PLANE1);

		glClipPlane(GL_CLIP_PLANE2, eqn);
		glEnable(GL_CLIP_PLANE2);
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0f, 0.0f, -0.6f);
		gluSphere(mqo, 1.5f, 32, 32);
		glDisable(GL_CLIP_PLANE2);

		glClipPlane(GL_CLIP_PLANE2, eqn);
		glEnable(GL_CLIP_PLANE2);
		//glColor3f(0.0, 0.0, 1.0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, shieldStarTexture);
		glTranslatef(0.0f, 0.0f, -0.65f);
		glRotatef(90, 1.00, 0.10, 0.05);
		gluSphere(mqo, 1.0f, 32, 32);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CLIP_PLANE2);
	}
	glPopMatrix();
}

void drawTripleCover() {
	glPushMatrix();
	{
		glTranslatef(-0.15f, -0.20f, 0.28f);
		glRotatef(-220.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.10f, 0.03f, 0.15f);
		drawPlate();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.22f, -0.05f, 0.28f);
		glRotatef(-260.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.10f, 0.03f, 0.15f);
		drawPlate();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-0.15f, 0.1f, 0.28f);
		glRotatef(-310.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(5.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.11f, 0.03f, 0.15f);
		drawPlate();
	}
	glPopMatrix();
}

void drawLowerArmCover() {
	glPushMatrix();
	{
		glScalef(3.0, 3.0, 3.0);

		glPushMatrix();
		{
			// drawTripleCover();
			glPushMatrix();
			{
				glTranslatef(-0.03f, -0.05f, -0.14f);
				glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.8f, 0.8f, 2.0f);
				drawTripleCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.03f, 0.0f, -0.02f);
				glScalef(0.8f, 0.8f, 1.5f);
				drawTripleCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.03f, -0.02f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(0.5f, 0.5f, 1.4f);
				drawTripleCover();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.04f, -0.02f);
				glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
				glRotatef(5.0f, 0.0f, 1.0f, 0.0f);
				glScalef(0.5f, 0.5f, 1.2f);
				drawTripleCover();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFinger(float fingerAngle) {
	glPushMatrix();
	{
		drawSkeleton(1.0f, 0.35f);
		float radius = 1.0f;
		glPushMatrix();
		{
			glScalef(0.9f, 0.7f, 0.9f);

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
				glTranslatef(-0.15f, 0.0f, 0.0f);
				glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
				gluCylinder(mqo, radius / 5.5f, radius / 5.5f, 0.50f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.5f);
					gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, -0.5f);
						gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0f, 0.0f, -0.1f); //Switch origin to prefered rotate point.
			glRotatef(fingerAngle, 0.0f, 1.0f, 0.0f); //Rotating joint.
			radius = 0.5f;
			drawHingeJoint(radius);
			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
				glScalef(1.0f, 1.0f, 1.0f);
				gluSphere(mqo, 0.12, 5, 5);
			}
			glPopMatrix();

			radius = 1.0f;
			glPushMatrix();
			{
				glTranslatef(0.0f, 0.0f, 0.1f); //Switch origin back to previous point.
				glTranslatef(0.0f, 0.0f, 0.0f); //Move to desired draw location.

				drawSkeleton(radius, 0.30f);
				glPushMatrix();
				{
					glScalef(-1.0f, 1.0f, 1.0f);
					glScalef(0.8f, 0.6f, 0.8f);

					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
						glTranslatef(-0.15f, 0.0f, 0.0f);
						glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
						gluCylinder(mqo, radius / 5.5f, radius / 5.5f, 0.50f, 4, stacks);
						glPushMatrix();
						{
							glTranslatef(0.0f, 0.0f, 0.5f);
							gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
							glPushMatrix();
							{
								glTranslatef(0.0f, 0.0f, -0.5f);
								gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
							}
							glPopMatrix();
						}
						glPopMatrix();
					}
					glPopMatrix();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f); //Switch origin to prefered rotate point.
					glRotatef(fingerAngle, 0.0f, 1.0f, 0.0f); //Rotating joint.
					radius = 0.5f;
					drawHingeJoint(radius);
					glPushMatrix();
					{
						glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
						glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
						glScalef(1.0f, 1.0f, 1.0f);

						gluSphere(mqo, 0.12, 5, 5);
					}
					glPopMatrix();
					radius = 1.0f;
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, -0.4f); //Switch origin back to previous point.
						glTranslatef(0.0f, 0.0f, 0.0f);
						drawSkeleton(radius, 0.30f);
						glPushMatrix();
						{
							glScalef(0.7f, 0.5f, 0.7f);

							glPushMatrix();
							{
								glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
								glTranslatef(-0.15f, 0.0f, 0.0f);
								glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
								gluCylinder(mqo, radius / 5.5f, radius / 5.5f, 0.50f, 4, stacks);
								glPushMatrix();
								{
									glTranslatef(0.0f, 0.0f, 0.5f);
									gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
									glPushMatrix();
									{
										glTranslatef(0.0f, 0.0f, -0.5f);
										gluDisk(mqo, 0.0f, radius / 5.5f, 4, stacks);
									}
									glPopMatrix();
								}
								glPopMatrix();
							}
							glPopMatrix();
						}
						glPopMatrix();
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawLegs()
{
	float adjustY = 6.4, adjustZ = -0.8;

	// left leg
	glPushMatrix();
	{
		glTranslatef(1.3, adjustY, adjustZ);
		glRotatef(2, 0, 0, 1);
		glRotatef(-rotateLegLX, 1, 0, 0);
		glTranslatef(0, -adjustY, -adjustZ);
		drawOneLeg(rotateLowerLegLX);
	}
	glPopMatrix();

	// right leg
	glPushMatrix();
	{
		glTranslatef(-1.3, adjustY, adjustZ);
		glRotatef(-2, 0, 0, 1);
		glRotatef(-rotateLegRX, 1, 0, 0);
		glTranslatef(0, -adjustY, -adjustZ);
		drawOneLeg(rotateLowerLegRX);
	}
	glPopMatrix();

}

void drawOneLeg(int rotateLowerLegX) {
	// foot	
	float radius = 3.0f;

	// lower leg
	glPushMatrix();
	{
		float adjustY = 2.7, adjustZ = -0.58;
		glTranslatef(0.0, adjustY, adjustZ);
		glRotatef(rotateLowerLegX, 1, 0, 0);
		glTranslatef(0.0, -adjustY, -adjustZ);

		//draw heel sole
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
			glPushMatrix();
			{
				glTranslatef(0, 0, 0.1);
				glPushMatrix();
				{
					glScalef(4, 1, 3);
					glTranslatef(0, 0, 0.1);
					glRotatef(180, 0, 1, 0);
					glRotatef(45, 0, 0, 1);
					gluCylinder(mqo, radius / 14.0f, radius / 10.0f, 0.4f, 4, stacks);
					gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.4f);;
						gluDisk(mqo, 0.0f, radius / 10.0f, 4, stacks);
					}
					glPopMatrix();

					glTranslatef(0.0f, 0.0f, -0.31f);
					gluCylinder(mqo, radius / 18.0f, radius / 14.0f, 0.3f, 4, stacks);
					gluDisk(mqo, 0.0f, radius / 18.0f, 4, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.3f);;
						gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glScalef(3, 0.8, 2.25);
					glTranslatef(0, 0.35, 0);
					glRotatef(180, 0, 1, 0);
					glRotatef(45, 0, 0, 1);
					gluCylinder(mqo, radius / 14.0f, radius / 10.0f, 0.4f, 4, stacks);
					gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.4f);;
						gluDisk(mqo, 0.0f, radius / 10.0f, 4, stacks);
					}
					glPopMatrix();

					glTranslatef(0.0f, 0.0f, -0.31f);
					gluCylinder(mqo, radius / 18.0f, radius / 14.0f, 0.3f, 4, stacks);
					gluDisk(mqo, 0.0f, radius / 18.0f, 4, stacks);
					glPushMatrix();
					{
						glTranslatef(0.0f, 0.0f, 0.3f);;
						gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glScalef(2.8, 1.6, 1);
				glTranslatef(0, 0.08, -1.17);
				glRotatef(45, 0, 0, 1);
				gluCylinder(mqo, radius / 14.0f, radius / 10.0f, 0.4f, 4, stacks);
				gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.4f);;
					gluDisk(mqo, 0.0f, radius / 10.0f, 4, stacks);
				}
				glPopMatrix();

				glTranslatef(0.0f, 0.0f, -0.31f);
				gluCylinder(mqo, radius / 18.0f, radius / 14.0f, 0.3f, 4, stacks);
				gluDisk(mqo, 0.0f, radius / 18.0f, 4, stacks);
				glPushMatrix();
				{
					glTranslatef(0.0f, 0.0f, 0.3f);;
					gluDisk(mqo, 0.0f, radius / 14.0f, 4, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			if (flying)
			{
				// foot flame
				glPushMatrix();
				{
					glTranslatef(0.0, -2.15, 0.0);
					glPushMatrix();
					{
						glRotatef(-90, 1, 0, 0);
						glBindTexture(GL_TEXTURE_2D, blueFlameTexture);
						gluCylinder(mqo, 0.0, 0.5, 2.15, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
		}
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
		// lower leg armour plate
		glPushMatrix();
		{
			glTranslatef(0, 0.7, 0);
			// front armour
			glPushMatrix();
			{
				glPushMatrix();
				{
					glTranslatef(0.0, 0.0, 0.05);
					glRotatef(-45, 1, 0, 0);
					glScalef(0.4, 0.5, 0.1);
					drawCube();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0, 0.6, 0.0);
					glScalef(0.4, 0.5, 0.1);
					drawCube();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0.0, 1.2, 0.0);
					glRotatef(10, 1, 0, 0);
					glScalef(0.4, 0.5, 0.1);
					drawCube();
				}
				glPopMatrix();
			}
			glPopMatrix();

			//right armour
			glPushMatrix();
			{
				glTranslatef(0.6, 0, -0.4);
				glRotatef(90, 0, 1, 0);

				glPushMatrix(); {
					glTranslatef(0.0, 1.2, 0.0);
					glRotatef(-20, 0, 1, 0);
					glScalef(0.4, 0.5, 0.1);
					drawCube();
				} glPopMatrix();
				glPushMatrix(); {
					glTranslatef(0.02, 0.4, -0.05);
					glRotatef(-10, 0, 1, 0);
					glScalef(0.3, 0.5, 0.1);
					drawCube();
				} glPopMatrix();
			}
			glPopMatrix();

			//left armour
			glPushMatrix();
			{
				glTranslatef(-0.6, 0, -0.4);
				glRotatef(-90, 0, 1, 0);

				glPushMatrix(); {
					glTranslatef(0.0, 1.2, 0.0);
					glRotatef(20, 0, 1, 0);
					glScalef(0.4, 0.5, 0.1);
					drawCube();
				}
				glPopMatrix();
				glPushMatrix(); {
					glTranslatef(-0.02, 0.4, -0.05);
					glRotatef(10, 0, 1, 0);
					glScalef(0.3, 0.5, 0.1);
					drawCube();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// lower leg skeleton
		glPushMatrix();
		{
			// lower leg bone
			glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
			glPushMatrix();
			{
				glTranslatef(0, 2.7, -0.7);
				glRotatef(90, 1, 0, 0);
				gluCylinder(mqo, 0.4, 0.4, 2.7, slices, stacks);
			}
			glPopMatrix();

			// lower leg gear
			glPushMatrix();
			{
				glTranslatef(-0.13, 1.2, -0.88);
				glRotatef(90, 0, 1, 0);
				glPushMatrix();
				{
					gluCylinder(mqo, 0.3, 0.3, 0.25, slices, stacks);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.24);
					gluCylinder(mqo, 0.4, 0.4, 0.2, slices, stacks);
					gluDisk(mqo, 0, 0.4, slices, stacks);
					glPushMatrix();
					{
						glTranslated(0, 0, 0.22);
						gluDisk(mqo, 0, 0.4, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0, 0, -0.22);
					gluCylinder(mqo, 0.4, 0.4, 0.2, slices, stacks);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// lower leg knee joint
			glPushMatrix();
			{
				glTranslatef(-0.13, 2.7, -0.58);
				glRotatef(90, 0, 1, 0);
				glPushMatrix();
				{
					glTranslatef(0, 0, -0.6);
					gluCylinder(mqo, 0.2, 0.2, 1.5, slices, stacks);
					gluDisk(mqo, 0, 0.2, slices, stacks);
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.8);
					gluCylinder(mqo, 0.3, 0.15, 0.2, slices, stacks);
					gluDisk(mqo, 0, 0.3, slices, stacks);
					glPushMatrix();
					{
						glTranslated(0, 0, 0.22);
						gluDisk(mqo, 0, 0.15, slices, stacks);
					}
					glPopMatrix();
				}
				glPopMatrix();
				glPushMatrix();
				{
					glTranslatef(0, 0, -0.8);
					gluCylinder(mqo, 0.15, 0.3, 0.2, slices, stacks);
					gluDisk(mqo, 0, 0.15, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			// lower leg knee cap
			glPushMatrix();
			{
				glTranslatef(0, 2.8, -0.15);
				glRotatef(25, 1, 0, 0);
				glScalef(0.4, 0.4, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// upper leg armour plate
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
		glTranslatef(0, 3.6, 0);
		// front armour
		glPushMatrix();
		{
			glPushMatrix();
			{
				glTranslatef(0.0, 0.3, 0.0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0.0, 0.85, 0.0);
				glRotatef(10, 1, 0, 0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//right armour
		glPushMatrix();
		{
			glTranslatef(0.6, 0, -0.4);
			glRotatef(90, 0, 1, 0);

			glPushMatrix(); {
				glTranslatef(0.0, 0.8, 0.0);
				glRotatef(-10, 0, 1, 0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			} glPopMatrix();
			glPushMatrix(); {
				glTranslatef(0.02, 0.2, -0.05);
				glRotatef(-2, 0, 1, 0);
				glScalef(0.3, 0.3, 0.1);
				drawCube();
			} glPopMatrix();
		}
		glPopMatrix();

		//left armour
		glPushMatrix();
		{
			glTranslatef(-0.6, 0, -0.4);
			glRotatef(-90, 0, 1, 0);

			glPushMatrix(); {
				glTranslatef(0.0, 0.8, 0.0);
				glRotatef(10, 0, 1, 0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
			glPushMatrix(); {
				glTranslatef(-0.02, 0.2, -0.05);
				glRotatef(3, 0, 1, 0);
				glScalef(0.3, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// upper leg skeleton
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, skeletonTextureArr[texCount]);
		glTranslatef(0, 2.3, 0);

		// Knee Joint
		glPushMatrix();
		{
			glTranslatef(0, 0.8, -0.7);
			gluSphere(mqo, 0.6, slices, stacks);
		}
		glPopMatrix();

		// upper leg bone
		glPushMatrix();
		{
			glTranslatef(0, 4.1, -0.8);
			glRotatef(-5, 1, 0, 0);
			glRotatef(90, 1, 0, 0);
			gluCylinder(mqo, 0.35, 0.35, 3.6, slices, stacks);
		}
		glPopMatrix();

		// upper leg ball joint
		glPushMatrix();
		{
			glTranslatef(0, 4.1, -0.8);
			gluSphere(mqo, 0.6, slices, stacks);
		}
		glPopMatrix();

		// upper leg front gear
		glPushMatrix();
		{
			glTranslatef(-0.18, 1.2, -0.88);
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
			{
				glTranslatef(0, 1.9, 0.2);
				gluCylinder(mqo, 0.4, 0.4, 0.4, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, 1.9, -0.2);
				gluCylinder(mqo, 0.4, 0.4, 0.4, slices, stacks);
				gluDisk(mqo, 0, 0.4, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 0.8);
					gluDisk(mqo, 0, 0.4, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, 1.9, 0.6);
				gluCylinder(mqo, 0.3, 0.3, 0.2, slices, stacks);
				gluDisk(mqo, 0, 0.3, slices, stacks);
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(0, 1.9, -0.4);
				gluCylinder(mqo, 0.3, 0.3, 0.2, slices, stacks);
				gluDisk(mqo, 0, 0.3, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 1.2);
					gluDisk(mqo, 0, 0.3, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0, 1.9, -0.72);
				gluCylinder(mqo, 0.2, 0.2, 1.7, slices, stacks);
				gluDisk(mqo, 0, 0.2, slices, stacks);
				glPushMatrix();
				{
					glTranslatef(0, 0, 1.7);
					gluDisk(mqo, 0, 0.2, slices, stacks);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		// upper leg knee cap
		glPushMatrix();
		{
			glTranslatef(0, 2.8, -0.15);
			glRotatef(20, 1, 0, 0);
			glScalef(0.4, 0.3, 0.1);
			drawCube();
		}
		glPopMatrix();
	}
	glPopMatrix();

	// thigh
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
		glTranslatef(0, 6.0, 0);
		glPushMatrix();
		{
			glTranslatef(0.0, 0.0, -0.1);
			glPushMatrix();
			{
				glTranslatef(0.312, 0, 0);
				glRotatef(-10, 1, 0, 0);
				glRotatef(25, 0, 1, 0);
				glScalef(0.4, 0.5, 0.1);
				drawCube();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.312, 0, 0);
				glRotatef(-10, 1, 0, 0);
				glRotatef(-25, 0, 1, 0);
				glScalef(0.4, 0.5, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0.1, -1.4);
			glRotatef(180, 0, 1, 0);
			glPushMatrix();
			{
				glTranslatef(0.312, 0, 0);
				glRotatef(5, 1, 0, 0);
				glRotatef(25, 0, 1, 0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.312, 0, 0);
				glRotatef(5, 1, 0, 0);
				glRotatef(-25, 0, 1, 0);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 0.1, 0);
			glPushMatrix();
			{
				glTranslatef(0.7, 0, -0.8);
				glRotatef(90, 0, 1, 0);
				glRotatef(-10, 0, 0, 1);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
			glPushMatrix();
			{
				glTranslatef(-0.7, 0, -0.8);
				glRotatef(-90, 0, 1, 0);
				glRotatef(10, 0, 0, 1);
				glScalef(0.4, 0.3, 0.1);
				drawCube();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawPlate() {
	glPushMatrix();
	{
		glColor3f(97 / 255.0f, 99 / 255.0f, 122 / 255.0f);

		glBindTexture(GL_TEXTURE_2D, armourTextureArr[texCount]);
		drawCube();
	}
	glPopMatrix();
}

void drawSkeleton(float radius, float skeletonLength) {
	glPushMatrix();
	{
		glColor3f(139 / 255.0f, 119 / 255.0f, 114 / 255.0f);
		gluCylinder(mqo, radius / 28, radius / 28, skeletonLength, 6, stacks);
	}
	glPopMatrix();

}

void drawBallJoint(float radius) {
	glPushMatrix();
	{
		gluSphere(mqo, radius / 25.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawHingeJoint(float radius) {
	glPushMatrix();
	{
		gluSphere(mqo, radius / 25.0f, slices, stacks);
	}
	glPopMatrix();
}

void drawCube() {
	glBegin(GL_QUADS);
	{
		// Top Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f, 1.0f);

		// Left Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, -1.0f);

		// Back Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f, -1.0f);

		// Right Face 
		glTexCoord2f(0, 0); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(1.0f, -1.0f, 1.0f);

		// Bottom Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, -1.0f);

		// Front Face 
		glTexCoord2f(0, 0); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 0); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1, 1); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0, 1); glVertex3f(-1.0f, -1.0f, 1.0f);
	}
	glEnd();
}

void drawSpike()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTexture);

	if (!draw_spike && raise_Spike > -9.0)
	{
		raise_Spike -= 0.6;
		rotateForeArmLX -= 5;
		rotateForeArmRX -= 5;
	}
	else if (raise_Spike <= 0.0)
	{
		raise_Spike += 0.6;
		rotateForeArmLX += 5;
		rotateForeArmRX += 5;
	}

	glPushMatrix();
	{
		glTranslatef(0, -1.2 + raise_Spike, 0);
		glScalef(6.0, 6.0, 6.0);

		// First Row
		glPushMatrix();
		{
			glTranslatef(1.5, 0, 2.95);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.16, 0.0, 2.0, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(1.0, 0, 2.28);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.11, 0.0, 1.8, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.5, 0, 2.38);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.08, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0, 0, 2.53);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.06, 0.0, 1.5, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.5, 0, 2.24);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.13, 0.0, 1.9, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.0, 0, 2.12);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.1, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.5, 0, 2.85);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.2, 0.0, 1.2, 20, 20);
		}
		glPopMatrix();

		// Second Row
		glPushMatrix();
		{
			glTranslatef(1.5, 0, 1.70);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.08, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(1.0, 0, 1.48);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.06, 0.0, 1.5, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.5, 0, 1.38);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.16, 0.0, 2.0, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0, 0, 1.53);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.11, 0.0, 1.8, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.5, 0, 1.44);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.13, 0.0, 1.9, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.0, 0, 1.32);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.2, 0.0, 1.2, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.5, 0, 1.65);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.1, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();

		// Third Row
		glPushMatrix();
		{
			glTranslatef(1.5, 0, 3.50);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.08, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(1.0, 0, 3.28);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.1, 0.0, 1.6, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.5, 0, 3.18);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.2, 0.0, 1.2, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(0.0, 0, 3.33);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.11, 0.0, 1.8, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-0.5, 0, 3.24);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.13, 0.0, 1.9, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.0, 0, 3.12);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.06, 0.0, 1.5, 20, 20);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslatef(-1.5, 0, 3.45);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(mqo, 0.16, 0.0, 2.0, 20, 20);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawBolt()
{
	boltRotate = boltRotate + 10;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, boltTexture);

	glPushMatrix();
	{
		glTranslatef(0.0, 11.16, 1.0);
		if (boltheight < 25 && draw_bolt)
		{
			boltheight += 0.3;
			if (rotateArmRX < 90)
				rotateArmRX += 2;
		}
		else if (boltheight > 0.0 && !draw_bolt)
		{
			boltheight -= 0.3;
			if (rotateArmRX > 0)
				rotateArmRX -= 2;
			glTranslatef(0, 0, 25);
			glRotatef(180, 1, 0, 0);
		}
		glRotatef(boltRotate, 0, 0, 1);

		gluCylinder(mqo, boltradius, boltradius, boltheight, 50, 50);
		gluDisk(mqo, 0, boltradius, slices, stacks);
		glPushMatrix();
		{
			glTranslatef(0, 0, boltheight);
			gluDisk(mqo, 0.0, boltradius, slices, stacks);
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(10.0f);
		glBegin(GL_LINE_STRIP);
		for (float z = 0.0, angle = 0; z < boltheight; z += 0.1, angle += 0.1)
		{
			glVertex3f((boltradius + 0.01) * sin(angle), (boltradius + 0.01) * cos(angle), z);
		}
		glEnd();
	}
	glPopMatrix();

}

void setPerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!switch_perspective)
	{
		gluPerspective(45 / zoom, 1, 1, 300);
	}
	else
	{
		glOrtho(-12.0, 12.0, -12.0, 12.0, 0.0, 300.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawBg()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glTranslatef(0.0, 3.77, 0.0);
		glScalef(4.0, 4.0, 4.0);
		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, earthTexture);
			glScalef(30, 1, 30);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0.1); glVertex3f(-1, -1, 1);
			glTexCoord2f(0.1, 0.1); glVertex3f(1, -1, 1);
			glTexCoord2f(0.1, 0); glVertex3f(1, -1, -1);
			glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
			glEnd();
		}
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, skyTexture);

		GLfloat ambient1[] = { 1.0, 1.0, 1.0, 0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
		glPushMatrix();
		{
			glScalef(30, 5, 30);
			glTranslated(0, -0.4, 0);
			glRotatef(75, 0, 1, 0);
			glRotatef(270, 1, 0, 0);
			gluCylinder(mqo, 1.0, 1.0, 15.0, slices, stacks);
		}
		glPopMatrix();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective();
	//glOrtho(-15.0, 15.0, -15.0, 15.0, 0.0, 150.0);	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	skyTexture = LoadTexture("textures/Sky.bmp");
	earthTexture = LoadTexture("textures/earth_spike.bmp");
	boltTexture = LoadTexture("textures/sun_texture.bmp");
	armourTexture = LoadTexture("textures/armor_texture.bmp");
	armourTexture1 = LoadTexture("textures/armor_texture_1.bmp");
	armourTexture2 = LoadTexture("textures/armor_texture_2.bmp");
	bodyTexture = LoadTexture("textures/armor_texture_3.bmp");
	skeletonTexture = LoadTexture("textures/plasma_texture.bmp");
	skeletonTexture1 = LoadTexture("textures/moon_texture.bmp");
	skeletonTexture2 = LoadTexture("textures/metal.bmp");
	swordTexture = LoadTexture("textures/stripe_texture.bmp");
	blueFlameTexture = LoadTexture("textures/boost_flame.bmp");
	redFlameTexture = LoadTexture("textures/boostFlame.bmp");
	shieldStarTexture = LoadTexture("textures/shield.bmp");

	armourTextureArr[0] = armourTexture;
	armourTextureArr[1] = armourTexture1;
	armourTextureArr[2] = armourTexture2;

	skeletonTextureArr[0] = skeletonTexture;
	skeletonTextureArr[1] = skeletonTexture1;
	skeletonTextureArr[2] = skeletonTexture2;

	eyesTexture = LoadTexture("textures/eyes_texture.bmp");
	redTexture = LoadTexture("textures/red_texture.bmp");
	turboTexture = LoadTexture("textures/reactor_turn1_texture.bmp");
	turboOuterTexture = LoadTexture("textures/reactor_outring_texture.bmp");

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDisable(GL_LIGHTING);

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

GLuint LoadTexture(char* fileName) {
	//glColor3f(1.0f, 1.0f, 1.0f);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);
	return texture;
}

//--------------------------------------------------------------------