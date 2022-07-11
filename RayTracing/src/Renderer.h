#pragma once

#include <memory>

#include "Walnut/Image.h"

class Renderer{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return _finalImage; };

private:
	std::shared_ptr<Walnut::Image> _finalImage;
	uint32_t* _imageData = nullptr;
};

