#pragma once
#include "Echo/Window.h"

#include <GLFW/glfw3.h>

namespace Echo {

	class Windows_Window :	public Window
	{
	public:
		Windows_Window(const sWindowProps& prop);
		virtual ~Windows_Window();

		virtual void UpdateWindow() override;




	private:
		GLFWwindow* m_pWindow;
		
		/// @brief 
		typedef struct sWindowData
		{
			
		};
	};

}


