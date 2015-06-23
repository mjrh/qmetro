#ifndef METRONOMPULS_H
#define METRONOMPULS_H

#include<thread>
#include<chrono>
#include<QSoundEffect>
#include <QWidget>

using namespace std;
typedef chrono::high_resolution_clock::time_point zeitmesser;
typedef chrono::milliseconds millisec_type;

class MetronomPuls : public QWidget
{
public:
    MetronomPuls(int number_of_beats, int beats_per_minute, QWidget *parent=0);
    void start();
    void stop();
    void setnumberofbeats(int beats);
    void setbpm(int beats);
    zeitmesser getrecentbeeptimer() const;
    ~MetronomPuls();
    QSoundEffect effect;
    bool isrunning();
private:
    void pulsieren_thread();
    int total_number;
    int bpm;
    bool running;
    millisec_type time_between_beeps;
    zeitmesser nullpunkt;
    std::thread m;
    //QSoundEffect effect;
};

#endif // METRONOMPULS_H
