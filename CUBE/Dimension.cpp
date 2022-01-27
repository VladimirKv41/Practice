#include "Dimension.h"

Dimension::Dimension(const std::string &a_name) : m_name(a_name) {
	
}

// Добавление связанной ТочкиДанных
void Dimension::push_DataPoint(DataPoint* a_point) {
	m_points.push_back(a_point);
}

// Получение вектора связанных ТочекДанных
const std::vector<DataPoint*>& Dimension::get_DataPoints() const {
	return m_points;
}

// Получение индекса позиции в Измерении
//                                   Позиция
uint32_t Dimension::get_mark(const std::string &a_mark) {
	// Если позиция не существует, то сначала создаётся
	if (std::find(m_vector.begin(), m_vector.end(), a_mark) == m_vector.end()) {
		m_vector.push_back(a_mark);
		return m_vector.end() - m_vector.begin() - 1;
	}
	else 
		return std::find(m_vector.begin(), m_vector.end(), a_mark) - m_vector.begin();
}

// Поиск позиции в Измерении
bool Dimension::search_mark(const std::string &a_mark) const {
	if (std::find(m_vector.begin(), m_vector.end(), a_mark) == m_vector.end()) {
		return false;
	}
	else
		return true;
}

// Получение названия Измерения
const std::string& Dimension::get_name() const {
	return m_name;
}

// Получение вектора позиций Измерения
const std::vector<std::string>& Dimension::get_positions() const {
	return m_vector;
}