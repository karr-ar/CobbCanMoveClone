#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <cassert>
//class
template<typename Identifier, typename Resource>
class ResourceHolder {
public:
	void load(Identifier id,
		const std::string& filename);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
private:
	std::unordered_map <Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"