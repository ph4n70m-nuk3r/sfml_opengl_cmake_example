#include "../include/graphics_settings.hpp"

sf::VideoMode
get_video_mode()
	{
	    sf::VideoMode vm;
	    vm.width = 1080;
		vm.height = 720;
		vm.bitsPerPixel = 32;
	
		return vm;
	}

sf::ContextSettings
get_context_settings()
	{
	    sf::ContextSettings cs;
		cs.depthBits = 24;
		cs.stencilBits = 8;
		cs.majorVersion = 4;
		cs.minorVersion = 5;
		cs.attributeFlags = sf::ContextSettings::Core;
	
	    return cs;
	}

