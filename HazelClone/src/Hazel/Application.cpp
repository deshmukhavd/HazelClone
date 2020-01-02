#include "hzpch.h"
#include "Application.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Platform/Windows/WindowsInput.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// just to check whether openGL is working or not
		/*{
			unsigned int id;
			unsigned int id1;
			glGenBuffers(1, &id);
			glGenVertexArrays(5, &id1);
		}*/
	}


	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		/*WindowResizeEvent w(1280, 720);
		if (w.IsInCategory(EventCategoryApplication))
		{
			HZ_CORE_TRACE(w);
		}
		if (w.IsInCategory(EventCategoryInput))
		{
			HZ_CORE_TRACE(w);
		}*/

		while (m_Running)
		{
			glClearColor(0, 0, 1, 1);          // OpenGL call
			glClear(GL_COLOR_BUFFER_BIT);      // OpenGL call

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			auto v = Input::GetMousePosition();
			//HZ_CORE_TRACE("{0}, {1}", v.first, v.second);

			m_Window->OnUpdate();
		}
	}

}
