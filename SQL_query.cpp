//----------------------------
#include "SQL_query.h"
//----------------------------

QString queryCreateNotes() {

    return QString("CREATE TABLE IF NOT EXISTS %1( "
                      "%2 VARCHAR(%3),"
                      "%4 VARCHAR(%5),"
                      "%6 TEXT        "
                   ");")
           .arg(TABLE_NOTES)
           .arg(NOTES_FIELD_UUID ).arg(NOTES_FIELD_UUID_LEN )
           .arg(NOTES_FIELD_TITLE).arg(NOTES_FIELD_TITLE_LEN)
           .arg(NOTES_FIELD_TEXT);
}
//-------------------------------------------------------------------------------------------

