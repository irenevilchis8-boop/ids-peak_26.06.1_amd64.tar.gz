/*!
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. It can be used for other QT widget
 *          applications as well.
 *
 * Copyright (C) 2021 - 2026, IDS Imaging Development Systems GmbH.
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

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QImage>
#include <QMutex>
#include <QRect>
#include <QWidget>



class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomGraphicsScene(QWidget* pParent = nullptr);

    void setImage(QImage image);

private:
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    QMutex m_mutex{};
    QImage m_image;
};

class CustomGraphicsView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget* parent = nullptr);

private:
    CustomGraphicsScene* m_scene;
    QGraphicsView* m_view;

public slots:
    void onImageReceived(QImage image);
};

#endif // DISPLAY_H
