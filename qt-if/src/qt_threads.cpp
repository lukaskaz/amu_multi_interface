#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QRect>
#include <QDesktopWidget>


#include "logging.hpp"
#include "gui.hpp"

#include "conversions.hpp"


myThread::myThread(): timeSec(0)
{
    static Log trace;

    trace.log(std::string(__func__)+" hello!");
    trace.log(std::string(__func__)+" threadID: " + CONV_NUM_GET_STR(uint64_t, hex, QThread::currentThread()));
}

myThread::~myThread()
{
    static Log trace;
    trace.log(std::string(__func__)+" bye bye!");
}

void myThread::run(void)
{
    static Log trace;
    trace.log(std::string(__func__)+" threadID: " + CONV_NUM_GET_STR(uint64_t, hex, QThread::currentThread()));

    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateTime()), Qt::DirectConnection);
    timer.start(1000);

    exec();

}

void myThread::updateTime()
{
    static Log trace;

    trace.log(std::string(__func__)+" threadID: " + CONV_NUM_GET_STR(uint64_t, hex, QThread::currentThread()));
    trace.log(std::string(__func__)+ " Time sec is: " + std::to_string(++timeSec));

    QString time = QString("Time: %1").arg(timeSec);
    emit updateLine(time);
}
