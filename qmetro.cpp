#include "qmetro.h"
#include "ui_qmetro.h"

qMetro::qMetro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qMetro),
    puls(10, 60, this)
{
    ui->setupUi(this);
    /* this is broken:
    QList<QLCDNumber*> lcdnumbers = ui->numbers_panel->findChildren<QLCDNumber*>();
    for(QList<QLCDNumber*>::iterator i = lcdnumbers.begin(); i != lcdnumbers.end(); ++i){
        (*i)->setVisible(false);
    }*/
    ui->lcdBigAdv->hide();
    ui->lcdSmallAdv->hide();
    ui->lcdOnPoint->hide();
    ui->lcdSmallRet->hide();
    ui->lcdBigRet->hide();

    recentdisp=ui->lcdBigAdv;

    this->setFocusPolicy(Qt::StrongFocus);
}

qMetro::~qMetro()
{
    delete ui;
    puls.stop();
}

void qMetro::on_pushStart_clicked()
{
    if(puls.isrunning()) return;
    bpm=ui->bpmBox->value();
    puls.setbpm(bpm);
    puls.setnumberofbeats(ui->totalbeatsBox->value());
    puls.start();
    this->setFocus();
}

void qMetro::on_pushAbort_clicked()
{
    puls.stop();
}

void qMetro::keyPressEvent(QKeyEvent *event)
{
    if(!puls.isrunning()) return;
    millisec_type latenz = std::chrono::duration_cast<millisec_type>(std::chrono::high_resolution_clock::now() - puls.getrecentbeeptimer());
    int x = latenz.count();
    int t = 30000/bpm;
    if(x > t)
        x -= 2*t;
    int tol = this->ui->toleranceBox->value();
    recentdisp->hide();
    // order is important:
    // more extreme cases handled first
    if(x < -2*tol)
    {
        recentdisp=ui->lcdBigAdv;
    }else if(x < -tol)
    {
        recentdisp=ui->lcdSmallAdv;
    }else if(x > 2*tol)
    {
        recentdisp=ui->lcdBigRet;
    }else if(x > tol)
    {
        recentdisp=ui->lcdSmallRet;
    }else
    {
        recentdisp=ui->lcdOnPoint;
    }
    recentdisp->show();
    recentdisp->display(x);
}
