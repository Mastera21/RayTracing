#include "Renderer.h"

#include "Walnut/Random.h"

void Renderer::OnResize(uint32_t width, uint32_t height) {

	if (_finalImage) {
		//No resize needed
		if (_finalImage->GetWidth() == width && _finalImage->GetHeight() == height) {
			return;
		}
		_finalImage->Resize(width, height);
	}else {
		_finalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] _imageData;
	_imageData = new uint32_t[width * height];
}

void Renderer::Render() {
	for (uint32_t i = 0; i < _finalImage->GetWidth() * _finalImage->GetHeight(); i++) {
		_imageData[i] = Walnut::Random::UInt();
		_imageData[i] |= 0xff000000;
	}
	_finalImage->SetData(_imageData);
}
