#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("BMI-Rechner");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("MB-SoftWorX");
    app.setOrganizationDomain("http://www.mbergmann-sh.de");

    /* Lokalisierung:             */
    /* Übersetzungsdatei f�r Qt: */

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    /* load our custom translations for this application */
    QTranslator myappTranslator;
    myappTranslator.load("myapp_" + QLocale::system().name());
    app.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();

    return app.exec();
}
