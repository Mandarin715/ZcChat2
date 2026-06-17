#ifndef WAKEWORDDETECTOR_H
#define WAKEWORDDETECTOR_H

#include <QAudioSource>
#include <QObject>

namespace sherpa_onnx
{
namespace cxx
{
class KeywordSpotter;
class OnlineStream;
} // namespace cxx
} // namespace sherpa_onnx

class WakeWordDetector : public QObject
{
    Q_OBJECT

  public:
    explicit WakeWordDetector(QObject *parent = nullptr);
    ~WakeWordDetector();

    bool init(const QString &modelDir, const QStringList &keywords,
              float threshold = 0.25f);
    void start();
    void stop();
    bool isRunning() const;

  signals:
    void wakeWordDetected(const QString &keyword);
    void audioLevel(float rms); // 每100ms发出当前音频块的RMS音量

  private slots:
    void processAudio();

  private:
    QAudioSource *m_audioSource = nullptr;
    QIODevice *m_audioDevice = nullptr;
    sherpa_onnx::cxx::KeywordSpotter *m_spotter = nullptr;
    sherpa_onnx::cxx::OnlineStream *m_stream = nullptr;
    bool m_initialized = false;
    bool m_running = false;
    bool m_stopRequested = false;
};

#endif // WAKEWORDDETECTOR_H
