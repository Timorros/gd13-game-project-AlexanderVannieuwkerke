//#pragma once
////ML Detection Extension
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
//#endif
//// SDL and OpenGL Includes
//#pragma warning(disable : 26812)
//#pragma warning(disable : 4820)
////#include <SDL.h>
//
//#pragma warning(default : 26812)
//#include "structs.h"
//
/////delete all underneath
//#define NOMINMAX
//
//// include Windows/SDL FIRST
//#include <windows.h>   // if used
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include <SDL_ttf.h> 
//#include <SDL_mixer.h> 
//#include <SDL_image.h>
//
//// FIX BAD MACROS IMMEDIATELY AFTER
//#ifdef next
//#undef next
//#endif
//#ifdef min
//#undef min
//#endif
//#ifdef max
//#undef max
//#endif
//
//// THEN standard headers
//#include <iterator>
//#include <algorithm>
//#include <vector>

#pragma once
#include "nlohmann/json.hpp"
//ML Detection Extension
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
// SDL and OpenGL Includes
#pragma warning(disable : 26812)
#pragma warning(disable : 4820)
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 
#include <SDL_image.h>

#pragma warning(default : 26812)
#include "structs.h"