#include "graphics/Scene"

#include "graphics/Model"

Scene::Scene(initializer_list<Camera*> cams, initializer_list<Model*> models) :
	m_cams(cams), m_activeCam(0), m_models(models)
{
}

Scene::~Scene()
{
}

Scene* Scene::createScene(initializer_list<Camera*> cams, initializer_list<Model*> models)
{
	BK_ASSERT(cams.size() > 0);
	BK_ASSERT(models.size() > 0);

	Scene* s = new Scene(cams, models);
	s->m_activeCam = *(cams.begin());

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
