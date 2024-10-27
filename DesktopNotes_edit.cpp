//----------------------------
#include "DesktopNotes.h"
#include "ui_DesktopNotes.h"
//----------------------------

void DesktopNotes::reactOnTitleNoteChanged() {

    QListWidgetItem* item = ui->notesList->currentItem();
    if( item == nullptr ) {
        return;
    }

    QString uuid = item->data(UuidRole).toString();
    if( uuid.isEmpty() ) {
        showError( tr("Ошибки при изменении заголовка заметки: Не удалось определить заметку") );
        return;
    }

    QString title = ui->titleEdit->text();

    Err err = changeTitleNoteDB( uuid, title );
    if( err.code > 0 ) {
        showError( tr("Ошибки при изменении заголовка заметки: %1").arg(err.text) );
        return;
    }

    item->setData( Qt::DisplayRole, title );
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::reactOnTextNoteChanged() {

    QListWidgetItem* item = ui->notesList->currentItem();
    if( item == nullptr ) {
        return;
    }

    QString uuid = item->data(UuidRole).toString();
    if( uuid.isEmpty() ) {
        showError( tr("Ошибки при изменении описания заметки: Не удалось определить заметку") );
        return;
    }

    QString text = ui->noteEdit->toPlainText();

    Err err = changeTextNoteDB( uuid, text );
    if( err.code > 0 ) {
        showError( tr("Ошибки при изменении описания заметки: %1").arg(err.text) );
        return;
    }

    item->setData( NoteRole       , text );
    item->setData( Qt::ToolTipRole, text );
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::showNoteInfo( QListWidgetItem* item ) {

    ui->titleEdit->blockSignals( true );
    ui->noteEdit ->blockSignals( true );

    ui->titleEdit->clear();
    ui->noteEdit ->clear();

    ui->titleEdit->blockSignals( false );
    ui->noteEdit ->blockSignals( false );


    if( item == nullptr ) {
        return;
    }

    ui->titleEdit->blockSignals( true );
    ui->noteEdit ->blockSignals( true );

    ui->titleEdit->setText( item->data(Qt::DisplayRole).toString() );
    ui->noteEdit ->setText( item->data(NoteRole       ).toString() );

    ui->titleEdit->blockSignals( false );
    ui->noteEdit ->blockSignals( false );

}
//-------------------------------------------------------------------------------------------
