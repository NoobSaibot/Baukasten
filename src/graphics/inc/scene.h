#ifndef SCENE_H_WQK5IRHV
#define SCENE_H_WQK5IRHV

#include "base.h"
#include "core/Identity"

class Camera;
class Model;

/*!
 * \brief Scene class declaration.
 */
class Scene : public Identity {
public:
	static shared_ptr<Scene> create(shared_ptr<Camera>&);

	void render(const int);
	shared_ptr<Camera> activeCamera() const;
	void setActiveCamera(const int);

	void addModel(shared_ptr<Model>&);
	void addCamera(shared_ptr<Camera>&, bool makeActive = false);

	virtual ~Scene();

private:
	Scene(shared_ptr<Camera>&);

	vector<shared_ptr<Camera>> m_cams;
	shared_ptr<Camera>         m_activeCam;
	vector<shared_ptr<Model>>  m_models;
};

#endif /* end of include guard: SCENE_H_WQK5IRHV */

