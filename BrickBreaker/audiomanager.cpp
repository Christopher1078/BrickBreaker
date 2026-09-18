#include "audiomanager.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QCoreApplication>
#include <QUrl>

AudioManager& AudioManager::instancia()
{
    static AudioManager instanciaUnica;
    return instanciaUnica;
}

AudioManager::AudioManager(QObject* parent)   : QObject(parent)
{
    volumenMusica = 70;
    volumenEfectos = 80;
    muteado = false;

    musica = new QMediaPlayer(this);
    salidaMusica = new QAudioOutput(this);
    musica->setAudioOutput(salidaMusica);

    sonidoPowerUp = new QMediaPlayer(this);
    salidaPowerUp = new QAudioOutput(this);
    sonidoPowerUp->setAudioOutput(salidaPowerUp);

    sonidoVida = new QMediaPlayer(this);
    salidaVida = new QAudioOutput(this);
    sonidoVida->setAudioOutput(salidaVida);

    QString carpetaAudio =
        QCoreApplication::applicationDirPath()
        + "/audio/";

    musica->setSource(
        QUrl::fromLocalFile(
            carpetaAudio + "musica.mp3"
            )
        );

    sonidoPowerUp->setSource(
        QUrl::fromLocalFile(
            carpetaAudio + "PowerUpSi.mpeg"
            )
        );

    sonidoVida->setSource(
        QUrl::fromLocalFile(
            carpetaAudio + "LifeLose.mp3"
            )
        );

    aplicarVolumenes();

    connect(
        musica,
        &QMediaPlayer::mediaStatusChanged,
        this,
        [this](QMediaPlayer::MediaStatus estado)
        {
            if(estado == QMediaPlayer::EndOfMedia)
            {
                musica->setPosition(0);
                musica->play();
            }
        }
        );
}

void AudioManager::reproducirMusica()
{
    if(
        musica->playbackState()
        != QMediaPlayer::PlayingState
        )
    {
        musica->play();
    }
}

void AudioManager::reproducirPowerUp()
{
    if(muteado)
    {
        return;
    }

    if(volumenEfectos == 0)
    {
        return;
    }

    sonidoPowerUp->stop();
    sonidoPowerUp->setPosition(0);
    sonidoPowerUp->play();
}

void AudioManager::reproducirPerderVida()
{
    if(muteado)
    {
        return;
    }

    if(volumenEfectos == 0)
    {
        return;
    }

    sonidoVida->stop();
    sonidoVida->setPosition(0);
    sonidoVida->play();
}

void AudioManager::subirMusica()
{
    volumenMusica += 10;

    if(volumenMusica > 100)
    {
        volumenMusica = 100;
    }

    aplicarVolumenes();
}

void AudioManager::bajarMusica()
{
    volumenMusica -= 10;

    if(volumenMusica < 0)
    {
        volumenMusica = 0;
    }

    aplicarVolumenes();
}

void AudioManager::subirEfectos()
{
    volumenEfectos += 10;

    if(volumenEfectos > 100)
    {
        volumenEfectos = 100;
    }

    aplicarVolumenes();
}

void AudioManager::bajarEfectos()
{
    volumenEfectos -= 10;

    if(volumenEfectos < 0)
    {
        volumenEfectos = 0;
    }

    aplicarVolumenes();
}

void AudioManager::alternarMute()
{
    muteado = !muteado;

    salidaMusica->setMuted(muteado);
    salidaPowerUp->setMuted(muteado);
    salidaVida->setMuted(muteado);
}

int AudioManager::getVolumenMusica() const
{
    return volumenMusica;
}

int AudioManager::getVolumenEfectos() const
{
    return volumenEfectos;
}

bool AudioManager::estaMuteado() const
{
    return muteado;
}

void AudioManager::aplicarVolumenes()
{
    salidaMusica->setVolume(
        volumenMusica / 100.0
        );

    salidaPowerUp->setVolume(
        volumenEfectos / 100.0
        );

    salidaVida->setVolume(
        volumenEfectos / 100.0
        );
}