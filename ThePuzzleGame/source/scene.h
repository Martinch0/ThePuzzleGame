#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class SceneManager;

class Scene : public CNode
{
protected:
	unsigned int m_NameHash;
	bool m_IsActive;
	bool m_IsInputActive;
	SceneManager* m_Manager;

public:
	bool IsActive() const;
	void SetActive(bool active);
	void SetName(const char* name);
	unsigned int GetNameHash() const;
	void SetManager(SceneManager* manager);
	void SetInputActive(bool active);

public:
	Scene();
	virtual ~Scene();

	//Initialise the scene
	virtual void Init();

	//Update the scene
	//deltaTime Number of seconds since last Update() call
	//alphaMul The alpha value being passed to this node. Default 1.0
	virtual void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	//Render the scene
	virtual void Render();
};

class SceneManager
{
protected:
	Scene* m_Current;
	Scene* m_Next;
	std::list<Scene*> m_Scenes;
public:
	Scene* GetCurrent();

public:
	SceneManager();
	~SceneManager();

	//Switch to a new scene.
	void SwitchTo(Scene* scene);

	//Update all scenes managed by the manager
	//deltaTime Number of seconds since last Update() call
	void Update(float deltaTime = 0.0f);

	//Render all scenes managed by the manager
	void Render();

	//Add a scene to the manager
	void Add(Scene* scene);

	//Remove the scene from the scene manager
	void Remove(Scene* scene);

	//Find a scene by name
	Scene* Find(const char* name);
};

extern SceneManager* g_pSceneManager;

#endif