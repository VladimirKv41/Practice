#pragma once
#include <string>

// Метрика
class Measure {
public:

	Measure(const std::string &a_name);

	// Получение название Метрики
	const std::string& get_name() const;

private:
	// Название Метрики
	std::string m_name;
};