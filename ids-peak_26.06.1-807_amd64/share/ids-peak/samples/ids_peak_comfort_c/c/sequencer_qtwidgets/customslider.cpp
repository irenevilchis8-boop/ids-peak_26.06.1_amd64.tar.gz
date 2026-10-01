/*!
 * \file    customslider.cpp
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

#include "customslider.h"


CustomSlider::CustomSlider(QString labelText)
{
    auto layout = new QHBoxLayout(this);

    m_label = new QLabel(labelText);
    m_label->adjustSize();
    m_label->setFixedWidth(m_label->width());

    m_slider = new QSlider(Qt::Horizontal);

    m_edit = new QLineEdit();
    m_edit->setFixedSize(80, 22);
    m_edit->setAlignment(Qt::AlignCenter);

    m_spinButtonLeft = new QPushButton();
    m_spinButtonLeft->setFixedSize(16, 24);
    m_spinButtonLeft->setIcon(QIcon(":/icons/arrow-left.png"));
    m_spinButtonLeft->setStyleSheet("QPushButton { margin-right: -2px; }");

    m_spinButtonRight = new QPushButton();
    m_spinButtonRight->setFixedSize(16, 24);
    m_spinButtonRight->setIcon(QIcon(":/icons/arrow-right.png"));
    m_spinButtonRight->setStyleSheet("QPushButton { margin-left: -2px; }");

    layout->setSpacing(0);
    layout->addWidget(m_label);
    layout->addSpacing(10);
    layout->addWidget(m_slider);
    layout->addSpacing(5);
    layout->addWidget(m_spinButtonLeft);
    layout->addWidget(m_edit);
    layout->addWidget(m_spinButtonRight);

    connect(m_slider, &QSlider::valueChanged, this, &CustomSlider::OnValueChanged, Qt::UniqueConnection);
    connect(m_slider, &QSlider::sliderReleased, this, &CustomSlider::OnSliderReleased, Qt::UniqueConnection);
    connect(m_edit, &QLineEdit::editingFinished, this, &CustomSlider::OnEdit, Qt::UniqueConnection);
    connect(m_spinButtonLeft, &QPushButton::pressed, this, &CustomSlider::OnSpinButtonLeft, Qt::UniqueConnection);
    connect(m_spinButtonRight, &QPushButton::pressed, this, &CustomSlider::OnSpinButtonRight, Qt::UniqueConnection);
}

void CustomSlider::changeEvent(QEvent* e)
{
    if (e->type() == QEvent::Type::EnabledChange)
    {
        bool enabled = this->isEnabled();
        m_label->setEnabled(enabled);
        m_slider->setEnabled(enabled);
        m_edit->setEnabled(enabled);
        m_spinButtonLeft->setEnabled(enabled);
        m_spinButtonRight->setEnabled(enabled);
    }

    QWidget::changeEvent(e);
}

void CustomSlider::EnableInteger(bool integer)
{
    m_integer = integer;
}

int CustomSlider::GetLabelWidth() const
{
    return m_label->width();
}

void CustomSlider::SetLabelWidth(int width)
{
    m_label->setFixedWidth(width);
}

void CustomSlider::SetRange(double min, double max, double inc)
{
    m_min = min;
    m_max = max;
    m_inc = inc;

    int steps = (max - min) / inc + 1;

    m_slider->setRange(0, steps - 1);
}

double CustomSlider::GetValue() const
{
    return m_value;
}

double CustomSlider::SetValue(double val)
{
    if (val < m_min)
    {
        val = m_min;
    }
    else if (val > m_max)
    {
        val = m_max;
    }

    int pos = static_cast<int>((val - m_min) / m_inc + 0.01);
    if (pos < 0)
    {
        pos = 0;
    }
    else if (pos > m_slider->maximum())
    {
        pos = m_slider->maximum();
    }

    m_slider->setValue(pos);
    m_value = m_min + pos * m_inc;

    QString text;

    if (m_integer)
    {
        text = QString::number(static_cast<int>(val));
    }
    else
    {
        text = QString::number(val, 'f', 2);
    }

    m_edit->setText(text);

    return val;
}

void CustomSlider::OnValueChanged(int value)
{
    if (!m_slider->isEnabled())
    {
        return;
    }

    double val = m_min + value * m_inc;

    val = SetValue(val);

    emit ImmediateUpdate(val);
}

void CustomSlider::OnSliderReleased()
{
    double val = m_min + m_slider->value() * m_inc;

    val = SetValue(val);

    emit ValueChanged(val);
}

void CustomSlider::OnEdit()
{
    QString str = m_edit->text();
    double val = str.toDouble();

    if (abs(val - m_value) < 0.001)
    {
        return;
    }

    val = SetValue(val);

    emit ImmediateUpdate(val);
    emit ValueChanged(val);
}

void CustomSlider::OnSpinButtonLeft()
{
    double val = m_value - m_inc;

    val = SetValue(val);

    emit ImmediateUpdate(val);
    emit ValueChanged(val);
}

void CustomSlider::OnSpinButtonRight()
{
    double val = m_value + m_inc;

    val = SetValue(val);

    emit ImmediateUpdate(val);
    emit ValueChanged(val);
}
