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
	
	for (uint32_t y = 0; y < _finalImage->GetHeight(); y++) {
		for (uint32_t x = 0; x < _finalImage->GetWidth(); x++) {

			glm::vec2 coord = { (float)x / (float)_finalImage->GetWidth(), (float)y / (float)_finalImage->GetHeight()};
			coord = coord * 2.0f - 1.0f; // -1 -> 1
			_imageData[x + y * _finalImage->GetWidth()] = PerPixel(coord);
		}
	}
	_finalImage->SetData(_imageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coord){

	//camera
	glm::vec3 rayOrigin(0.0f, 0.0f, 2.0f);
	glm::vec3 rayDiraction(coord.x, coord.y, -1.0f);
	float radius = 0.5f;
	//rayDiraction = glm::normalize(rayDiraction);

	float a = glm::dot(rayDiraction, rayDiraction);
	float b = 2.0f * glm::dot(rayOrigin, rayDiraction);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.0f) {
		return 0xffff00ff;
	}

	return 0xff000000;
}