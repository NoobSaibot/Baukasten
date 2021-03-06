#include "core/Debug"
#include "graphics/Animation"
#include "graphics/Bitmap"
#include "graphics/Camera"
#include "graphics/Context"
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
#include "model/Action"
#include "model/Actor"
#include "model/ActorType"
#include "model/Model"
#include "model/State"

using namespace bk;

int main(int argc, char const *argv[])
{
	auto display = Graphics::init(1680, 1050, true, "demo");

	auto footballBitmap = Graphics::createBitmapFromFile("football.jpg");
	auto texFootball = Graphics::createTextureFromBitmap("texture.football", *footballBitmap);
	footballBitmap->release();

	auto ramzaBitmap = Graphics::createBitmapFromFile("ramza_tex.png");
	auto texRamza = Graphics::createTextureFromBitmap("texture.ramza", *ramzaBitmap);
	ramzaBitmap->release();

	auto program = Graphics::stockProgram(StockProgramName::MVP_BASIC_TEX);
	auto pColor  = Graphics::stockProgram(StockProgramName::MVP_BASIC_COL);
	auto pSkyBox = Graphics::stockProgram(StockProgramName::SKYBOX);

	auto meshRamza = Graphics::createMesh("mesh.ramza");
	meshRamza->setProgram(program);
	meshRamza->setVertices(18, 3, {
		-1.0f,-1.0f, 0.0f, 1.0f,-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	});

	auto meshSphere = Graphics::createSphere("mesh.sphere", program, 1.0, 50, 100, vec3(0.5, 1.0, 0.0));
	auto sphere = Model::createActor("actor.sphere",
		Graphics::createForm("form.sphere", meshSphere, program, texFootball, display ));
	sphere->form()->translate(0.0, 3.0, 0.0);

	sphere->setEventHandler([&sphere](Event* e) {
		InputEvent* iEvent = static_cast<InputEvent*>( e );
		auto key = iEvent->key();

		float rotationY = 0.0f;
		float rotationX = 0.0f;

		auto owner = sphere;

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

	auto meshTorus = Graphics::createTorus("mesh.torus", pColor, 2.0, 1.5, 40, 40, vec3(0.5, 1.0, 0.0));
	auto torus = Model::createActor("actor.torus",
		Graphics::createForm("form.torus", meshTorus, pColor, nullptr, display ));
	torus->form()->translate(-5.0, 3.0, 0.0);
	torus->form()->setDisplayMode(DisplayMode::WIREFRAME);

	auto meshSkyBox = Graphics::createCube("mesh.skyBox", pSkyBox, 100.0);
	auto texSkyBox  = Graphics::createSkyBox("texture.skyBox", "pos_x.tga", "neg_x.tga",
		"pos_y.tga", "neg_y.tga", "pos_z.tga", "neg_z.tga");
	auto skyBox = Model::createActor("actor.skyBox",
		Graphics::createForm("form.skyBox", meshSkyBox, pSkyBox, texSkyBox, display ));
	skyBox->form()->setOption(GraphicsOption::CULLING, false);
	skyBox->form()->setOption(GraphicsOption::ROTATION_MATRIX, true);

	meshRamza->setTexture(12, 2, {
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
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
		Animation::Frame(0.0, 0.75, 0.07, 0.25, 1, true),
	}));

	ramza->form()->addAnimation( new Animation("animation.walk_right", {
		//               x     y   width height duration
		Animation::Frame(0.07, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.14, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.21, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.28, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.35, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.28, 0.75, 0.07, 0.25, 10),
		Animation::Frame(0.14, 0.75, 0.07, 0.25, 10),
	}));

	ramza->form()->addAnimation( new Animation("animation.die", {
		Animation::Frame(0.42, 0.75, 0.07, 0.25, 30),
		Animation::Frame(0.49, 0.75, 0.07, 0.25, 80),
		Animation::Frame(0.56, 0.75, 0.07, 0.25, 1, true),
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

	auto font = Graphics::createFont("/usr/share/fonts/corefonts/georgia.ttf", 12);
	auto debug = Model::createActor("actor.debug",
		Graphics::createTextForm("form.debug", "60 fps", font,
			Graphics::stockProgram(StockProgramName::M_BASIC_RED), display )
	);
	debug->form()->translate(0.01f, 0.92f, 0.0f);

	auto cam = Graphics::createCamera("camera.front");

	cam->setPosition(vec3(-3, 3, 15));
	cam->pan(15.0, 0.0);
	cam->setAspectRatio((f32)display->width() / (f32)display->height());

	auto scene = Model::createActor("actor.scene", 0);
	scene->setInput(Input::createInput("input.default"));

	EventManager::instance().subscribe("event.keyPressed", ramza);
	EventManager::instance().subscribe("event.keyPressed", sphere);

	scene->addChild(skyBox);
	scene->addChild(ramza);
	scene->addChild(sphere);
	scene->addChild(debug);
	scene->addChild(torus);

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

	scene->setContext(context);

	double lastTime = glfwGetTime();
	double pastTime = lastTime;
	unsigned int frameCount = 0;

	const float zoomSensitivity = -2.0;

	Camera* activeCam = cam;

	display->setBackgroundColor(0.0f, 0.0f, 0.0f);
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
	scene->release();
	context->release();

	glfwTerminate();
	return 0;
}
