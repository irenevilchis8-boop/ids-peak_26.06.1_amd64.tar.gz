/*!
 * \brief   The Display class implements an easy way to display images from a
 *          camera in a QT widgets window. It can be used for other QT widget
 *          applications as well.
 *
 * Copyright (C) 2019 - 2026, IDS Imaging Development Systems GmbH.
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

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>

#include <cstdint>


class CustomDisplay;


class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomGraphicsScene(CustomDisplay* pParent);
    ~CustomGraphicsScene() = default;

    void setImage(QImage image);
    QRectF getImageRect();

private:
    CustomDisplay* m_parent;
    QImage m_image;

    virtual void drawBackground(QPainter* painter, const QRectF& rect);
};


class CustomDisplay : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CustomDisplay(QWidget* parent);
    ~CustomDisplay() = default;

    QRectF getImageRect();
    void toggleDrawROI();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    CustomGraphicsScene* m_scene;
    bool m_drawROI = false;
    QGraphicsRectItem* m_dragRect{};

public slots:
    void onImageReceived(QImage image);

signals:
    void newROI(QRectF roi);
};

#endif // DISPLAY_H
