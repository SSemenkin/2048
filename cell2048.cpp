#include "cell2048.h"

Cell2048::Cell2048(QWidget *parent) : QWidget(parent), m_text ("")
{
    auto m_font = this->font ();
    m_font.setPointSize (m_font.pointSize () * 2);
    this->setFont (m_font);
}

void Cell2048::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing, true);
    painter.setBrush (backgroundFromValue (m_text.toInt ()));
    painter.drawRoundedRect (QRect(0,0,this->width (), this->height ()), this->width ()/20, this->height ()/20);
    painter.setPen (foregroundColor);
    painter.drawText ( QRect(0, 0, this->width (), this->height ()), Qt::AlignCenter, m_text);
}

QColor Cell2048::backgroundFromValue(const int &value)
{
    uint powTwo = 0;
    uint tmpValue = value;
    while (tmpValue) {
        tmpValue/=2;
        powTwo++;
    }
    QColor colors[] = {"#EEE4DA", "#EDE0C8", "#F2B179", "#F59563", "#F67C5F", "#F65E3B", "#EDCF72", "#EDCC61", "#EDC850", "#EDC53F", "#EDC22E", "#3C3A32"};
    powTwo <=3  ? foregroundColor = QColor("#776E62") : foregroundColor = QColor("#F9F6F2");
    return powTwo < 12 ? colors[powTwo] : QColor();
}
