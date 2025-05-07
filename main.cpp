#include <iostream>
#include <sstream>
#include <string>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/sdl.h"
#include "SDL3/SDL_main.h"

#include "squirrel.h"

#include "sqlite3.h"

static HSQUIRRELVM v = nullptr;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static sqlite3* db = nullptr;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {

    SDL_SetAppMetadata("Warren Test", "1.0", "com.warrentest");

    if (sqlite3_open_v2("test", &db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_MEMORY|SQLITE_OPEN_NOMUTEX, nullptr) != SQLITE_OK) {
        SDL_Log("Couldn't initialize sqlite: %s",sqlite3_errmsg(db));
        return SDL_APP_FAILURE;
    }

    v = sq_open(1024);
    if (!v) {
        SDL_Log("Couldn't initialize Squirrel: %s",'NA');
        return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("warren-test", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) { return SDL_APP_SUCCESS; }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){

    /* just blank the screen. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    if (v) { sq_close(v); v = nullptr;}
    if (db) {sqlite3_close(db); db=nullptr;}
}
