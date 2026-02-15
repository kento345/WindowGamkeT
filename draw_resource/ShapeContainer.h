#pragma once
#include"Shape.h"	
#include<unordered_map>
#include<memory>

class ShapeContainer final
{
public:
	static ShapeContainer& instance()noexcept
	{
		static ShapeContainer instance;
		return instance;
	}
public:

	template <class T>
	UINT64 create() noexcept
	{
		const auto id = id::get<T>();
		if (shapes_.find(id) != shapes_.end()) {
			return id;
		}
		auto p = std::make_unique<T>();
		if(!p -> create()) {
			assert(false && "Œ`ó‚Ì¶¬‚É¸”s‚µ‚Ü‚µ‚½");
			return 0;
		}
		shapes_.emplace(id, std::move(p));
		return id;
	}

	void draw(const command_list& commandlist, UINT64 id)noexcept;
	
private:
	ShapeContainer() = default;
	~ShapeContainer() = default;

	ShapeContainer(const ShapeContainer&) = delete;
	ShapeContainer& operator=(const ShapeContainer&) = delete;
	ShapeContainer(ShapeContainer&&) = delete;
	ShapeContainer& operator=(ShapeContainer&&) = delete;
protected:
	std::unordered_map<UINT64, std::unique_ptr<Shape>> shapes_;
};

