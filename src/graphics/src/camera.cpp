#include "graphics/Camera"

#include "core/Assert"

namespace bk {

class CameraPrivate {
public:
	CameraPrivate() :
		m_fieldOfView(50), m_aspectRatio(4.0/3.0),
		m_nearPlane(0.01), m_farPlane(100),
		m_horizontalAngle(0), m_verticalAngle(0),
		m_position(0,0,1)
	{
	}

	CameraPrivate(
		const f32 fieldOfView, const f32 aspectRatio,
		const f32 nearPlane, const f32 farPlane,
		const f32 horizontalAngle, const f32 verticalAngle,
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

	~CameraPrivate()
	{
	}

	void init()
	{
	}

	f32 fieldOfView() const
	{
		return m_fieldOfView;
	}

	void setFieldOfView(const f32 fieldOfView)
	{
		BK_ASSERT(fieldOfView > 0.0f && fieldOfView < 180.0f, "fieldOfView must be in a range of (0.0, 180)");
		m_fieldOfView = fieldOfView;
	}

	f32 aspectRatio() const
	{
		return m_aspectRatio;
	}

	void setAspectRatio(const f32 aspectRatio)
	{
		m_aspectRatio = aspectRatio;
	}

	mat4 matrix(const bool rotationOnly) const
	{
		mat4 m = perspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
		m *= orientation();

		if (rotationOnly) {
			return m;
		}

		return translate(m, -m_position);
	}

	void pan(const f32 up, const f32 right)
	{
		m_horizontalAngle += right;
		while(m_horizontalAngle > 360.0f) m_horizontalAngle -= 360.0;
		while(m_horizontalAngle < 0.0f) m_horizontalAngle += 360.0;

		m_verticalAngle += up;
		if(m_verticalAngle > 85.0f) m_verticalAngle = 85.0f;
		if(m_verticalAngle < -85.0f) m_verticalAngle = -85.0f;
	}

	mat4 orientation() const
	{
		mat4 o;
		o = rotate(o, m_verticalAngle, vec3(1,0,0));
		o = rotate(o, m_horizontalAngle, vec3(0,1,0));
		return o;
	}

	void setPosition(const vec3 position)
	{
		m_position = position;
	}

	vec3 position() const
	{
		return m_position;
	}

	void move(const vec3 to)
	{
		m_position += to;
	}

	vec3 left() const
	{
		return -right();
	}

	vec3 right() const
	{
		return vec3(inverse(orientation()) * vec4(1,0,0,1));
	}

	vec3 forward() const
	{
		return vec3(inverse(orientation()) * vec4(0,0,-1,1));
	}

	vec3 back() const
	{
		return -forward();
	}

	vec3 up() const
	{
		return vec3(inverse(orientation()) * vec4(0,1,0,1));
	}

	vec3 down() const
	{
		return -up();
	}

private:
	f32 m_fieldOfView;
	f32 m_aspectRatio;
	f32 m_nearPlane;
	f32 m_farPlane;
	f32 m_horizontalAngle;
	f32 m_verticalAngle;
	vec3  m_position;
};

Camera::Camera(const string& name) :
	Managed(name, "Camera"),
	m_impl(new CameraPrivate())
{
}

Camera::Camera(
		const string& name,
	const f32 fieldOfView, const f32 aspectRatio,
	const f32 nearPlane, const f32 farPlane,
	const f32 horizontalAngle, const f32 verticalAngle,
	const vec3 position) :

	Managed(name, "Camera"),
	m_impl(new CameraPrivate(fieldOfView, aspectRatio, nearPlane,
		farPlane, horizontalAngle, verticalAngle, position))
{
}

Camera::~Camera()
{
	SAFE_DELETE(m_impl);
}

float Camera::fieldOfView() const
{
	return m_impl->fieldOfView();
}

void Camera::setFieldOfView(const f32 fieldOfView)
{
	m_impl->setFieldOfView(fieldOfView);
}

float Camera::aspectRatio() const
{
	return m_impl->aspectRatio();
}

void Camera::setAspectRatio(const f32 aspectRatio)
{
	m_impl->setAspectRatio(aspectRatio);
}

mat4
Camera::matrix(const bool rotationOnly) const
{
	return m_impl->matrix(rotationOnly);
}

void Camera::pan(const f32 up, const f32 right)
{
	m_impl->pan(up, right);
}

mat4 Camera::orientation() const
{
	return m_impl->orientation();
}

void Camera::setPosition(const vec3 position)
{
	m_impl->setPosition(position);
}

vec3 Camera::position() const
{
	return m_impl->position();
}

void Camera::move(const vec3 to)
{
	m_impl->move(to);
}

vec3 Camera::left() const
{
	return m_impl->left();
}

vec3 Camera::right() const
{
	return m_impl->right();
}

vec3 Camera::forward() const
{
	return m_impl->forward();
}

vec3 Camera::back() const
{
	return m_impl->back();
}

vec3 Camera::up() const
{
	return m_impl->up();
}

vec3 Camera::down() const
{
	return m_impl->down();
}

}

