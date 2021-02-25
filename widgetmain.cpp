#include "widgetmain.h"
#include "ui_widgetmain.h"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMain)
{
    ui->setupUi(this);
}

WidgetMain::~WidgetMain()
{
    delete ui;
}

void WidgetMain::showEvent(QShowEvent *event)
{
    event->setAccepted(true);
}

void WidgetMain::resizeEvent(QResizeEvent *event)
{
    int genislik, yukseklik;
    QPixmap resimPixmap;

    resimPixmap.load(":/img/IMG_20191030_173910.jpg");
    genislik = ui->labelResim1->width();
    yukseklik = ui->labelResim1->height();
    ui->labelResim1->setPixmap(resimPixmap.scaled(genislik,yukseklik));

    genislik = ui->labelResim2->width();
    yukseklik = ui->labelResim2->height();
    ui->labelResim2->setPixmap(resimPixmap.scaled(genislik,yukseklik));

    event->setAccepted(true);
}

void WidgetMain::closeEvent(QCloseEvent *event)
{
    event->setAccepted(true);
}

QImage WidgetMain::doParlaklik(QImage &resim, int faktor)
{
    double kirmizi, yesil, mavi;
    int pixels;
    unsigned int *data;

    pixels = resim.width() * resim.height();
    data = (unsigned int *)resim.bits();
    for (int i = 0; i < pixels; ++i)
    {
        kirmizi= qRed(data[i])+ faktor;
        kirmizi = (kirmizi < 0x00) ? 0x00 : (kirmizi > 0xff) ? 0xff : kirmizi;
        yesil= qGreen(data[i])+faktor;
        yesil = (yesil < 0x00) ? 0x00 : (yesil > 0xff) ? 0xff : yesil;
        mavi= qBlue(data[i])+faktor;
        mavi =  (mavi  < 0x00) ? 0x00 : (mavi  > 0xff) ? 0xff : mavi ;
        data[i] = qRgba(kirmizi, yesil, mavi, qAlpha(data[i]));
    }
    return resim;
}

void WidgetMain::on_btnSifirla_clicked()
{
    QImage resim;
    QPixmap resimPixmap;

    resim=ui->labelResim1->pixmap()->toImage();
    resimPixmap=QPixmap::fromImage(resim);
    ui->labelResim2->setPixmap(resimPixmap);
    ui->verticalSliderParlaklik->setValue(0);
}

void WidgetMain::on_verticalSliderParlaklik_valueChanged(int value)
{
    QImage resim;
    QPixmap resimPixmap;

    resim=ui->labelResim1->pixmap()->toImage();
    resim=doParlaklik(resim, value);
    resimPixmap=QPixmap::fromImage(resim);
    ui->labelResim2->setPixmap(resimPixmap);
}

void WidgetMain::on_btnKaydet_clicked()
{
    QString fullName;

    fullName = QFileDialog::getSaveFileName(this, "Kaydet", "modifiedResim.jpg", "*.*");
    if (fullName=="")
    {
        return;
    }

    ui->labelResim2->pixmap()->save(fullName);
}
