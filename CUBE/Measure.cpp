#include "Measure.h"

Measure::Measure(const std::string& a_name) : m_name(a_name) {
	
}

// Получение название Метрики
const std::string& Measure::get_name() const {
	return m_name;
}



