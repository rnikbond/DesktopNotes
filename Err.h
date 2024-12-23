//----------------------------
#ifndef ERR_H
#define ERR_H
//----------------------------
#include <QString>
//----------------------------

struct Err {

    int     code; // Код ошибки
    QString text; // Описание ошибки

    Err() {
        code = 0;
    }

    Err( int code, const QString& text ) {
        this->code = code;
        this->text = text;
    }
};
//-------------------------------------------------------------------------------------------

#endif // ERR_H
//-------------------------------------------------------------------------------------------
