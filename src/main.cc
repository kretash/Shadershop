
#include "shadershop.hh"
#include "gl_helper.h"
#include "input.h"
#include "canvas.hh"

int main( int argc, char** argv )
{
    SDL_Window*                                        m_window = nullptr;
    SDL_GLContext                                      m_gl_context = {};

    int32_t sdl_init_ = SDL_Init( SDL_INIT_VIDEO );
    if ( sdl_init_ < 0 )
        std::cout << "SDL error ->" << SDL_GetError() << std::endl;

    m_window = SDL_CreateWindow( "ShaderShop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 1920, 1000, SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE );

    m_gl_context = SDL_GL_CreateContext( m_window );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetSwapInterval( 1 );

    glewExperimental = GL_TRUE;
    GLenum glew_init_;
    if ( ( glew_init_ = glewInit() ) != GLEW_OK )
    {
        std::cout << glewGetErrorString( glew_init_ ) << std::endl;
        assert( false && "GLEW INIT FAILED" );
    }

#if DEBUG
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG );

    glEnable( GL_DEBUG_OUTPUT );
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
    glDebugMessageCallback( opengl_error_callback, nullptr );
    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true );
#endif

    ImGui_ImplSdlGL3_Init( m_window );

    std::shared_ptr<Input> input = Input::get_instace();

    std::shared_ptr<Canvas> imageCanvas = std::make_shared<Canvas>();
    std::shared_ptr<Canvas> framebufferCanvas = std::make_shared<Canvas>();

    imageCanvas->create( 0, 0, 900, 900 );
    framebufferCanvas->create( 1, 0, 900, 900 );

    imageCanvas->load( CanvasType::kFILE, "Frank Ocean", "../data/images/frank.jpg" );
    framebufferCanvas->load( CanvasType::kFILE, "backflip", "../data/images/backflip.jpg" );
    //framebufferCanvas->load( CanvasType::kFRAMEBUFFER, "Frank Ocean Shaded" );

    bool showDebugMenu = false;
    bool show_frank = true;
    while ( input->should_quit() == false )
    {
        imageCanvas->update();
        framebufferCanvas->update();

        glClearColor( 0.5f, 0.5f, 1.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        glDisable( GL_DEPTH_TEST );

        ImGui_ImplSdlGL3_NewFrame( m_window );
        input->update();

        ImGui::BeginMainMenuBar();

        if ( ImGui::BeginMenu( "File" ) )
        {
            if ( ImGui::MenuItem( "Show Debug Menu" ) )
            {
                showDebugMenu = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

        if ( showDebugMenu )
        {
            ImGui::ShowTestWindow( &showDebugMenu );
        }

        imageCanvas->render();
        framebufferCanvas->render();

        ImGui::Render();

        SDL_GL_SwapWindow( m_window );

    }

    ImGui_ImplSdlGL3_Shutdown();
    SDL_DestroyWindow( m_window );
    SDL_Quit();

    return 0;
}