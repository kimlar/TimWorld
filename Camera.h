#pragma once

#include "Controls.h"

class Camera
{
public:
	void Setup(Controls &controls);
	void Update(float delta);

	void SetCameraMoveSpeed(float speed);
	void SetCameraPosition(float x, float y);
	float GetX();
	float GetY();

private:
	Controls* controls;

	float speed = 600.0f;
	float x;
	float y;
};
