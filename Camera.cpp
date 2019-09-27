#include "Camera.h"

void Camera::Setup(Controls &controls)
{
	this->controls = &controls;

	x = 0.0f;
	y = 0.0f;
}

void Camera::Update(float delta)
{
	bool moveLeft = controls->moveCameraLeft;
	bool moveRight = controls->moveCameraRight;
	bool moveUp = controls->moveCameraUp;
	bool moveDown = controls->moveCameraDown;

	if (!moveLeft || !moveRight)
	{
		if (moveLeft)
			x -= speed * delta;
		else if (moveRight)
			x += speed * delta;
	}
	if (!moveUp || !moveDown)
	{
		if (moveUp)
			y -= speed * delta;
		else if (moveDown)
			y += speed * delta;
	}
}

void Camera::SetCameraMoveSpeed(float speed)
{
	this->speed = speed;
}

void Camera::SetCameraPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Camera::GetX()
{
	return x;
}

float Camera::GetY()
{
	return y;
}
