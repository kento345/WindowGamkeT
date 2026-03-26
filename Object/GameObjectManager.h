#pragma once

#include"GameObject.h"
#include<functional>

namespace game {

	class GameObjectManager final
	{
    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	インスタンスの取得
         * @return	インスタンスの参照
         */
        static GameObjectManager& instance() noexcept {
            static GameObjectManager instance;
            return instance;
        }

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの更新
         */
        void update() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの後更新
         */
        void postUpdate() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトの描画
         * @param	commandList	コマンドリスト
         */
        void draw(const CommandList& commandList) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	管理オブジェクトのクリア
         */
        void clear() noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト取得
         * @param	handle	オブジェクトハンドル
         * @return	オブジェクトのポインタ(存在しない場合はnullopt)
         */
        [[nodiscard]] std::optional<GameObject*> gameObject(UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	衝突判定オブジェクトを登録
         * @param	handle	衝突オブジェクトハンドル
         */
        void registerHit(UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト削除登録
         * @param	handle	削除オブジェクトハンドル
         */
        void registerDelete(UINT64 handle) noexcept;

    public:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト生成
         * @tparam	T		生成するオブジェクトの型
         * @tparam	Args	コンストラクタ引数の型
         * @param	args	コンストラクタ引数（複数の引数を渡せるように）
         * @return	生成したオブジェクトのハンドル
         */
        template <typename T, typename... Args>
        [[nodiscard]] UINT64 createObject(Args&&... args) noexcept {
            static_assert(std::is_base_of<GameObject, T>::value, "GameObject ではない物を作ろうとしています");
            const auto handle = ++counter_;

            // パラメータパックをラムダ式のキャプチャに渡す
            // a には「コピー or ムーブ」のどちらかの方法で args がキャプチャされる
            // args のインスタンスがそのまま渡されるのではなく、a という別インスタンスとして生まれている点に注意
            auto func = [... a = std::forward<Args>(args)]() mutable {
                // パラメータパックをムーブで展開してコンストラクタ引数にして T を生成
                // つまり T の生成では必ず T のムーブコンストラクタを呼ぼうとする
                // ムーブコンストラクタが無い場合はコピーコンストラクタが呼ばれる
                // 元の引数の種類に合わせてムーブコンストラクタとコピーコンストラクタを呼び分けられるわけではない点に注意
                auto p = std::make_unique<T>(std::move(a)...);
                p->setTypeId(id::get<T>());
                return p;
                };

            // 渡された引数をキャプチャしたラムダ式を登録してオブジェクト生成を遅延させる
            // テンプレートやパラメータパック、ムーブ、完全転送、関数オブジェクトなどの例でこの様な実装にしている
            // ただ「可変長引数を受け取って、引数型に合わせてインスタンスを生成する」事は本来もっとシンプルに実装できる
            registerCreation(std::move(func), handle);

            return handle;
        }

    private:
        //---------------------------------------------------------------------------------
        /**
         * @brief	オブジェクト生成
         * @param	creation	生成関数
         * @param	handle		オブジェクトハンドル
         */
        void registerCreation(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept;

        //---------------------------------------------------------------------------------
        /**
         * @brief 登録済みの削除オブジェクトを削除待ちリストに反映する
         */
        void registerWaitDelete() noexcept;

    private:
        //---------------------------------------------------------------------------------
        /**
         * @brief    コンストラクタ
         */
        GameObjectManager() = default;

        //---------------------------------------------------------------------------------
        /**
         * @brief    デストラクタ
         */
        ~GameObjectManager();

        //---------------------------------------------------------------------------------
        /**
         * @brief	コピーとムーブの禁止
         */
        GameObjectManager(const GameObjectManager& r) = delete;
        GameObjectManager& operator=(const GameObjectManager& r) = delete;
        GameObjectManager(GameObjectManager&& r) = delete;
        GameObjectManager& operator=(GameObjectManager&& r) = delete;

    private:
        UINT64 counter_{};
	};
}

