#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>

class QMediaPlayer;
class QAudioOutput;

class AudioManager : public QObject
{
    Q_OBJECT

public:
    static AudioManager& instancia();

    void reproducirMusica();
    void reproducirPowerUp();
    void reproducirPerderVida();

    void subirMusica();
    void bajarMusica();

    void subirEfectos();
    void bajarEfectos();

    void alternarMute();

    int getVolumenMusica() const;
    int getVolumenEfectos() const;

    bool estaMuteado() const;

private:
    explicit AudioManager(QObject* parent = nullptr);

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    void aplicarVolumenes();

    QMediaPlayer* musica;
    QAudioOutput* salidaMusica;

    QMediaPlayer* sonidoPowerUp;
    QAudioOutput* salidaPowerUp;

    QMediaPlayer* sonidoVida;
    QAudioOutput* salidaVida;

    int volumenMusica;
    int volumenEfectos;

    bool muteado;
};

#endif