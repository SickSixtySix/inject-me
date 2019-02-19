#pragma once

// SFML
#include <SFML/System/String.hpp>
#include <SFML/System/Mutex.hpp>

// Direct3D 9
#include <d3d9.h>

// C++
#include <map>

namespace InjectMe::UI
{
	// Класс фабрики текстур
	class TextureFactory
	{
		// Экземпляр класса
		static TextureFactory *s_instance;

		// Список текстур данной фабрики текстур
		std::map<sf::String, LPDIRECT3DTEXTURE9> m_textures;
		sf::Mutex m_texuresMutex;

		// Конструктор фабрики текстур
		TextureFactory();

	public:

		// Возвращает экземпляр класса
		static TextureFactory* Instance();

		// Возвращает текстуру
		void* MakeTexture(const sf::String &btzFileName, const sf::String &texFileName, bool readAlphaBM8 = true);

		// Освобождает ресурсы текстур
		void ReleaseTextures();
	};
}