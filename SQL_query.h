//----------------------------
#ifndef SQL_QUERY_H
#define SQL_QUERY_H
//----------------------------
#include <QString>
//----------------------------

#define TABLE_NOTES       "notes"
#define NOTES_FIELD_UUID  "uuid"
#define NOTES_FIELD_TITLE "title_"
#define NOTES_FIELD_TEXT  "text_"
//----------------------------
#define NOTES_FIELD_UUID_LEN  38
#define NOTES_FIELD_TITLE_LEN 100
//----------------------------

QString queryCreateNotes();
//----------------------------

#endif // SQL_QUERY_H
//----------------------------

