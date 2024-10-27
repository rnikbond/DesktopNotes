//----------------------------
#ifndef DESKTOPNOTES_H
#define DESKTOPNOTES_H
//----------------------------
#include <QtSql>
#include <QWidget>
//----------------------------
#include "Err.h"
//----------------------------
QT_BEGIN_NAMESPACE
namespace Ui { class DesktopNotes; }
QT_END_NAMESPACE
//----------------------------
class QListWidgetItem;
//----------------------------
struct Err;
//----------------------------

class DesktopNotes : public QWidget {

    Q_OBJECT

    enum CustomRoles {
        UuidRole = Qt::UserRole + 1,
        NoteRole,
    };

    QSqlDatabase* m_DBase;
    Ui::DesktopNotes *ui;

public:

    DesktopNotes( QWidget* parent = nullptr );
    ~DesktopNotes();

    void init( QSqlDatabase* db );

private:

    void reload();
    void showError( const QString& text );

public: // API

    void createNote();
    void deleteNote();

private: // List Widget

    QListWidgetItem* createNoteItem( const QString& uuid, const QString& title, const QString& text );
    void reactOnSelectNote( QListWidgetItem* item, QListWidgetItem* );

private: // DataBase

    Err createNoteDB( const QString& uuid, const QString& title, const QString& text );
    Err deleteNoteDB( const QString& uuid );
};
//------------------------------------------------------------------------------------------

#endif // DESKTOPNOTES_H
//-------------------------------------------------------------------------------------------
