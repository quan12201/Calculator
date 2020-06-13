#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;

bool divide = false;
bool multi = false;
bool plus = false;
bool minus = false;

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Plus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Minus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->EqualButton, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ClearButton, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->Display->text();
    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0) {
        ui->Display->setText(buttonValue);
    } else {
        QString newValue = displayValue + buttonValue;
        double doubleNewValue = newValue.toDouble();
        ui->Display->setText(QString::number(doubleNewValue, 'g', 12));
    }
}
void Calculator::MathButtonPressed() {
    divide = false;
    multi = false;
    plus = false;
    minus = false;
    QString displayValue = ui->Display->text();
    calcValue = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    if(buttonValue == "/") {
        divide = true;
    } else if(buttonValue == "*") {
        multi = true;
    } else if(buttonValue == "+") {
        plus = true;
    } else {
        minus = true;
    }
    ui->Display->setText("");
}
void Calculator::EqualButtonPressed() {
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double doubleDisplayValue = displayValue.toDouble();
    if(divide || multi || plus || minus) {
        if (plus) {
            solution = calcValue + doubleDisplayValue;
        } else if(multi) {
            solution = calcValue * doubleDisplayValue;
        } else if(minus) {
            solution = calcValue - doubleDisplayValue;
        } else {
            solution = calcValue / doubleDisplayValue;
        }
    }
    ui->Display->setText(QString::number(solution));
}
void Calculator::ClearButtonPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    if(buttonValue == "Clear") {
        calcValue = 0;
        ui->Display->setText(QString::number(calcValue));
    }
}
