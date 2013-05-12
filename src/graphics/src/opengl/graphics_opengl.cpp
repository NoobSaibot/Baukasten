#include "graphics/inc/opengl/graphics_opengl.h"

#include "graphics/Graphics"
#include "graphics/IMesh"
#include "graphics/IProgram"

#include "graphics/inc/opengl/assert_opengl.h"

namespace bk {

static IProgram* s_mBasicRed     = nullptr;
static IProgram* s_mvpBasicCol   = nullptr;
static IProgram* s_mvpBasicTex   = nullptr;
static IProgram* s_mvpBasicRed   = nullptr;
static IProgram* s_skyBox        = nullptr;

static IProgram*
createStockProgram(const string& name, const string& vShader, const string& fShader)
{
	ShaderList shader;
	shader.push_back( Graphics::createShaderFromSource("v."+name, vShader, ShaderType::VERTEX) );
	shader.push_back( Graphics::createShaderFromSource("f."+name, fShader, ShaderType::FRAGMENT) );

	return Graphics::createProgram("program." + name, shader);
}

/*!
 * \brief GraphicsOpenGLPrivate class declaration.
 */
class GraphicsOpenGLPrivate {
public:
	GraphicsOpenGLPrivate() : m_mode(DisplayMode::FULL)
	{
	}

	~GraphicsOpenGLPrivate()
	{
	}

	void setDisplayMode(DisplayMode mode)
	{
		m_mode = mode;

		switch ( m_mode ) {
		case DisplayMode::WIREFRAME:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			break;
		case DisplayMode::FULL:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			break;
		case DisplayMode::POINT:
			BK_GL_ASSERT(glPolygonMode(GL_FRONT_AND_BACK, GL_POINT));
			break;
		}
	}

	void setPolygonOffset(const f32 factor, const f32 units)
	{
		BK_GL_ASSERT(glPolygonOffset(factor, units));
	}

	DisplayMode displayMode() const
	{
		return m_mode;
	}

private:
	DisplayMode m_mode;
};

GraphicsOpenGL::GraphicsOpenGL() :
	m_impl(new GraphicsOpenGLPrivate())
{
}

GraphicsOpenGL::~GraphicsOpenGL()
{
	SAFE_DELETE(m_impl);
}

void
GraphicsOpenGL::init()
{
	// m_basic_red {{{
	s_mBasicRed = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			gl_Position = transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(1, 1, 1, texture(tex, bk_fragTex0).r) * vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// mvp_basic_col {{{
	s_mvpBasicCol = createStockProgram("shader.mvp_basic_col", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;
		out vec3 bk_Normal;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			bk_Normal = bk_normal;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		in vec2 bk_fragTex0;
		in vec3 bk_Color;
		in vec3 bk_Normal;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// mvp_basic_tex {{{
	s_mvpBasicTex = createStockProgram("shader.mvp_basic_tex", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;
		out vec3 bk_Normal;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			bk_Normal = bk_normal;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;
		in vec3 bk_Normal;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = texture(tex,  (bk_texSize0 * bk_fragTex0) + bk_texOffset0);
		}
	)");
	// }}}

	// mvb_basic_red {{{
	s_mvpBasicRed = createStockProgram("shader.mvp_basic", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;
		in vec3 bk_color;
		in vec3 bk_normal;

		out vec2 bk_fragTex0;
		out vec3 bk_Color;

		void main() {
			bk_fragTex0 = bk_texture0;
			bk_Color = bk_color;
			gl_Position = camera * transformation * bk_vertex;
		}
	)", R"(
		#version 130

		uniform sampler2D tex;
		uniform vec2 bk_texOffset0;
		uniform vec2 bk_texSize0;
		in vec2 bk_fragTex0;
		in vec3 bk_Color;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = vec4(1, 1, 1, texture(tex, bk_fragTex0).r) * vec4(bk_Color, 1.0);
		}
	)");
	// }}}

	// skyBox {{{
	s_skyBox = createStockProgram("shader.skybox", R"(
		#version 130

		uniform mat4 projection;
		uniform mat4 camera;
		uniform mat4 transformation;

		in vec4 bk_vertex;
		in vec2 bk_texture0;

		out vec3 bk_fragTex0;

		void main() {
			bk_fragTex0 = normalize(bk_vertex.xyz);
			gl_Position = camera * bk_vertex;
		}
	)", R"(
		#version 130

		uniform samplerCube tex;
		in vec3 bk_fragTex0;

		out vec4 bk_FragColor;

		void main() {
			bk_FragColor = texture(tex,  bk_fragTex0);
		}
	)");
	// }}}
}

void
GraphicsOpenGL::enable(GraphicsOption option)
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(glEnable(GL_DEPTH_TEST));
		BK_GL_ASSERT(glDepthFunc(GL_LESS));
		break;
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(glEnable(GL_BLEND));
		BK_GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		break;
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(glEnable(GL_CULL_FACE));
		BK_GL_ASSERT(glCullFace(GL_BACK));
		break;
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_FILL));
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_LINE));
		BK_GL_ASSERT(glEnable(GL_POLYGON_OFFSET_POINT));
		break;
	}
}

bool
GraphicsOpenGL::isEnabled(GraphicsOption option) const
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(return glIsEnabled(GL_DEPTH_TEST));
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(return glIsEnabled(GL_BLEND));
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(return glIsEnabled(GL_CULL_FACE));
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(return glIsEnabled(GL_POLYGON_OFFSET_LINE));
	}
	return false;
}

void
GraphicsOpenGL::disable(GraphicsOption option)
{
	switch ( option ) {
	case GraphicsOption::DEPTH:
		BK_GL_ASSERT(glDisable(GL_DEPTH_TEST));
		break;
	case GraphicsOption::BLEND:
		BK_GL_ASSERT(glDisable(GL_BLEND));
		break;
	case GraphicsOption::CULLING:
		BK_GL_ASSERT(glDisable(GL_CULL_FACE));
		break;
	case GraphicsOption::POLYGON_OFFSET:
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_FILL));
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_LINE));
		BK_GL_ASSERT(glDisable(GL_POLYGON_OFFSET_POINT));
		break;
	}
}

DisplayMode
GraphicsOpenGL::displayMode() const
{
	return m_impl->displayMode();
}

void
GraphicsOpenGL::set(const GraphicsOption option, const bool active)
{
	if ( active ) {
		enable(option);
	} else {
		disable(option);
	}
}

void
GraphicsOpenGL::setDisplayMode(DisplayMode mode)
{
	m_impl->setDisplayMode(mode);
}

void
GraphicsOpenGL::setPolygonOffset(const f32 factor, const f32 units)
{
	m_impl->setPolygonOffset(factor, units);
}

IProgram*
GraphicsOpenGL::stockProgram(const StockProgramName programName)
{
	switch ( programName ) {
	case StockProgramName::M_BASIC_RED:   return s_mBasicRed;
	case StockProgramName::MVP_BASIC_TEX: return s_mvpBasicTex;
	case StockProgramName::MVP_BASIC_COL: return s_mvpBasicCol;
	case StockProgramName::MVP_BASIC_RED: return s_mvpBasicRed;
	case StockProgramName::SKYBOX:        return s_skyBox;
	}
}

} /* bk */
