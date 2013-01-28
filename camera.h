#ifndef CAMERA_H_T6GLZWCT
#define CAMERA_H_T6GLZWCT

#include "base.h"

/*!
 * \brief Camera class declaration.
 */
class Camera {
public:
	static Camera* create();
	static Camera* create(const float, const float, const float,
			const float, const float, const float, const vec3);

	float fieldOfView() const;
	void setFieldOfView(const float);

	float aspectRatio() const;
	void setAspectRatio(const float);

	mat4 matrix() const;

	void pan(const float, const float);
	mat4 orientation() const;

	void setPosition(const vec3);
	vec3 position() const;
	void move(const vec3);

	vec3 left() const;
	vec3 right() const;

	vec3 forward() const;
	vec3 back() const;

	vec3 up() const;
	vec3 down() const;

private:
	Camera();
	Camera(const float, const float, const float,
			const float, const float, const float, const vec3);
	virtual ~Camera();

	float m_fieldOfView;
	float m_aspectRatio;
	float m_nearPlane;
	float m_farPlane;
	float m_horizontalAngle;
	float m_verticalAngle;
	vec3  m_position;
};

#endif /* end of include guard: CAMERA_H_T6GLZWCT */

