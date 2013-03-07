#include "base.h"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Context"
#include "graphics/Graphics"
#include "graphics/IDisplay"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/Model"
#include "graphics/VertexFormat"
#include "io/Filesystem"
#include "model/Actor"

using namespace bk;

int main(int argc, char const *argv[])
{
	auto display = Graphics::createDisplay();
	display->init(800, 600);

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

	auto stride = 5*sizeof(float);
	auto offset = 3*sizeof(float);
	VertexFormat format = {
		VertexFormat::Data(VertexFormat::POSITION, 3, 0, stride),
		VertexFormat::Data(VertexFormat::TEXCOORD0, 2, offset, stride)
	};

	auto bitmap = Graphics::createBitmapFromFile("wooden-crate.jpg");
	auto tex = Graphics::createTextureFromBitmap( "Wooden Crate", *bitmap );
	bitmap->release();

	ShaderList shader;
	shader.push_back( Graphics::createShaderFromFile("Standard Vertex", "default.vert", ShaderType::VERTEX) );
	shader.push_back( Graphics::createShaderFromFile("Standard Fragment", "default.frag", ShaderType::FRAGMENT) );

	auto program = Graphics::createProgram("program.main", shader);
	auto mesh = Graphics::createMesh("Box", *program, vertices,
			MeshUsageHint::STATIC, format, sizeof(vertices));

	auto dot = Actor::create("actor.dot", Graphics::createModel( "Dot", mesh, program, tex ));

	auto i = Actor::create("actor.i", Graphics::createModel( "I", mesh, program, tex ));
	i->model()->translate(0, -4, 0);
	i->model()->scale(1, 2, 1);

	auto hLeft = Actor::create("actor.hLeft", Graphics::createModel( "H-Left", mesh, program, tex ));
	hLeft->model()->translate(-7, -2, 0);
	hLeft->model()->scale(1, 4, 1);

	auto hRight = Actor::create("actor.hRight", Graphics::createModel( "H-Right", mesh, program, tex ));
	hRight->model()->translate(-3, -2, 0);
	hRight->model()->scale(1, 4, 1);

	auto hMid = Actor::create("actor.hMide", Graphics::createModel( "H-Mid", mesh, program, tex ));
	hMid->model()->translate(-5, -2, 0);

	auto cam = Graphics::createCamera("Front Cam");

	cam->setPosition(vec3(0,0,4));
	cam->setAspectRatio(800.0f/640.0f);

	auto cam2 = Graphics::createCamera("camera.cam2");

	cam2->setPosition(vec3(4,0,4));
	cam2->setAspectRatio(800.0f/640.0f);

	auto scene = Actor::create("actor.scene", 0);

	scene->addChild(dot);
	scene->addChild(i);
	scene->addChild(hLeft);
	scene->addChild(hMid);
	scene->addChild(hRight);

	auto context = Graphics::createContext("context.standard");
	context->addCamera(cam);

	scene->setContext(context);

	GLfloat rotationY = 0.0f;
	GLfloat rotationX = 0.0f;
	const float moveSpeed = 0.05f;
	double lastTime = glfwGetTime();

	const float mouseSensitivity = 0.05f;
	int mouseX, mouseY;

	const float zoomSensitivity = -2.0;

	Camera* activeCam = cam;

	while (glfwGetWindowParam(GLFW_OPENED)) {
		display->clear();

		double thisTime = glfwGetTime();
		float secondsElapsed = thisTime - lastTime;

		if(glfwGetKey('G')) {
			activeCam = (activeCam == cam) ? cam2 : cam;
			scene->context()->setActiveCamera(activeCam->id());
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

		dot->model()->translate(
			rotate(mat4(), rotationY, vec3(0,1,0)) * rotate(mat4(), rotationX, vec3(1,0,0))
		);

		scene->update(secondsElapsed);
		scene->render();

		rotationX = rotationY = 0.0f;

		display->display();
	}

	cam->release();
	cam2->release();
	scene->release();
	context->release();

	glfwTerminate();
	return 0;
}
