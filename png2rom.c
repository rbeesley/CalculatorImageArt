#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <png.h>

int main(int argc, char **argv)
{
    png_image image;
    png_bytep buffer;
    void *colormap;
    unsigned int imgsize;
    unsigned int rowstride;
    unsigned int numrows;
    unsigned int written;
    unsigned int row;
    FILE *fp;
    int rc;

    if (argc != 3) {
        fprintf(stderr, "usage: %s PNGFILEIN ROMFILEOUT\n", argv[0]);
        return 2;
    }

    /* Initialize the 'png_image' structure. */
    memset(&image, 0, sizeof image);
    image.version = PNG_IMAGE_VERSION;

    /* Begin to read the PNG file named by argv[1]. */
    if (png_image_begin_read_from_file(&image, argv[1]) == 0) {
        fprintf(stderr, "%s: error: %s\n", argv[1], image.message);
        return 1;
    }

    /* We expect to read color-mapped images. */
    image.format = PNG_FORMAT_RGB_COLORMAP;

    /* Image size is the ROM size. */
    rowstride = PNG_IMAGE_ROW_STRIDE(image);
    imgsize = PNG_IMAGE_BUFFER_SIZE(image, rowstride);
    numrows = image.height;

    /* Allocate memory to hold the image in this format. */
    buffer = malloc(imgsize);
    colormap = malloc(PNG_IMAGE_COLORMAP_SIZE(image));
    if (!buffer || !colormap) {
        fprintf(stderr, "Memory allocation error\n");
        free(buffer);
        free(colormap);
        png_image_free(&image);
        return 1;
    }

    if (png_image_finish_read(&image, NULL, buffer, 0, colormap) == 0) {
        fprintf(stderr, "%s: error: %s\n", argv[1], image.message);
        png_image_free(&image);
        free(buffer);
        free(colormap);
        return 1;
    }

    /* Write the ROM image named by argv[2]. */
    fp = fopen(argv[2], "wb");
    if (!fp) {
        perror(argv[2]);
        png_image_free(&image);
        free(buffer);
        free(colormap);
        return 1;
    }
    for (row = 0; row < numrows; row++) {
        png_bytep rowbuf = buffer + rowstride * (numrows - row - 1);

        written = fwrite(rowbuf, 1, rowstride, fp);
        if (written < rowstride) {
            break;
        }
    }

    if (row < numrows) {
        fprintf(stderr, "%s: Write error!\n", argv[2]);
    }
    rc = fclose(fp);
    if (rc == EOF) {
        perror(argv[2]);
    }
    png_image_free(&image);
    free(buffer);
    free(colormap);
    if (row < numrows || rc != 0) {
        return 1;
    }
    return 0;
}