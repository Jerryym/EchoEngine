#pragma once

namespace Echo {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void swapBuffers() = 0;
	};

}