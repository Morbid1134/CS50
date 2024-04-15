// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// define a byte
typedef uint8_t BYTE;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // copy first header_size bytes to the output file

    BYTE header[HEADER_SIZE];
    fread(&header, HEADER_SIZE, 1, input);
    fwrite(&header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // while read is successful

    // create buffer for my segments size of 2 bytes 16 bits
    int16_t buffer;

    // while we can read segments
    while (fread(&buffer, sizeof(buffer), 1, input) != 0)
    {
        // multiply buffer by factor
        buffer = buffer * factor;
        // write bytes to output
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
