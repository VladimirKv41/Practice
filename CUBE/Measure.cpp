#include "Measure.h"

Measure::Measure(const std::string& a_name) : m_name(a_name) {
	
}

// ��������� �������� �������
const std::string& Measure::get_name() const {
	return m_name;
}



