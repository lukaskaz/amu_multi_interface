#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QThread>
#include <QObject>
#include <QTimer>
#include <qobjectdefs.h>
 
namespace Ui {
   class MainWindow;
}
 
class myThread : public QThread
{
    Q_OBJECT;

public:
    myThread();
    ~myThread();


signals:
    void updateLine(const QString&);

private slots:
    void updateTime();

private:
    int timeSec;

    void run(void);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);
    bool closeWindow(void);

private slots:
    void handleButton();
    void handleText();
    void handleLine(const QString& text);

private:
    QPushButton *m_button;
    QTextEdit *m_text;
    QLineEdit *m_line;

    myThread* updateThread;
};


void* deploy_window(void* arg);


#endif
