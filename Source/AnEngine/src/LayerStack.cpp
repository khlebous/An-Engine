#include "AnEngine/LayerStack.h"

#include <Core/Core.h>

using namespace an;

//--------------------------------------------------------------------------------------------------
LayerStack::LayerStack()
{
    m_layerInsertIndex = 0U;
}

//--------------------------------------------------------------------------------------------------
void LayerStack::pushLayer(std::unique_ptr<Layer> layer)
{
    auto it = m_layers.insert(m_layers.begin() + m_layerInsertIndex, std::move(layer));
    (*it)->onAttach();

    m_layerInsertIndex++;
}

//--------------------------------------------------------------------------------------------------
void LayerStack::pushOverlay(std::unique_ptr<Layer> overlay)
{
    m_layers.push_back(std::move(overlay));
    m_layers.back()->onAttach();
}

//--------------------------------------------------------------------------------------------------
void LayerStack::popLayer(Layer *layer)
{
    auto it = std::find_if(
        m_layers.begin(),
        m_layers.begin() + m_layerInsertIndex,
        [layer](const auto &currLayer) { return currLayer.get() == layer; });
    AN_ASSERT(it != m_layers.end(), "Layer is not on the stack.");

    layer->onDetach();
    m_layers.erase(it);
    m_layerInsertIndex--;
}

//--------------------------------------------------------------------------------------------------
void LayerStack::popOverlay(Layer *overlay)
{
    auto it = std::find_if(
        m_layers.begin() + m_layerInsertIndex,
        m_layers.end(),
        [overlay](const auto &currOverlay) { return currOverlay.get() == overlay; });
    AN_ASSERT(it != m_layers.end(), "Ovelay is not on the stack.");

    overlay->onDetach();
    m_layers.erase(it);
}
