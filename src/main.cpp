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
#include "graphics/ITexture"
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

	auto tex = Texture::fromBitmap(
		"Wooden Crate", *Bitmap::fromFile("wooden-crate.jpg")
	);

	ShaderList shader;
	shader.push_back( Shader::fromFile("Standard Vertex", "default.vert", ShaderType::VERTEX) );
	shader.push_back( Shader::fromFile("Standard Fragment", "default.frag", ShaderType::FRAGMENT) );

	auto program = Program::create("Main", shader);
	auto mesh = Mesh::create("Box", *program, vertices,
			IMesh::STATIC, format, sizeof(vertices));

	auto dot = Model::create( mesh, program, tex );

	auto i = Model::create( mesh, program, tex );
	i->translate(0, -4, 0);
	i->scale(1, 2, 1);

	auto hLeft = Model::create( mesh, program, tex );
	hLeft->translate(-7, -2, 0);
	hLeft->scale(1, 4, 1);

	auto hRight = Model::create( mesh, program, tex );
	hRight->translate(-3, -2, 0);
	hRight->scale(1, 4, 1);

	auto hMid = Model::create( mesh, program, tex );
	hMid->translate(-5, -2, 0);

	auto cam = Camera::create("Front Cam");

	cam->setPosition(vec3(0,0,4));
	cam->setAspectRatio(800.0f/640.0f);

	auto cam2 = Camera::create("Right Cam");

	cam2->setPosition(vec3(4,0,4));
	cam2->setAspectRatio(800.0f/640.0f);

	auto scene = Scene::create("Die Unendlichkeit", cam);

	scene->addModel(dot);
	scene->addModel(i);
	scene->addModel(hLeft);
	scene->addModel(hMid);
	scene->addModel(hRight);

	scene->addCamera(cam2);

	GLfloat rotationY = 0.0f;
	GLfloat rotationX = 0.0f;
	const float moveSpeed = 0.05f;
	double lastTime = glfwGetTime();

	const float mouseSensitivity = 0.05f;
	int mouseX, mouseY;

	const float zoomSensitivity = -2.0;

	auto activeCam = cam;

	while (glfwGetWindowParam(GLFW_OPENED)) {
		double thisTime = glfwGetTime();
		float secondsElapsed = thisTime - lastTime;

		if(glfwGetKey('G')) {
			activeCam = (activeCam == cam) ? cam2 : cam;
			scene->setActiveCamera(activeCam->id());
		}

		if(glfwGetKey('S')) {
			activeCam->move(secondsElapsed * moveSpeed * activeCam->back());
		} else if(glfwGetKey('W')) {
			activeCam->move(secondsElapsed * moveSpeed * activeCam->forward());
		}

		if(glfwGetKey('A')) {
			activeCam->move(secondsElapsed * moveSpeed * activeCam->left());
		} else if(glfwGetKey('D')) {
			activeCam->move(secondsElapsed * moveSpeed * activeCam->right());
		}

		if(glfwGetKey('Y')) {
			activeCam->move(secondsElapsed * moveSpeed * -vec3(0,1,0));
		} else if(glfwGetKey('X')) {
			activeCam->move(secondsElapsed * moveSpeed * vec3(0,1,0));
		}

		if(glfwGetKey(GLFW_KEY_ESC))
			glfwCloseWindow();

		glfwGetMousePos(&mouseX, &mouseY);
		activeCam->pan(mouseSensitivity * mouseY, mouseSensitivity * mouseX);
		glfwSetMousePos(0, 0);

		float fieldOfView = activeCam->fieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
		if(fieldOfView < 5.0f) fieldOfView = 5.0f;
		if(fieldOfView > 130.0f) fieldOfView = 130.0f;
		activeCam->setFieldOfView(fieldOfView);
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

	glfwTerminate();
	return 0;
}
