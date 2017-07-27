#include "sizepickerdialog.h"
#include "matrix.h"
#include <cmath>

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

void SizePickerDialog::setSize(const QSize &s)
{
    row->setValue(s.height());
    col->setValue(s.width());
}

void SizePickerDialog::createUI()
{
    row = new QSpinBox;
    col = new QSpinBox;

    int max_size = std::sqrt(double(std::numeric_limits<Matrix::value_type>::max()));
    row->setRange(2, max_size);
    col->setRange(2, max_size);

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
