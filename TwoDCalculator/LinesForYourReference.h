
const float span = .3;

// Vertices and lines:
vec2 bottomLeft(-span, -span);
vec2 topLeft(-span, span);
vec2 topRight(span, span);
vec2 bottomRight(span, -span);
vec2 roofTop(0, span + .25);

vec2 lines[] = { 
	bottomLeft, topLeft,
	topLeft, topRight,
	topRight, bottomRight,
	bottomRight, bottomLeft,
	topLeft, roofTop,
	topRight, roofTop
};

int numLines = sizeof(lines) / (sizeof(*lines) * 2);
