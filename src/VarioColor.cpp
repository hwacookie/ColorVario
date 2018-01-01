#include "VarioColor.h"

void Kystsoft::VarioColor::load(const Settings& settings)
{
	// color points
	clearColorPoints();
	for (auto value : settings.values("Color.point"))
	{
		VarioColorPoint point;
		std::istringstream is(value);
		if (point.load(is))
			addColorPoint(point);
	}
}

Kystsoft::Color Kystsoft::VarioColor::color(float climb) const
{
	if (colorPoints.empty())
		return defaultColor(climb);
	if (colorPoints.size() < 2)
		return colorPoints[0].color;
	size_t i = colorPointInterval(climb);
	float x = climb;
	float x1 = colorPoints[i].climb;
	float x2 = colorPoints[i+1].climb;
	float y1 = colorPoints[i].color.hue();
	float y2 = colorPoints[i+1].color.hue();
	if (y1 == Color::hueUndefined || y2 == Color::hueUndefined)
	{
		// interpolate RGBA values
		y1 = colorPoints[i].color.red();
		y2 = colorPoints[i+1].color.red();
		float R = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
		y1 = colorPoints[i].color.green();
		y2 = colorPoints[i+1].color.green();
		float G = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
		y1 = colorPoints[i].color.blue();
		y2 = colorPoints[i+1].color.blue();
		float B = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
		y1 = colorPoints[i].color.alpha();
		y2 = colorPoints[i+1].color.alpha();
		float A = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
		return Color(R,G,B,A);
	}
	// interpolate HSLA values
	float H = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
	y1 = colorPoints[i].color.saturationHSL();
	y2 = colorPoints[i+1].color.saturationHSL();
	float S = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
	y1 = colorPoints[i].color.lightness();
	y2 = colorPoints[i+1].color.lightness();
	float L = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
	y1 = colorPoints[i].color.alpha();
	y2 = colorPoints[i+1].color.alpha();
	float A = y1 + (y2 - y1) / (x2 - x1) * (x - x1);
	return Color::fromHSLA(H,S,L,A);
}

Kystsoft::Color Kystsoft::VarioColor::defaultColor(float climb)
{
	// calculate hue as a function of climb (https://en.wikipedia.org/wiki/Logistic_function)
	float k = 0.5f; // curve steepness
//	float H = 300 / (1 + std::exp( k * climb)) - 30; // blue - green - red
	float H = 120 / (1 + std::exp(-k * climb)); // red - yellow - green
	if (H < 0)
		H += 360;

	// create color
	return Color::fromHSLA(H, 1.0f, 0.5f);
//	return Color::fromHSVA(H, 1.0f, 0.5f);
//	return Color::fromHSIA(H, 1.0f, 0.5f);
//	return Color::fromHCYA(H, 1.0f, 0.5f);
}

size_t Kystsoft::VarioColor::colorPointInterval(float climb) const
{
	if (colorPoints.size() > 2)
	{
		size_t i = 0;
		for (; i < colorPoints.size() - 2; ++i)
			if (climb <= colorPoints[i+1].climb)
				return i;
		return i;
	}
	return 0;
}
