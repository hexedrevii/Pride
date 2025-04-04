#include <SDL3/SDL.h>

#include <pride/game.h>
#include <pride/vec2.h>
#include <pride/renderer.h>
#include <pride/colour.h>

int main()
{
	Pride::Math::Vec2 game_size = Pride::Math::Vec2(320, 180);
	Pride::Game game = Pride::Game();

	game.set_config_flags(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	if (!game.create_window("Test window", game_size * 3)) return -1;

	Pride::Renderer renderer = Pride::Renderer(&game);
	if (!renderer.create(game_size)) return -1;

	while (!game.window_should_close())
	{
		// Update 
		// ----------------
		game.poll_events();

		// Draw
		// ----------------

		// Draw inside window world
		game.clear(Pride::Colours::Black);

		// Draw inside the renderer
		renderer.attach();
		game.clear(Pride::Colours::SkyBlue);

		// Draw the renderer in the window world
		renderer.detach_and_draw();

		// Advance to the next frame
		game.advance_frame();
	}

	renderer.destroy();

	game.close_window();

    // Since C++ 11
    // Returning 0 is no longer required
    // As the compiler will assume 0.
}