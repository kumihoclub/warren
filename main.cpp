#include <iostream>
#include <sstream>
#include <string>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/sdl.h"
#include "SDL3/SDL_main.h"

#include "squirrel.h"

#include "leveldb/db.h"

static HSQUIRRELVM v = nullptr;

static leveldb::DB* db = nullptr;
static leveldb::Options options;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
//static SDL_AudioDeviceID audio_device = 0;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {

    SDL_SetAppMetadata("Warren Test", "1.0", "com.warrentest");

    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    if (!status.ok()) {
        SDL_Log("Couldn't initialize LevelDB: %s", status.ToString());
        return SDL_APP_FAILURE;
    }

    // Add 256 values to the database
    leveldb::WriteOptions writeOptions;
    for (unsigned int i = 0; i < 256; ++i)
    {
        std::ostringstream keyStream;
        keyStream << "Key" << i;

        std::ostringstream valueStream;
        valueStream << "Test data value: " << i;

        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }

    // Iterate over each item in the database and print them
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        std::cout << it->key().ToString() << " : " << it->value().ToString() << std::endl;
    }

    if (false == it->status().ok())
    {
        SDL_Log("An error was found during LevelDB scan: %s", it->status().ToString());
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
    if (v) { sq_close(v); }
    if (db) {delete db; db = nullptr;}
}
