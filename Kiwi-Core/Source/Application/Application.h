#pragma once

namespace Kiwi {

	class Application
	{
	public:
		virtual ~Application() {};

		// If the bool returns false, then we should restart the app.
		virtual bool Run() = 0;
	};

}