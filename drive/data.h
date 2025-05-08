//
// Created by rgoodson on 5/8/2025.
//

#ifndef STORAGE_H
#define STORAGE_H
#include "../cmake-build-release/_deps/sdl3-src/include/SDL3/SDL_storage.h"

#include <vector>
#include <string>

namespace drive::data {

class RuntimeArchive {
public:
    RuntimeArchive() = default;
    RuntimeArchive(std::vector<const string>& load_order);
    ~RuntimeArchive() = default;
    RuntimeArchive(const RuntimeArchive &other) = delete;
    RuntimeArchive(RuntimeArchive &&other) noexcept = delete;
    RuntimeArchive & operator=(const RuntimeArchive &other) = delete;
    RuntimeArchive & operator=(RuntimeArchive &&other) noexcept = delete;
private:

};

class Context {
    public:
    Context();
    Context(const Context &other) = delete;
    Context(Context &&other) noexcept = delete;
    Context & operator=(const Context &other) = delete;
    Context & operator=(Context &&other) noexcept = delete;
    ~Context();
    static const SDL_Storage* const userStorage();
    static const SDL_Storage* const titleStorage();
private:
    static SDL_Storage* m_user_storage;
    static SDL_Storage* m_title_storage;
};



}

#endif //STORAGE_H
