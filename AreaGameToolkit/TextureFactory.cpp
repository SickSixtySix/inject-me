// InjectMe
#include "TextureFactory.hpp"
#include "D3D9Hook.hpp"

using namespace InjectMe::Hook::D3D9;
using namespace InjectMe::UI;

// SFML
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Lock.hpp>

// unzipper
#include "unzipper/unzipper.h"

TextureFactory *TextureFactory::s_instance = nullptr;

TextureFactory::TextureFactory() {}

TextureFactory* TextureFactory::Instance()
{
	if (s_instance == nullptr)
		s_instance = new TextureFactory();

	return s_instance;
}

void* TextureFactory::MakeTexture(const sf::String &btzFileName, const sf::String &texFileName, bool readAlphaBM8)
{
	sf::Lock lock(m_texuresMutex);

	auto it = m_textures.find(texFileName);
	
	if (m_textures.end() != it)
	{
		return it->second;
	}
	
	sf::Image image;
	sf::Uint32 sizeX, sizeY;
	sf::Uint8 *pixels; sf::Uint16 bpp = 4;

	LPDIRECT3DTEXTURE9 texture; D3DLOCKED_RECT rectangle;
	auto device = GetCurrentDevice();
	auto aBtzFileName = btzFileName.toAnsiString();
	auto cBtzFileName = aBtzFileName.c_str();
	
	ziputils::unzipper zipFile;
	
	if (zipFile.open(cBtzFileName) == false)
	{
		return 0;
	}
	else
	{
		auto aTexFileName = texFileName.toAnsiString();
		auto cTexFileName = aTexFileName.c_str();
	
		if (zipFile.openEntry(cTexFileName) == false)
		{
			return 0;
		}
		else
		{
			Buffer *pBuffer;
			(zipFile >> pBuffer).closeEntry();

			char extension[4];
			pBuffer->Read(36, extension);
	
			if (sf::String("BM8") == extension)
			{
				pBuffer->Read(54, sizeX);
				pBuffer->Read(58, sizeY);
				pixels = new sf::Uint8[sizeX * sizeY * bpp];
	
				sf::Uint16 depth;
				pBuffer->Read(64, depth);

				if (depth == 24 || !readAlphaBM8)
				{
					for (size_t i = 0; i < sizeX * sizeY; i++)
					{
						pixels[i * bpp + 0] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 0];
						pixels[i * bpp + 1] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 1];
						pixels[i * bpp + 2] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 2];
						pixels[i * bpp + 3] = 0xFFu;
					}
				}
				else
				{
					for (size_t i = 0; i < sizeX * sizeY; i++)
					{
						pixels[i * bpp + 0] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 0];
						pixels[i * bpp + 1] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 1];
						pixels[i * bpp + 2] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 2];
						pixels[i * bpp + 3] = pBuffer->GetMemory().lpAddress[90 + (i % sizeX + (sizeY - i / sizeX - 1) * sizeX) * bpp + 3];
					}
				}
			}
			else
			{
				if (!image.loadFromMemory(pBuffer->GetMemory().lpAddress + 0x24, pBuffer->GetOffset() - 0x24))
					return 0;

				sizeX = image.getSize().x;
				sizeY = image.getSize().y;
				pixels = new sf::Uint8[sizeX * sizeY * bpp];

				for (size_t i = 0; i < sizeX * sizeY; i++)
				{
					pixels[i * bpp + 0] = *(image.getPixelsPtr() + i * bpp + 2);
					pixels[i * bpp + 1] = *(image.getPixelsPtr() + i * bpp + 1);
					pixels[i * bpp + 2] = *(image.getPixelsPtr() + i * bpp + 0);
					pixels[i * bpp + 3] = *(image.getPixelsPtr() + i * bpp + 3);
				}
			}
	
			auto result = device->CreateTexture(sizeX, sizeY, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture, NULL);
			if (result < 0)
				return 0;

			if (texture->LockRect(0, &rectangle, NULL, 0) != D3D_OK)
				return 0;

			for (sf::Uint32 y = 0; y < sizeY; y++)
				memcpy(reinterpret_cast<char*>(rectangle.pBits) + rectangle.Pitch * y, pixels + (sizeX * bpp) * y, (sizeX * bpp));

			texture->UnlockRect(0);

			delete[] pixels;
			delete pBuffer;
		}
	
		zipFile.close();
	}
	
	m_textures[texFileName] = texture;
	
	return texture;
}

void TextureFactory::ReleaseTextures()
{
	sf::Lock lock(m_texuresMutex);

	for (auto texture : m_textures)
	{
		texture.second->Release();
		texture.second = NULL;
	}

	m_textures.clear();
}