#include "DataPoint.h"
#include "Fact.h"
#include "Dimension.h"

DataPoint::DataPoint(Fact* a_fact, Dimension* a_dim, uint32_t a_position_index) : m_fact(a_fact), m_dim(a_dim), m_position_index(a_position_index) {
	// ��� ������ �� ��� ����������� ����� � ���������, ��������� � ���� ������������
	m_fact->push_DataPoint(this);
	m_dim->push_DataPoint(this);
}	

// ��������� ���������
const Dimension* const DataPoint::get_Dimension() const {
	return m_dim;
}

// ��������� �����
const Fact* const DataPoint::get_Fact() const {
	return m_fact;
}

// ��������� ������� � ��������� ���������
const std::string& DataPoint::get_dim_position_name() const {
	return m_dim->get_positions().at(m_position_index);
}

// ��������� ������� ������� � ��������� ���������
uint32_t DataPoint::get_dim_position_index() const {
	return m_position_index;
}
