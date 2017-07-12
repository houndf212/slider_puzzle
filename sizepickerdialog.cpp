#include "sizepickerdialog.h"

SizePickerDialog::SizePickerDialog(QWidget *parent)
    :QDialog(parent)
{
    createUI();
    setMinimumWidth(100);
}

QSize SizePickerDialog::getSize() const
{
    return QSize(col->value(), row->value());
}

void SizePickerDialog::setSize(QSize s)
{
    row->setValue(s.height());
    col->setValue(s.width());
}

void SizePickerDialog::createUI()
{
    row = new QSpinBox;
    col = new QSpinBox;

    row->setRange(3, 10);
    col->setRange(3, 10);

    btn = new QPushButton("OK");
    connect(btn, &QPushButton::clicked, this, &SizePickerDialog::accept);

    QFormLayout* flayout = new QFormLayout;
    flayout->addRow("row:", row);
    flayout->addRow("col:", col);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(flayout);
    layout->addWidget(btn);
    setLayout(layout);
}
