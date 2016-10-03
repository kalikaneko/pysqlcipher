#ifndef PYSQLITE_BLOB_H
#define PYSQLITE_BLOB_H

#include "connection.h"
#include "sqlite3.h"


/* Calls where error could be set.  We assume that a variable 'res' is set.  Also need the db to take
   the mutex on */
#define _PYSQLITE_CALL_E(db, x)                     \
do {                                                \
  Py_BEGIN_ALLOW_THREADS                            \
    {                                               \
      sqlite3_mutex_enter(sqlite3_db_mutex(db));    \
      x;                                            \
      if(res!=SQLITE_OK && res!=SQLITE_DONE && res!=SQLITE_ROW) \
        set_errmsg(sqlite3_errmsg((db)));      \
      sqlite3_mutex_leave(sqlite3_db_mutex(db));    \
    }                                               \
  Py_END_ALLOW_THREADS;                             \
 } while(0)


/* call from blob code */
#define PYSQLITE_BLOB_CALL(y) _PYSQLITE_CALL_E(self->connection->db, y)
/* BLOB TYPE */
struct pysqlite_Blob {
  PyObject_HEAD
  pysqlite_Connection *connection;
  sqlite3_blob *pBlob;
  unsigned inuse;                 /* track if we are in use preventing concurrent thread mangling */
  int curoffset;                  /* SQLite only supports 32 bit signed int offsets */
  PyObject *weakreflist;          /* weak reference tracking */
};

typedef struct pysqlite_Blob pysqlite_Blob;

static PyTypeObject pysqlite_BlobType;
static PyTypeObject pysqlite_BlobType;
static PyTypeObject ZeroBlobBindType;
void
pysqlite_Blob_init(pysqlite_Blob *self, pysqlite_Connection *connection, sqlite3_blob *blob);


#endif
