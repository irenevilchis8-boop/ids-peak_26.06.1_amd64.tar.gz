/*!
 * \file    display.cpp
 * \author  IDS Imaging Development Systems GmbH
 * \date    2022-06-01
 * \since   2.1.0
 *
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. It can be used for other QT widget
 *          applications as well.
 *
 * \version 1.1.0
 *
 * Copyright (C) 2022 - 2026, IDS Imaging Development Systems GmbH.
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
#include <QHBoxLayout>

#include <cmath>
#include <utility>


Display::Display(QWidget* parent)
    : QWidget(parent)
{
    m_scene = new CustomGraphicsScene(this);

    m_view = new QGraphicsView;
    m_view->setScene(m_scene);

    auto* layout = new QHBoxLayout;
    layout->addWidget(m_view);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

void Display::OnImageReceived(QImage image)
{
    m_scene->setSceneRect(image.rect());
    m_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);

    m_scene->setImage(std::move(image));
}

void Display::setBrightnessRoiRect(QRect rect)
{
    m_scene->setBrightnessRoiRect(rect);
}

void Display::setWhitebalanceRoiRect(QRect rect)
{
    m_scene->setWhitebalanceRoiRect(rect);
}

CustomGraphicsScene::CustomGraphicsScene(Display* parent)
    : QGraphicsScene(parent)
    , m_parent(parent)
{}

void CustomGraphicsScene::setImage(QImage image)
{
    QMutexLocker lock{ &m_mutex };
    m_image = std::move(image);
    update();
}

void CustomGraphicsScene::drawBackground(QPainter* painter, const QRectF&)
{
    // Display size
    QMutexLocker lock{ &m_mutex };
    painter->drawImage(0, 0, m_image);

    painter->setPen(QPen(Qt::green, 3));
    painter->drawRect(m_roi_brightness_rect);

    painter->setPen(QPen(Qt::red, 3));
    painter->drawRect(m_roi_whitebalance_rect);
}

void CustomGraphicsScene::setBrightnessRoiRect(QRect rect)
{
    m_roi_brightness_rect = rect;
}

void CustomGraphicsScene::setWhitebalanceRoiRect(QRect rect)
{
    m_roi_whitebalance_rect = rect;
}