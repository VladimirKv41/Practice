#include "Fact.h"
#include "Measure.h"

Fact::Fact(double a_value,Measure* a_mes) : m_value(a_value), m_mes(a_mes) {
	
}

// Добавление связанной ТочкиДанных
void Fact::push_DataPoint(DataPoint* a_point) {
	m_points.push_back(a_point);
}

// Получение вектора связанных ТочекДанных
const std::vector<DataPoint*>& Fact::get_DataPoints() const {
	return m_points;
}

// Получение значения Факта
double Fact::get_value() const {
	return m_value;
}

// Получение названия Метрики Факта
const std::string& Fact::get_Measure_name() const {
	return m_mes->get_name();
}

// Получение связанной Метрики
const Measure* const Fact::get_Measure() const {
	return m_mes;
}