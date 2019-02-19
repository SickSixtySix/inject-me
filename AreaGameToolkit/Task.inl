namespace priv
{
	class Function
	{
	public:

		virtual void Invoke() = 0;
	};

	template<typename F> class FreeFunction : public Function
	{
		F m_function;

	public:

		FreeFunction(F function) : m_function(function) {}

		void Invoke() final
		{
			m_function();
		}
	};

	template<typename C> class MemberFunction : public Function
	{
		void(C::*m_function)();

		C *m_object;

	public:

		MemberFunction(void(C::*function)(), C *object) : m_function(function), m_object(object) {}

		void Invoke() final
		{
			(m_object->*m_function)();
		}
	};
}

template<typename F> Task::Task(F function, sf::Time delay) : m_function(new priv::FreeFunction(function)), m_delay(delay) {}

template<typename C> Task::Task(void(C::*function)(), C *object, sf::Time delay) : m_function(new priv::MemberFunction(function, object)), m_delay(delay) {}