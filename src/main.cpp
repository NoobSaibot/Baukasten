#include "core/Debug"
#include "graphics/Animation"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/IContext"
#include "graphics/Graphics"
#include "graphics/IDisplay"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/Form"
#include "graphics/VertexFormat"
#include "io/Filesystem"
#include "model/Action"
#include "model/Actor"
#include "model/ActorType"
#include "model/Model"
#include "model/State"

using namespace bk;

int main(int argc, char const *argv[])
{
	auto display = Graphics::createDisplay();
	display->init(800, 600);

	float verticesRamza[] = {
		-1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		 1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
	};

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

	auto waterBitmap = Graphics::createBitmapFromFile("water4xw1.png");
	auto texWater = Graphics::createTextureFromBitmap("texture.water", *waterBitmap);
	waterBitmap->release();

	auto ramzaBitmap = Graphics::createBitmapFromFile("ramza_tex.png");
	auto texRamza = Graphics::createTextureFromBitmap("texture.ramza", *ramzaBitmap);
	ramzaBitmap->release();

	ShaderList shader;
	shader.push_back( Graphics::createShaderFromFile("Standard Vertex", "default.vert", ShaderType::VERTEX) );
	shader.push_back( Graphics::createShaderFromFile("Standard Fragment", "default.frag", ShaderType::FRAGMENT) );

	auto program = Graphics::createProgram("program.main", shader);
	auto mesh = Graphics::createMesh("Box", *program, vertices,
		MeshUsageHint::STATIC, format, sizeof(vertices));
	auto meshRamza = Graphics::createMesh("mesh.ramza", *program, verticesRamza,
		MeshUsageHint::STATIC, format, sizeof(verticesRamza));

	auto blockType = Model::createActorType("actortype.block");
	blockType->addState(Model::createState<int>("state.height", 1));
	blockType->addState(Model::createState<int>("state.width", 1));

	auto unitType = Model::createActorType("actortype.unit");
	unitType->addState(Model::createState<int>("state.hp", 10));
	unitType->addState(Model::createState<int>("state.mp", 10));
	unitType->addState(Model::createState<int>("state.exp", 0));
	unitType->addState(Model::createState<int>("state.level", 1));

	auto ramza = Model::createActor("actor.ramza", Graphics::createForm( "form.ramza", meshRamza, program, texRamza ));
	ramza->setActorType(unitType);
	ramza->form()->translate(0, -3.5, -0.5);

	ramza->form()->addAnimation( new Animation("animation.stand", {
		Animation::Frame(0.0, 0.0, 0.07, 0.25, 1, true),
	}));

	ramza->form()->addAnimation( new Animation("animation.walk_right", {
		Animation::Frame(0.07, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.14, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.21, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.28, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.35, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.28, 0.0, 0.07, 0.25, 10),
		Animation::Frame(0.14, 0.0, 0.07, 0.25, 10),
	}));

	ramza->form()->addAnimation( new Animation("animation.die", {
		Animation::Frame(0.42, 0.0, 0.07, 0.25, 30),
		Animation::Frame(0.49, 0.0, 0.07, 0.25, 80),
		Animation::Frame(0.56, 0.0, 0.07, 0.25, 1, true),
	}));

	ramza->form()->startAnimation("animation.stand");

	auto dot = Model::createActor("actor.dot", Graphics::createForm( "form.dot", mesh, program, tex ));
	dot->form()->translate(0, -5.5, 0);
	dot->setActorType(blockType);

	auto i = Model::createActor("actor.i", Graphics::createForm( "I", mesh, program, tex ));
	i->setActorType(blockType);
	i->form()->translate(0, -4, 0);
	i->form()->scale(1, 2, 1);

	auto hLeft = Model::createActor("actor.hLeft", Graphics::createForm( "H-Left", mesh, program, tex ));
	hLeft->setActorType(blockType);
	hLeft->form()->translate(-7, -2, 0);
	hLeft->form()->scale(1, 4, 1);

	auto hRight = Model::createActor("actor.hRight", Graphics::createForm( "H-Right", mesh, program, tex ));
	hRight->form()->translate(-3, -2, 0);
	hRight->form()->scale(1, 4, 1);

	auto hMid = Model::createActor("actor.hMide", Graphics::createForm( "H-Mid", mesh, program, tex ));
	hMid->form()->translate(-5, -2, 0);

	auto surface = Model::createActor("actor.surface", Graphics::createForm("form.surface", mesh, program, texWater ));
	surface->form()->translate(-3, -7, 0);
	surface->form()->scale(10, 0.5, 10);

	auto cam = Graphics::createCamera("Front Cam");

	cam->setPosition(vec3(-3, 3, 15));
	cam->pan(15.0, 0.0);
	cam->setAspectRatio(800.0f/640.0f);

	auto cam2 = Graphics::createCamera("camera.cam2");

	cam2->setPosition(vec3(10,0,4));
	cam2->setAspectRatio(800.0f/640.0f);
	cam2->pan(0.0, -90.0);

	auto scene = Model::createActor("actor.scene", 0);

	scene->addChild(dot);
	//scene->addChild(i);
	//scene->addChild(hLeft);
	//scene->addChild(hMid);
	//scene->addChild(hRight);
	scene->addChild(surface);
	scene->addChild(ramza);

	auto context = Graphics::createContext("context.standard");
	context->addCamera(cam);
	context->addCamera(cam2, false);
	context->setOption(ContextOption::ENABLE_BLEND, true);

	scene->setContext(context);

	GLfloat rotationY = 0.0f;
	GLfloat rotationX = 0.0f;
	const float moveSpeed = 0.5f;
	double lastTime = glfwGetTime();

	const float mouseSensitivity = 0.05f;
	int mouseX, mouseY;

	const float zoomSensitivity = -2.0;

	Camera* activeCam = cam;

	Action* bla = Model::createAction("action.bla", ramza, ([]( Action* action, vector<Actor*> targets ) {
		for ( Actor* t: targets ) {
			BK_DEBUG("reduce " << t->name() << "s hp by 10!");
		}
		return true;
	}));

	ramza->addAction(bla);
	ramza->invokeAction("action.bla");
	ramza->runActions();

	while (glfwGetWindowParam(GLFW_OPENED)) {
		display->clear();

		double thisTime = glfwGetTime();
		float secondsElapsed = thisTime - lastTime;

		if(glfwGetKey('G')) {
			activeCam = (activeCam == cam) ? cam2 : cam;
			scene->context()->setActiveCamera(activeCam->id());
		}

		if(glfwGetKey('S')) {
			activeCam->move(moveSpeed * activeCam->back());
		} else if(glfwGetKey('W')) {
			activeCam->move(moveSpeed * activeCam->forward());
		}

		if(glfwGetKey('A')) {
			activeCam->move(moveSpeed * activeCam->left());
		} else if(glfwGetKey('D')) {
			activeCam->move(moveSpeed * activeCam->right());
		}

		if(glfwGetKey('Y')) {
			activeCam->move(moveSpeed * -vec3(0,1,0));
		} else if(glfwGetKey('X')) {
			activeCam->move(moveSpeed * vec3(0,1,0));
		}

		if(glfwGetKey(GLFW_KEY_ESC))
			glfwCloseWindow();

		if (glfwGetKey('I')) {
			ramza->form()->startAnimation("animation.die");
		} else if (glfwGetKey('O')) {
			ramza->form()->startAnimation("animation.walk_right");
		}

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

		dot->form()->translate(
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
