#include "OpenGLWrapper.h"


void (*displayFunction)(unsigned int*);
void (*displayTextFunction)();

GLuint textureID;
GLuint textureBufferID;
GLuint objectsBufferID;

struct cudaGraphicsResource* cudaTextureBuffer;
struct cudaGraphicsResource* cudaObjectsBuffer;

int g_window_width;
int g_window_height;

ProcessorType processorType = CPU;

void textDisplay()
{

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);

	displayTextFunction();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

}

void display()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	//glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	// Select the appropriate buffer
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textureBufferID);
	// Select the appropriate texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Make a texture from the buffer
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_window_width, g_window_height,
		GL_BGRA, GL_UNSIGNED_BYTE, NULL);

	if (processorType == CPU)
	{
		GLubyte* ptr = (GLubyte*)(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
		unsigned int* dst = (unsigned int*)ptr;

		displayFunction(dst);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER); // release pointer to mapping buffer
	}
	else
	{

		unsigned int *out_data;
		size_t num_bytes;

		cudaGraphicsMapResources(1, &cudaTextureBuffer, 0);
		cudaGraphicsResourceGetMappedPointer((void **)&out_data, &num_bytes,
			cudaTextureBuffer);

		displayFunction(out_data);

		cudaGraphicsUnmapResources(1, &cudaTextureBuffer, 0);
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glViewport(0, 0, g_window_width, g_window_height);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.5);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	textDisplay();
	glutSwapBuffers(); glutPostRedisplay();
}


inline void Engine::OpenGLWrapper::initializeCuda()
{
	checkCudaErrors(cudaGLSetGLDevice(0));
	// Generate a buffer ID
	checkCudaErrors(cudaGraphicsGLRegisterBuffer(&cudaTextureBuffer, textureBufferID, cudaGraphicsMapFlagsWriteDiscard));
}

void Engine::OpenGLWrapper::updateObjectsAtCudaMemory(std::function<void(float*)>cudaUpdate)
{
	cudaGraphicsMapResources(1, &cudaObjectsBuffer, 0);
	size_t num_bytes2;
	float* objects;
	cudaGraphicsResourceGetMappedPointer((void**)&objects, &num_bytes2, cudaObjectsBuffer);

	cudaUpdate(objects);
	//delete objects may be necessary
}

void Engine::OpenGLWrapper::unMapObjects()
{
	cudaGraphicsUnmapResources(1, &cudaObjectsBuffer, 0);
}


Engine::OpenGLWrapper::OpenGLWrapper(int window_width_i, int window_heigt_i)
{
	this->window_width = window_width_i;
	this->window_height = window_heigt_i;

	g_window_width = this->window_width;
	g_window_height = this->window_height;

	char fakeParam[] = "fake";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;

	// Create GL context
	glutInit(&fakeargc, fakeargv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(window_width_i, window_heigt_i);
	glutCreateWindow("NginR");

	// initialize necessary OpenGL extensions
	glewInit();

	glClearColor(1.0, 0.1, 0.5, 1.0);
	glDisable(GL_DEPTH_TEST);
	// viewport
	glViewport(0, 0, window_width_i, window_heigt_i);

	// projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)window_width_i / (GLfloat)window_heigt_i, 0.1f, 10.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// register callbacks
	glutDisplayFunc(display);

	glGenBuffers(1, &textureBufferID);
	// Make this the current UNPACK buffer (OpenGL is state-based)
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textureBufferID);
	// Allocate data for the buffer. 4-channel 8-bit image
	glBufferData(GL_PIXEL_UNPACK_BUFFER, window_width * window_height * 4,
		NULL, GL_DYNAMIC_COPY);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);
	// Generate a texture ID
	glGenTextures(1, &textureID);
	// Make this the current texture (remember that GL is state-based)
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Allocate the texture memory. The last parameter is NULL since we only
	// want to allocate memory, not initialize it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, window_width_i, window_heigt_i, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, NULL);
	// Must set the filter mode, GL_LINEAR enables interpolation when scaling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Engine::OpenGLWrapper::setMainLoop(void(*fnc)(unsigned int*))
{
	displayFunction = fnc;
}

void Engine::OpenGLWrapper::setTextDisplayFunction(void(*fnc)())
{
	displayTextFunction = fnc;
}

void Engine::OpenGLWrapper::changeProcessorType(ProcessorType type)
{
	if (processorType == type)
		return;
	processorType = type;
}

void Engine::OpenGLWrapper::startMainLoop()
{
	glutMainLoop();
}

void Engine::OpenGLWrapper::setKeyboardEvents(void(*fnc)(unsigned char key, int _x, int _y))
{
	glutKeyboardFunc(fnc);
}

void Engine::OpenGLWrapper::setCleanupFunction(void(*fnc)())
{
	glutCloseFunc(fnc);
}

void Engine::OpenGLWrapper::copyObjectsFromCuda(float* objectArr, int size)
{
}

inline void Engine::OpenGLWrapper::initializeCudaMemory(int size)
{
	glGenBuffers(1, &objectsBufferID);
	// Make this the current UNPACK buffer (OpenGL is state-based)
	glBindBuffer(GL_ARRAY_BUFFER, objectsBufferID);
	// Allocate data for the buffer. 4-channel 8-bit image
	glBufferData(GL_ARRAY_BUFFER, size,
		NULL, GL_DYNAMIC_COPY);
	checkCudaErrors(cudaGraphicsGLRegisterBuffer(&cudaObjectsBuffer, objectsBufferID, cudaGraphicsMapFlagsWriteDiscard));
}

void Engine::OpenGLWrapper::copyObjectsToCuda(float* objectArr, int size)
{
	initializeCudaMemory(size);
	GLfloat* obj = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (int i = 0; i < size;i++)
		obj[i] = objectArr[i];
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
