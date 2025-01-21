#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("计算器");

    QFont f("微软雅黑",14);
    ui->lineEdit->setFont(f);

    ui->equal->setStyleSheet("QPushButton {"
                                 "background-color: yellow;"
                                 "}");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton0_clicked()
{
    expression+="0";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton1_clicked()
{
    expression+="1";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton2_clicked()
{
    expression+="2";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton3_clicked()
{
    expression+="3";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton4_clicked()
{
    expression+="4";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton5_clicked()
{
    expression+="5";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton6_clicked()
{
    expression+="6";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton7_clicked()
{
    expression+="7";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton8_clicked()
{
    expression+="8";
    ui->lineEdit->setText(expression);
}

void Widget::on_pushButton9_clicked()
{
    expression+="9";
    ui->lineEdit->setText(expression);
}


void Widget::on_pushButtonpoint_clicked()
{
    expression+=".";
    ui->lineEdit->setText(expression);
}

void Widget::on_add_clicked()
{
    expression+="+";
    ui->lineEdit->setText(expression);
}

void Widget::on_sub_clicked()
{
    expression+="-";
    ui->lineEdit->setText(expression);
}

void Widget::on_mul_clicked()
{
    expression+="*";
    ui->lineEdit->setText(expression);
}

void Widget::on_div_clicked()
{
    expression+="/";
    ui->lineEdit->setText(expression);
}

void Widget::on_right_clicked()
{
    expression+=")";
    ui->lineEdit->setText(expression);
}

void Widget::on_left_clicked()
{
    expression+="(";
    ui->lineEdit->setText(expression);
}

void Widget::on_Clear_clicked()
{
    expression.clear();
    ui->lineEdit->clear();
}

void Widget::on_delete_2_clicked()
{
    //删除字符串结尾1位
    expression.chop(1);
    ui->lineEdit->setText(expression);
}

int Priority(char op)
{
    switch (op)
    {
        case '(':
            return 0;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;
    }
}

double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default:  return 0;
    }
}

void Widget::on_equal_clicked()
{
    QStack<double> values;
    QStack<char>op;

//    //将QString转换为QbyteArray
//    QByteArray arr;
//    arr.append(expression);

//    //将QbyteArray转换为char *
//    char opt[128]={0};
//    strcpy(opt,arr.data());

    int i=0;
    QString num;
    while (i<expression.length()) {
        QChar ch = expression[i];
        if(ch.isDigit()||ch=='.'){
            num+=ch;
            i++;
            if(i==expression.length() || !(expression[i].isDigit() ||expression[i]=='.') ){
                //字符串 num 转换为 double 类型的数字
                double value=num.toDouble();
                values.push(value);

            }
            num.clear();
        }
        else {
            if(ch=='(')
            op.push(ch.toLatin1());  //将 QChar 转换为 char
        else if(ch==')'){
            while(!op.isEmpty()&&op.top()!='(')
            {
                double num2=values.pop();
                double num1=values.pop();
                char opt=op.pop();
                values.push(applyOp(num1,num2,opt));
            }
            op.pop();//取出'('

        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
            while (!op.isEmpty()&&Priority(op.top())>=Priority(ch.toLatin1())) {
                double num2=values.pop();
                double num1=values.pop();
                char opt=op.pop();
                values.push(applyOp(num1,num2,opt));
            }
            op.push(ch.toLatin1());
        }
            i++;
        }
    }

    if (!num.isEmpty()) {
            double value = num.toDouble();
            values.push(value);
        }
        while (!op.isEmpty()) {
            double num2 = values.pop();
            double num1 = values.pop();
            char opt = op.pop();
            values.push(applyOp(num1, num2, opt));
        }

    ui->lineEdit->setText(QString::number(values.pop()));
    expression.clear();
}




























