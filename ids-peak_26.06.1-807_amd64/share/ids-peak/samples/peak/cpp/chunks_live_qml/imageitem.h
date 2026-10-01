/*!
 * Copyright (C) 2020 - 2026, IDS Imaging Development Systems GmbH.
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

#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QImage>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>

class ImageItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit ImageItem(QQuickItem* parent = nullptr);

    Q_INVOKABLE void setImage(const QImage& image);
    void paint(QPainter* painter) override;

private:
    QImage m_qimage;
    QPointF m_center;
};

#endif // IMAGEITEM_H
