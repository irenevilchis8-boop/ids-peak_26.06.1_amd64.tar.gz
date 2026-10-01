/*!
 * \file    customslider.h
 * \author  IDS Imaging Development Systems GmbH
 * \date    2024-10-31
 * \since   2.14.0
 *
 * \brief   The CustomSlider class implements a QSlider combined with a
 *          QLineEdit to provide easy access functions to set and get values.
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

#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QEvent>


class CustomSlider : public QWidget
{
    Q_OBJECT

public:

    explicit CustomSlider(QString labelText);
    ~CustomSlider() override = default;

    void EnableInteger(bool integer);
    void SetRange(double min, double max, double inc);
    double SetValue(double val);
    double GetValue() const;
    int GetLabelWidth() const;
    void SetLabelWidth(int width);

private:

    double m_value;
    double m_min;
    double m_max;
    double m_inc;

    bool m_integer{};

    QLabel* m_label{};
    QSlider* m_slider{};
    QLineEdit* m_edit{};
    QPushButton* m_spinButtonLeft{};
    QPushButton* m_spinButtonRight{};

    void changeEvent(QEvent* e) override;

private slots:

    void OnValueChanged(int value);
    void OnSliderReleased();
    void OnEdit();
    void OnSpinButtonLeft();
    void OnSpinButtonRight();

signals:

    void ImmediateUpdate(double value);
    void ValueChanged(double value);
};

#endif // CUSTOMSLIDER_H
