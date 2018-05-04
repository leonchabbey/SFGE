/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <graphics/graphics.h>
#include <graphics/sprite.h>
#include <graphics/texture.h>
#include <graphics/shape.h>
#include <engine/log.h>
#include <engine/config.h>

//Dependencies includes
#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui-SFML.h"
#include "imgui.h"

#include <sstream>
#include <p2world.h>
#include <physics\physics.h>

namespace sfge
{
GraphicsManager::GraphicsManager(Engine& engine, bool enable, bool windowless) :
		Module(engine, enable), m_Windowless(windowless)
{
	
}
void GraphicsManager::Init()
{
	auto config = m_Engine.GetConfig();
	if (config == nullptr)
	{
		Log::GetInstance()->Error("[Error] Config is null from Graphics Manager");
	}
	if (!m_Windowless && config != nullptr)
	{
		m_Window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(config->screenResolution.x, config->screenResolution.y),
			"SFGE 0.1");
		if (config->maxFramerate)
		{
			m_Window->setFramerateLimit(config->maxFramerate);
			CheckVersion();
		}
	}
	//Init Texture and Sprite Manager
	m_TextureManager = std::make_shared<TextureManager>();
	m_SpriteManager = std::make_shared<SpriteManager>(*this);
	m_ShapeManager = std::make_shared<ShapeManager>(*this);
}

void GraphicsManager::Update(sf::Time dt)
{
	if (!m_Windowless)
	{
		m_Window->clear();

		m_Engine.GetPhysicsManager()->GetWorld()->Debug(*m_Window);
		m_SpriteManager->Update(dt);
		m_SpriteManager->Draw(*m_Window);

		m_ShapeManager->Draw(*m_Window);
	}
}

void GraphicsManager::Display()
{
	if (!m_Windowless)
	{
		m_Window->display();
	}
}

void GraphicsManager::DrawLine(sf::Vector2f from, sf::Vector2f to, sf::Color color)
{
	sf::Vertex vertices[2] =
	{
	    sf::Vertex(from, color),
	    sf::Vertex(to, color)
	};

	m_Window->draw(vertices, 2, sf::Lines);
}

std::shared_ptr<sf::RenderWindow> GraphicsManager::GetWindow()
{
	return m_Window;
}

std::shared_ptr<SpriteManager> GraphicsManager::GetSpriteManager()
{
	return m_SpriteManager;
}

std::shared_ptr<TextureManager> GraphicsManager::GetTextureManager()
{
	return m_TextureManager;
}

std::shared_ptr<ShapeManager> GraphicsManager::GetShapeManager()
{
	return m_ShapeManager;
}

void GraphicsManager::CheckVersion()
{
	sf::ContextSettings settings = m_Window->getSettings();
	std::stringstream log_message;
	log_message << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

	Log::GetInstance()->Msg(log_message.str());
}

void checkVersion()
{

}


void GraphicsManager::Destroy()
{
	Reset();
	Collect();
	m_Window = nullptr;
	ImGui::SFML::Shutdown();
}

void GraphicsManager::Reset()
{
	m_TextureManager->Reset();
	m_SpriteManager->Reset();
}

void GraphicsManager::Collect()
{

	m_TextureManager->Collect();
	m_SpriteManager->Collect();
}

}
