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
	// ����� ������� �������
	class TextureFactory
	{
		// ��������� ������
		static TextureFactory *s_instance;

		// ������ ������� ������ ������� �������
		std::map<sf::String, LPDIRECT3DTEXTURE9> m_textures;
		sf::Mutex m_texuresMutex;

		// ����������� ������� �������
		TextureFactory();

	public:

		// ���������� ��������� ������
		static TextureFactory* Instance();

		// ���������� ��������
		void* MakeTexture(const sf::String &btzFileName, const sf::String &texFileName, bool readAlphaBM8 = true);

		// ����������� ������� �������
		void ReleaseTextures();
	};
}