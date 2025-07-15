#pragma once
#include "Common.h"

namespace Kiwi {

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using WeakRef = std::weak_ptr<T>;

	template <typename T>
	Ref<T> MakeRef();

}

using Kiwi::Ref;

using Kiwi::WeakRef;

using Kiwi::MakeRef;

#include "Pointers.inl"