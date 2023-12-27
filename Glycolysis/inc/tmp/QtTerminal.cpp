/*
 * QtTerminal.cpp
 *
 *  Created on: May 9, 2018
 *      Author: peter
 */

//#include <QApplication>
//#include <QDebug>
//#include <QIcon>
//#include <QMainWindow>
//#include <QMenuBar>
#include <QLineEdit>
//#include <QLabel>
//#include <QGroupBox>
#include <QtWidgets>
//#include <QComboBox>
//#include <QWidget>

//#include <qtermwidget5/qtermwidget.h>
#include "../inc/QtTerminal.h"

QtTerminal::QtTerminal() {
  init();
}

void QtTerminal::echoChanged(int index)
{
    switch (index) {
    case 0:
        echoLineEdit->setEchoMode(QLineEdit::Normal);
        break;
    case 1:
        echoLineEdit->setEchoMode(QLineEdit::Password);
        break;
    case 2:
        echoLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        break;
    case 3:
        echoLineEdit->setEchoMode(QLineEdit::NoEcho);
    }
}

int QtTerminal::init()
{
    int argc = 1;
    char * argv[] = {"Lua Terminal"};
    QApplication app(argc, argv);
    QMainWindow *mainWindow = new QMainWindow();

    QGroupBox *echoGroup = new QGroupBox("Echo");
    QLabel *echoLabel = new QLabel("Mode:");
    QComboBox *echoComboBox = new QComboBox;
    echoComboBox->addItem("Normal");
    echoComboBox->addItem("Password");
    echoComboBox->addItem("PasswordEchoOnEdit");
    echoComboBox->addItem("No Echo");
    echoLineEdit = new QLineEdit;
    echoLineEdit->setPlaceholderText("Placeholder Text");
    echoLineEdit->setFocus();

    QObject::connect(echoComboBox, SIGNAL(activated(int)),
                this, SLOT(echoChanged(int)));

    QGridLayout *echoLayout = new QGridLayout;
    echoLayout->addWidget(echoLabel, 0, 0);
    echoLayout->addWidget(echoComboBox, 0, 1);
    echoLayout->addWidget(echoLineEdit, 1, 0, 1, 2);
    echoGroup->setLayout(echoLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(echoGroup, 0, 0);

    setLayout(layout);
    setWindowTitle("Line Edits");

//    mainWindow->setCentralWidget(echoComboBox);
//    mainWindow->resize(600, 400);

    /* EPEBROR: below is for terminal
    QTermWidget *console = new QTermWidget();

    QMenuBar *menuBar = new QMenuBar(mainWindow);
    QMenu *actionsMenu = new QMenu("Actions", menuBar);
    menuBar->addMenu(actionsMenu);
    actionsMenu->addAction("Find..", console, SLOT(toggleShowSearchBar()), QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F));
    actionsMenu->addAction("About Qt", &app, SLOT(aboutQt()));
    mainWindow->setMenuBar(menuBar);

    QFont font = QApplication::font();
#ifdef Q_WS_MAC
    font.setFamily("Monaco");
#elif defined(Q_WS_QWS)
    font.setFamily("fixed");
#else
    font.setFamily("Monospace");
#endif
    font.setPointSize(12);

    console->setTerminalFont(font);

    console->setColorScheme("/usr/share/qtermwidget5/color-schemes/BlackOnRandomLight.colorscheme");
    console->setScrollBarPosition(QTermWidget::ScrollBarRight);

    const auto arguments = QApplication::arguments();
    for (const QString& arg : arguments)
    {
        if (console->availableColorSchemes().contains(arg))
            console->setColorScheme(arg);
        if (console->availableKeyBindings().contains(arg))
            console->setKeyBindings(arg);
    }
*/
//    mainWindow->setCentralWidget(console);
//    mainWindow->resize(600, 400);

    // info output
//    qDebug() << "* INFO *************************";
//    qDebug() << " availableKeyBindings:" << console->availableKeyBindings();
//    qDebug() << " keyBindings:" << console->keyBindings();
//    qDebug() << " availableColorSchemes:" << console->availableColorSchemes();
//    qDebug() << "* INFO END *********************";

    // real startup
//    EPEBROR : used by Terminal, QObject::connect(console, SIGNAL(finished()), mainWindow, SLOT(close()));

    // EPEBROR: Move QMainWindow stuff to LuaInteractive
    mainWindow->show();
    app.exec();
    return 1;
}
