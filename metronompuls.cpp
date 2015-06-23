#include "metronompuls.h"

MetronomPuls::MetronomPuls(int number_of_beats, int beats_per_minute, QWidget *parent)
    :QWidget(parent),
     total_number(number_of_beats),
     bpm(beats_per_minute),
     running(false)
{
    effect.setSource(QUrl::fromLocalFile("beep-07.wav"));
    effect.setVolume(0.25f);
}

MetronomPuls::~MetronomPuls()
{
    this->stop();
}

void MetronomPuls::setnumberofbeats(int beats)
{
    total_number=beats;
}

void MetronomPuls::setbpm(int beats)
{
    bpm=beats;
}

zeitmesser MetronomPuls::getrecentbeeptimer() const
{
    return nullpunkt;
}

bool MetronomPuls::isrunning()
{
    return running;
}

void MetronomPuls::pulsieren_thread()
{
    for(int i=0; i<total_number && running; ++i)
    {
        effect.play();
        nullpunkt = chrono::high_resolution_clock::now();
        this_thread::sleep_for(time_between_beeps);
    }
    running=false;
}

void MetronomPuls::start()
{
    if(!running)
    {
        // close the old thread if there is one
        if(m.joinable())
        {
            m.join();
        }
        // let's go
        running=true;
        time_between_beeps=millisec_type(60000/bpm);
        nullpunkt=chrono::high_resolution_clock::now();

        m=std::thread(&MetronomPuls::pulsieren_thread, this);

    }
/*
    for(int i=0; i<10; ++i){
        cin.get();
//        beep();
        millisec_type zeitdifferenz = chrono::duration_cast<millisec_type>(chrono::high_resolution_clock::now() - nullpunkt);
        if(zeitdifferenz > time_between_beeps/2)
            zeitdifferenz -= time_between_beeps;
        cout << zeitdifferenz.count() << "\n";
    }

    //Stop Metronom
    stop_metronom=true;
    //Warten auf Metronom-Ende
    m.join();
    std::cout << "Stop\n";*/
}

void MetronomPuls::stop()
{
    if(running)
    {
        running=false;
        m.join();
    }
}
