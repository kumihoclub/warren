//
// Created by rgoodson on 5/7/2025.
//

#include "../dbio.h"

#include "SDL3/SDL.h"

#define MAX_PATH 260

const sqlite3_io_methods drive::io::db::methods = {
    3,
    +[](sqlite3_file* hfile) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, void* data, int amount, sqlite3_int64 offset) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, const void* data, int amount, sqlite3_int64 offset) -> int { // xClose
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, sqlite3_int64 size) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int flags) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, sqlite3_int64* size) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int lock) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int lock) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int* hres_out) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int op, void* arg_p) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile) -> int {
        return 0;
    },
    +[](sqlite3_file* hfile) -> int {
        return 0;
    },
    +[](sqlite3_file* hfile, int pg, int pgsz, int, void volatile** hmap) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, int offset, int n, int flags) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile) -> void {
        // void
    },
    +[](sqlite3_file* hfile, int delete_flag) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, sqlite3_int64 offset, int amt, void** hh) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_file* hfile, sqlite3_int64 offset, void* h) -> int {
        return SQLITE_OK;
    }
};

//const sqlite3_file drive::io::db::file = { &methods };

const sqlite3_vfs drive::io::db::vfs = {
    3,
    sizeof(file),
    MAX_PATH,
    0,
    "sdl3",
    nullptr,
    +[](sqlite3_vfs *hvfs, const char* name, sqlite3_file *hfile, int flags, int *hout_flags) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *hvfs, const char* filename, int syncdir) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *hvfs, const char* filename, int flags, int *hres_out) -> int {
        return SQLITE_OK;
    },
    +[](  sqlite3_vfs *hvfs, const char* zRelative, int nfull, char *hfull) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *hvfs, const char* filename) -> void* {
        return nullptr;
    },
    +[](sqlite3_vfs *hvfs, int nbuf, char *hbuffer_out) -> void {
        // void
    },
    +[](sqlite3_vfs *pVfs,void *pH,const char *zSym) -> void(*)() {
        return nullptr;
    },
    +[](sqlite3_vfs *pVfs, void *pHandle) -> void {
        // void
    },
    +[](sqlite3_vfs *pVfs, int nBuf, char *zBuf) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pVfs, int microsec) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pVfs, double *prNow) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pVfs, int nBuf, char *zBuf) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pVfs, sqlite3_int64 *piNow) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pNotUsed, const char *zName, sqlite3_syscall_ptr pNewFunc) -> int {
        return SQLITE_OK;
    },
    +[](sqlite3_vfs *pNotUsed, const char *zName) -> void(*)() {
        return nullptr;
    },
    +[](sqlite3_vfs *p, const char *zName) -> const char* {
        return nullptr;
    }
};