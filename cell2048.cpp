#include "cell2048.h"

Cell2048::Cell2048(QWidget *parent) : QWidget(parent), m_text (""), paintDigits(true), isAnimated(true)
{
    auto m_font = this->font ();
    m_font.setPointSize (m_font.pointSize () * 2);
    this->setFont (m_font);
}

void Cell2048::startAnimated(int mcsec)
{
    isAnimated  = false;
    QTimer *timer = new QTimer(this);
    timer->start(mcsec * 3);
    QObject::connect( timer, &QTimer::timeout, [=] () {
        isAnimated = true;
        timer->stop();
        delete timer;
    });
}

void Cell2048::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setRenderHint (QPainter::Antialiasing, true);
    painter.setBrush (backgroundFromValue (m_text.toInt ()));
    painter.drawRoundedRect (QRect(0,0,this->width (), this->height ()), this->width ()/20, this->height ()/20);
    painter.setPen (foregroundColor);
    if(paintDigits) {
         painter.drawText ( QRect(0, 0, this->width (), this->height ()), Qt::AlignCenter, m_text);
    } else {
         painter.drawPixmap( QRect(10, 10, this->width ()-20, this->height ()-20), mapFromValue());
         painter.drawText( QRect (0, 0, this->width(), 50), Qt::AlignRight, m_text);
    }
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

QPixmap Cell2048::mapFromValue()
{
    QVector<QPixmap> faces = {QPixmap(),QPixmap(":/icons/prb2.jpg"),QPixmap(":/icons/archer.jpg"), QPixmap(":/icons/kolya.jpg"),
                              QPixmap(":/icons/rude.jpg"), QPixmap(":/icons/iron.jpg"), QPixmap(":/icons/jelezlo.jpg"),
                             QPixmap(":/icons/shtorm.jpg"), QPixmap(":/icons/mallboro.jpg"), QPixmap(":/icons/andrew.jpg"),
                             QPixmap(":/icons/vlad2.jpg"), QPixmap(":/icons/jekezniy_kurdos.jpg")};

    QMap <QString, QPixmap> container;

    int value = 2;
    for ( int i = 0; i < faces.size(); i++) {
        container[QString::number(value/2)] = faces[i];
        value *=2;
    }

    return container[m_text];
}
