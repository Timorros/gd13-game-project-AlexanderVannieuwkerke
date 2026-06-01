#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "iostream"

//delete
#include "Physics.h"

Game::Game(const Window& window, float scale ) 
	: BaseGame{ window }
	, m_Scale{scale}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	//utils::HitInfo hit{};
	//std::cout << "test: " << Raycast(Vector2f{ 50,50 }, Vector2f(0, 100), Vector2f{ 50,100 }, 20, hit) << std::endl;
	//std::cout << "test: " << Raycast(Vector2f{ 50,50 }, Vector2f(0, 100), Vector2f{ 50,100 }, 0.5f, 20, hit) << std::endl;
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	if(!m_PauseMenu.GetState())
		m_Map.Update(elapsedSec);
	m_Ball.Update(elapsedSec);
	if (m_Ball.GetBounds().center.y < 0)
	{
		m_Ball.SetPosition(243, 60);
		m_Ball.SetVelocity(0, 0);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	glPushMatrix();
	{
		glScalef(GLfloat(m_Scale), GLfloat(m_Scale), GLfloat(m_Scale));
		

		if (!m_IsDevMode)
		{
			glTranslatef(GLfloat(0), GLfloat((m_Ball.GetBounds().center.y > 100) ? -1*(m_Ball.GetBounds().center.y - 100) : 0), GLfloat(0));
		}

		//layer0
		m_Map.DrawBG();

		//layer1
		m_Ball.Draw();
		m_Map.Draw();

		//layer2
		m_PauseMenu.Draw();
	}
	glPopMatrix();
	if (m_IsDevMode)
	{
		glPushMatrix();

		glScalef(GLfloat(m_Scale), GLfloat(m_Scale), GLfloat(m_Scale));
		m_MapMaker.Draw();
		glPopMatrix();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Map.KeyDownHandler(e);

	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}
void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_MapMaker.KeyboardHandler(e);
	m_Map.KeyUpHandler(e);
	switch ( e.keysym.sym )
	{
	case SDLK_ESCAPE:
		m_PauseMenu.ToggleState();
		break;
	case SDLK_1:
		m_Ball.SetPosition(51, 149);
		m_Ball.SetVelocity(Vector2f{ -400,400 });
		break;
	case SDLK_2:
		m_Ball.SetPosition(Vector2f{ 62.5f,240 });
		m_Ball.SetVelocity(400, 90);
		break;
	case SDLK_3:
		m_Ball.SetPosition(Vector2f{ 211,182.5f });
		m_Ball.SetVelocity(400, 60);
		break;
	case SDLK_4:
		m_Ball.SetPosition(Vector2f{ 135, 210 });
		m_Ball.SetVelocity(400,70);
		break;
	case SDLK_5:
		m_Ball.SetPosition(Vector2f{ 176.33f, 168.67f });
		m_Ball.SetVelocity(400, 70);
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}
void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}
void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	m_MapMaker.MouseHandler(e);
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	ellipse.push_back(Vector2f{ float(e.x), float(e.y) });
	//	std::cout << "Vector2f{" << std::to_string(e.x) << "," << std::to_string(e.y) << "},";
	//	
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}