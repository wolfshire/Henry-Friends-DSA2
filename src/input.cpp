#include "input.h"
#include <iostream>

GLFWwindow* Input::window = NULL;
unordered_map<int, bool> Input::cur;
unordered_map<int, bool> Input::prev;
unordered_map<int, bool> Input::pressed;
unordered_map<int, bool> Input::released;

int Input::VALID_KEYS[] =
{
    GLFW_KEY_A,
    GLFW_KEY_B,
    GLFW_KEY_C,
    GLFW_KEY_D,
    GLFW_KEY_E,
    GLFW_KEY_F,
    GLFW_KEY_G,
    GLFW_KEY_H,
    GLFW_KEY_I,
    GLFW_KEY_J,
    GLFW_KEY_K,
    GLFW_KEY_L,
    GLFW_KEY_M,
    GLFW_KEY_N,
    GLFW_KEY_O,
    GLFW_KEY_P,
    GLFW_KEY_Q,
    GLFW_KEY_R,
    GLFW_KEY_S,
    GLFW_KEY_T,
    GLFW_KEY_U,
    GLFW_KEY_V,
    GLFW_KEY_W,
    GLFW_KEY_X,
    GLFW_KEY_Y,
    GLFW_KEY_Z,
    GLFW_KEY_1,
    GLFW_KEY_2,
    GLFW_KEY_3,
    GLFW_KEY_4,
    GLFW_KEY_5,
    GLFW_KEY_6,
    GLFW_KEY_7,
    GLFW_KEY_8,
    GLFW_KEY_9,
    GLFW_KEY_0,
    GLFW_KEY_SPACE,
    GLFW_KEY_LEFT_CONTROL,
    GLFW_KEY_LEFT_SHIFT,
    GLFW_KEY_LEFT_ALT,
    GLFW_KEY_COMMA,
    GLFW_KEY_PERIOD,
    GLFW_KEY_SLASH,
    GLFW_KEY_SEMICOLON,
    GLFW_KEY_APOSTROPHE,
    GLFW_KEY_LEFT_BRACKET,
    GLFW_KEY_RIGHT_BRACKET,
    GLFW_KEY_BACKSLASH,
    GLFW_KEY_MINUS,
    GLFW_KEY_EQUAL,
    GLFW_KEY_BACKSPACE,
    GLFW_KEY_ENTER,
    GLFW_KEY_RIGHT_CONTROL,
    GLFW_KEY_RIGHT_SHIFT,
    GLFW_KEY_RIGHT_ALT,
    GLFW_KEY_GRAVE_ACCENT,
    GLFW_KEY_TAB,
    GLFW_KEY_ESCAPE,
    GLFW_KEY_F1,
    GLFW_KEY_F2,
    GLFW_KEY_F3,
    GLFW_KEY_F4,
    GLFW_KEY_F5,
    GLFW_KEY_F6,
    GLFW_KEY_F7,
    GLFW_KEY_F8,
    GLFW_KEY_F9,
    GLFW_KEY_F10,
    GLFW_KEY_F11,
    GLFW_KEY_F12,
    GLFW_KEY_INSERT,
    GLFW_KEY_DELETE,
    GLFW_KEY_HOME,
    GLFW_KEY_END,
    GLFW_KEY_PAGE_UP,
    GLFW_KEY_PAGE_DOWN,
    GLFW_KEY_KP_0,
    GLFW_KEY_KP_1,
    GLFW_KEY_KP_2,
    GLFW_KEY_KP_3,
    GLFW_KEY_KP_4,
    GLFW_KEY_KP_5,
    GLFW_KEY_KP_6,
    GLFW_KEY_KP_7,
    GLFW_KEY_KP_8,
    GLFW_KEY_KP_9,
    GLFW_KEY_KP_DIVIDE,
    GLFW_KEY_KP_MULTIPLY,
    GLFW_KEY_KP_SUBTRACT,
    GLFW_KEY_KP_ADD,
    GLFW_KEY_KP_DECIMAL,
    GLFW_KEY_KP_ENTER
};
int Input::NUM_KEYS = sizeof(VALID_KEYS) / sizeof(int);

Input::Input() {}

void Input::init(GLFWwindow* win)
{
	window = win;
}

