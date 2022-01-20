#ifndef BCM2835CONTROL_H
#define BCM2835CONTROL_H

#include <QObject>
#include <QFutureWatcher>

extern "C" {
#include <bcm2835.h>
}

class Bcm2835Control : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isBlinking READ isBlinking NOTIFY isBlinkingChanged)
    Q_PROPERTY(bool isLedOn MEMBER m_isLedOn NOTIFY isLedOnChanged)

public:
    explicit Bcm2835Control(QObject *parent = nullptr);
    ~Bcm2835Control();
    Q_INVOKABLE void toggleLed();
    Q_INVOKABLE void blinkLed();

    bool isBlinking() const;

signals:
    void isBlinkingChanged();
    void isLedOnChanged();

private:
    bool m_isInitialized = false;
    uint8_t m_isLedOn = LOW;
    const int m_ledPin = RPI_GPIO_P1_12;
    bool m_isBlinking = false;
    QFutureWatcher<void> m_blinkFutureWatcher;
};

#endif // BCM2835CONTROL_H
