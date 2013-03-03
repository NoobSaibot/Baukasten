#ifndef SCENE_H_WQK5IRHV
#define SCENE_H_WQK5IRHV

#include "base.h"
#include "core/Identity"

namespace bk {

class Camera;
class Model;

class Scene : public Identity {
public:
	static shared_ptr<Scene> create(const string&, shared_ptr<Camera>&);

	void render(const int);
	shared_ptr<Camera> activeCamera() const;
	void setActiveCamera(const int);

	void addModel(Model*);
	void addCamera(shared_ptr<Camera>&, bool makeActive = false);

	virtual ~Scene();

private:
	Scene(const string&, shared_ptr<Camera>&);

	vector<shared_ptr<Camera>> m_cams;
	shared_ptr<Camera>         m_activeCam;
	vector<Model*>  m_models;
};

}

#endif /* end of include guard: SCENE_H_WQK5IRHV */

