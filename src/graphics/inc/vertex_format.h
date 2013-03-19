#ifndef VERTEX_FORMAT_H_TQDUSHNY
#define VERTEX_FORMAT_H_TQDUSHNY

#include "graphics/Global"

namespace bk {

class VertexFormat {
public:
	enum VertexType {
		POSITION = 1,
		NORMAL = 2,
		COLOR = 3,
		TANGENT = 4,
		BINORMAL = 5,
		BLENDWEIGHTS = 6,
		BLENDINDICES = 7,
		TEXCOORD0 = 8,
		TEXCOORD1 = 9,
		TEXCOORD2 = 10,
		TEXCOORD3 = 11,
		TEXCOORD4 = 12,
		TEXCOORD5 = 13,
		TEXCOORD6 = 14,
		TEXCOORD7 = 15
	};

	struct Data {
		Data(VertexType _type, const int _size,
				const int _offset = 0, const int _stride = 0) :
			type(_type), size(_size), offset(_offset), stride(_stride)
		{
		}

		VertexType type;
		int size;
		int offset;
		int stride;
	};

	VertexFormat();
	VertexFormat(initializer_list<Data>);
	virtual ~VertexFormat();

	int size() const;
	vector<Data> elements() const;

	void operator=(const VertexFormat&);

private:
	vector<Data> m_elements;
	int m_size;
};

}

#endif /* end of include guard: VERTEX_FORMAT_H_TQDUSHNY */

