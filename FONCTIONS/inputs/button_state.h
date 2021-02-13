#pragma once



struct ButtonState {
	bool isDown;
	bool changed;
};

enum Buttons {
	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,

	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,

	BUTTON_COUNT	// Nombre de touche claviers pour les inputs
};

struct Input {

	ButtonState buttons[BUTTON_COUNT];

};