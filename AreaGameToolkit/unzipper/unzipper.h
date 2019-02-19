#pragma once

// InjectMe
#include "../Buffer.hpp"

using namespace InjectMe::Utils;

#include <ioapi.h>
#include <unzip.h>
#include <string>
#include <vector>
#include <iostream>
#include <SFML\Graphics\Texture.hpp>

namespace ziputils
{
	class unzipper
	{
	public:
		unzipper();
		~unzipper(void);

		bool open( const char* filename );
		void close();
		bool isOpen();

		bool openEntry( const char* filename );
		void closeEntry();
		bool isOpenEntry();
		unsigned int getEntrySize();

		const std::vector<std::string>& getFilenames();
		const std::vector<std::string>& getFolders();

		unzipper& operator>>( std::ostream& os );
		unzipper& operator>>( InjectMe::Utils::Buffer*& buffer );

	private:
		void readEntries();

	private:
		unzFile			zipFile_;
		bool			entryOpen_;

		std::vector<std::string> files_;
		std::vector<std::string> folders_;
	};
};
