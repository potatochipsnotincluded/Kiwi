#pragma once

namespace Kiwi {

	class Application
	{
	public:
		virtual ~Application() = default;

		// If the bool returns false, then we should restart the app.
		virtual bool Run() = 0;
	};

}