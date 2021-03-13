#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = (int) gray;
            image[i][j].rgbtGreen = (int)gray;
            image[i][j].rgbtRed = (int)gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
           RGBTRIPLE temp;
           temp = image[i][j];
           image[i][j] = image[i][width - j - 1];
           image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int mb[3][3] = {{1, 1, 1},
                    {1, 1, 1},
                    {1, 1, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumb = 0;
            int sumg = 0;
            int sumr = 0;
            if (i < height -1 && j < width - 1 && i > 0 && j > 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        sumb += mb[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                        sumg += mb[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                        sumr += mb[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 9.0);
                temp[i][j].rgbtGreen = round(sumg / 9.0);
                temp[i][j].rgbtRed = round(sumr / 9.0);
            }
            if (i == 0 && j > 0 && j < width -1)
            {
                for (int o = 0; o < 2; o++)
                {
                    for (int g = 0; g < 3; g++)
                    {
                        sumb += mb[o][g] * image[i + o][j - 1 + g].rgbtBlue;
                        sumg += mb[o][g] * image[i + o][j - 1 + g].rgbtGreen;
                        sumr += mb[o][g] * image[i + o][j - 1 + g].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 6.0);
                temp[i][j].rgbtGreen = round(sumg / 6.0);
                temp[i][j].rgbtRed = round(sumr / 6.0);
            }
            if (i == height - 1 && j > 0 && j < width -1)
            {
                for (int y = 0; y < 2; y++)
                {
                    for (int u = 0; u < 3; u++)
                    {
                        sumb += mb[y][u] * image[i - y][j - 1 + u].rgbtBlue;
                        sumg += mb[y][u] * image[i - y][j - 1 + u].rgbtGreen;
                        sumr += mb[y][u] * image[i - y][j - 1 + u].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 6.0);
                temp[i][j].rgbtGreen = round(sumg / 6.0);
                temp[i][j].rgbtRed = round(sumr / 6.0);
            }
            if (j == 0 && i > 0 && i < height - 1)
            {
                for (int r = 0; r < 3; r++)
                {
                    for (int t = 0; t < 2; t++)
                    {
                        sumb += mb[r][t] * image[i - 1 + r][j + t].rgbtBlue;
                        sumg += mb[r][t] * image[i - 1 + r][j + t].rgbtGreen;
                        sumr += mb[r][t] * image[i - 1 + r][j + t].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 6.0);
                temp[i][j].rgbtGreen = round(sumg / 6.0);
                temp[i][j].rgbtRed = round(sumr / 6.0);
            }
            if (j == width - 1 && i > 0 && i < height - 1)
            {
                for (int n = 0; n < 3; n++)
                {
                    for (int m = 0; m < 2; m++)
                    {
                        sumb += mb[n][m] * image[i - 1 + n][j - m].rgbtBlue;
                        sumg += mb[n][m] * image[i - 1 + n][j - m].rgbtGreen;
                        sumr += mb[n][m] * image[i - 1 + n][j - m].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 6.0);
                temp[i][j].rgbtGreen = round(sumg / 6.0);
                temp[i][j].rgbtRed = round(sumr / 6.0);
            }
            if (i == 0 && j == 0)
            {
                for (int q = 0; q < 2; q++)
                {
                    for (int w = 0; w < 2; w++)
                    {
                        sumb += mb[q][w] * image[i + q][j + w].rgbtBlue;
                        sumg += mb[q][w] * image[i + q][j + w].rgbtGreen;
                        sumr += mb[q][w] * image[i + q][j + w].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 4.0);
                temp[i][j].rgbtGreen = round(sumg / 4.0);
                temp[i][j].rgbtRed = round(sumr / 4.0);
            }
            if (i == height - 1 && j == width - 1)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int s = 0; s < 2; s++)
                    {
                        sumb += mb[a][s] * image[i - 1 + a][j - 1 + s].rgbtBlue;
                        sumg += mb[a][s] * image[i - 1 + a][j - 1 + s].rgbtGreen;
                        sumr += mb[a][s] * image[i - 1 + a][j - 1 + s].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 4.0);
                temp[i][j].rgbtGreen = round(sumg / 4.0);
                temp[i][j].rgbtRed = round(sumr / 4.0);
            }
            if (i == height - 1 && j == 0)
            {
                for (int z = 0; z < 2; z++)
                {
                    for (int x = 0; x < 2; x++)
                    {
                        sumb += mb[z][x] * image[i - 1 + z][j + x].rgbtBlue;
                        sumg += mb[z][x] * image[i - 1 + z][j + x].rgbtGreen;
                        sumr += mb[z][x] * image[i - 1 + z][j + x].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 4.0);
                temp[i][j].rgbtGreen = round(sumg / 4.0);
                temp[i][j].rgbtRed = round(sumr / 4.0);
            }
            if (i == 0 && j == width - 1)
            {
                for (int gg = 0; gg < 2; gg++)
                {
                    for (int ez = 0; ez < 2; ez++)
                    {
                        sumb += mb[gg][ez] * image[i + gg][j - 1 + ez].rgbtBlue;
                        sumg += mb[gg][ez] * image[i + gg][j - 1 + ez].rgbtGreen;
                        sumr += mb[gg][ez] * image[i + gg][j - 1 + ez].rgbtRed;
                    }
                }
                temp[i][j].rgbtBlue = round(sumb / 4.0);
                temp[i][j].rgbtGreen = round(sumg / 4.0);
                temp[i][j].rgbtRed = round(sumr / 4.0);
            }
            }
        }
    for (int h = 0; h < height; h++)
    {
        for (int b = 0; b < width; b++)
        {
            image[h][b] = temp[h][b];
        }
    }
    return;
    
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
        
    };
    int gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int xb = 0; 
            int xg = 0; 
            int xr = 0;
            int yb = 0;
            int yg = 0;
            int yr = 0;
            if (i < height - 1 && j < width - 1 && i > 0 && j > 0)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        xb += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                        xg += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                        xr += gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                        yb += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                        yg += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                        yr += gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
                
            }
            if (i == 0 && j > 0 && j < width - 1)
            {
                for (int o = 0; o < 2; o++)
                {
                    for (int g = 0; g < 3; g++)
                    {
                        xb += gx[o + 1][g] * image[i + o][j - 1 + g].rgbtBlue;
                        xg += gx[o + 1][g] * image[i + o][j - 1 + g].rgbtGreen;
                        xr += gx[o + 1][g] * image[i + o][j - 1 + g].rgbtRed;
                        yb += gy[o + 1][g] * image[i + o][j - 1 + g].rgbtBlue;
                        yg += gy[o + 1][g] * image[i + o][j - 1 + g].rgbtGreen;
                        yr += gy[o + 1][g] * image[i + o][j - 1 + g].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                for (int y = 0; y < 2; y++)
                {
                    for (int u = 0; u < 3; u++)
                    {
                        xb += gx[y][u] * image[i - 1 + y][j - 1 + u].rgbtBlue;
                        xg += gx[y][u] * image[i - 1 + y][j - 1 + u].rgbtGreen;
                        xr += gx[y][u] * image[i - 1 + y][j - 1 + u].rgbtRed;
                        yb += gy[y][u] * image[i - 1 + y][j - 1 + u].rgbtBlue;
                        yg += gy[y][u] * image[i - 1 + y][j - 1 + u].rgbtGreen;
                        yr += gy[y][u] * image[i - 1 + y][j - 1 + u].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (j == 0 && i > 0 && i < height - 1)
            {
                for (int r = 0; r < 3; r++)
                {
                    for (int t = 0; t < 2; t++)
                    {
                        xb += gx[r][t + 1] * image[i - 1 + r][j + t].rgbtBlue;
                        xg += gx[r][t + 1] * image[i - 1 + r][j + t].rgbtGreen;
                        xr += gx[r][t + 1] * image[i - 1 + r][j + t].rgbtRed;
                        yb += gy[r][t + 1] * image[i - 1 + r][j + t].rgbtBlue;
                        yg += gy[r][t + 1] * image[i - 1 + r][j + t].rgbtGreen;
                        yr += gy[r][t + 1] * image[i - 1 + r][j + t].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (j == width - 1 && i > 0 && i < height - 1)
            {
                for (int n = 0; n < 3; n++)
                {
                    for (int m = 0; m < 2; m++)
                    {
                        xb += gx[n][m] * image[i - 1 + n][j - 1 + m].rgbtBlue;
                        xg += gx[n][m] * image[i - 1 + n][j - 1 + m].rgbtGreen;
                        xr += gx[n][m] * image[i - 1 + n][j - 1 + m].rgbtRed;
                        yb += gy[n][m] * image[i - 1 + n][j - 1 + m].rgbtBlue;
                        yg += gy[n][m] * image[i - 1 + n][j - 1 + m].rgbtGreen;
                        yr += gy[n][m] * image[i - 1 + n][j - 1 + m].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (i == 0 && j == 0)
            {
                for (int q = 0; q < 2; q++)
                {
                    for (int w = 0; w < 2; w++)
                    {
                        xb += gx[q + 1][w + 1] * image[i + q][j + w].rgbtBlue;
                        xg += gx[q + 1][w + 1] * image[i + q][j + w].rgbtGreen;
                        xr += gx[q + 1][w + 1] * image[i + q][j + w].rgbtRed;
                        yb += gy[q + 1][w + 1] * image[i + q][j + w].rgbtBlue;
                        yg += gy[q + 1][w + 1] * image[i + q][j + w].rgbtGreen;
                        yr += gy[q + 1][w + 1] * image[i + q][j + w].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (i == height - 1 && j == width - 1)
            {
                for (int a = 0; a < 2; a++)
                {
                    for (int s = 0; s < 2; s++)
                    {
                        xb += gx[a][s] * image[i - 1 + a][j - 1 + s].rgbtBlue;
                        xg += gx[a][s] * image[i - 1 + a][j - 1 + s].rgbtGreen;
                        xr += gx[a][s] * image[i - 1 + a][j - 1 + s].rgbtRed;
                        yb += gy[a][s] * image[i - 1 + a][j - 1 + s].rgbtBlue;
                        yg += gy[a][s] * image[i - 1 + a][j - 1 + s].rgbtGreen;
                        yr += gy[a][s] * image[i - 1 + a][j - 1 + s].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (i == height - 1 && j == 0)
            {
                for (int z = 0; z < 2; z++)
                {
                    for (int x = 0; x < 2; x++)
                    {
                        xb += gx[z][x + 1] * image[i - 1 + z][j + x].rgbtBlue;
                        xg += gx[z][x + 1] * image[i - 1 + z][j + x].rgbtGreen;
                        xr += gx[z][x + 1] * image[i - 1 + z][j + x].rgbtRed;
                        yb += gy[z][x + 1] * image[i - 1 + z][j + x].rgbtBlue;
                        yg += gy[z][x + 1] * image[i - 1 + z][j + x].rgbtGreen;
                        yr += gy[z][x + 1] * image[i - 1 + z][j + x].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
            if (i == 0 && j == width - 1)
            {
                for (int gg = 0; gg < 2; gg++)
                {
                    for (int ez = 0; ez < 2; ez++)
                    {
                        xb += gx[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtBlue;
                        xg += gx[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtGreen;
                        xr += gx[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtRed;
                        yb += gy[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtBlue;
                        yg += gy[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtGreen;
                        yr += gy[gg + 1][ez] * image[i + gg][j - 1 + ez].rgbtRed;
                    }
                }
                int zb = round(sqrt((xb * xb) + (yb * yb)));
                int zg = round(sqrt((xg * xg) + (yg * yg)));
                int zr = round(sqrt((xr * xr) + (yr * yr)));
                if (zb > 255)
                {
                    temp[i][j].rgbtBlue = 255;
                }
                else
                {
                    temp[i][j].rgbtBlue = zb;
                }
                if (zg > 255)
                {
                    temp[i][j].rgbtGreen = 255;
                }
                else
                {
                    temp[i][j].rgbtGreen = zg;
                }
                if (zr > 255)
                {
                    temp[i][j].rgbtRed = 255;
                }
                else
                {
                    temp[i][j].rgbtRed = zr;
                }
            }
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int b = 0; b < width; b++)
        {
            image[h][b] = temp[h][b];
        }
    }
    return;
}
