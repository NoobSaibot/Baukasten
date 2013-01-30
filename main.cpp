#include "base.h"
#include "bitmap.h"
#include "camera.h"
#include "scene.h"
#include "shader.h"
#include "program.h"
#include "filesystem.h"
#include "mesh.h"
#include "model.h"
#include "texture.h"

int main(int argc, char const *argv[])
{
	glfwInit();

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(800, 600, 8, 8, 8, 8, 16, 0, GLFW_WINDOW);

	glewInit();
	BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
	BK_GL_ASSERT(glDepthFunc(GL_LESS));

	glfwDisable(GLFW_MOUSE_CURSOR);
	glfwSetMousePos(0, 0);
	glfwSetMouseWheel(0);

	Shaders shader;
	shader.push_back( Shader::fromFile("default.vert", GL_VERTEX_SHADER) );
	shader.push_back( Shader::fromFile("default.frag", GL_FRAGMENT_SHADER) );

	Program *p = Program::createProgram(shader);

	float vertices[] = {
		 0.0f, 0.8f, 0.0f, 0.5f, 0.0f,
		-0.8f,-0.8f, 0.0f, 0.0f, 1.0f,
		 0.8f,-0.8f, 0.0f, 1.0f, 1.0f,
	};

	VertexFormat format = {
		VertexFormat::Data(VertexFormat::POSITION, 3, 0),
		VertexFormat::Data(VertexFormat::TEXCOORD0, 2, 3)
	};

	Bitmap *bitmap = Bitmap::fromFile("wooden-crate.jpg");

	Model *model = Model::createModel(
		Mesh::createMesh(vertices, Mesh::STATIC, format, sizeof(vertices)),
		p,
		Texture::fromBitmap(bitmap)
	);

	while(glfwGetWindowParam(GLFW_OPENED)) {
		BK_GL_ASSERT(glClearColor(0, 0, 0, 1)); // black
		BK_GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		model->render(0);

		BK_GL_ASSERT(glfwSwapBuffers());
	}

	glfwTerminate();
	return 0;
}
