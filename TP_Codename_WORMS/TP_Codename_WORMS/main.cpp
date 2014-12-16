
#if defined(__APPLE__) && defined(__MACH__) /* __APPLE & __MACH__ sont les deux Macro défini par LLVM */
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32 /* _Win32 Pour les configuration windows 32 & 64 bit */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#endif

#include <math.h>

/*!
 @method DegToRad.
 @brief Change les DegrÈs en Radian.
 @discussion Utile.
 */
double DegToRad(double _Degre){
	return _Degre * M_PI / 180;
}

/*!
 @method RadToDeg.
 @brief Change les Radians en DegrÈs.
 @discussion Utile.
 */
double RadToDeg(double _Radian){
	return _Radian * 180 / M_PI;
}

#define WIDTH 1280
#define HEIGHT 720

#include <time.h>
#include "CWorms.h"




int main(int argc, char** argv) {
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);// Initialisation des composantes
	TTF_Init();				 // SDL et autres librairies.
	Mix_Init(0);
	CWorms::Init(argv[0]);
	CWorms::Start();
	CWorms::Quit();
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
	return 0;
}