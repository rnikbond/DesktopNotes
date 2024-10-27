//----------------------------
#include "DesktopNotes.h"
#include "ui_DesktopNotes.h"
//----------------------------

/*!
 * \brief Обработка выбора заметки в списке
 * \param item Указатель на выбранный элемент
 */
void DesktopNotes::reactOnSelectNote( QListWidgetItem* item, QListWidgetItem* ) {

    ui->titleEdit->clear();
    ui->noteEdit ->clear();

    if( item == nullptr ) {
        return;
    }

    ui->titleEdit->setText( item->data(Qt::DisplayRole).toString() );
    ui->noteEdit ->setText( item->data(NoteRole       ).toString() );
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Создание заметки в списке
 * \param uuid Удентификатор заметки
 * \param title Заголовок заметки
 * \param text Текст заметки
 * \return Указатель на созданный элемент списка
 */
QListWidgetItem* DesktopNotes::createNoteItem( const QString& uuid, const QString& title, const QString& text ) {

    QListWidgetItem* item = new QListWidgetItem( ui->notesList );
    item->setData( UuidRole       , uuid  );
    item->setData( NoteRole       , text  );
    item->setData( Qt::DisplayRole, title );

    return item;
}
//-------------------------------------------------------------------------------------------
