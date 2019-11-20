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
        //baca huruf angka
        BMP bmp_0("char_0.bmp");
        BMP bmp_1("char_1.bmp");
        BMP bmp_2("char_2.bmp");
        BMP bmp_3("char_3.bmp");
        BMP bmp_4("char_4.bmp");
        BMP bmp_5("char_5.bmp");
        BMP bmp_6("char_6.bmp");
        BMP bmp_7("char_7.bmp");
        BMP bmp_8("char_8.bmp");
        BMP bmp_9("char_9.bmp");
        BMP bmp_a("char_a.bmp");
        BMP bmp_b("char_b.bmp");
        BMP bmp_c("char_c.bmp");
        BMP bmp_d("char_d.bmp");
        BMP bmp_e("char_e.bmp");
        BMP bmp_f("char_f.bmp");
        BMP bmp_g("char_g.bmp");
        BMP bmp_h("char_h.bmp");
        BMP bmp_i("char_i.bmp");
        BMP bmp_j("char_j.bmp");
        BMP bmp_k("char_k.bmp");
        BMP bmp_l("char_l.bmp");
        BMP bmp_m("char_m.bmp");
        BMP bmp_n("char_n.bmp");
        BMP bmp_o("char_o.bmp");
        BMP bmp_p("char_p.bmp");
        BMP bmp_q("char_q.bmp");
        BMP bmp_r("char_r.bmp");
        BMP bmp_s("char_s.bmp");
        BMP bmp_t("char_t.bmp");
        BMP bmp_u("char_u.bmp");
        BMP bmp_v("char_v.bmp");
        BMP bmp_w("char_w.bmp");
        BMP bmp_x("char_x.bmp");
        BMP bmp_y("char_y.bmp");
        BMP bmp_z("char_z.bmp");
        Image image_0,image_1,image_2,image_3,image_4,image_5,image_6,image_7,image_8,image_9;
        Image image_a,image_b,image_c,image_d,image_e,image_f,image_g,image_h,image_i,image_j,image_k,image_l,image_m,image_n,image_o,image_p,image_q,image_r,image_s,image_t,image_u,image_v,image_w,image_x,image_y,image_z;
        bmp_0.readFile(image_0);
        bmp_1.readFile(image_1);
        bmp_2.readFile(image_2);
        bmp_3.readFile(image_3);
        bmp_4.readFile(image_4);
        bmp_5.readFile(image_5);
        bmp_6.readFile(image_6);
        bmp_7.readFile(image_7);
        bmp_8.readFile(image_8);
        bmp_9.readFile(image_9);
        bmp_a.readFile(image_a);
        bmp_b.readFile(image_b);
        bmp_c.readFile(image_c);
        bmp_d.readFile(image_d);
        bmp_e.readFile(image_e);
        bmp_f.readFile(image_f);
        bmp_g.readFile(image_g);
        bmp_h.readFile(image_h);
        bmp_i.readFile(image_i);
        bmp_j.readFile(image_j);
        bmp_k.readFile(image_k);
        bmp_l.readFile(image_l);
        bmp_m.readFile(image_m);
        bmp_n.readFile(image_n);
        bmp_o.readFile(image_o);
        bmp_p.readFile(image_p);
        bmp_q.readFile(image_q);
        bmp_r.readFile(image_r);
        bmp_s.readFile(image_s);
        bmp_t.readFile(image_t);
        bmp_u.readFile(image_u);
        bmp_v.readFile(image_v);
        bmp_w.readFile(image_w);
        bmp_x.readFile(image_x);
        bmp_y.readFile(image_y);
        bmp_z.readFile(image_z);

        // convert to binary
        image_0.colorToGrayscale();
        image_0.tresholding(150);
        image_1.colorToGrayscale();
        image_1.tresholding(150);
        image_2.colorToGrayscale();
        image_2.tresholding(150);
        image_3.colorToGrayscale();
        image_3.tresholding(150);
        image_4.colorToGrayscale();
        image_4.tresholding(150);
        image_5.colorToGrayscale();
        image_5.tresholding(150);
        image_6.colorToGrayscale();
        image_6.tresholding(150);
        image_7.colorToGrayscale();
        image_7.tresholding(150);
        image_8.colorToGrayscale();
        image_8.tresholding(150);
        image_9.colorToGrayscale();
        image_9.tresholding(150);
        image_a.colorToGrayscale();
        image_a.tresholding(150);
        image_b.colorToGrayscale();
        image_b.tresholding(150);
        image_c.colorToGrayscale();
        image_c.tresholding(150);
        image_d.colorToGrayscale();
        image_d.tresholding(150);
        image_e.colorToGrayscale();
        image_e.tresholding(150);
        image_f.colorToGrayscale();
        image_f.tresholding(150);
        image_g.colorToGrayscale();
        image_g.tresholding(150);
        image_h.colorToGrayscale();
        image_h.tresholding(150);
        image_i.colorToGrayscale();
        image_i.tresholding(150);
        image_j.colorToGrayscale();
        image_j.tresholding(150);
        image_k.colorToGrayscale();
        image_k.tresholding(150);
        image_l.colorToGrayscale();
        image_l.tresholding(150);
        image_m.colorToGrayscale();
        image_m.tresholding(150);
        image_n.colorToGrayscale();
        image_n.tresholding(150);
        image_o.colorToGrayscale();
        image_o.tresholding(150);
        image_p.colorToGrayscale();
        image_p.tresholding(150);
        image_q.colorToGrayscale();
        image_q.tresholding(150);
        image_r.colorToGrayscale();
        image_r.tresholding(150);
        image_s.colorToGrayscale();
        image_s.tresholding(150);
        image_t.colorToGrayscale();
        image_t.tresholding(150);
        image_u.colorToGrayscale();
        image_u.tresholding(150);
        image_v.colorToGrayscale();
        image_v.tresholding(150);
        image_w.colorToGrayscale();
        image_w.tresholding(150);
        image_x.colorToGrayscale();
        image_x.tresholding(150);
        image_y.colorToGrayscale();
        image_y.tresholding(150);
        image_z.colorToGrayscale();
        image_z.tresholding(150);

        // main prog
        BMP bmp(argv[1]);
        Image image;
        Image mask;
        Image smearing;
        Image* tes;
        int count;
        cout<<"flag10"<<endl;
        bmp.readFile(image);
        image.colorToGrayscale();
        cout<<"flag10"<<endl;
        mask = image;
        cout<<"flag10"<<endl;
        mask.citraNegativeGrayscale();
        cout<<"flag10"<<endl;
        mask.tresholding(220);
        cout<<"flag10"<<endl;
        mask.dilation(2);
        cout<<"flag10"<<endl;
        mask.penapisRatio(stof(argv[2]), stof(argv[3]));
        cout<<"flag10"<<endl;
        image.crop(mask);
        cout<<"flag10"<<endl;
        image.tresholding(stoi(argv[4]));
        cout<<"flag10"<<endl;
        image.thinning();
        cout<<"flag10"<<endl;
        image.resizePixels(160, 80);
        cout<<"flag10"<<endl;
        image.penapisArea(0.01 * image.size, image.size);
        smearing = image;
        smearing.smearing(stoi(argv[5]));
        tes = image.ekstraksi(smearing, &count);
        cout<<"flag10"<<endl;
        for (int i=0; i<count; i++){
            tes[i].crop();
            tes[i].resizePixels(80, 130);
            drawImage(tes[i]);
        }
        cout << "Plat Number: ";
        for (int i=count-1; i>=0; i--){
            int maks = 0;
            char val =' ';
            if (maks < tes[i].pixelMatching(image_0)){
                maks = tes[i].pixelMatching(image_0);
                val = '0';
            }
            if (maks < tes[i].pixelMatching(image_1)){
                maks = tes[i].pixelMatching(image_1);
                val = '1';
            }
            if (maks < tes[i].pixelMatching(image_2)){
                maks = tes[i].pixelMatching(image_2);
                val = '2';
            }
            if (maks < tes[i].pixelMatching(image_3)){
                maks = tes[i].pixelMatching(image_3);
                val = '3';
            }
            if (maks < tes[i].pixelMatching(image_4)){
                maks = tes[i].pixelMatching(image_4);
                val = '4';
            }
            if (maks < tes[i].pixelMatching(image_5)){
                maks = tes[i].pixelMatching(image_5);
                val = '5';
            }
            if (maks < tes[i].pixelMatching(image_6)){
                maks = tes[i].pixelMatching(image_6);
                val = '6';
            }
            if (maks < tes[i].pixelMatching(image_7)){
                maks = tes[i].pixelMatching(image_7);
                val = '7';
            }
            if (maks < tes[i].pixelMatching(image_8)){
                maks = tes[i].pixelMatching(image_8);
                val = '8';
            }
            if (maks < tes[i].pixelMatching(image_9)){
                maks = tes[i].pixelMatching(image_9);
                val = '9';
            }
            if (maks < tes[i].pixelMatching(image_a)){
                maks = tes[i].pixelMatching(image_a);
                val = 'A';
            }
            if (maks < tes[i].pixelMatching(image_b)){
                maks = tes[i].pixelMatching(image_b);
                val = 'B';
            }
            if (maks < tes[i].pixelMatching(image_c)){
                maks = tes[i].pixelMatching(image_c);
                val = 'C';
            }
            if (maks < tes[i].pixelMatching(image_d)){
                maks = tes[i].pixelMatching(image_d);
                val = 'D';
            }
            if (maks < tes[i].pixelMatching(image_e)){
                maks = tes[i].pixelMatching(image_e);
                val = 'E';
            }
            if (maks < tes[i].pixelMatching(image_f)){
                maks = tes[i].pixelMatching(image_f);
                val = 'F';
            }
            if (maks < tes[i].pixelMatching(image_g)){
                maks = tes[i].pixelMatching(image_g);
                val = 'G';
            }
            if (maks < tes[i].pixelMatching(image_h)){
                maks = tes[i].pixelMatching(image_h);
                val = 'h';
            }
            if (maks < tes[i].pixelMatching(image_i)){
                maks = tes[i].pixelMatching(image_i);
                val = 'I';
            }
            if (maks < tes[i].pixelMatching(image_j)){
                maks = tes[i].pixelMatching(image_j);
                val = 'J';
            }
            if (maks < tes[i].pixelMatching(image_k)){
                maks = tes[i].pixelMatching(image_k);
                val = 'K';
            }
            if (maks < tes[i].pixelMatching(image_l)){
                maks = tes[i].pixelMatching(image_l);
                val = 'L';
            }
            if (maks < tes[i].pixelMatching(image_m)){
                maks = tes[i].pixelMatching(image_m);
                val = 'M';
            }
            if (maks < tes[i].pixelMatching(image_n)){
                maks = tes[i].pixelMatching(image_n);
                val = 'N';
            }
            if (maks < tes[i].pixelMatching(image_o)){
                maks = tes[i].pixelMatching(image_o);
                val = 'O';
            }
            if (maks < tes[i].pixelMatching(image_p)){
                maks = tes[i].pixelMatching(image_p);
                val = 'p';
            }
            if (maks < tes[i].pixelMatching(image_q)){
                maks = tes[i].pixelMatching(image_q);
                val = 'Q';
            }
            if (maks < tes[i].pixelMatching(image_r)){
                maks = tes[i].pixelMatching(image_r);
                val = 'R';
            }
            if (maks < tes[i].pixelMatching(image_s)){
                maks = tes[i].pixelMatching(image_s);
                val = 'S';
            }
            if (maks < tes[i].pixelMatching(image_t)){
                maks = tes[i].pixelMatching(image_t);
                val = 'T';
            }
            if (maks < tes[i].pixelMatching(image_u)){
                maks = tes[i].pixelMatching(image_u);
                val = 'U';
            }
            if (maks < tes[i].pixelMatching(image_v)){
                maks = tes[i].pixelMatching(image_v);
                val = 'V';
            }
            if (maks < tes[i].pixelMatching(image_w)){
                maks = tes[i].pixelMatching(image_w);
                val = 'W';
            }
            if (maks < tes[i].pixelMatching(image_x)){
                maks = tes[i].pixelMatching(image_x);
                val = 'X';
            }
            if (maks < tes[i].pixelMatching(image_y)){
                maks = tes[i].pixelMatching(image_y);
                val = 'Y';
            }
            if (maks < tes[i].pixelMatching(image_z)){
                maks = tes[i].pixelMatching(image_z);
                val = 'Z';
            }
            cout << val;
        }
        cout << endl;
    }

    return 0;
}