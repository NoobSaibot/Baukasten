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
#include "graphics/Font"
#include "graphics/TextForm"
#include "input/Input"
#include "input/IKeyboard"
#include "input/IMouse"
#include "io/Filesystem"
#include "io/Event"
#include "io/EventManager"
#include "io/InputEvent"
#include "math/Vector3"
#include "model/Action"
#include "model/Actor"
#include "model/ActorType"
#include "model/Model"
#include "model/State"

using namespace bk;

int main(int argc, char const *argv[])
{
	auto display = Graphics::init(800, 600, "demo");

	auto bitmap = Graphics::createBitmapFromFile("wooden-crate.jpg");
	auto tex = Graphics::createTextureFromBitmap( "Wooden Crate", *bitmap );
	bitmap->release();

	auto waterBitmap = Graphics::createBitmapFromFile("water4xw1.png");
	auto texWater = Graphics::createTextureFromBitmap("texture.water", *waterBitmap);
	waterBitmap->release();

	auto ramzaBitmap = Graphics::createBitmapFromFile("ramza_tex.png");
	auto texRamza = Graphics::createTextureFromBitmap("texture.ramza", *ramzaBitmap);
	ramzaBitmap->release();

	auto program = Graphics::stockProgram(StockProgramName::MVP_BASIC_TEX);

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

	auto meshSphere = Graphics::createSphere("mesh.sphere", program, 3.0, 50, 100, Vector3(0.5, 1.0, 0.0));
	auto sphere = Model::createActor("actor.sphere",
		Graphics::createForm("form.sphere", meshSphere, program, nullptr, display ));
	sphere->form()->translate(0.0, 3.0, 0.0);
	sphere->form()->setDisplayMode(DisplayMode::WIREFRAME);

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
		InputEvent* iEvent = static_cast<InputEvent*>( e );
		auto key = iEvent->key();

		if (key == KEY_I) {
			ramza->form()->startAnimation("animation.die");
		}

		if (key == KEY_O) {
			ramza->form()->startAnimation("animation.walk_right");
		}

		return false;
	});

	auto box = Model::createActor("actor.box",
		Graphics::createForm( "form.box", meshBox, program, tex, display ));

	box->form()->translate(0, -5.5, 0);
	box->setActorType(blockType);
	box->setEventHandler([&box](Event* e) {
		InputEvent* iEvent = static_cast<InputEvent*>( e );
		auto key = iEvent->key();

		float rotationY = 0.0f;
		float rotationX = 0.0f;

		auto owner = box;

		if (key == KEY_K) {
			rotationY += 0.5f;
		}

		if (key == KEY_J) {
			rotationY -= 0.5f;
		}

		if (key == KEY_U) {
			rotationX += 0.5f;
		}

		if (key == KEY_M) {
			rotationX -= 0.5f;
		}

		owner->form()->translate(
			rotate(mat4(), rotationY, vec3(0,1,0)) * rotate(mat4(), rotationX, vec3(1,0,0))
		);

		return false;
	});

	auto surface = Model::createActor("actor.surface",
		Graphics::createForm("form.surface", meshBox, program, texWater, display ));
	surface->form()->translate(-3, -7, 0);
	surface->form()->scale(10, 0.5, 10);

	auto font = Graphics::createFont("/usr/share/fonts/corefonts/georgia.ttf", 12);
	auto debug = Model::createActor("actor.debug",
		Graphics::createTextForm("form.debug", "60 fps", font,
			Graphics::stockProgram(StockProgramName::M_BASIC_RED), display )
	);
	debug->form()->translate(0.01f, 0.92f, 0.0f);

	auto fontBeschriftung = Graphics::createFont("/usr/share/fonts/infected/INFECTED.ttf", 90);
	auto kisteBeschriftung = Model::createActor("actor.beschriftung",
		Graphics::createTextForm("form.beschriftung", "HAZARDOUS", fontBeschriftung,
			Graphics::stockProgram(StockProgramName::MVP_BASIC_RED), display )
	);

	kisteBeschriftung->form()->translate(0.1f, -5.0f, 1.0f);
	kisteBeschriftung->form()->setPolygonOffset(-1.0f, -1.0f);
	static_cast<TextForm*>(kisteBeschriftung->form())->setColor({1.0f, 0.0f, 0.0f});

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
	scene->addChild(debug);
	scene->addChild(kisteBeschriftung);
	scene->addChild(sphere);

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
			InputEvent* iEvent = static_cast<InputEvent*>( event );
			bk::Key key = iEvent->key();

			if (key == KEY_G) {
				context->setActiveCamera((activeCam->name() == "camera.front") ?  "camera.right" : "camera.front");
			}

			if (key == KEY_S) {
				context->camera()->move(moveSpeed * activeCam->back());
			} else if(key == KEY_W) {
				context->camera()->move(moveSpeed * activeCam->forward());
			}

			if (key == KEY_A) {
				context->camera()->move(moveSpeed * activeCam->left());
			} else if(key == KEY_D) {
				context->camera()->move(moveSpeed * activeCam->right());
			}

			if (key == KEY_Y) {
				context->camera()->move(moveSpeed * -vec3(0,1,0));
			} else if(key == KEY_X) {
				context->camera()->move(moveSpeed * vec3(0,1,0));
			}

			if (key == KEY_ESC) {
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
			static_cast<TextForm*>(debug->form())->setText(to_string(frameCount) + " fps");
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
