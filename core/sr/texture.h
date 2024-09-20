#include "../ew/external/glad.h"
#include "../ew/ewMath/ewMath.h"
#include "../ew/external/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture2D {
	public:
		Texture2D(const char* filePath, int filterMode, int wrapMode, bool flipOnLoad = true);
		~Texture2D();
		void Bind(unsigned int slot = 0);
		int GetID();
		int GetWidth();
		int GetHeight();
	private:
		unsigned int m_id;
		int m_width, m_height;
};