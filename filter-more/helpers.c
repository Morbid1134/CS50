#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row of pixels
    for (int i = 0; i < height; i++)
    {
        // and for each pixel in each column of this row
        for (int j = 0; j < width; j++)
        {
            // take a look at each pixels rgb values and average them up
            int average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3;
            // set each to the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row of pixels
    for (int i = 0; i < height; i++)
    {
        // save a buffer of the row
        RGBTRIPLE buffer[width];
        // and for each pixel in a column of this row
        for (int j = 0; j < width; j++)
        {
            // current pixel needs to be on opposite side of row
            // i.e. row size of 3, pixel 0 needs to be at position 2 (3 - (pixel + 1)) where 3 is
            // width pixel 1 at position 1 and pixel 2 at position 0
            int new_column = (width - (j + 1));
            buffer[new_column].rgbtRed = image[i][j].rgbtRed;
            buffer[new_column].rgbtBlue = image[i][j].rgbtBlue;
            buffer[new_column].rgbtGreen = image[i][j].rgbtGreen;
        }
        // for row in buffer, set as image output
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[j].rgbtRed;
            image[i][j].rgbtBlue = buffer[j].rgbtBlue;
            image[i][j].rgbtGreen = buffer[j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // buffer image
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    // for row in height
    for (int i = 0; i < height; i++)
    {
        // and for pixel in width
        for (int j = 0; j < width; j++)
        {
            // set current pixels average values to 0
            image[i][j].rgbtRed = 0;
            image[i][j].rgbtGreen = 0;
            image[i][j].rgbtBlue = 0;

            // set pixel_count to 0
            // and keep track of colors
            int pixel_count = 0;
            int red = 0;
            int blue = 0;
            int green = 0;

            // for pixels in relative 3x3 to this pixel
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // if target pixel exists
                    int target_y = i + (k - 1);
                    int target_x = j + (l - 1);
                    if (target_x >= 0 && target_x < width && target_y >= 0 && target_y < height)
                    {
                        // add it to average pixel values and increase counted pixels
                        red += buffer[target_y][target_x].rgbtRed;
                        green += buffer[target_y][target_x].rgbtGreen;
                        blue += buffer[target_y][target_x].rgbtBlue;
                        pixel_count++;
                    }
                }
            }
            // divide pixel by number of counted pixels
            image[i][j].rgbtRed = round(red / pixel_count);
            image[i][j].rgbtGreen = round(green / pixel_count);
            image[i][j].rgbtBlue = round(blue / pixel_count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // buffer image
    RGBTRIPLE buffer[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][j] = image[i][j];
        }
    }

    // for row in height
    for (int i = 0; i < height; i++)
    {
        // and for pixel in width
        for (int j = 0; j < width; j++)
        {
            // initialize Gx and Gy kernels of this pixel
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // set pixel_count to 0
            // and keep track of colors
            int pixel_count = 0;
            int tgx_red = 0;
            int tgx_green = 0;
            int tgx_blue = 0;
            int tgy_red = 0;
            int tgy_green = 0;
            int tgy_blue = 0;

            // for pixels in relative 3x3 to this pixel
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // if target pixel exists
                    int target_y = i + (k - 1);
                    int target_x = j + (l - 1);
                    if (target_x >= 0 && target_x < width && target_y >= 0 && target_y < height)
                    {
                        // multiple each value of the pixel by cooresponding position in kernal
                        // resulting in a target_Gx and target_Gy
                        tgx_red += buffer[target_y][target_x].rgbtRed * Gx[k][l];
                        tgx_green += buffer[target_y][target_x].rgbtGreen * Gx[k][l];
                        tgx_blue += buffer[target_y][target_x].rgbtBlue * Gx[k][l];
                        tgy_red += buffer[target_y][target_x].rgbtRed * Gy[k][l];
                        tgy_green += buffer[target_y][target_x].rgbtGreen * Gy[k][l];
                        tgy_blue += buffer[target_y][target_x].rgbtBlue * Gy[k][l];
                    }
                }
            }

            int tmp[3];
            tmp[0] = round(sqrt(pow(tgx_red, 2) + pow(tgy_red, 2)));
            tmp[1] = round(sqrt(pow(tgx_green, 2) + pow(tgy_green, 2)));
            tmp[2] = round(sqrt(pow(tgx_blue, 2) + pow(tgy_blue, 2)));
            for (int k = 0; k < 3; k++)
            {
                if (tmp[k] > 255)
                {
                    tmp[k] = 255;
                }
            }

            image[i][j].rgbtRed = tmp[0];
            image[i][j].rgbtGreen = tmp[1];
            image[i][j].rgbtBlue = tmp[2];
        }
    }

    return;
}
