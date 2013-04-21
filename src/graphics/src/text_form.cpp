#include "graphics/TextForm"

#include "core/Debug"
#include "graphics/Animation"
#include "graphics/Camera"
#include "graphics/Font"
#include "graphics/Graphics"
#include "graphics/IDisplay"
#include "graphics/IProgram"
#include "graphics/ITexture"
#include "graphics/IMesh"
#include "math/Vector3"

#include "graphics/inc/opengl/assert_opengl.h"

namespace bk {

class TextFormPrivate {
public:
	TextFormPrivate(const string& text, Font* font, IProgram* program, TextForm* form) :
		m_font(font), m_text(text), m_form(form), m_dirty(false),
		m_color(Vector3(0.0, 0.0, 0.0))
	{
		m_form->setProgram(program);

		m_mesh = Graphics::createMesh("mesh.font");
		m_mesh->setProgram(program);

		initMesh();
	}

	TextFormPrivate(const string& text, Font* font, TextForm* form) :
		m_font(font), m_text(text), m_form(form), m_dirty(false),
		m_color(Vector3(0.0, 0.0, 0.0))
	{
		initProgram();

		m_mesh = Graphics::createMesh("mesh.font");
		m_mesh->setProgram(m_form->program());

		initMesh();
	}

	~TextFormPrivate()
	{
	}

	void setText(const string& text)
	{
		if ( text == m_text ) return;

		m_text = text;
		m_dirty = true;
	}

	void setFont(Font& font)
	{
		m_font = &font;
		m_dirty = true;
	}

	void setColor(const Vector3& color)
	{
		m_color = color;
		m_dirty = true;
	}

	void render(const Camera* cam, const f32 timeDelta)
	{
		if ( m_dirty ) {
			initMesh();
		}

		auto program = m_form->program();
		program->activate();

		if ( m_mesh ) {
			m_mesh->activate();
		}

		// set camera matrix
		program->setConstant("camera", cam->matrix());
		program->setConstant("transformation", m_form->translation());

		// set default value if no animation is present
		program->setConstant("bk_texSize0", vec2(1.0, 1.0));

		auto text = m_text.c_str();
		Glyph glyph;
		for ( u32 i = 0; i < m_text.size(); ++i ) {
			glyph = m_font->glyph(text[i]);
			glyph.tex->activate(*program);

			// draw 6 mesh coordinates, for every char is represented by
			// 6 vertices
			m_mesh->render(6, 6*i);
			glyph.tex->deactivate();
		}

		if (m_mesh) {
			m_mesh->deactivate();
		}

		program->deactivate();
	}

	void initProgram()
	{
		m_form->setProgram( Graphics::stockProgram(StockProgramName::M_BASIC_RED) );
	}

	void initMesh()
	{
		vector<f32> vertices, textures, colors;
		auto text = m_text.c_str();
		Glyph glyph;
		const f32 MAX_VERTEX_WIDTH  = 2.0f;
		const f32 MAX_VERTEX_HEIGHT = 2.0f;
		const f32 Y_START = 0.0f;
		IDisplay* display = m_form->display();

#define V(v) vertices.push_back(v);
#define T(t) textures.push_back(t);
#define C(c) colors.push_back(c);
		f32 currX  = -1.0;
		for ( u32 i = 0; i < m_text.size(); ++i ) {
			glyph = m_font->glyph(text[i]);

			// max ySize berechnet sich aus dem verhältnis der pixelhöhe des
			// zeichens zu der gesamthöhe des viewports, multipliziert mit dem maximal
			// verfügbaren vertikalen vertexbereich
			f32 ySize    = (MAX_VERTEX_HEIGHT * (f32)glyph.height)  / (f32)display->height();

			// berechnung der verschiebung des zeichens nach unten
			f32 yBottom  = (MAX_VERTEX_HEIGHT * (f32)(glyph.height - glyph.topBearing)) / (f32)display->height();
			f32 yUp      = ySize - yBottom;
			f32 yMax     = Y_START + yUp;
			f32 yMin     = Y_START - yBottom;

			f32 xSize    = (MAX_VERTEX_WIDTH  * (f32)glyph.width)   / (f32)display->width();
			f32 xAdvance = (MAX_VERTEX_WIDTH  * (f32)glyph.advance) / (f32)display->width();

			V(currX + xSize); V(yMin);     V(0.0f);
			V(currX);         V(yMax);   V(0.0f);
			V(currX);         V(yMin);     V(0.0f);
			V(currX + xSize); V(yMin);     V(0.0f);
			V(currX + xSize); V(yMax);   V(0.0f);
			V(currX);         V(yMax);   V(0.0f);

			T( 0.0); T(1.0);
			T(-1.0); T(0.0);
			T(-1.0); T(1.0);
			T( 0.0); T(1.0);
			T( 0.0); T(0.0);
			T(-1.0); T(0.0);

			C(m_color.r); C(m_color.g); C(m_color.b);
			C(m_color.r); C(m_color.g); C(m_color.b);
			C(m_color.r); C(m_color.g); C(m_color.b);
			C(m_color.r); C(m_color.g); C(m_color.b);
			C(m_color.r); C(m_color.g); C(m_color.b);
			C(m_color.r); C(m_color.g); C(m_color.b);

			currX += xAdvance;
		}
#undef V
#undef T
#undef C

		m_mesh->setVertices(vertices.size(), 3, vertices.data());
		m_mesh->setTexture(textures.size(), 2, textures.data());
		m_mesh->setColors(colors.size(), 3, colors.data());

		m_dirty = false;
	}

private:
	Font* m_font;
	string m_text;
	TextForm* m_form;
	IMesh* m_mesh;
	bool m_dirty;
	Vector3 m_color;
};

TextForm::TextForm(const string& name, const string& text,
		Font* font, IDisplay* display) :
	IForm(name, display), m_impl(new TextFormPrivate(text, font, this))
{
}

TextForm::TextForm(const string& name, const string& text,
		Font* font, IProgram* program, IDisplay* display) :
	IForm(name, display), m_impl(new TextFormPrivate(text, font, program, this))
{
}

TextForm::~TextForm()
{
	SAFE_DELETE(m_impl);
}

void
TextForm::setText(const string& text)
{
	m_impl->setText(text);
}

void
TextForm::setFont(Font& font)
{
	m_impl->setFont(font);
}

void
TextForm::setColor(const Vector3& color)
{
	m_impl->setColor(color);
}

void
TextForm::render(const Camera* camera, const f32 timeDelta)
{
	m_impl->render(camera, timeDelta);
}

} /* bk */
