#ifndef AN_ENGINE_LAYER_STACK
#define AN_ENGINE_LAYER_STACK

#include "AnEngine/Export.h"
#include "AnEngine/Layer.h"

#include <memory>
#include <vector>

namespace an
{

class A
{
  public:
    AN_API A();
};

class LayerStack
{
  public:
    AN_API LayerStack();

    void pushLayer(std::unique_ptr<Layer> layer);
    void pushOverlay(std::unique_ptr<Layer> overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_layers.begin(); }
    std::vector<std::unique_ptr<Layer>>::iterator end() { return m_layers.end(); }

  private:
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::size_t m_layerInsertIndex = 0;
};

} // namespace an

#endif // AN_ENGINE_LAYER_STACK
