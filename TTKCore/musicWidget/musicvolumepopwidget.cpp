#include "musicvolumepopwidget.h"
#include "musickugouuiobject.h"
#include "musicuiobject.h"

#include <QTimer>
#include <QSlider>
#include <QHBoxLayout>

MusicVolumePopWidget::MusicVolumePopWidget(QWidget *parent)
    : MusicToolMenuWidget(parent)
{
    initWidget();

    m_menuShown = false;

    disconnect(this, SIGNAL(clicked()), this, SLOT(popupMenu()));
}

MusicVolumePopWidget::~MusicVolumePopWidget()
{
    delete m_volumeSlider;
}

QString MusicVolumePopWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicVolumePopWidget::setValue(int value)
{
    m_volumeSlider->blockSignals(true);
    m_volumeSlider->setValue(value);
    m_volumeSlider->blockSignals(false);

    QString style = MusicKuGouUIObject::MKGBtnSound;
    if(66 < value && value <=100)
    {
        style += "QToolButton{ margin-left:-60px; }";
    }
    else if(33 < value && value <=66)
    {
        style += "QToolButton{ margin-left:-40px; }";
    }
    else if(0 < value && value <=33)
    {
        style += "QToolButton{ margin-left:-20px; }";
    }
    else
    {
        style += "QToolButton{ margin-left:-80px; }";
    }
    setStyleSheet(style);
    setToolTip(QString::number(value));
}

int MusicVolumePopWidget::value() const
{
    return m_volumeSlider->value();
}

void MusicVolumePopWidget::enterEvent(QEvent *event)
{
    MusicToolMenuWidget::enterEvent(event);;
    if(!m_menuShown)
    {
        m_menuShown = true;
        popupMenu();
        QTimer::singleShot(500, this, SLOT(timeToResetFlag()));
    }
}

void MusicVolumePopWidget::timeToResetFlag()
{
    m_menuShown = false;
}

void MusicVolumePopWidget::initWidget()
{
    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
    m_menu->setAttribute(Qt::WA_TranslucentBackground);
    m_menu->setStyleSheet(MusicUIObject::MMenuStyle03);

    m_containWidget->setFixedSize(20, 100);
    QHBoxLayout *layout = new QHBoxLayout(m_containWidget);
    layout->setContentsMargins(0, 9, 0, 9);
    layout->setSpacing(0);

    m_volumeSlider = new QSlider(Qt::Vertical, this);
    m_volumeSlider->setRange(0, 100);
    m_volumeSlider->setStyleSheet(MusicUIObject::MSliderStyle07);

    connect(m_volumeSlider, SIGNAL(valueChanged(int)), SIGNAL(musicVolumeChanged(int)));

    layout->addWidget(m_volumeSlider);
    m_containWidget->setLayout(layout);
}
