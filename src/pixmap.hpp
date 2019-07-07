#pragma once

#include "macros.hpp"


namespace dainty
{

enum class FileFormat
{
    png,
    jpg
};


enum class PixmapFormat
{
    rgb,
    rgba
};


class PixmapImage
{
private:
    unsigned char * data;
    NUM_ATTR_WITH_GET(unsigned int, width);
    NUM_ATTR_WITH_GET(unsigned int, height);
    NUM_ATTR_WITH_GET(PixmapFormat, format);
public:
    PixmapImage(const char *);
    PixmapImage(PixmapImage &&) = delete;
    PixmapImage(const PixmapImage &) = delete;
    PixmapImage operator=(PixmapImage &&) = delete;
    PixmapImage operator=(const PixmapImage &) = delete;
    virtual ~PixmapImage();
public:
    unsigned char * get_data();
};

}
