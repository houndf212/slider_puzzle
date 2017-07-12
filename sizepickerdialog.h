#ifndef SIZEPICKERDIALOG_H
#define SIZEPICKERDIALOG_H
#include <QtWidgets>

class SizePickerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SizePickerDialog(QWidget* parent=nullptr);
    QSize getSize() const;
    void setSize(QSize s);
private:
    void createUI();
private:
    QPushButton* btn;
    QSpinBox* row;
    QSpinBox* col;
};

#endif // SIZEPICKERDIALOG_H
