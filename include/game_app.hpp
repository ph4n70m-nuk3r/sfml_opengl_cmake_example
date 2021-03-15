#ifndef GAME_APP_HPP
#define GAME_APP_HPP

#include <GL/glew.h>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Game_App {

public:
	Game_App( ) = delete; // Disable default constructor

	Game_App( const sf::VideoMode cSF_video_mode, const char* ccp_title, const sf::ContextSettings cSF_ContextSettings ) 
			: m_game_wnd( cSF_video_mode, ccp_title, sf::Style::Close, cSF_ContextSettings ) {
	}

	void m_init( );

	void m_run( );

	void m_render( );

	void build_shader( const GLchar *vertexPath, const GLchar *fragmentPath );

	void use_shader( );

	void v_push( GLfloat v );
	
private:
	sf::Window m_game_wnd;	

	GLuint m_shader_prog;

	std::vector<GLfloat> m_vertices;

	GLuint m_VBO, m_VAO;

protected:
	
};

#endif // GAME_APP_HPP
