#ifndef GRAPHICS_OPENGL_H_BTYF5ENU
#define GRAPHICS_OPENGL_H_BTYF5ENU

#include "graphics/Global"
#include "graphics/IGraphics"

namespace bk {

class IProgram;

/*!
 * \brief GraphicsOpenGL class declaration.
 */
class GraphicsOpenGL : public IGraphics {
public:
	GraphicsOpenGL();
	virtual ~GraphicsOpenGL();

	void init();

	void disable(GraphicsOption) override;
	DisplayMode displayMode() const override;
	void enable(GraphicsOption) override;
	bool isEnabled(GraphicsOption) const override;
	void set(const GraphicsOption, const bool) override;
	void setDisplayMode(DisplayMode);
	void setPolygonOffset(const f32, const f32) override;
	IProgram* stockProgram(const StockProgramName) override;

private:
	BK_IMPL(GraphicsOpenGL);
};

} /* bk */

#endif /* end of include guard: GRAPHICS_OPENGL_H_BTYF5ENU */

