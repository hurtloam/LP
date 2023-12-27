/*
 * QtTerminal.h
 *
 *  Created on: May 9, 2018
 *      Author: peter
 */

#pragma once
#include <QLineEdit>
#include <QWidget>
#include <QObject>

class QtTerminal : public QWidget
{

  public:
    QtTerminal();
    virtual ~QtTerminal() {};

    int init();

  public slots:
    void echoChanged(int);

  private:
    QLineEdit *echoLineEdit;
};
