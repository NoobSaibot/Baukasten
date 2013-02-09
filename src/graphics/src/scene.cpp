#include "graphics/Scene"

#include "graphics/Model"

Scene::Scene(Camera& cam) :
	m_cams({&cam}), m_activeCam(&cam)
{
}

Scene::~Scene()
{
}

Scene* Scene::create(Camera& cam)
{
	Scene* s = new Scene(cam);
	return s;
}

void Scene::render(const int time)
{
	BK_GL_ASSERT(glClearColor(0, 0, 0, 1));
	BK_GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	for ( Model* m: m_models ) {
		m->render(*m_activeCam, time);
	}
	BK_GL_ASSERT(glfwSwapBuffers());
}

Camera* Scene::activeCamera() const
{
	return m_activeCam;
}

void
Scene::addModel(Model& model)
{
	m_models.push_back(&model);
}

void
Scene::addCamera(Camera& cam, bool makeActive)
{
	m_cams.push_back(&cam);
	if (makeActive) {
		m_activeCam = &cam;
	}
}
