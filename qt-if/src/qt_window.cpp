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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
 {
    // Create the button, make "this" the parent
    m_button = new QPushButton("Clear text", this);
    // set size and location of the button
    m_button->setGeometry(QRect(QPoint(10, 10), QSize(80, 40)));

    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));

    m_text = new QTextEdit(this);
    m_text->setGeometry(QRect(QPoint(150, 60), QSize(150, 80)));
    m_text->setText("Test: ");

    connect(m_text, SIGNAL (textChanged()), this, SLOT (handleText()));

    m_line = new QLineEdit(this);
    m_line->setGeometry(QRect(QPoint(150, 160), QSize(150, 70)));
    m_line->setText("Lukasz K :)");

    static Log trace;
    trace.log(std::string(__func__)+" threadID: " + CONV_NUM_GET_STR(uint64_t, hex, QThread::currentThread()));

    updateThread = new myThread;
    updateThread->start();
    connect(updateThread, SIGNAL (updateLine(const QString &)), this, SLOT (handleLine(const QString &)));
 }

 MainWindow::~MainWindow(void)
 {
     updateThread->quit();
     updateThread->wait();
 }

 void MainWindow::handleButton()
 {
    // change the text
    m_button->setText("Cleared");
    // resize button
    m_button->resize(60,30);
    m_text->clear();
 }

 void MainWindow::handleText()
 {
     static Log trace;

    // change the text
    QString str = m_text->toPlainText();
    // resize button
    m_button->resize(60,30);

    trace.log(std::string(__func__)+" Have button pressed -> " + str.toStdString());
 }

 void MainWindow::handleLine(const QString& text)
 {
     static Log trace;

     trace.log(std::string(__func__)+" Have line modified -> " + text.toStdString());

     // change the text
     m_line->setText(text);
 }

 void MainWindow::closeEvent(QCloseEvent* event)
 {
     event->setAccepted(closeWindow());
 }


 bool MainWindow::closeWindow(void)
 {
     bool ret = false;

//     QMessageBox::StandardButton answer = QMessageBox::question(this,
//             "Window close", "Sure to close the window?",
//       QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::No );
//
//     ret = (answer == QMessageBox::Yes) ? true : false;
    QMessageBox msgBox;
    msgBox.setText("Window close");
    msgBox.addButton("Not sure", QMessageBox::RejectRole);
    msgBox.addButton("Negative", QMessageBox::NoRole);
    QPushButton *buttonConfirm = msgBox.addButton("SURE!", QMessageBox::YesRole);

    msgBox.exec();
    if(msgBox.clickedButton() == buttonConfirm) {
        ret = true;
    }

    return ret;
 }


 void* deploy_window(void* arg)
 {
     int argc = 0;
     char** argv = NULL;

     QApplication app(argc, argv);

     MainWindow mainWindow;
     mainWindow.setWindowTitle("RPI graphical interface");

     mainWindow.resize(400, 250);
     //mainWindow.showMaximized();
     QRect rect = mainWindow.geometry();
     rect.moveCenter(QApplication::desktop()->availableGeometry().center());
     mainWindow.setGeometry(rect);
     mainWindow.show();

     app.exec();

     return NULL;
 }


