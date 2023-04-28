#ifndef BITMAPGRAPHICS_BITMAPIMAGEAPP_H
#define BITMAPGRAPHICS_BITMAPIMAGEAPP_H

#include "../Commands/CommandDispatcher.h"
#include "../SessionManager/SessionManager.h"



class BitmapImageApp {

public:
    static BitmapImageApp &getInstance();
    void start();

private:
    BitmapImageApp() = default;
    BitmapImageApp(const BitmapImageApp &other) = delete;
    BitmapImageApp &operator=(const BitmapImageApp &other) = delete;
    SessionManager manager;
};


#endif //BITMAPGRAPHICS_BITMAPIMAGEAPP_H
