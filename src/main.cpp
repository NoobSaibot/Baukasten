#include "base.h"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Context"
#include "graphics/Display"
#include "graphics/IDisplay"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/Mesh"
#include "graphics/Model"
#include "graphics/Program"
#include "graphics/Scene"
#include "graphics/Shader"
#include "graphics/Texture"
#include "io/Filesystem"
#include "model/Actor"

using namespace bk;

int main(int argc, char const *argv[])
{
	auto display = Display::create();
	display->init();

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

	auto program = Graphics::createProgram("program.main", shader);
	auto mesh = Graphics::createMesh("Box", *program, vertices,
			MeshUsageHint::STATIC, format, sizeof(vertices));

	auto dot = Actor::create("actor.dot", Model::create( "Dot", mesh, program, tex ));

	auto i = Actor::create("actor.i", Model::create( "I", mesh, program, tex ));
	i->model()->translate(0, -4, 0);
	i->model()->scale(1, 2, 1);

	auto hLeft = Actor::create("actor.hLeft", Model::create( "H-Left", mesh, program, tex ));
	hLeft->model()->translate(-7, -2, 0);
	hLeft->model()->scale(1, 4, 1);

	auto hRight = Actor::create("actor.hRight", Model::create( "H-Right", mesh, program, tex ));
	hRight->model()->translate(-3, -2, 0);
	hRight->model()->scale(1, 4, 1);

	auto hMid = Actor::create("actor.hMide", Model::create( "H-Mid", mesh, program, tex ));
	hMid->model()->translate(-5, -2, 0);

	auto cam = Camera::create("Front Cam");

	cam->setPosition(vec3(0,0,4));
	cam->setAspectRatio(800.0f/640.0f);

	auto cam2 = Camera::create("camera.cam2");

	cam2->setPosition(vec3(4,0,4));
	cam2->setAspectRatio(800.0f/640.0f);

	auto scene = Actor::create("actor.scene", 0);

	scene->addChild(dot);
	scene->addChild(i);
	scene->addChild(hLeft);
	scene->addChild(hMid);
	scene->addChild(hRight);

	auto context = Context::create();
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
