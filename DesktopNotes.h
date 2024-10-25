//----------------------------
#ifndef DESKTOPNOTES_H
#define DESKTOPNOTES_H
//----------------------------
#include <QWidget>
//----------------------------
QT_BEGIN_NAMESPACE
namespace Ui { class DesktopNotes; }
QT_END_NAMESPACE
//----------------------------
class QListWidgetItem;
//----------------------------

class DesktopNotes : public QWidget {

    Q_OBJECT

    enum CustomRoles {
        UuidRole = Qt::UserRole + 1,
        NoteRole,
    };

public:

    DesktopNotes(QWidget *parent = nullptr);
    ~DesktopNotes();

public: // API

    void createNote();
    void deleteNote();

    void reactOnSelectNote( QListWidgetItem* item, QListWidgetItem* );

private:

    Ui::DesktopNotes *ui;
};
//-------------------------------------------------------------------------------------------

#endif // DESKTOPNOTES_H
