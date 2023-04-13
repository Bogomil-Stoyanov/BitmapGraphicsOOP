#ifndef BITMAPGRAPHICS_BITMAPIMAGEAPP_H
#define BITMAPGRAPHICS_BITMAPIMAGEAPP_H

#include "../Commands/CommandDispatcher.h"



class BitmapImageApp {

public:
    static BitmapImageApp &getInstance();
    void start();

private:
    BitmapImageApp();
    BitmapImageApp(const BitmapImageApp &other) = delete;
    BitmapImageApp &operator=(const BitmapImageApp &other) = delete;

};


#endif //BITMAPGRAPHICS_BITMAPIMAGEAPP_H
