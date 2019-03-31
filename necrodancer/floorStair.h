#pragma once
#include "parentObj.h"
class floorStair : public parentObj
{
private:
	string nextScene;


public:
	floorStair();
	~floorStair();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();


	void SetNextScene(string sceneName) { nextScene = sceneName; };
};

