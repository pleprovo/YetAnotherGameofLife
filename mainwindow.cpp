/*
    Yet Another Game of Life
    Copyright (C) 2020  Pierre Leprovost

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <memory>

#include <QtWidgets>
#include <QtTest>

#include "mainwindow.h"
#include "gameview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_view(new GameView(this)),
      m_timer(new QTimer(this))
{
    std::clog << "    Yet Another Game of Life  Copyright (C) 2020  Pierre Leprovost\n \
                 This program comes with ABSOLUTELY NO WARRANTY;\n  \
                 This is free software, and you are welcome to redistribute it\n \
                 under certain conditions; " << std::endl;

    setObjectName(tr("GameofLife"));
    setWindowTitle(tr("Yet Another Game of Life"));

    setCentralWidget(m_view);
    std::clog << "GameView Created." << std::endl;

    // Create all the ncessary controls.
    createActions();
    createStatusBar();

    // Connect the timer to the next method.
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(next()));

    // Start a game.
    newGame();
}

void MainWindow::newGame()
{
    QDialog *dialog = new QDialog(this);

    QFormLayout form(dialog);

    form.addRow(new QLabel(tr("Choose the size of the grid.")));

    QSpinBox *rowEdit = new QSpinBox(dialog);
    rowEdit->setRange(2, 1000);
    rowEdit->setValue(25);
    form.addRow(tr("Row"), rowEdit);

    QSpinBox *columnEdit = new QSpinBox(dialog);
    columnEdit->setRange(2, 1000);
    columnEdit->setValue(25);
    form.addRow(tr("Column"), columnEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel,
                                                       Qt::Horizontal, dialog);
    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    std::clog << "New game." << std::endl;
    if (dialog->exec() == QDialog::Accepted)
    {
        // Check if valid input
        QVERIFY(rowEdit->text().toInt() < 1000);
        QVERIFY(rowEdit->text().toInt() > 2);
        QVERIFY(columnEdit->text().toInt() < 1000);
        QVERIFY(columnEdit->text().toInt() > 2);

        QString msg = QString("%1 x %2 grid created.")
                .arg(rowEdit->text().toInt())
                .arg(columnEdit->text().toInt());
        statusBar()->showMessage(msg);
        m_view->populate(rowEdit->text().toInt(), columnEdit->text().toInt());
    }
}

void MainWindow::start()
{
    // Start the timer event
    statusBar()->showMessage(tr("Started."));
    if(m_timer)
    {
        if (!m_timer->isActive())
        {
            m_timer->start(100); // time in ms
        }
    }
    std::clog << "Timer started" << std::endl;
}

void MainWindow::stop()
{
    // Stop the timer event
    if (m_timer->isActive()) m_timer->stop();
    statusBar()->showMessage(tr("Stopped."));
    std::clog << "Timer Stopped." << std::endl;
}

void MainWindow::next()
{
    // Update the scene
    m_view->update();
    m_update_count++;
    if (m_timer->isActive())
    {
        statusBar()->showMessage(tr("Auto."));
    } else {
        statusBar()->showMessage(tr("Updated."));
    }
    std::clog << m_update_count << " update." << std::endl;
}

void MainWindow::clear()
{
    // Clear the scene, turn all cells to 0;
    m_view->clear();
    m_update_count = 0;
    statusBar()->showMessage(tr("Cleared."));
    std::clog << "GameView Cleared" << std::endl;
}

void MainWindow::createActions()
{
    QToolBar *menuToolBar = addToolBar(tr("Menu"));

    // New Game Action button
    QAction *newGameAction = new QAction(tr("New"), this);
    newGameAction->setStatusTip(tr("Create a new game"));
    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    menuToolBar->addAction(newGameAction);

    // Start Action button
    QAction *startGameAction = new QAction(tr("Start"), this);
    startGameAction->setStatusTip(tr("Start a game"));
    connect(startGameAction, &QAction::triggered, this, &MainWindow::start);
    menuToolBar->addAction(startGameAction);

    // Stop Action button
    QAction *stopGameAction = new QAction(tr("Stop"), this);
    stopGameAction->setStatusTip(tr("Stop a game"));
    connect(stopGameAction, &QAction::triggered, this, &MainWindow::stop);
    menuToolBar->addAction(stopGameAction);

    // Next Action button
    QAction *nextGameAction = new QAction(tr("Next"), this);
    nextGameAction->setStatusTip(tr("Update the scene"));
    connect(nextGameAction, &QAction::triggered, this, &MainWindow::stop);
    connect(nextGameAction, &QAction::triggered, this, &MainWindow::next);
    menuToolBar->addAction(nextGameAction);

    // Clear Action button
    QAction *clearGameAction = new QAction(tr("Clear"), this);
    clearGameAction->setStatusTip(tr("Clear the scene"));
    connect(clearGameAction, &QAction::triggered, this, &MainWindow::stop);
    connect(clearGameAction, &QAction::triggered, this, &MainWindow::clear);
    menuToolBar->addAction(clearGameAction);

    std::clog << "Menu Bar Created." << std::endl;
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready."));
    std::clog << "Status Bar created." << std::endl;
}
