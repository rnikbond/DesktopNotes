//----------------------------
#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
//----------------------------
#include "SQL_query.h"
#include "DesktopNotes.h"
//----------------------------

QString createTables( QSqlDatabase* dbase );
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

    DesktopNotes notes;
    notes.init( &dbase );
    notes.show();

    return a.exec();
}
//-------------------------------------------------------------------------------------------

QString createTables( QSqlDatabase* dbase ) {

    QSqlQuery query( *dbase );
    if( !query.exec(queryCreateNotes()) ) {
        return query.lastError().text();
    }

    return QString();
}
//-------------------------------------------------------------------------------------------
