#pragma once
#include "BaseGame.h"
#include "Texture.h"
#include "vector"

#include "ball.h"
#include "Map.h"
#include "MapMaker.h"
#include "PauseMenu.h"
class Game : public BaseGame
{
public:
	explicit Game(const Window& window, float scale = 1.f );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	const float m_Scale{1.f};

	PauseMenu m_PauseMenu{ GetViewPort() };

	MapMaker m_MapMaker{m_Scale};

	Ball m_Ball{ Circlef{100,180,5}, Vector2f{0,5}};
	Map m_Map{ &m_Ball, m_Scale };

	bool m_IsDevMode{ false };
};