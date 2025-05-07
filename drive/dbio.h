//
// Created by rgoodson on 5/7/2025.
//

#ifndef DBIO_H
#define DBIO_H

#include "sqlite3.h"

namespace drive::io::db {

extern const sqlite3_io_methods methods;
extern const sqlite3_file file;
extern const sqlite3_vfs vfs;

}

#endif //DBIO_H
