#pragma once
#include <lole/shader_m.h>

class OlObject
{
public:
		OlObject();
		virtual void prepareRender();
		virtual void render();
		virtual void destroy();
		virtual bool operator==(const OlObject& other) const = default;
};
