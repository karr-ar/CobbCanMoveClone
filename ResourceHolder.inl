#pragma once

//load function definition
template<typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::load - Failed to Load " + filename);
	}
	assert(mResourceMap.find(id) == mResourceMap.end() && "Resource ID already exists!");
	mResourceMap[id] = std::move(resource);
}
//get function definition
template<typename Identifier, typename Resource>
Resource& ResourceHolder <Identifier, Resource>::get(Identifier id) {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end() && "Resource ID does not exist!");
	return *found->second; // Access via iterator is slightly faster
}
template<typename Identifier, typename Resource>
const Resource& ResourceHolder <Identifier, Resource>::get(Identifier id) const {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end() && "Resource ID does not exist!");
	return *found->second;
}
