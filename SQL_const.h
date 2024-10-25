//----------------------------
#ifndef SQL_CONST_H
#define SQL_CONST_H
//----------------------------
#include <QString>
//----------------------------

#define TABLE_NOTES       "notes"
#define NOTES_FIELD_UUID  "uuid"
#define NOTES_FIELD_TITLE "title_"
#define NOTES_FIELD_TEXT  "text_"

#define NOTES_FIELD_UUID_LEN  38
#define NOTES_FIELD_TITLE_LEN 100

QString CREATE_TBL_NOTES_SQL = QString("CREATE TABLE IF NOT EXISTS %1( "
                                          "%2 VARCHAR(%3),"
                                          "%4 VARCHAR(%5),"
                                          "%6 TEXT        "
                                       ");")
                               .arg(TABLE_NOTES)
                               .arg(NOTES_FIELD_UUID ).arg(NOTES_FIELD_UUID_LEN )
                               .arg(NOTES_FIELD_TITLE).arg(NOTES_FIELD_TITLE_LEN)
                               .arg(NOTES_FIELD_TEXT);

#endif // SQL_CONST_H
//----------------------------