void Input::update()
{
    pressed.clear();
    released.clear();
    cur.clear();

    //store all current keys
    for (int i = 0; i < NUM_KEYS; i++)
        cur[VALID_KEYS[i]] = glfwGetKey(window, VALID_KEYS[i]);

    for (int i = 0; i < NUM_KEYS; i++)
    {
        if (cur[VALID_KEYS[i]] == GLFW_PRESS &&
            prev[VALID_KEYS[i]] == GLFW_RELEASE)
        {
            pressed[VALID_KEYS[i]] = true;
            continue;
        }

        if (cur[VALID_KEYS[i]] == GLFW_RELEASE &&
            prev[VALID_KEYS[i]] == GLFW_PRESS)
            released[VALID_KEYS[i]] = true;
    }

    //store cur into prev
    prev.clear();
    for (int i = 0; i < NUM_KEYS; i++)
        prev[VALID_KEYS[i]] = cur[VALID_KEYS[i]];
}

bool Input::getKey(int keycode)
{
	return glfwGetKey(window, keycode) == GLFW_PRESS;
}

bool Input::getKeyUp(int keycode)
{
    unordered_map<int, bool>::const_iterator i = released.find(keycode);
    return i != released.end() ? true : false;
}

bool Input::getKeyDown(int keycode)
{
    unordered_map<int, bool>::const_iterator i = pressed.find(keycode);
    return i != pressed.end() ? true : false;
}

char Input::getKeyChar(int keycode)
{
	bool upper = getKey(GLFW_KEY_LEFT_SHIFT) || getKey(GLFW_KEY_RIGHT_SHIFT);

	switch (keycode)
	{
	case GLFW_KEY_A: return upper ? 'A' : 'a';
	case GLFW_KEY_B: return upper ? 'B' : 'b';
	case GLFW_KEY_C: return upper ? 'C' : 'c';
	case GLFW_KEY_D: return upper ? 'D' : 'd';
	case GLFW_KEY_E: return upper ? 'E' : 'e';
	case GLFW_KEY_F: return upper ? 'F' : 'f';
	case GLFW_KEY_G: return upper ? 'G' : 'g';
	case GLFW_KEY_H: return upper ? 'H' : 'h';
	case GLFW_KEY_I: return upper ? 'I' : 'i';
	case GLFW_KEY_J: return upper ? 'J' : 'j';
	case GLFW_KEY_K: return upper ? 'K' : 'k';
	case GLFW_KEY_L: return upper ? 'L' : 'l';
	case GLFW_KEY_M: return upper ? 'M' : 'm';
	case GLFW_KEY_N: return upper ? 'N' : 'n';
	case GLFW_KEY_O: return upper ? 'O' : 'o';
	case GLFW_KEY_P: return upper ? 'P' : 'p';
	case GLFW_KEY_Q: return upper ? 'Q' : 'q';
	case GLFW_KEY_R: return upper ? 'R' : 'r';
	case GLFW_KEY_S: return upper ? 'S' : 's';
	case GLFW_KEY_T: return upper ? 'T' : 't';
	case GLFW_KEY_U: return upper ? 'U' : 'u';
	case GLFW_KEY_V: return upper ? 'V' : 'v';
	case GLFW_KEY_W: return upper ? 'W' : 'w';
	case GLFW_KEY_X: return upper ? 'X' : 'x';
	case GLFW_KEY_Y: return upper ? 'Y' : 'y';
	case GLFW_KEY_Z: return upper ? 'Z' : 'z';
	case GLFW_KEY_1: return upper ? '!' : '1';
	case GLFW_KEY_2: return upper ? '@' : '2';
	case GLFW_KEY_3: return upper ? '#' : '3';
	case GLFW_KEY_4: return upper ? '$' : '4';
	case GLFW_KEY_5: return upper ? '%' : '5';
	case GLFW_KEY_6: return upper ? '^' : '6';
	case GLFW_KEY_7: return upper ? '&' : '7';
	case GLFW_KEY_8: return upper ? '*' : '8';
	case GLFW_KEY_9: return upper ? '(' : '9';
	case GLFW_KEY_0: return upper ? ')' : '0';
	case GLFW_KEY_GRAVE_ACCENT: return upper ? '~' : '`';
	case GLFW_KEY_COMMA: return upper ? '<' : ',';
	case GLFW_KEY_PERIOD: return upper ? '>' : '.';
	case GLFW_KEY_SLASH: return upper ? '?' : '/';
	case GLFW_KEY_SEMICOLON: return upper ? ':' : ';';
	case GLFW_KEY_APOSTROPHE: return upper ? '"' : '\'';
	case GLFW_KEY_LEFT_BRACKET: return upper ? '{' : '[';
	case GLFW_KEY_RIGHT_BRACKET: return upper ? '}' : ']';
	case GLFW_KEY_BACKSLASH: return upper ? '|' : '\\';
	case GLFW_KEY_MINUS: return upper ? '_' : '-';
	case GLFW_KEY_EQUAL: return upper ? '+' : '=';
	default: return '\0';
	}
}