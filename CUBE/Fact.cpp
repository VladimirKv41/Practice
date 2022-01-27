#include "Fact.h"
#include "Measure.h"

Fact::Fact(double a_value,Measure* a_mes) : m_value(a_value), m_mes(a_mes) {
	
}

// ���������� ��������� �����������
void Fact::push_DataPoint(DataPoint* a_point) {
	m_points.push_back(a_point);
}

// ��������� ������� ��������� �����������
const std::vector<DataPoint*>& Fact::get_DataPoints() const {
	return m_points;
}

// ��������� �������� �����
double Fact::get_value() const {
	return m_value;
}

// ��������� �������� ������� �����
const std::string& Fact::get_Measure_name() const {
	return m_mes->get_name();
}

// ��������� ��������� �������
const Measure* const Fact::get_Measure() const {
	return m_mes;
}