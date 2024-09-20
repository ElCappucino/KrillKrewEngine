#pragma once

struct OrthographicValue {
	float left;
	float right;
	float bottom;
	float top;
};

struct CameraZoomInfo {
	float zoomMultiplier;
	float minZoom;
	float MaxZoom;
	float velocity;
	float smoothTime;
};