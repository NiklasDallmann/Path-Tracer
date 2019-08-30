#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <stddef.h>

#include <QObject>
#include <QThread>

#include <framebuffer.h>
#include <geometrycontainer.h>
#include <simdrenderer.h>

namespace PathTracer
{

class RenderThread : public QThread
{
	Q_OBJECT
	
public:
	enum class ImageType
	{
		Color,
		Albedo,
		Normal
	};
	
	RenderThread(QObject *parent = nullptr);
	virtual ~RenderThread() override;
	
	void run() override;
	
	void configure(Rendering::FrameBuffer *frameBuffer, Rendering::Obj::GeometryContainer *geometry,
				   const float fieldOfView, const uint32_t samples, const uint32_t bounces, const ImageType imageType);
	
signals:
	void pixelAvailable(const uint32_t x, const uint32_t y);
	void dataAvailable();
	void colorMapFinished();
	void albedoMapFinished();
	void normalMapFinished();
	
public slots:
	void quit();
	
private slots:
	void _onFinished();
	
private:
	bool _abort = false;
	ImageType _imageType = ImageType::Color;
	float _fieldOfView = 0;
	uint32_t _samples = 0;
	uint32_t _bounces = 0;
	Rendering::FrameBuffer *_frameBuffer = nullptr;
	Rendering::Obj::GeometryContainer *_geometry = nullptr;
	Rendering::SimdRenderer _renderer;
};

} // namespace PathTracer

#endif // RENDERTHREAD_H
