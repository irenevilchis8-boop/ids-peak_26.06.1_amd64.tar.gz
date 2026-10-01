/*!
 * \file    display.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. The display is adapted to show only
 *          images with an explicit number.
 *
 * \version 1.0.0
 *
 * Copyright (C) 2024 - 2026, IDS Imaging Development Systems GmbH.
 *
 * The information in this document is subject to change without notice
 * and should not be construed as a commitment by IDS Imaging Development Systems GmbH.
 * IDS Imaging Development Systems GmbH does not assume any responsibility for any errors
 * that may appear in this document.
 *
 * This document, or source code, is provided solely as an example of how to utilize
 * IDS Imaging Development Systems GmbH software libraries in a sample application.
 * IDS Imaging Development Systems GmbH does not assume any responsibility
 * for the use or reliability of any portion of this document.
 *
 * General permission to copy or modify is hereby granted.
 */

#include "display.h"

#include <QGraphicsView>
#include <QImage>
#include <QWidget>

#include <cmath>
#include <utility>


Display::Display(int number, QWidget* parent)
    : QGraphicsView(parent)
{
    m_number = number;
    m_scene = new CustomGraphicsScene(this);
    setScene(m_scene);
}

void Display::OnImageReceived(int numDisplay, QImage image)
{
    if (numDisplay != m_number)
    {
        return;
    }

    m_scene->SetImage(std::move(image));
}

void Display::mousePressEvent(QMouseEvent* event)
{
    emit Signal_Selected();
    QGraphicsView::mousePressEvent(event);
}

void Display::SetColorBackground(const QColor& col)
{
    m_scene->SetColorBackground(col);
}

CustomGraphicsScene::CustomGraphicsScene(Display* parent)
    : QGraphicsScene(parent)
    , m_parent(parent)
{}

void CustomGraphicsScene::SetImage(QImage image)
{
    m_image = std::move(image);
    update();
}

void CustomGraphicsScene::SetColorBackground(const QColor& col)
{
    m_colorBackground = col;
}

void CustomGraphicsScene::drawBackground(QPainter* painter, const QRectF& r)
{
    // Display size
    auto displayWidth = static_cast<double>(m_parent->width());
    auto displayHeight = static_cast<double>(m_parent->height());

    // Image size
    auto imageWidth = static_cast<double>(m_image.width());
    auto imageHeight = static_cast<double>(m_image.height());

    // Calculate aspect ratio of the display
    double ratio1 = displayWidth / displayHeight;

    // Calculate aspect ratio of the image
    double ratio2 = imageWidth / imageHeight;

    if (ratio1 > ratio2)
    {
        // the height must fit to the display height. So h remains and w must be scaled down
        imageWidth = displayHeight * ratio2;
        imageHeight = displayHeight;
    }
    else
    {
        // the image width must fit to the display width. So w remains and h must be scaled down
        imageWidth = displayWidth;
        imageHeight = displayWidth / ratio2;
    }

    painter->fillRect(r, m_colorBackground);

    double imagePosX = -1.0 * (imageWidth / 2.0);
    double imagePosY = -1.0 * (imageHeight / 2.0);

    // Remove digits afer point
    imagePosX = trunc(imagePosX);
    imagePosY = trunc(imagePosY);

    QRectF rect(imagePosX, imagePosY, imageWidth, imageHeight);

    painter->drawImage(rect, m_image);
}
