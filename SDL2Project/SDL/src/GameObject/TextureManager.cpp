#include "TextureManager.h"
#include "SDL_image.h"
#include "Camera.h"
TextureManager::TextureManager()
{
	m_Texture = NULL;
	Init();
}

TextureManager::~TextureManager()
{
	//Delete something here
	Free();
}

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load texture");
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log(" failed to create");
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Free()
{
	for (auto it = m_ListTextures.begin(); it != m_ListTextures.end(); ++it)
	{
		SDL_DestroyTexture(*it);
	}
	m_ListTextures.clear();
}

bool TextureManager::Init()
{
	//Initialize PNG loading
	bool ret = true;
	int imgFlags = IMG_INIT_PNG; //we can use other type maybe jpg, bmp...
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		ret = false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	return ret;
}

bool TextureManager::LoadImage(const std::string& path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		m_Texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), loadedSurface);
		if (m_Texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			originWidth = loadedSurface->w; // width of texture
			originHeight = loadedSurface->h;//height of texture
			m_ListTextures.push_back(m_Texture);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	
	return m_Texture != NULL;
}

void TextureManager::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(m_Texture, red, green, blue);
}

void TextureManager::Render(int x, int y, int width, int height, double angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { 0, 0, width, height };
    Vector2 cam = Camera::GetInstance()->GetPosition() * 0.25;
    SDL_Rect dstRect = { x, y, width, height };

    if (width == MAP_WIDTH) {
        dstRect.x -= cam.x;
        dstRect.y -= cam.y;
    }
    else if (width > MAP_WIDTH) {
        dstRect.x -= cam.x * 4;
        dstRect.y -= cam.y * 4;
    }

    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), m_Texture, NULL, &dstRect, angle, nullptr, flip);
}

void TextureManager::RenderTile(std::string tilesetID, int tileSize, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = { x, y, tileSize, tileSize };
    SDL_Rect dstRect = { tileSize * frame, tileSize * (row - 1), tileSize, tileSize };
    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::RenderFrame(int x, int y, int width, int height, int spriteRow, int currentframe, int framecount, int numAction, double angle, SDL_RendererFlip flip)
{
    float srcWidth = originWidth / framecount;
    float srcHeight = originHeight / numAction;
    SDL_Rect srcRect = { srcWidth * currentframe, srcHeight * (spriteRow - 1), srcWidth, srcHeight };
    SDL_Rect dstRect = { x - Camera::GetInstance()->GetPosition().x, y - Camera::GetInstance()->GetPosition().y, width, height };
    SDL_RenderCopyEx(Renderer::GetInstance()->GetRenderer(), m_Texture, &srcRect, &dstRect, angle, nullptr, flip);
}

void TextureManager::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_Texture, blending);
}

void TextureManager::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

bool TextureManager::LoadFromRendererText(TTF_Font* font, std::string& textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture ( loai bo texture co san)
	Free();
	//Render texture surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface ! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture formm surface pixels
		m_Texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetRenderer(), textSurface);
		if (m_Texture == NULL)
		{
			printf("Unable to create texture from renderered text!  SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			originWidth = textSurface->w;
			originHeight = textSurface->h;
			m_ListTextures.push_back(m_Texture);
		}
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	return m_Texture!= NULL;
}


