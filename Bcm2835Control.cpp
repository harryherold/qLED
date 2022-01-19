#include "Bcm2835Control.h"

#include <QDebug>

Bcm2835Control::Bcm2835Control(QObject *parent)
    : QObject{parent}
{
    m_isInitialized = bcm2835_init();
    if (! m_isInitialized) {
        qDebug() << "bcm2835 could not be initialized";
        return;
    }
    bcm2835_gpio_fsel(m_ledPin, BCM2835_GPIO_FSEL_OUTP);
}

Bcm2835Control::~Bcm2835Control()
{
    bcm2835_close();
}

void Bcm2835Control::toggleLed()
{
    m_isLedOn = m_isLedOn == HIGH ? LOW : HIGH;
    bcm2835_gpio_write(m_ledPin, m_isLedOn);
}
