#pragma once
#include "shadershop.hh"
#include "math.hh"

enum CanvasType
{
    kUNDEFINED = 0,
    kFILE = 1,
    kFRAMEBUFFER = 2
};

class Canvas
{
public:

    Canvas() {}
    ~Canvas();

    void create( int32_t startX, int32_t startY, int32_t sizeX, int32_t sizeY );
    void load( CanvasType type, std::string name, std::string filename = "" );
    void update();
    void render();

private:

    CanvasType m_type = kUNDEFINED;
    std::string name = "";
    std::string m_filename = "";
    bool m_show_canvas = true;
    int32_t m_channels = 0;

    int2 m_window_position;
    int2 m_window_size;
    int2 m_canvas_size;

    uint8_t* m_image = nullptr;
    GLuint m_image_id = 0;
    int2 m_image_size;
};