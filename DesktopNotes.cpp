//----------------------------
#include <QUuid>
#include <QMouseEvent>
#include <QMessageBox>
//----------------------------
#include "SQL_query.h"
//----------------------------
#include "DesktopNotes.h"
#include "ui_DesktopNotes.h"
//----------------------------

DesktopNotes::DesktopNotes(QWidget *parent) : QWidget(parent) , ui(new Ui::DesktopNotes) {

    ui->setupUi( this );

    setAttribute        ( Qt::WA_TranslucentBackground );
    setMouseTracking    ( true );
    setContextMenuPolicy( Qt::CustomContextMenu );
    setWindowFlags( Qt::SubWindow );

    m_DBase          = nullptr;
    m_IsMousePressed = false;

    m_ResizeGrip = new QSizeGrip( this );
    m_ResizeGrip->setVisible( true );

    updateGripPosition();

    ui->titleEdit->setPlaceholderText( tr("Заголовок заметки...") );
    ui->noteEdit ->setPlaceholderText( tr("Здесь Вы можете написать подробности заметки...") );
    ui->splitter ->setSizes( {200, 10} );

    ui->titleEdit->setMaxLength( NOTES_FIELD_TITLE_LEN );

    connect( ui->createButton, &QToolButton::clicked           , this, &DesktopNotes::createNote              );
    connect( ui->deleteButton, &QToolButton::clicked           , this, &DesktopNotes::deleteNote              );
    connect( ui->notesList   , &QListWidget::currentItemChanged, this, &DesktopNotes::reactOnSelectNote       );
    connect( ui->titleEdit   , &QLineEdit  ::textChanged       , this, &DesktopNotes::reactOnTitleNoteChanged );
    connect( ui->noteEdit    , &QTextEdit  ::textChanged       , this, &DesktopNotes::reactOnTextNoteChanged  );
}
//-------------------------------------------------------------------------------------------

DesktopNotes::~DesktopNotes() {
    delete ui;
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Инициализация
 * \param db Указатель на подключение к БД
 */
void DesktopNotes::init( QSqlDatabase* db ) {

    m_DBase = db;

    reload();
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Создание заметки
 */
void DesktopNotes::createNote() {

    QString title = ui->titleEdit->text();
    if( title.isEmpty() ) {
        return;
    }

    QString uuid = QUuid::createUuid().toString();
    QString text = ui->noteEdit ->toPlainText();

    Err err = createNoteDB( uuid, title, text );
    if( err.code > 0 ) {
        showError( tr("Возникла ошибка при создании заметки: %1").arg(err.text) );
        return;
    }

    QListWidgetItem* item = createNoteItem( uuid, title, text );

    ui->notesList->blockSignals( true );
    ui->notesList->setCurrentItem( item );
    ui->notesList->scrollToItem  ( item );
    ui->notesList->blockSignals( false );
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Удаление заметки
 */
void DesktopNotes::deleteNote() {

    QListWidgetItem* item = ui->notesList->currentItem();
    if( item == nullptr ) {
        showError( tr("Не выбрана заметка для удаления") );
        return;
    }

    QString uuid = item->data(UuidRole).toString();
    if( uuid.isEmpty() ) {
        showError( tr("Не удалось определить заметку") );
        return;
    }

    Err err = deleteNoteDB( uuid );
    if( !err.code ) {
        showError( err.text );
        return;
    }

    delete item;
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Перезагрузка заметок
 */
void DesktopNotes::reload() {

    ui->notesList->clear();

    QString sql = QString("SELECT * FROM %1").arg(TABLE_NOTES);

    QSqlQuery query( *m_DBase );
    if( !query.exec( sql ) ) {
        showError( tr("Не удалось восстановить заментки: %1").arg(query.lastError().text()) );
        return;
    }

    while( query.next() ) {
        QString uuid  = query.value(NOTES_FIELD_UUID ).toString();
        QString title = query.value(NOTES_FIELD_TITLE).toString();
        QString text  = query.value(NOTES_FIELD_TEXT ).toString();
        createNoteItem( uuid, title, text );
    }

    QListWidgetItem* item = ui->notesList->item( 0 );
    if( item == nullptr ) {
        return;
    }

    ui->notesList->setCurrentItem( item );
    ui->notesList->scrollToItem( item );
}
//-------------------------------------------------------------------------------------------

/*!
 * \brief Отображение ошибка в MessageBox
 * \param text Текст ошибки
 */
void DesktopNotes::showError( const QString& text ) {

    QMessageBox::critical( this, tr("Ошибка"), text );
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::updateGripPosition() {

    QSize gripSize = m_ResizeGrip->size();
    m_ResizeGrip->move( width () - gripSize.width(), height() - gripSize.height() );
}
//-------------------------------------------------------------------------------------------

void DesktopNotes::mousePressEvent( QMouseEvent *event ) {

    QWidget::mousePressEvent( event );

    if( event->buttons() & Qt::MiddleButton ) {
        close();
        return;
    }

    m_IsMousePressed = true;
    m_OldMousePos    = event->globalPos();

    QApplication::setOverrideCursor( Qt::ClosedHandCursor );
}
//------------------------------------------------------------------------------

void DesktopNotes::mouseReleaseEvent( QMouseEvent* event ) {

    QWidget::mouseReleaseEvent( event );

    m_IsMousePressed = false;
    QApplication::restoreOverrideCursor();
}
//-----------------------------------------------------------------------------

void DesktopNotes::mouseMoveEvent( QMouseEvent* event ) {

    QWidget::mouseMoveEvent( event );

    if( !m_IsMousePressed ) {
        return;
    }

    const QPoint delta = event->globalPos() - m_OldMousePos;
    move( x() + delta.x(), y() + delta.y() );

    m_OldMousePos = event->globalPos();
}
//------------------------------------------------------------------------------

void DesktopNotes::showEvent( QShowEvent* event ) {

    updateGripPosition();
    QWidget::showEvent( event );
}
//------------------------------------------------------------------------------

void DesktopNotes::resizeEvent( QResizeEvent* event ) {

    QWidget::resizeEvent( event );
    updateGripPosition();
}
//------------------------------------------------------------------------------
