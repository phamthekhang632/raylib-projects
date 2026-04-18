#include <raylib.h>

#include <string>

Texture2D loadTextureKey(const std::string& path, const Color& color_key)
{
    Image image = LoadImage(path.c_str());
    ImageColorReplace(&image, color_key, BLANK);
    return LoadTextureFromImage(image);
}
