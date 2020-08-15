#include "Keyboard.h"


//EVENT

Keyboard::Event::Event(Type type, unsigned char code) 
	: type(type), code(code) {}

bool Keyboard::Event::isPress() const {
	return type == Type::PRESS;
}

bool Keyboard::Event::isRelease() const {
	return type == Type::RELEASE;
}

bool Keyboard::Event::isInvalid() const {
	return type == Type::INVALID;
}

unsigned char Keyboard::Event::getCode() const {
	return code;
}

//END OF EVENT

//KEYBOARD


bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept {
	return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey() noexcept {
	if (keybuffer.size() > 0u) {
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	} else {
		return Keyboard::Event(Keyboard::Event::Type::INVALID, 0u);
	}
}

bool Keyboard::KeyIsEmpty() const noexcept {
	return keybuffer.empty();
}

char Keyboard::ReadChar() noexcept {
	if (charbuffer.size() > 0u) {
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	} else {
		return 0;
	}
}

bool Keyboard::CharIsEmpty() const noexcept {
	return charbuffer.empty();
}

void Keyboard::FlushKey() noexcept {
	keybuffer = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept {
	charbuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept {
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutorepeat() noexcept {
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept {
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept {
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode) noexcept {
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::PRESS, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept {
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::Type::RELEASE, keycode));
	TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept {
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept {
	keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept {
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}

//END OF KEYBOARD