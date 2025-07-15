namespace Kiwi {

	template<typename T>
	Ref<T> MakeRef()
	{
		return std::make_shared<T>();
	}

}
