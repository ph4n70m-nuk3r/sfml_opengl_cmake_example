/*-*-*-*-*-*-*-*-*-*-*-*-|
| PREPROCESSOR DIRECTIVE |
|-*-*-*-*-*-*-*-*-*-*-*-*/
#include "../include/graphics_settings.hpp"
#include "../include/game_app.hpp"

// #include <GL/glew.h>
// #include <iostream>

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-|
| ENTRY POINT OF APPLICATION |
|-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
int main( ) {

    sf::VideoMode video_mode = get_video_mode(); // func declared in graphics_settings.hpp

    sf::ContextSettings context_settings = get_context_settings(); // func declared in graphics_settings.hpp

    Game_App game(video_mode, "Window Title.", context_settings);

    /* Define static VERTEX and COLOUR data for a single TRIANGLE */
    GLfloat tri[] = 
    {
        -1.0f, -1.0f, 0.0f, /* vertex position: Bottom Left of window  */  1.0f, 0.0f, 0.0f, /* colour: Red   */
         0.0f,  1.0f, 0.0f, /* vertex position: Top Centre of window   */  0.0f, 1.0f, 0.0f, /* colour: Green */
         1.0f, -1.0f, 0.0f, /* vertex position: Bottom Right of window */  0.0f, 0.0f, 1.0f  /* colour: Blue  */
    };
    
    for(auto&& i : tri)
    {
        game.v_push(i);
    }

    game.m_init();

    game.m_run();

    return 0;
}
