#include "Bcm2835Control.h"

#include <QDebug>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

Bcm2835Control::Bcm2835Control(QObject *parent)
    : QObject{parent}
{
    m_isInitialized = bcm2835_init();
    if (! m_isInitialized) {
        qDebug() << "bcm2835 could not be initialized";
        return;
    }
    bcm2835_gpio_fsel(m_ledPin, BCM2835_GPIO_FSEL_OUTP);

    connect(&m_blinkFutureWatcher, &QFutureWatcher<void>::finished, this, &Bcm2835Control::isBlinkingChanged);
    connect(&m_blinkFutureWatcher, &QFutureWatcher<void>::started, this, &Bcm2835Control::isBlinkingChanged);
}

Bcm2835Control::~Bcm2835Control()
{
    bcm2835_close();
}

void Bcm2835Control::toggleLed()
{
    m_isLedOn = m_isLedOn == HIGH ? LOW : HIGH;
    bcm2835_gpio_write(m_ledPin, m_isLedOn);
    emit isLedOnChanged();
}

void Bcm2835Control::blinkLed()
{
    auto blinkFuture = QtConcurrent::run([=]() {
        int count = 5;
        if (m_isLedOn) {
            toggleLed();
        }
        while(count-- > 0) {
            toggleLed();
            QThread::sleep(1);
        }
        if (m_isLedOn) {
            toggleLed();
        }
    });
    m_blinkFutureWatcher.setFuture(blinkFuture);
    emit isBlinkingChanged();
}

bool Bcm2835Control::isBlinking() const
{
    return m_blinkFutureWatcher.isRunning();
}
