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
        // PPM ppm(argv[1]);
        Image image;
        Image mask;
        // pgm.readFile(image);
        bmp.readFile(image);
        // bmp.readFile(image2);
        // ppm.readFile(image);
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
            if(image.isColor){
                image.colorToGrayscale();
            }
            image.canny(stoi(argv[3]));
            image.thinning();
            break;
        case 20:
            // metode 1
            image.colorToGrayscale();
            mask = image;
            mask.citraNegativeGrayscale();
            // image.gaussianSmoothing();
            // image.autoTresholding(100, 10);
            mask.tresholding(220);
            // image.canny(100);
            // image.thinning();
            mask.dilation(2);
            mask.penapisRatio(stof(argv[3]), stof(argv[4]));
            // image.penapisArea(stoi(argv[3]), stoi(argv[4]));
            image.crop(mask);
            image.tresholding(stoi(argv[5]));
            image.thinning();
            image.resizePixels(160, 80);
            image.penapisArea(0.01 * image.size, image.size);

            cout << "flag" << endl;
            image = image.smearing(stoi(argv[6]));
            cout << "flag" << endl;
            // image.resizePixels(200, 69);
            break;
        case 21:
            // metode 1
            image.colorToGrayscale();
            mask = image;
            mask.citraNegativeGrayscale();
            // image.gaussianSmoothing();
            // image.autoTresholding(100, 10);
            mask.tresholding(220);
            // image.canny(100);
            // image.thinning();
            mask.dilation(2);
            mask.penapisRatio(stof(argv[3]), stof(argv[4]));
            // image.penapisArea(stoi(argv[3]), stoi(argv[4]));
            image.crop(mask);
            image.tresholding(stoi(argv[5]));
            image.thinning();
            image.resizePixels(160, 80);
            image.penapisArea(0.01 * image.size, image.size);
        default:
            break;
        }
        cout << "drawing" << endl;
        image.show();
        drawImage(image);
    }

    return 0;
}