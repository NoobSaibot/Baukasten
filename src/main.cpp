#include "core/Debug"
#include "graphics/Animation"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/IContext"
#include "graphics/Graphics"
#include "graphics/IDisplay"
#include "graphics/IProgram"
#include "graphics/IMesh"
#include "graphics/ITexture"
#include "graphics/IForm"
#include "input/Input"
#include "input/IKeyboard"
#include "input/IMouse"
#include "io/Filesystem"
#include "io/Event"
#include "io/EventManager"
#include "math/Vector3"
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

	auto meshBox = Graphics::createMesh("mesh.box");

	meshBox->setProgram(program);
	meshBox->setVertices(108, 3, {
		-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f, -1.0f, 1.0f,-1.0f, -1.0f,-1.0f,-1.0f, -1.0f,-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f, 1.0f,
	});

	meshBox->setTexture(72, 2, {
		0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	});

	auto meshRamza = Graphics::createMesh("mesh.ramza");

	meshRamza->setProgram(program);
	meshRamza->setVertices(18, 3, {
		-1.0f,-1.0f, 0.0f, 1.0f,-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	});

	meshRamza->setTexture(12, 2, {
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	});

	auto blockType = Model::createActorType("actortype.block");
	blockType->addState(Model::createState<int>("state.height", 1));
	blockType->addState(Model::createState<int>("state.width", 1));

	auto unitType = Model::createActorType("actortype.unit");
	unitType->addState(Model::createState<int>("state.hp", 10));
	unitType->addState(Model::createState<int>("state.mp", 10));
	unitType->addState(Model::createState<int>("state.exp", 0));
	unitType->addState(Model::createState<int>("state.level", 1));

	auto ramza = Model::createActor("actor.ramza",
		Graphics::createForm( "form.ramza", meshRamza, program, texRamza, display ));

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

	ramza->setEventHandler([&ramza](Event* e) {
		std::stringstream s;
		e->serialize(s);
		string key = s.str();

		if (key == "I") {
			ramza->form()->startAnimation("animation.die");
		}

		if (key == "O") {
			ramza->form()->startAnimation("animation.walk_right");
		}

		return false;
	});

	auto box = Model::createActor("actor.box",
		Graphics::createForm( "form.box", meshBox, program, tex, display ));

	box->form()->translate(0, -5.5, 0);
	box->setActorType(blockType);
	box->setEventHandler([&box](Event* event) {
			float rotationY = 0.0f;
			float rotationX = 0.0f;

			auto owner = box;
			stringstream s;
			event->serialize(s);
			string key = s.str();

			if (key == "K") {
				rotationY += 0.5f;
			}
			if (key == "J") {
				rotationY -= 0.5f;
			}
			if (key == "U") {
				rotationX += 0.5f;
			}

			if (key == "M") {
				rotationX -= 0.5f;
			}

			owner->form()->translate(
				rotate(mat4(), rotationY, vec3(0,1,0)) * rotate(mat4(), rotationX, vec3(1,0,0))
			);

			return false;
		}
	);

	auto surface = Model::createActor("actor.surface",
		Graphics::createForm("form.surface", meshBox, program, texWater, display ));
	surface->form()->translate(-3, -7, 0);
	surface->form()->scale(10, 0.5, 10);

	auto font = Graphics::createFont("/usr/share/fonts/corefonts/georgia.ttf", 20);
	auto text = Model::createActor("actor.text",
		Graphics::createTextForm("form.text", "hallo", font, program, display ));
	(static_cast<TextForm*>(text->form()))->setColor(Vector3(1.0f, 0.0, 0.0));
	//text->form()->scale(0.2, 0.2, 1);

	auto cam = Graphics::createCamera("camera.front");

	cam->setPosition(vec3(-3, 3, 15));
	cam->pan(15.0, 0.0);
	cam->setAspectRatio(800.0f/640.0f);

	auto cam2 = Graphics::createCamera("camera.right");

	cam2->setPosition(vec3(10,0,4));
	cam2->setAspectRatio(800.0f/640.0f);
	cam2->pan(0.0, -90.0);

	auto scene = Model::createActor("actor.scene", 0);
	scene->setInput(Input::createInput("input.default"));

	EventManager::instance().subscribe("event.keyPressed", ramza);
	EventManager::instance().subscribe("event.keyPressed", box);

	scene->addChild(box);
	scene->addChild(surface);
	scene->addChild(ramza);
	scene->addChild(text);

	scene->addAction(
		Model::createAction("action.trackMouse", scene, ([] (Action *action, vector<Actor*> targets) {
			auto owner = action->owner();
			auto context = owner->context();
			auto mouse = owner->input()->mouse();
			const float mouseSensitivity = 0.05f;
			int x, y;

			mouse->position(&x, &y);
			context->camera()->pan(mouseSensitivity * y, mouseSensitivity * x);
			mouse->setPosition(0, 0);

			return false;
		}))
	);

	EventManager::instance().subscribe("event.keyPressed", scene);
	scene->setEventHandler([&scene, &display](Event* event) {
			const float moveSpeed = 0.5f;

			auto owner = scene;
			auto context = owner->context();
			auto activeCam = context->camera();
			stringstream s;
			event->serialize(s);
			int key = (int)(*(s.str().c_str()));

			if (key == 'G') {
				context->setActiveCamera((activeCam->name() == "camera.front") ?  "camera.right" : "camera.front");
			}

			if (key == 'S') {
				context->camera()->move(moveSpeed * activeCam->back());
			} else if(key == 'W') {
				context->camera()->move(moveSpeed * activeCam->forward());
			}

			if (key == 'A') {
				context->camera()->move(moveSpeed * activeCam->left());
			} else if(key == 'D') {
				context->camera()->move(moveSpeed * activeCam->right());
			}

			if (key == 'Y') {
				context->camera()->move(moveSpeed * -vec3(0,1,0));
			} else if(key == 'X') {
				context->camera()->move(moveSpeed * vec3(0,1,0));
			}

			if (key == 50) {
				display->exit();
			}

			return false;
		}
	);

	scene->invokeAction("action.trackMouse");

	auto context = Graphics::createContext("context.standard");
	context->addCamera(cam);
	context->addCamera(cam2, false);
	context->setOption(GraphicsOption::BLEND, true);
	context->setOption(GraphicsOption::CULLING, true);

	scene->setContext(context);

	double lastTime = glfwGetTime();
	double pastTime = lastTime;
	unsigned int frameCount = 0;

	const float zoomSensitivity = -2.0;

	Camera* activeCam = cam;

	display->setBackgroundColor(1.0f, 1.0f, 1.0f);
	while (glfwGetWindowParam(GLFW_OPENED)) {
		display->clear();

		double thisTime = glfwGetTime();
		float secondsElapsed = thisTime - lastTime;

		// framerate berechnen
		if ((thisTime - pastTime) >= 1.0) {
			pastTime = thisTime;
			BK_DEBUG("fps: " << frameCount);
			frameCount = 0;
		}
		frameCount++;

		float fieldOfView = activeCam->fieldOfView() + zoomSensitivity * (float)glfwGetMouseWheel();
		if(fieldOfView < 5.0f) fieldOfView = 5.0f;
		if(fieldOfView > 130.0f) fieldOfView = 130.0f;
		activeCam->setFieldOfView(fieldOfView);
		glfwSetMouseWheel(0);

		scene->update(secondsElapsed);
		scene->runActions();
		scene->render();

		display->display();
	}

	cam->release();
	cam2->release();
	scene->release();
	context->release();

	glfwTerminate();
	return 0;
}
