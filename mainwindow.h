#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int wynik;
    void zmiana_rozdzielczosci();

private slots:
    void on_przycisk_nowa_gra_clicked();
    void on_przycisk_ustawienia_clicked();
    void uaktualnij_wynik();
    void on_przycisk_wyjscie_clicked();
    void on_wprowadz_imie_returnPressed();
    void on_przycisk_menu_glowne_1_clicked();
    void on_przycisk_menu_glowne_2_clicked();
    void on_przycisk_menu_glowne_3_clicked();
    void on_przycisk_wyniki_clicked();
    void on_przycisk_autorzy_clicked();
    void on_pelny_ekran_clicked();
    void on_rozdzielczosc_currentIndexChanged(int index);
    void on_okno_clicked();
    void on_poziom_trudnosci_1_clicked();
    void on_poziom_trudnosci_2_clicked();
    void on_poziom_trudnosci_3_clicked();
    void zapisz_wyniki(int punkty, QString imie);
    void odczytaj_wyniki();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int pelny_ekran;

};



#endif // MAINWINDOW_H
