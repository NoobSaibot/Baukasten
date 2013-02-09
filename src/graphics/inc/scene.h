#ifndef SCENE_H_WQK5IRHV
#define SCENE_H_WQK5IRHV

#include "base.h"
#include "core/Managed"

class Camera;
class Model;

/*!
 * \brief Scene class declaration.
 */
class Scene : public Managed {
public:
	static Scene* createScene(Camera&);

	void render(const int);
	Camera* activeCamera() const;

	void addModel(Model&);
	void addCamera(Camera&, bool);

private:
	Scene(Camera&);
	virtual ~Scene();

	vector<Camera*> m_cams;
	Camera*         m_activeCam;
	vector<Model*>  m_models;
};

#endif /* end of include guard: SCENE_H_WQK5IRHV */

