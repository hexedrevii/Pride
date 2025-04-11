# Pride
Pride is a small SDL wrapper written in C++ for my own projects.

> [!IMPORTANT]
> This project is not meant for outside use.
> It is only meant for my own projects.
> I do not guarantee any stability or any quality!

# Example
The below example creates a Celeste-Like renderer and draws two boxes inside of it.

```cpp
class Game : public Pride::Game
{
public:
  Game() : Pride::Game("My Game", 800, 600)
  {
    this->m_flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE;
  };

  // This is a required function.
  void initialise() override
  {
    // Initialise renderer.
    // NOTE: The renderer is not usable yet.
    this->m_renderer = std::make_unique<Pride::Renderer>(this);

    // Calling create() makes the renderer usable.
    this->m_renderer->create(320, 180);

    this->content.register_asset_relative("box", std::filesystem::path("Content/box.png"))
  }

  // This is a required function.
  void process(float delta) override
  {
  }

  // This is a required function
  void render() override
  {
    // Drawing inside window world
    this->drawables.clear(Pride::Colours::Black);

    // Drawing inside renderer world
    this->m_renderer->attach();
    this->drawables.clear(Pride::Colours::SkyBlue);

    // Draw normal texture
    game.draw_texture(
      this->content.assets["box"],
      Pride::Math::Vec2(),
      Pride::Colours::White
    );

    // Draw texture scaled and red
    game.draw_texture(
      this->content.assets["box"],
      Pride::Math::Vec2(10, 10),
      3.0f, Pride::Colours::Red
    );

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

```

![showcase](./Github/showcase.png)

# License
GPL 3.0
