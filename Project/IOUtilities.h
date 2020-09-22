#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace irrklang;

typedef ISoundEngine SoundEngine;

class IO {
public:
    static class Sound {
    public:
        static SoundEngine* engine;

        static int Initialize() {
            engine = createIrrKlangDevice();
            if (!engine) {
                std::cout << "[SEVERE] Unable to initialize sound device.\n";
            }
            return !engine;
        }

        static void ClearSoundSources() {
            engine->removeAllSoundSources();
        }

        static int Revoke() {
            engine->drop();
            return 0;
        }

        ~Sound() {
            if (engine) Revoke();
        }
    };

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS) {
            switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                std::cout << "[INPUT] MOUSE'S LEFT BUTTON PRESSED\n";
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                std::cout << "[INPUT] MOUSE'S RIGHT BUTTON PRESSED\n";
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                std::cout << "[INPUT] MOUSE'S MIDDLE BUTTON PRESSED\n";
                break;
            }
        }
    }

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (action) {
        case GLFW_PRESS:
            break;
        case GLFW_RELEASE:
            switch (key) {
            case GLFW_KEY_ESCAPE:
                std::cout << "SAYONARA NO IMI";
                break;
            }
        case GLFW_REPEAT:
            break;
        }
    }

    static void cursor_position_callback(GLFWwindow* window, double x, double y) {
        std::cout << "Mouse position move to " << x << " " << y << '\n';
    }

    static void scroll_callback(GLFWwindow* window, double offset_x, double offset_y) {
        std::cout << "[INPUT] SCROLL MOVED: " << offset_x << " " << offset_y << '\n';
    }
};

SoundEngine* IO::Sound::engine;