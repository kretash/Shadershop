#include "canvas.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

void Canvas::create( int32_t startX, int32_t startY, int32_t sizeX, int32_t sizeY )
{
    m_window_position = int2( startX, startY );
    m_window_size = int2( sizeX, sizeY );
    m_canvas_size = int2( sizeX - 64, sizeY - 64 );
}

void Canvas::load( CanvasType type, std::string name, std::string filename )
{
    m_type = type;
    name = name;
    m_filename = filename;

    if( type == kUNDEFINED ) return;

    if ( type == kFRAMEBUFFER ) 
    {

        return;
    }

    m_image = stbi_load( filename.c_str(), &m_image_size.x, &m_image_size.y, &m_channels, 0 );

    if( m_image == nullptr )
    {
        std::cerr << "Could not load image: " << filename << "\n";
        return;
    }

    glGenTextures( 1, &m_image_id );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_image_id );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    GLint internal_format = 0;
    GLint format = 0;

    if ( m_channels == 4 )
    {
        internal_format = GL_RGBA;
        format = GL_RGBA;
    }
    else if ( m_channels == 3 )
    {
        internal_format = GL_RGB;
        format = GL_RGB;
    }
    else if ( m_channels == 1 )
    {
        internal_format = GL_R;
        format = GL_R;
    }
    else
    {
        assert(false && "idk dude");
    }

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_image_size.x, m_image_size.y, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, m_image );

}

void Canvas::update()
{

}

void Canvas::render()
{
    if ( m_show_canvas )
    {
        ImGui::SetNextWindowSize( ImVec2( m_window_size.x, m_window_size.y ), ImGuiCond_FirstUseEver );

        ImGui::Begin( name.c_str(), &m_show_canvas );
        ImGui::SetCursorPos( ImVec2( m_window_position.x, m_window_position.y ) );
        ImGui::Image
        ( 
            ( ImTextureID ) m_image_id,
            ImVec2( m_canvas_size.x, m_canvas_size.y ),
            ImVec2( 0.0f, 0.0f ),
            ImVec2( 1.0f, 1.0f )
        );
        ImGui::End();
    }

}

Canvas::~Canvas() {
    stbi_image_free( m_image );
}