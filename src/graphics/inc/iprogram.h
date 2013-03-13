#ifndef IPROGRAM_H_R9MJXBZH
#define IPROGRAM_H_R9MJXBZH

#include "base.h"
#include "core/Managed"

namespace bk {

class IProgram : public Managed {
public:
	IProgram(const string& name) : Managed(name, "Program")
	{
		m_vars[(int)ProgramVariableType::VERTEX]          = "bk_vertex";
		m_vars[(int)ProgramVariableType::TEXTURE0]        = "bk_texture0";
		m_vars[(int)ProgramVariableType::TEXTURE1]        = "bk_texture1";
		m_vars[(int)ProgramVariableType::TEXTURE2]        = "bk_texture2";
		m_vars[(int)ProgramVariableType::TEXTURE3]        = "bk_texture3";
		m_vars[(int)ProgramVariableType::TEXTURE4]        = "bk_texture4";
		m_vars[(int)ProgramVariableType::TEXTURE5]        = "bk_texture5";
		m_vars[(int)ProgramVariableType::TEXTURE6]        = "bk_texture6";
		m_vars[(int)ProgramVariableType::TEXTURE7]        = "bk_texture7";
		m_vars[(int)ProgramVariableType::COLOR]           = "bk_color";
		m_vars[(int)ProgramVariableType::CAMERA]          = "bk_camera";
		m_vars[(int)ProgramVariableType::TRANSFORMATION]  = "bk_transformation";
	}

	virtual int attrib(const string&) const = 0;
	virtual void setAttrib(const string&, const mat4&) = 0;

	virtual int constant(const string&) const = 0;
	virtual void setConstant(const string&, const mat4&) = 0;

	void setVariableName(const ProgramVariableType type, const string& value)
	{
		m_vars[(int)type] = value;
	}

	string getVariableName(const ProgramVariableType type) const
	{
		return m_vars[(int)type];
	}

	virtual void activate() const = 0;
	virtual void deactivate() const = 0;

private:
	string m_vars[12];
};

}

#endif /* end of include guard: IPROGRAM_H_R9MJXBZH */

