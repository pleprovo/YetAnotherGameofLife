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

#include "gameview.h"
#include "cell.h"

#include <QWheelEvent>
#include <QKeyEvent>
#include <QtTest>

#include "qmath.h"

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent),
      m_scene(new QGraphicsScene)
{
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 400);
    m_cells.reserve(250000);
}


void GameView::zoomIn()
{
    scaleView(qreal(1.2));
}


void GameView::zoomOut()
{
    scaleView(qreal(1.2));
}


void GameView::update()
{
    foreach (Cell *cell, m_cells) {
        cell->saveState();
    }

    foreach (Cell *cell, m_cells) {
        int count = 0;
        foreach (Cell* neighbor, cell->getNeighbors()) {
            if(neighbor->getPreviousState()) {
                ++count;
            }
        }
        if (cell->getPreviousState()) {
            if ( count < 2 || count >= 4 ) cell->off();
        } else {
            if ( count == 3 ) cell->on();
        }
    }
}


void GameView::clear()
{
    foreach(Cell *cell, m_cells)
    {
        cell->off();
    }
}


void GameView::populate(const int n, const int m)
{
    m_scene->clear();   // Clear the scene of all it's items.
    m_cells.clear();    // Clear the Cell List.
    m_scene->setSceneRect(0, 0, 10*n, 10*m); // Resezie the scene for the new grid.

    // Populate scene with cells
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            Cell *cell = new Cell(this);
            cell->setPos(10*i+5, 10*j+5);
            m_scene->addItem(cell);
            m_cells << cell;
        }
    }

    // Set neighborhood with no boundary conditions
    // Boundary cells behave like this outside of the grid is always dead.
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            // Scan the 8 neighbors kernel
            for (int k = -1; k < 2; ++k ) {
                for (int l = -1; l < 2; ++l) {
                    if ( l != 0 or k != 0) // Dont add itself as a neighbor
                    {
                        int p = i+k;
                        int q = j+l;
                        if ( p < n && p >= 0) // Check if out of the box on the rows
                        {
                            if ( q < m && q >= 0) // Check if out of the box on the columns
                            {
                                m_cells.at(n*i+j)->addNeighbor(m_cells.at(n*p+q));
                            }
                        }
                    }
                }
            }
        }
    }

    QCOMPARE(m_cells.size(), n*m);

    std::clog << m_cells.size() << " cells created." << std::endl;
}


void GameView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}


void GameView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().
            scale(scaleFactor, scaleFactor).
            mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100) return;
    scale(scaleFactor, scaleFactor);
}

