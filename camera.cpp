#include "camera.h"

Camera::Camera() :
	m_fieldOfView(50),
	m_aspectRatio(4.0/3.0),
	m_nearPlane(0.01),
	m_farPlane(100),
	m_horizontalAngle(0),
	m_verticalAngle(0),
	m_position(0,0,1)
{
}

Camera::Camera(
	const float fieldOfView, const float aspectRatio,
	const float nearPlane, const float farPlane,
	const float horizontalAngle, const float verticalAngle,
	const vec3 position) :

	m_fieldOfView(fieldOfView),
	m_aspectRatio(aspectRatio),
	m_nearPlane(nearPlane),
	m_farPlane(farPlane),
	m_horizontalAngle(horizontalAngle),
	m_verticalAngle(verticalAngle),
	m_position(position)
{
}

Camera::~Camera()
{
}

Camera* Camera::create()
{
	return new Camera();
}

Camera* Camera::create(
	const float fieldOfView, const float aspectRatio,
	const float nearPlane, const float farPlane,
	const float horizontalAngle, const float verticalAngle,
	const vec3 position)
{
	return new Camera(fieldOfView, aspectRatio, nearPlane, farPlane,
			horizontalAngle, verticalAngle, position);
}

float Camera::aspectRatio() const
{
	return m_aspectRatio;
}

void Camera::setAspectRatio(const float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}

mat4 Camera::matrix() const
{
	mat4 m = perspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
	m *= orientation();
	m = translate(m, -m_position);
	return m;
}

void Camera::pan(const float up, const float right)
{
	m_horizontalAngle += right;
	while(m_horizontalAngle > 360.0f) m_horizontalAngle -= 360.0;
	while(m_horizontalAngle < 0.0f) m_horizontalAngle += 360.0;

	m_verticalAngle += up;
	if(m_verticalAngle > 85.0f) m_verticalAngle = 85.0f;
	if(m_verticalAngle < -85.0f) m_verticalAngle = -85.0f;
}

mat4 Camera::orientation() const
{
	mat4 o;
	o = rotate(o, m_verticalAngle, vec3(1,0,0));
	o = rotate(o, m_horizontalAngle, vec3(0,1,0));
	return o;
}

void Camera::setPosition(const vec3 position)
{
	m_position = position;
}

vec3 Camera::position() const
{
	return m_position;
}

void Camera::move(const vec3 to)
{
	m_position += to;
}

vec3 Camera::left() const
{
	return -right();
}

vec3 Camera::right() const
{
	return vec3(inverse(orientation()) * vec4(1,0,0,1));
}

vec3 Camera::forward() const
{
	return vec3(inverse(orientation()) * vec4(0,0,-1,1));
}

vec3 Camera::back() const
{
	return -forward();
}

vec3 Camera::up() const
{
	return vec3(inverse(orientation()) * vec4(0,1,0,1));
}

vec3 Camera::down() const
{
	return -up();
}

