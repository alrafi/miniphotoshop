#include "BMP.hpp"
#include <iostream>
#include "Histogram.hpp"
#include "HistogramColor.hpp"
#include "Image.hpp"
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
            for (int i = 0; i < img.width; i++) {
                for (int j = 0; j < img.height; j++) {
                    if (img.isColor) {
                        Color c = img.getColorData(i,j);
                        SDL_SetRenderDrawColor(renderer, c.R, c.G, c.B, 0);
                    } else {
                        int g = img.getGreyData(i,j);
                        SDL_SetRenderDrawColor(renderer, g, g, g, 0);
                    }
                    SDL_RenderDrawPoint(renderer,j,i);
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
    // PGM pgm("baboon.ascii.pgm");
    // Image image;
    // pgm.readFile(image);

    // cout << image.width << endl;
    // cout << image.height << endl;
    // for(int i = 0; i<10; i++){
    //     cout << (unsigned int) image.greyData[i] << endl;
    // }
    // pgm.writeFile(image, "anjay");
    if (argc < 2) {
        cout << "error" << endl;
    } else {
        BMP bmp(argv[1]);
        BMP bmp2(argv[1]);
        Image image;
        bmp.readFile(image);
        Histogram histogram(image);
        // image.contrastStretching(50,200,0.2,2,0.2,25,250);
        cout << "drawing" << endl;
        image = histogram.createImage();
        image.show();
        drawImage(image);
        bmp.writeFile(image, "tes");
    }

    return 0;
}