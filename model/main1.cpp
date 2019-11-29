#include "BMP.hpp"
#include "PPM.hpp"
#include "PGM.hpp"
#include <iostream>
#include "Histogram.hpp"
#include "HistogramColor.hpp"
#include "Image.hpp"
#include "Processing.hpp"
#include "Spektrum.hpp"
#include <SDL.h>

using namespace std;

void drawImage(Image& img) {
    // window 
    SDL_Window* window = NULL;

    // surface contained in window
    SDL_Surface* screenSurface = NULL;

    // init SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0) {
        cout << "Could not initialize sdl" << SDL_GetError() << endl; 
    } else {
        // create window
        window = SDL_CreateWindow( "SDL TUTORIAL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, img.width, img.height, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            cout << "Could not initialize window" << SDL_GetError() << endl;
        } else {
            SDL_Renderer *renderer;
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            for (int i = 0; i < img.height; i++) {
                for (int j = 0; j < img.width; j++) {
                    if (img.isColor) {
                        Color c = img.getColorData(j,i);
                        SDL_SetRenderDrawColor(renderer, c.R, c.G, c.B, 0);
                    } else {
                        int g = img.getGreyData(j,i);
                        SDL_SetRenderDrawColor(renderer, g, g, g, 0);
                    }
                    SDL_RenderDrawPoint(renderer,img.width-1-j,i);
                }
            }
            SDL_RenderPresent(renderer);
            cout << "isColor: " << img.isColor << endl;

            SDL_Delay(5000);

            // destroy window
            SDL_DestroyWindow(window);
        }
        // quit sdl subsystem
        SDL_Quit();
    }
}

int main(int argc, char** argv){
    if (argc < 2) {
        cout << "error" << endl;
    } else {
        // main prog
        BMP bmp(argv[1]);
        Image image;
        bmp.readFile(image);
        image.colorToGrayscale();
        image.canny(100);
        image.thinning();
        drawImage(image);
        image.transformHough(stoi(argv[2]),stoi(argv[3]),stoi(argv[4]));
        drawImage(image);
    }
    return 0;
}