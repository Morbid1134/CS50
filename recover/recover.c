#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover [raw filename]\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File couldn't be opened :(\n");
        return 1;
    }

    // store block
    BYTE *block = malloc(BLOCK_SIZE);
    if (block == NULL)
    {
        printf("Out of memory");
        return 1;
    }

    // set n to -1
    int n = -1;

    // image name
    char *filename = malloc(8);
    if (filename == NULL)
    {
        printf("Out of memory");
        return 1;
    }
    strcpy(filename, "000.jpg");
    FILE *image = fopen(filename, "w");

    // loop through blocks
    while (fread(block, sizeof(BYTE), BLOCK_SIZE, file))
    {
        // if start with signature
        if (block[0] == 255 && block[1] == 216 && block[2] == 255 && block[3] >= 224)
        {
            // close image
            fclose(image);

            // increase n by 1
            n++;

            // create new filename
            sprintf(filename, "%03i.jpg", n);

            // open new image file
            image = fopen(filename, "w");
        }
        // Copy block to image file
        fwrite(block, BLOCK_SIZE, 1, image);
    }

    fclose(file);
    fclose(image);
    free(filename);
    free(block);
}
