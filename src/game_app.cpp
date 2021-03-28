#include "../include/game_app.hpp"

void Game_App::v_push( GLfloat v )
	{
		m_vertices.push_back( v );
	}

void Game_App::m_init( )
	{
		m_game_wnd.setVerticalSyncEnabled( true );
		m_game_wnd.setFramerateLimit( 60 );

		glewExperimental = GL_TRUE;

		if ( GLEW_OK != glewInit( ) )
			{
				std::cout << "Failed to initialize GLEW" << '\n';
				exit(-1);
			}

		int width  = m_game_wnd.getSize( ).x;
		int height = m_game_wnd.getSize( ).y;

		glViewport( 0, 0, width, height );

		build_shader( "shaders/core.vert", "shaders/core.frag" );

		glGenVertexArrays( 1, &m_VAO );
		glGenBuffers( 1, &m_VBO );

		glBindVertexArray( m_VAO );

		glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
		glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW );

		glVertexAttribPointer( 0,  // Index: Should match shader layout
							   3,  // Size : Elements per attribute ( x, y, z )
							   GL_FLOAT,  // Type
							   GL_FALSE,  // Normalised?
							   6 * sizeof( GLfloat ),  // Stride
							   ( GLvoid* ) 0  // Pointer: Offset to first element
							 );
		glEnableVertexAttribArray( 0 );

		glVertexAttribPointer( 1,  // Index: Should match shader layout
							   3,  // Size : Elements per attribute ( x, y, z )
							   GL_FLOAT,  // Type
							   GL_FALSE,  // Normalised?
							   6 * sizeof( GLfloat ),  // Stride
							   ( GLvoid* ) ( 3 * sizeof( GLfloat ) )  // Pointer: Offset to first element
							 );
		glEnableVertexAttribArray( 1 );

		glBindVertexArray( 0 );
	}

void Game_App::m_run( )
	{
		bool running = true;

		while(running)
			{
				sf::Event e;
				while(m_game_wnd.pollEvent( e ) )
					{
						switch( e.type )
							{
								case sf::Event::Closed:
									{
										running = false;
										break;
									}
								case sf::Event::KeyReleased:
									{
										if(e.key.code == sf::Keyboard::Key::Left)
											std::cout << "Left key pressed!" << std::endl;

										if(e.key.code == sf::Keyboard::Key::Right)
											std::cout << "Right key pressed!" << std::endl;

										if(e.key.code == sf::Keyboard::Key::Up)
											std::cout << "Up key pressed!" << std::endl;

										if(e.key.code == sf::Keyboard::Key::Down)
											std::cout << "Down key pressed!" << std::endl;
										break;
									}
								default: /* unhandled event types */
									{
										break;
									}
							}
					}
				m_render( );
			}
		glDeleteVertexArrays( 1, &m_VAO );
		glDeleteBuffers( 1, &m_VBO );

		m_game_wnd.close( );
	}

void Game_App::m_render( )
	{
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		use_shader( );
		glBindVertexArray( m_VAO );
		glDrawArrays( GL_TRIANGLES, 0, m_vertices.size() / 6 );
		glBindVertexArray( 0 );

		m_game_wnd.display( );
	}



/* SHADER FUNCTIONS */

void Game_App::build_shader( const GLchar *vertexPath, const GLchar *fragmentPath )
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions ( std::ifstream::badbit );
		fShaderFile.exceptions ( std::ifstream::badbit );
		try
			{
				// Open files
				vShaderFile.open( vertexPath );
				fShaderFile.open( fragmentPath );
				std::stringstream vShaderStream, fShaderStream;
				// Read file's buffer contents into streams
				vShaderStream << vShaderFile.rdbuf( );
				fShaderStream << fShaderFile.rdbuf( );
				// close file handlers
				vShaderFile.close( );
				fShaderFile.close( );
				// Convert stream into string
				vertexCode = vShaderStream.str( );
				fragmentCode = fShaderStream.str( );
			}
		catch ( std::ifstream::failure & e )
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}
		const GLchar *vShaderCode = vertexCode.c_str( );
		const GLchar *fShaderCode = fragmentCode.c_str( );

		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];

		// Vertex Shader
		vertex = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vertex, 1, &vShaderCode, NULL );
		glCompileShader( vertex );

		// Print compile errors if any
		glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
		if ( !success )
			{
				glGetShaderInfoLog( vertex, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

		// Fragment Shader
		fragment = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fragment, 1, &fShaderCode, NULL );
		glCompileShader( fragment );

		// Print compile errors if any
		glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
		if ( !success )
			{
				glGetShaderInfoLog( fragment, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}

		// Shader Program
		this->m_shader_prog = glCreateProgram( );
		glAttachShader( this->m_shader_prog, vertex );
		glAttachShader( this->m_shader_prog, fragment );
		glLinkProgram( this->m_shader_prog );

		// Print linking errors if any
		glGetProgramiv( this->m_shader_prog, GL_LINK_STATUS, &success );
		if (!success)
			{
				glGetProgramInfoLog( this->m_shader_prog, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}
		
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader( vertex );
		glDeleteShader( fragment );
	}

void Game_App::use_shader( )
	{
		glUseProgram( this->m_shader_prog );
	}

