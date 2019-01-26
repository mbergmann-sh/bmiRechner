#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*************************/
    /* Interface vorbereiten */
    /*************************/
    initGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGUI()
{
    /************************/
    /* Default-Werte        */
    /***********************/
    getDefaults();

    /********************************************************************************************/
    /* Signale und Slots                                                                        */
    /* Maske: QObject::connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(aboutClicked())); */
    /********************************************************************************************/

    // Schaltflächen:
    QObject::connect(ui->doubleSpinBoxGewicht, SIGNAL(valueChanged(double)), this, SLOT(berechneBMI()));
    QObject::connect(ui->spinBoxAlter, SIGNAL(valueChanged(int)), this, SLOT(berechneBMI()));
    QObject::connect(ui->spinBoxGroesse, SIGNAL(valueChanged(int)), this, SLOT(berechneBMI()));
    // Radio-Knöpfe:
    QObject::connect(ui->radioButtonMann, SIGNAL(clicked(bool)), this, SLOT(berechneBMI()));
    QObject::connect(ui->radioButtonWeib, SIGNAL(clicked(bool)), this, SLOT(berechneBMI()));
    // Menüs:
    QObject::connect(ui->action_ueber_das_Programm, SIGNAL(triggered()), SLOT(about()));
    QObject::connect(ui->actionBerechnen, SIGNAL(triggered()), SLOT(berechneBMI()));
    QObject::connect(ui->actionWerte_zuruecksetzen, SIGNAL(triggered()), SLOT(resetForm()));
    QObject::connect(ui->actionProgramm_beenden, SIGNAL(triggered()), SLOT(close()));

    /* Erstberechnung */
    berechneBMI();
}

// BMI berechnen und auswerten
void MainWindow::berechneBMI()
{
    qDebug() << "berechneBMI() aufgerufen";
    /*******************************************************************/
    /* Formel: BMI = Körpermasse in kg / ( Körpergröße * Körpergröße) */
    /*****************************************************************/
    double bmi = 0.0, gewicht = 0.0, groesse = 0.0;
    gewicht = ui->doubleSpinBoxGewicht->value();
    groesse = (double)ui->spinBoxGroesse->value() / 100;
    // berechnen!
    bmi = (gewicht / (groesse * groesse));
    ui->labelBMI->setText(QString("%1").arg(bmi,0, 'f', 2));
    qDebug() << "BMI: " << bmi;

    // Auswertung MANN:
    /* Untergewicht */
    if(bmi < 16.0)
    {
        ui->labelAuswertung->setText("starkes Untergewicht");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/untergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-uebergewicht.png"));
    }
    if(bmi >= 16.0 && bmi < 17.0)
    {
        ui->labelAuswertung->setText("mäßiges Untergewicht");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/untergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-uebergewicht.png"));
    }
    if(bmi >= 17.0 && bmi < 20.0)
    {
        ui->labelAuswertung->setText("leichtes Untergewicht");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/leichtes-untergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-leichtes-untergewicht.png"));
    }
    /* Normalgewicht */
    if(bmi >= 20.0 && bmi <= 25.0)
    {
        ui->labelAuswertung->setText("Normalgewicht");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/normgewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-normgewicht.png"));
    }
    /* Präadipositas */
    if(bmi > 25.0 && bmi < 30.0)
    {
        ui->labelAuswertung->setText("leichtes Übergewicht");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/leichtes-uebergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-leichtes-uebergewicht.png"));
    }
    /* Adipositas I */
    if(bmi >= 30.0 && bmi < 35.0)
    {
        ui->labelAuswertung->setText("Adipositas Grad I");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/uebergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-uebergewicht.png"));
    }
    /* Adipositas II */
    if(bmi >= 35.0 && bmi < 40.0)
    {
        ui->labelAuswertung->setText("Adipositas Grad II");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/uebergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-uebergewicht.png"));
    }
    /* Adipositas III */
    if(bmi >= 40.0)
    {
        ui->labelAuswertung->setText("Adipositas Grad III");
        ui->btnAuswertungFarbe->setIcon(QPixmap(":/icon/uebergewicht.png"));
        ui->labelBewertung->setPixmap(QPixmap(":/icon/daumen-uebergewicht.png"));
    }
}

// Über das Programm
void MainWindow::about()
{
    QMessageBox messageBox (this);
    messageBox.setIconPixmap(QPixmap(":/icon/personenwaage.png"));
    messageBox.setText("<b>BMI-Rechner v0.98</b> <br /><i>Ein Programm zur Berechnung des Body Mass Index von Erwachsenen</i><br /><br />Autor: Michael Bergmann<br />Web: www.mbergmann-sh.de<br />Mail: mb@mbergmann-sh.de");

    messageBox.setWindowTitle(tr("Über das Programm"));
    QAbstractButton *okButton = messageBox.addButton(tr("Hab's gelesen"), QMessageBox::ActionRole);
    messageBox.exec();
}

// Default-Werte wiederherstellen
void MainWindow::resetForm()
{
    qDebug() << "resetForm() aufgerufen";
    // gespeicherte Defaults holen
    getDefaults();
    // Radio-Knöpfe zurücksetzen
    ui->radioButtonMann->setChecked(true);
}

// close() Event abfangen:
void MainWindow::closeEvent( QCloseEvent *event )
{
    // einen Dialog instanzieren:
    QMessageBox exitBox (this);
    // Eigene Schaltflächen definieren:
    QAbstractButton *exitButton = exitBox.addButton(tr("Programm beenden"), QMessageBox::ActionRole);
    QAbstractButton *stayButton = exitBox.addButton(tr("nicht beenden"), QMessageBox::ActionRole);
    // Dialog-Icon setzen:
    exitBox.setIconPixmap(QPixmap(":/icon/ende.png"));
    // Meldungstext:
    exitBox.setText("Möchten Sie das Programm wirklich beenden?");
    // Dialogfenster-Titel:
    exitBox.setWindowTitle(tr("Programm beenden"));

    // Dialog öffnen
    exitBox.exec();

    // Dialog Antwort des Benutzers auswerten:
    // Auf das close-Event reagieren
    if (exitBox.clickedButton() == exitButton)
    {
        // Damit die Anwendung schließt muß das Event akzeptiert werden
        // Anwendung schließen:
        event->accept();
    }

    else if (exitBox.clickedButton() == stayButton)
    {
        // Damit die Anwendung nicht schließt muß das Event verworfen werden
        // Beenden abbrechen
        event->ignore();
    }


}

void MainWindow::getDefaults()
{
    qDebug() << "getDefaults() aufgerufen";
    ui->doubleSpinBoxGewicht->setValue(p_Gewicht);
    ui->spinBoxAlter->setValue(p_Alter);
    ui->spinBoxGroesse->setValue(p_Size);
}
