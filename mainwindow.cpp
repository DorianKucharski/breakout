#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gra.h"
#include <QString>
#include <QTimer>
#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QtCore>
#include <QFile>
#include <QString>
#include <QList>
#include <QApplication>

Gra *gra;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    pelny_ekran = 0;
    gra = new Gra();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zapisz_wyniki(int punkty, QString imie){
    QVector<QString>vimie;
    QVector<int>vpunkty;
    QFile plik("wyniki.txt");
    plik.open(QIODevice::ReadWrite);
    QDataStream odczyt(&plik);
    vimie << imie; vpunkty << punkty;
    for (int i = 0; i < 10; i++)
    {
       odczyt >> imie >> punkty;
       vimie << imie;
       vpunkty << punkty;
    }

    for (int i = 0; i < vpunkty.size(); i++) {
        for(int j=1; j<vpunkty.size()-i; j++)
            if(vpunkty[j-1]<vpunkty[j])
        {
           punkty = vpunkty[j-1]; imie = vimie[j-1];
           vpunkty[j-1] = vpunkty[j]; vimie[j-1] = vimie[j];
           vpunkty[j] = punkty; vimie[j] = imie;
        }
    }


    plik.flush();
    plik.close();

    QDataStream zapis(&plik);
    plik.open(QIODevice::ReadWrite);
    ui->listWidget->clear();
    for (int i = 0; i < 10; ++i) {
        ui->listWidget->addItem((QString("%1\t - \t %2").arg(vpunkty.at(i)).arg(vimie.at(i))));
         zapis << vimie.at(i) << vpunkty.at(i);
    }

    plik.flush();
    plik.close();

}

void MainWindow::odczytaj_wyniki()
{
    ui->listWidget->clear();
    int punkty;
    QString imie;
    QFile plik("wyniki.txt");
    plik.open(QIODevice::ReadOnly);
    QDataStream odczyt(&plik);
    for (int i = 0; i < 10; i++)
    {
       odczyt >> imie >> punkty;
       ui->listWidget->addItem((QString("%1\t - \t %2").arg(punkty).arg(imie)));
    }
    plik.flush();
    plik.close();
}

void MainWindow::on_przycisk_nowa_gra_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->okno_gra->setScene(gra->scene);
    ui->okno_gra->scale(ui->okno_gra->width() / gra->width(), ui->okno_gra->height() / gra->height());
    gra->start();
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(uaktualnij_wynik()));
    timer->start(15);
}


void MainWindow::on_przycisk_ustawienia_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void MainWindow::uaktualnij_wynik(){
   ui->napis_punkty->setText(QString("Punkty: %1").arg(gra->wynik));
   ui->napis_ilosc_zyc->setText(QString("Ilość żyć: %1").arg(gra->ilosc_zyc));
   if (gra->ilosc_zyc <= 0){
       timer->stop();
       ui->stackedWidget->setCurrentIndex(2);
       ui->napis_wynik->setText(QString("Twój wynik wynosi: %1 punktów").arg(gra->wynik));
   }
}


void MainWindow::on_przycisk_wyjscie_clicked()
{
    close();

}

void MainWindow::on_wprowadz_imie_returnPressed()
{
   zapisz_wyniki(gra->wynik, ui->wprowadz_imie->text());
   ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_przycisk_menu_glowne_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_przycisk_menu_glowne_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_przycisk_menu_glowne_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_przycisk_wyniki_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    odczytaj_wyniki();
}

void MainWindow::on_przycisk_autorzy_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pelny_ekran_clicked()
{
    pelny_ekran = 1;
    this->showFullScreen();
    qDebug() << "x" << this->width() << "y" << this->height();
}

void MainWindow::on_rozdzielczosc_currentIndexChanged(int index)
{
   if (index == 0){gra->rozdzielczoscx = 800; gra->rozdzielczoscy = 600; zmiana_rozdzielczosci();}
   if (index == 1){gra->rozdzielczoscx = 1280; gra->rozdzielczoscy = 720; zmiana_rozdzielczosci();}
   if (index == 2){gra->rozdzielczoscx = 1920; gra->rozdzielczoscy = 1080; zmiana_rozdzielczosci();}
}

void MainWindow::zmiana_rozdzielczosci(){

    if (pelny_ekran == 0) this->setFixedSize(gra->rozdzielczoscx, gra->rozdzielczoscy);
}

void MainWindow::on_okno_clicked()
{
    pelny_ekran = 0;
    this->showNormal();
    zmiana_rozdzielczosci();
}

void MainWindow::on_poziom_trudnosci_1_clicked()
{
    gra->poziom_trudnosci = 1;
}

void MainWindow::on_poziom_trudnosci_2_clicked()
{
    gra->poziom_trudnosci = 1.5;
}
void MainWindow::on_poziom_trudnosci_3_clicked()
{
    gra->poziom_trudnosci = 2;
}
