#ifndef IGRAPHICS_H_BLTZVSAH
#define IGRAPHICS_H_BLTZVSAH

#include "graphics/Global"

namespace bk {

class IMesh;
class IProgram;

/*!
 * \brief IGraphics class declaration.
 */
class IGraphics {
public:
	virtual void init() = 0;

	virtual  void         disable(GraphicsOption) = 0;
	virtual  DisplayMode  displayMode() const = 0;
	virtual  void         enable(GraphicsOption) = 0;
	virtual  bool         isEnabled(GraphicsOption) const = 0;
	virtual  void         set(const GraphicsOption, const bool) = 0;
	virtual  void         setDisplayMode(DisplayMode) = 0;
	virtual  void         setPolygonOffset(const f32, const f32) = 0;
	virtual IProgram*     stockProgram(const StockProgramName) = 0;
};

} /* bk */

#endif /* end of include guard: IGRAPHICS_H_BLTZVSAH */

