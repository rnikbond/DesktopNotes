//----------------------------
#include "SQL_query.h"
//----------------------------
#include "DesktopNotes.h"
#include "ui_DesktopNotes.h"
//----------------------------

/*!
 * \brief Создание заметки в базе данных
 * \param uuid Удентификатор заметки
 * \param title Заголовок заметки
 * \param text Текст заметки
 * \return Структуру ошибки
 */
Err DesktopNotes::createNoteDB( const QString& uuid, const QString& title, const QString& text ) {

    const QString sql = QString("INSERT INTO %1 VALUES(:uuid, :title, :text)").arg(TABLE_NOTES);

    QSqlQuery query( *m_DBase );
    query.prepare( sql );
    query.bindValue(":uuid" , uuid );
    query.bindValue(":title", title);
    query.bindValue(":text" , text );

    if( !query.exec() ) {
        return Err( query.lastError().number(), query.lastError().text() );
    }

    return Err();
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Удаление заметки в базе данных
 * \param uuid Идентификатор заметки
 * \return Структуру ошибки
 */
Err DesktopNotes::deleteNoteDB( const QString& uuid ) {

    const QString sql = QString("DELETE FROM %1 WHERE %2 = :uuid").arg(TABLE_NOTES, NOTES_FIELD_UUID);

    QSqlQuery query( *m_DBase );
    query.prepare( sql );
    query.bindValue(":uuid" , uuid );

    if( !query.exec() ) {
        return Err( query.lastError().number(), query.lastError().text() );
    }

    return Err();
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Изменение заголовка заметки в базе данных
 * \param uuid Идентификатор заметки
 * \param title Заголовок
 * \return Структуру ошибки
 */
Err DesktopNotes::changeTitleNoteDB( const QString& uuid, const QString& title ) {

    const QString sql = QString("UPDATE %1 SET %2 = :title WHERE %3 = :uuid").arg(TABLE_NOTES, NOTES_FIELD_TITLE, NOTES_FIELD_UUID);

    QSqlQuery query( *m_DBase );
    query.prepare( sql );
    query.bindValue(":uuid" , uuid  );
    query.bindValue(":title", title );

    if( !query.exec() ) {
        return Err( query.lastError().number(), query.lastError().text() );
    }

    return Err();
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Изменение описания заметки в базе данных
 * \param uuid Идентификатор заметки
 * \param text Описание
 * \return Структуру ошибки
 */
Err DesktopNotes::changeTextNoteDB( const QString& uuid, const QString& text ) {

    const QString sql = QString("UPDATE %1 SET %2 = :title WHERE %3 = :uuid").arg(TABLE_NOTES, NOTES_FIELD_TEXT, NOTES_FIELD_UUID);

    QSqlQuery query( *m_DBase );
    query.prepare( sql );
    query.bindValue(":uuid" , uuid );
    query.bindValue(":title", text );

    if( !query.exec() ) {
        return Err( query.lastError().number(), query.lastError().text() );
    }

    return Err();
}
//-------------------------------------------------------------------------------------------

