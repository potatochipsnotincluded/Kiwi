#pragma once
#include "Common.h"

namespace Kiwi {

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using WeakRef = std::weak_ptr<T>;

}

using Kiwi::Ref;

using Kiwi::WeakRef;