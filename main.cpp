//----------------------------
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
//----------------------------
#include "SQL_const.h"
#include "DesktopNotes.h"
//----------------------------

QString createTables(QSqlDatabase* dbase) {

    QSqlQuery query( *dbase );
    if( !query.exec(CREATE_TBL_NOTES_SQL) ) {
        return query.lastError().text();
    }

    return QString();
}
//-------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName( "E:/DesktopNotes.sqlite" );
    if( !dbase.open() ) {
        QMessageBox::critical( nullptr,
                              QObject:: tr("Ошибка подключения к базе данных"),
                              dbase.lastError().text());
        return 0;
    }

    QString errText = createTables(&dbase);
    if( !errText.isEmpty() ) {
        QMessageBox::critical( nullptr,
                               QObject:: tr("Ошибка инициализации таблиц в базе данных"),
                               errText);
        return 0;
    }

    DesktopNotes w;
    w.show();
    return a.exec();
}
//-------------------------------------------------------------------------------------------

