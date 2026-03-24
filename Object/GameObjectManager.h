#pragma once

#include"GameObject.h"
#include<functional>

namespace game {

	class GameObjectManager final
	{
	public:	
		static GameObjectManager& getInstance()noexcept {
			static GameObjectManager instance;
			return instance;
		}
	public:
		void update()noexcept;

		void postUpdate()noexcept;
		
		void draw(const CommandList& commandList)noexcept;

		void clear()noexcept;

		std::optional<GameObject*> gameObject(UINT64 handle)noexcept;

		void registerDelete(UINT64 handle)noexcept;

	public:

		template <typename T, typename... Args>
		UINT64 createObject(Args&&... args)noexcept {
			static_assert(std::is_base_of<GameObject, T>::value, "GameObjectÅ@Ç≈ÇÕÇ»Ç¢ï®ÇçÏÇÎÇ§Ç∆ÇµÇƒÇ¢Ç‹Ç∑");
			const auto handle = nextHandle_++;

			auto func = [...a = std::forward<Args>(args)]() mutable {
				auto p = std::make_unique<T>(std::move(a)...);
				p->setTypeId(id::get<T>());
				return p;
			};

			registerCreate(std::move(func),handle);

			return handle;
		}

	private:

		void registerCreate(std::function<std::unique_ptr<GameObject>()> create , const UINT64 handle)noexcept;
	
		void registerWaitDelete()noexcept;

	private:

		GameObjectManager() = default;

		~GameObjectManager();

		GameObjectManager(const GameObjectManager&) = delete;
		GameObjectManager& operator=(const GameObjectManager& r) = delete;
		GameObjectManager(GameObjectManager&& r) = delete;
		GameObjectManager& operator=(GameObjectManager&& r) = delete;

	private:
		UINT64 counter_{};
	};
}

