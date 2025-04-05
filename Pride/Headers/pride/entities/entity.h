#pragma once

namespace Pride
{
    class Entity
    {
    private:
        // TODO: components
    public:
        virtual void awake() {};

        virtual void process() {};
        virtual void render() {};
    };
}