#pragma once

struct OrthographicValue {
	float left;
	float right;
	float bottom;
	float top;
};

struct CameraZoomInfo {
	float minZoom_horizontal; // minimum of the length between left and right
	float minZoom_vertical; // minimum of the length between bottom and top
	float maxZoom_horizontal; // maximum of the length between left and right
	float maxZoom_vertical; // maximum of the length between bottom and top
	float t; // use to calculate the zoom amount based on current projection and target projection. the value is between 0-1 
			 // (ex. t = 0.1 when using with a + (t * (b - a)) means that the zoom is increase 10% towards target projection every update time)
};