#pragma once



struct ButtonState {
	bool isDown;
	bool changed;
};

enum Buttons {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT	// Nombre de touche claviers pour les inputs
};

struct {

	ButtonState buttons[BUTTON_COUNT];

};