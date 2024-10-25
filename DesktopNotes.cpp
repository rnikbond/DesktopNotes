//----------------------------
#include <QUuid>
//----------------------------
#include "DesktopNotes.h"
#include "ui_DesktopNotes.h"
//----------------------------

DesktopNotes::DesktopNotes(QWidget *parent) : QWidget(parent) , ui(new Ui::DesktopNotes) {

    ui->setupUi( this );

    connect( ui->createButton, &QToolButton::clicked           , this, &DesktopNotes::createNote        );
    connect( ui->deleteButton, &QToolButton::clicked           , this, &DesktopNotes::deleteNote        );
    connect( ui->notesList   , &QListWidget::currentItemChanged, this, &DesktopNotes::reactOnSelectNote );
}
//-------------------------------------------------------------------------------------------

DesktopNotes::~DesktopNotes() {
    delete ui;
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::createNote() {

    QString title = ui->titleEdit->text();
    QString note  = ui->noteEdit ->toPlainText();

    if( title.isEmpty() ) {
        return;
    }

    QListWidgetItem* item = new QListWidgetItem( ui->notesList );
    item->setData( UuidRole       , QUuid::createUuid() );
    item->setData( NoteRole       , note                );
    item->setData( Qt::DisplayRole, title               );

    ui->notesList->blockSignals( true );
    ui->notesList->setCurrentItem( item );
    ui->notesList->scrollToItem( item );
    ui->notesList->blockSignals( false );
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::deleteNote() {

    QListWidgetItem* item = ui->notesList->currentItem();
    if( item == nullptr ) {
        return;
    }

    delete item;
}
//-------------------------------------------------------------------------------------------

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
