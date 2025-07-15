#pragma once
#include "Common.h"

namespace Kiwi {

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using WeakRef = std::weak_ptr<T>;

	template <typename T, typename... Args>
	Ref<T> MakeRef(Args&&... args);

}

using Kiwi::Ref;

using Kiwi::WeakRef;

using Kiwi::MakeRef;

#include "Pointers.inl"