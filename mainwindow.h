#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QAbstractButton>
#include <QString>
#include <QColor>
#include <QColorDialog>
#include <QCloseEvent>
#include <QLibraryInfo>
#include <QTranslator>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // Hilfsroutine: Getter für Default-Werte
    void getDefaults();

public slots:
    void initGUI();
    void berechneBMI();
    void about();
    void resetForm();

private:
    Ui::MainWindow *ui;
    static const int p_Alter = 54;
    static const int p_Size = 193;
    const double p_Gewicht = 97.00;

protected:
        void closeEvent( QCloseEvent *event );

};

#endif // MAINWINDOW_H
