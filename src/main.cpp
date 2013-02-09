#include "base.h"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Mesh"
#include "graphics/Model"
#include "graphics/Program"
#include "graphics/IProgram"
#include "graphics/Scene"
#include "graphics/Shader"
#include "graphics/Texture"
#include "io/Filesystem"

int main(int argc, char const *argv[])
{
	glfwInit();

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 8, 8, 8, 8, 16, 0, GLFW_WINDOW);

	glewInit();
	BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
	BK_GL_ASSERT(glDepthFunc(GL_LESS));

	glfwDisable(GLFW_MOUSE_CURSOR);
	glfwSetMousePos(0, 0);
	glfwSetMouseWheel(0);

	float vertices[] = {
	-1.0f,-1.0f,-1.0f,   0.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,

	// top
	-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,

	// front
	-1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 0.0f,

	// back
	-1.0f,-1.0f,-1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

	// left
	-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,   0.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

	// right
	 1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
	 1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,   0.0f, 0.0f
	};

	VertexFormat format = {
		VertexFormat::Data(VertexFormat::POSITION, 3, 0),
		VertexFormat::Data(VertexFormat::TEXCOORD0, 2, 3)
	};

	Bitmap *bitmap = Bitmap::fromFile("wooden-crate.jpg");
	ITexture *tex = Texture::fromBitmap(*bitmap);
	bitmap->release();

	ShaderList shader;
	shader.push_back( Shader::fromFile("default.vert", IShader::VERTEX) );
	shader.push_back( Shader::fromFile("default.frag", IShader::FRAGMENT) );

	IProgram *program = Program::create(shader);
	IMesh *mesh = Mesh::create(*program, vertices, IMesh::STATIC, format, sizeof(vertices));

	Model *dot = Model::create( mesh, program, tex );

	Model *i = Model::create( mesh, program, tex );
	i->translate(0, -4, 0);
	i->scale(1, 2, 1);

	Model *hLeft = Model::create( mesh, program, tex );
	hLeft->translate(-7, -2, 0);
	hLeft->scale(1, 4, 1);

	Model *hRight = Model::create( mesh, program, tex );
	hRight->translate(-3, -2, 0);
	hRight->scale(1, 4, 1);

	Model *hMid = Model::create( mesh, program, tex );
	hMid->translate(-5, -2, 0);

	Camera* cam = Camera::create();

	cam->setPosition(vec3(0,0,4));
	cam->setAspectRatio(800.0f/640.0f);

	Scene *scene = Scene::create(*cam);

	scene->addModel(*dot);
	scene->addModel(*i);
	scene->addModel(*hLeft);
	scene->addModel(*hMid);
	scene->addModel(*hRight);

	GLfloat rotationY = 0.0f;
	GLfloat rotationX = 0.0f;
	const float moveSpeed = 0.05f;
	double lastTime = glfwGetTime();

	const float mouseSensitivity = 0.05f;
	int mouseX, mouseY;

	const float zoomSensitivity = -2.0;

	while (glfwGetWindowParam(GLFW_OPENED)) {
		double thisTime = glfwGetTime();
		float secondsElapsed = thisTime - lastTime;

		if(glfwGetKey('S')) {
			cam->move(secondsElapsed * moveSpeed * cam->back());
		} else if(glfwGetKey('W')) {
			cam->move(secondsElapsed * moveSpeed * cam->forward());
		}

		if(glfwGetKey('A')) {
			cam->move(secondsElapsed * moveSpeed * cam->left());
		} else if(glfwGetKey('D')) {
			cam->move(secondsElapsed * moveSpeed * cam->right());
		}

		if(glfwGetKey('Y')) {
			cam->move(secondsElapsed * moveSpeed * -vec3(0,1,0));
		} else if(glfwGetKey('X')) {
			cam->move(secondsElapsed * moveSpeed * vec3(0,1,0));
		}

		if(glfwGetKey(GLFW_KEY_ESC))
			glfwCloseWindow();

		glfwGetMousePos(&mouseX, &mouseY);
		cam->pan(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
		glfwSetMousePos(0, 0);

		float fieldOfView = cam->fieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
		if(fieldOfView < 5.0f) fieldOfView = 5.0f;
		if(fieldOfView > 130.0f) fieldOfView = 130.0f;
		cam->setFieldOfView(fieldOfView);
		glfwSetMouseWheel(0);

		if(glfwGetKey('K'))
			rotationY += 0.5f;
		if(glfwGetKey('J'))
			rotationY -= 0.5f;
		if(glfwGetKey('U'))
			rotationX += 0.5f;
		if(glfwGetKey('M'))
			rotationX -= 0.5f;

		dot->translate(
			rotate(mat4(), rotationY, vec3(0,1,0)) * rotate(mat4(), rotationX, vec3(1,0,0))
		);

		scene->render(secondsElapsed);

		rotationX = rotationY = 0.0f;
	}

	scene->release();
	glfwTerminate();
	return 0;
}