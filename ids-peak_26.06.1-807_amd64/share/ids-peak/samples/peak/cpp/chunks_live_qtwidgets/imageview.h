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

#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QObject>
#include <QImage>
#include <QGraphicsView>
#include <cstdint>

class ImageScene;

class ImageView : public QGraphicsView
{
    Q_OBJECT

public:
    ImageView(QWidget* parent, int64_t imageWidth, int64_t imageHeight);

    QImage getImage() const;
    int64_t getImageWidth() const;
    int64_t getImageHeight() const;

private:
    ImageScene* m_imageScene = nullptr;
    QImage m_image;

    int64_t m_imageWidth = 1;
    int64_t m_imageHeight = 1;

signals:
    void messageBoxTrigger(QString messageTitle, QString messageText);

public slots:
    void updateImage(QImage image, double chunkDataExposureTime_ms);
};

#endif // IMAGEVIEW_H
