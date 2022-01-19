#ifndef BCM2835CONTROL_H
#define BCM2835CONTROL_H

#include <QObject>

extern "C" {
#include <bcm2835.h>
}

class Bcm2835Control : public QObject
{
    Q_OBJECT
public:
    explicit Bcm2835Control(QObject *parent = nullptr);
    ~Bcm2835Control();
    Q_INVOKABLE void toggleLed();

private:
    bool m_isInitialized = false;
    uint8_t m_isLedOn = LOW;
    const int m_ledPin = RPI_GPIO_P1_12;
};

#endif // BCM2835CONTROL_H
