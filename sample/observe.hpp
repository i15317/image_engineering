#pragma once
#include <vector>
#include<string>

namespace Observer {
	// private base class
	template <class T>
	class ObserverBase {
	private:
		virtual bool shouldNotify(const std::string& key) = 0;
		virtual void update(T* sender, const std::string& key) = 0;

		template <class F>
		friend class observable;
	};

	// Observer
	template <class T, const std::string&... keys>
	class Observer : public ObserverBase<T> {
	public:
		virtual void update(T* sender, const std::string& key) = 0;

	private:
		std::vector<std::string> observeKeys = { keys... };
		bool shouldNotify(const std::string& key) {
			return (std::find(observeKeys.begin(), observeKeys.end(), key) != observeKeys.end());
		}
	};

	// observable
	template <class T>
	class observable {
	public:
		void addObserver(ObserverBase<T> *Observer) {
			m_Observers.push_back(Observer);
		}

		void removeObserver(ObserverBase<T> *Observer) {
			auto it = std::find(m_Observers.begin(), m_Observers.end(), Observer);
			if (it != m_Observers.end())
				m_Observers.erase(it);
		}

		void notify(const std::string& key) {
			for (const auto& o : m_Observers) {
				if (o->shouldNotify(key))
					o->update(static_cast<T*>(this), key);
			}
		}

	private:
		std::vector<ObserverBase<T>*> m_Observers;
	};
}

