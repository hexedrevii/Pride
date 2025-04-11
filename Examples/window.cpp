#include "pride/colour.h"
#include "pride/renderer.h"
#include <SDL3/SDL.h>
#include <memory>
#include <pride/pride.h>

class Game : public Pride::Game
{
public:
	Game() : Pride::Game("My Game", 800, 600)
	{
		this->m_flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
	};

	// This is a required function
	void initialise() override
	{
		// Initialise renderer.
		// NOTE: The renderer is not usable yet.
		this->m_renderer = std::make_unique<Pride::Renderer>(this);

		// Calling create() makes the renderer usable.
		this->m_renderer->create(320, 180);
	}

	// This is a required function.
	void process(float delta) override {}

	// This is a required function
	void render() override
	{
		// Drawing inside window world
		this->drawables.clear(Pride::Colours::Black);

		// Drawing inside renderer world
		this->m_renderer->attach();
		this->drawables.clear(Pride::Colours::SkyBlue);

		// Drawing the renderer.
		this->m_renderer->detach_and_draw();
	}

	// This is an optional function.
	void leave() override
	{
		this->m_renderer->destroy();
	}
private:
	std::unique_ptr<Pride::Renderer> m_renderer = nullptr;
};

int main()
{
    // Create the game...
    // NOTE: SDL is NOT initialised in the constructor. Initialise the ConfigFlags there.
    Game game = Game();

    // This will automatically handle all SDL things.
    game.create_and_run();

    // Since C++ 11
    // Returning 0 is no longer required
    // As the compiler will assume 0.
}
