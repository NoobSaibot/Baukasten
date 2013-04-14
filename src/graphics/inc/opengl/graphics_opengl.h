#ifndef GRAPHICS_OPENGL_H_BTYF5ENU
#define GRAPHICS_OPENGL_H_BTYF5ENU

#include "graphics/Global"
#include "graphics/IGraphics"

namespace bk {

/*!
 * \brief GraphicsOpenGL class declaration.
 */
class GraphicsOpenGL : public IGraphics {
public:
	GraphicsOpenGL();
	virtual ~GraphicsOpenGL();

	void init(const u16, const u16, const string&);

	void disable(GraphicsOption) override;
	DisplayMode displayMode() const override;
	void enable(GraphicsOption) override;
	bool isEnabled(GraphicsOption) const override;
	void setDisplayMode(DisplayMode);

private:
	BK_IMPL(GraphicsOpenGL);
};

} /* bk */

#endif /* end of include guard: GRAPHICS_OPENGL_H_BTYF5ENU */

