#ifndef GLOBALS_HPP
#define GLOBALS_HPP

extern const int SCREEN_WIDTH = 1280;
extern const int SCREEN_HEIGHT = 720;
extern const int FPS = 60;
extern const int TICKS_PER_FRAME = 1000 / FPS;

extern bool paused = true;
extern bool showDeathMenu = false;
extern bool showMainMenu = true;
extern bool showOptionMenu = false;
extern bool gameRunning = true;

extern int BGMVolume = 50;
extern int SFXVolume = 100;
extern int frameTime = 0;
extern int delay = 0;
extern int playerScore = 0;
extern int maxScore = 0;
extern int countedFrame = 0;
extern int SpawnSpeed = 100;
extern int SpawnNumber = 1;

#endif