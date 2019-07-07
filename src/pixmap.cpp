#include <cstdio>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "png.h"
#include "jpeglib.h"
#include "error.hpp"
#include "pixmap.hpp"


namespace dainty
{

PixmapImage::PixmapImage(const char * file_path) :
    data{nullptr}
{
    using boost::iequals;
    using boost::filesystem::extension;
    using std::fclose;
    using std::fopen;
    using std::string;

    string file_extension = extension(file_path);
    if (iequals(file_extension, ".png")) {
        png_image file;
        file.version = PNG_IMAGE_VERSION;
        file.opaque = nullptr;
        file.format = PNG_FORMAT_RGBA;
        format = PixmapFormat::rgba;

        int stride = 0;
        if (!png_image_begin_read_from_file(&file, file_path))
            throw Error{file.message};
        if ((data = (unsigned char *) malloc(PNG_IMAGE_SIZE(file))) == nullptr)
         {
            png_image_free(&file);
            throw Error{"Out of memory"};
        };
        if (!png_image_finish_read(&file, NULL, data, stride, NULL)) {
            png_image_free(&file);
            free(data);
            throw Error{file.message};
        };

        width = file.width;
        height = file.height;
    } else if (iequals(file_extension, ".jpg") || iequals(file_extension,
     ".jpeg")) {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;
        cinfo.err = jpeg_std_error(&jerr);
        jpeg_create_decompress(&cinfo);

        FILE * file;

        if ((file = fopen(file_path, "rb")) == nullptr) {
            throw Error{"Can not open file"};
        };
        jpeg_stdio_src(&cinfo, file);

        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);

        int row_stride = cinfo.output_width * cinfo.output_components;
        if ((data = (unsigned char *) malloc(row_stride * cinfo.output_height))
         == nullptr) {
            jpeg_destroy_decompress(&cinfo);
            fclose(file);
            throw Error{"Out of memory"};
        };

        unsigned char * scan_position = data;
        while (cinfo.output_scanline < cinfo.output_height) {
            jpeg_read_scanlines(&cinfo, &scan_position, 1);
            scan_position += row_stride;
        };

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(file);

        width = cinfo.output_width;
        height = cinfo.output_height;
        format = PixmapFormat::rgb;
    } else {
        throw Error{"Unrecognized file format"};
    };
};


PixmapImage::~PixmapImage()
{
    free(data);
};


unsigned char * PixmapImage::get_data()
{
    return data;
};

}
