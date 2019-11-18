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
        // PGM pgm(argv[1]);
        BMP bmp(argv[1]);
        // BMP bmp2(argv[1]);
        Image image;
        // pgm.readFile(image);
        bmp.readFile(image);
        // bmp.readFile(image2);
        int c = stoi(argv[2]);
        
        // Spektrum fourier(image);
        // HistogramColor hist(image);
        switch (c)
        {
        case 0:
            image.gaussianSmoothing();
            break;
        case 1:
            image.tresholding(50);
            break;
        case 2:
            image.gaussian();
            break;
        case 3:
            image.laplace();
            break;
        case 4:
            image.loG();
            break;
        case 5:
            image.sobel();
            break;
        case 6:
            image.prewitt();
            break;
        case 7:
            image.roberts(); 
            break;
        case 8:
            image.canny(stoi(argv[3])); 
            break;
        case 9:
            image.transformasiLog(stof(argv[3]));
            break;
        case 10:
            image.transformasiLogInv(stof(argv[3]));
            break;
        case 11:
            image.grayLevelSlicing();
            break;
        case 12:
            Image* imgs;
            imgs = image.bitPlaneSlicing();
            drawImage(imgs[stoi(argv[3])]);
            break;
        case 13:
            image.transformFourier();
            break;
        case 14:
            // image = hist.b->createImage();
            // hist.b->show();
            break;
        // case 15:
        // //     fourier.show();
        // //     image = fourier.getSpektrum();
        // //     break;
        // // case 16:
        // //     fourier.show();
        // //     image = fourier.balikan();
        case 17:
            image.tresholding(stoi(argv[3]),stoi(argv[4]));
            break;
        case 18:
            image.autoTresholding(stoi(argv[3]),stoi(argv[4]));
            break;
        case 19:
            image.canny(stoi(argv[3]));
            image.thinning();
            break;
        case 20:
            image.loG();
            image.tresholding(stod(argv[3]));
            image.thinning();
            break;
        default:
            break;
        }
        cout << "drawing" << endl;
        image.show();
        drawImage(image);
    }

    return 0;
}