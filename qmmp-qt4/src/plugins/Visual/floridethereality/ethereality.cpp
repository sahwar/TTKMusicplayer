#include "ethereality.h"

#include <QFile>
#include <QPainter>

Ethereality::Ethereality(QWidget *parent)
    : QWidget(parent)
{
    loadFile();
    qsrand(QDateTime::currentMSecsSinceEpoch());

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void Ethereality::start()
{
    m_timer->start();
}

void Ethereality::stop()
{
    m_timer->stop();
}

bool Ethereality::isRunning() const
{
    return m_timer->isActive();
}

void Ethereality::timeout()
{
    if(m_word_list.empty())
    {
        return;
    }

    m_word.clear();
    for(int i = 0; i < 10; i++)
    {
        const int index = qrand() % m_word_list.count();
        m_word.append(m_word_list.at(index));
    }
    update();
}

void Ethereality::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    for(int i=0; i<m_word.count(); ++i)
    {
        painter.setPen(QColor(0, 255, 0, 23 * i));
        QFont font("Microsoft YaHei", 10);
        font.setBold(true);
        QFontMetrics fm(font);
        int textHeightInPixels = fm.height();
        painter.setFont(font);
        painter.drawText(0, textHeightInPixels * (i + 1), m_word.at(i));
    }
}

void Ethereality::loadFile()
{
    QFile file(":/data/text");
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    while(!file.atEnd())
    {
        m_word_list << file.readLine().trimmed();
    }
}