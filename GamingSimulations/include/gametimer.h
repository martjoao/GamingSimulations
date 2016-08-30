#include <Windows.h>

/*
    GameTimer class, responsible for handling time
*/
class GameTimer
{
private:
    //time at the creation of the current instance of GameTimer
    LARGE_INTEGER startTime;
    
    //float lastFrameTime;
    LARGE_INTEGER frequency;

public:
    float currentTime();

    LARGE_INTEGER getStartTime();
    //float getLastFrameTime();
    //float getDeltaT();

    bool init();
    void update();
    bool shutdown();


};