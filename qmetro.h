#ifndef QMETRO_H
#define QMETRO_H

#include <QWidget>
#include <QLCDNumber>
#include "metronompuls.h"

namespace Ui {
class qMetro;
}

class qMetro : public QWidget
{
    Q_OBJECT

public:
    explicit qMetro(QWidget *parent = 0);
    ~qMetro();

    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pushStart_clicked();

    void on_pushAbort_clicked();

private:
    Ui::qMetro *ui;
    MetronomPuls puls;
    int bpm;
    QLCDNumber * recentdisp;
};

#endif // QMETRO_H
