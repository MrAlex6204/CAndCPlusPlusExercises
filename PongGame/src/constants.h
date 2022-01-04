#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define FSP	60
#define FRAME_TARGET_TIME	(1000/FSP)
#define CENTERED_POS (position){ WINDOW_WIDTH * 0.5 , WINDOW_HEIGHT * 0.5 }
#define CENTERED_X (WINDOW_WIDTH * 0.5)
#define CENTERED_Y (WINDOW_HEIGHT * 0.5)
#define WHITE_COLOR (SDL_Color){255,255,255,255}
#define RED_COLOR (SDL_Color){255,0,0,255}
#define YELLOW_COLOR (SDL_Color){255,255,0,255}
#define GREEN_COLOR (SDL_Color){0, 143, 17}


const char* FONT_FILE_NAME = "PressStart.ttf";
const int FONT_SZ = 28;


typedef struct strc_velocity {
	
	float x;
	float y;
	
} velocity ;

typedef struct {
	float x;
	float y;
	float width;
	float height;
	
	velocity vel;
	
} rect;

typedef struct {
	float x;
	float y;
} position ;



SDL_Rect toSDLRect(rect r){
	
	SDL_Rect rect = {
		(int)r.x,(int)r.y,(int)r.width,(int)r.height
	};
	
	return rect;	
}

void DrawText(SDL_Renderer *renderer,const char* text,int fsz ,position pos,SDL_Color color,bool center){
	
	TTF_Init();
	
	TTF_Font *font = TTF_OpenFont(FONT_FILE_NAME,fsz);
	//SDL_Color color = {r,g,b,a};
	SDL_Surface *textSurface = TTF_RenderText_Solid(font,text,color);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
	
	if(center){
		
		pos.x -= (textSurface->w * 0.5);
		pos.y -=(textSurface->h * 0.5);
	}
	
	SDL_Rect textRect = {
		(int)pos.x,
		(int)pos.y,
		textSurface->w,
		textSurface->h
	};
	
	SDL_RenderCopy(renderer,textTexture,NULL,&textRect);
	
	SDL_FreeSurface(textSurface);
	TTF_Quit();
	
}




