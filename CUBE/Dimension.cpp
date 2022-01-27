#include "Dimension.h"

Dimension::Dimension(const std::string &a_name) : m_name(a_name) {
	
}

// ���������� ��������� �����������
void Dimension::push_DataPoint(DataPoint* a_point) {
	m_points.push_back(a_point);
}

// ��������� ������� ��������� �����������
const std::vector<DataPoint*>& Dimension::get_DataPoints() const {
	return m_points;
}

// ��������� ������� ������� � ���������
//                                   �������
uint32_t Dimension::get_mark(const std::string &a_mark) {
	// ���� ������� �� ����������, �� ������� ��������
	if (std::find(m_vector.begin(), m_vector.end(), a_mark) == m_vector.end()) {
		m_vector.push_back(a_mark);
		return m_vector.end() - m_vector.begin() - 1;
	}
	else 
		return std::find(m_vector.begin(), m_vector.end(), a_mark) - m_vector.begin();
}

// ����� ������� � ���������
bool Dimension::search_mark(const std::string &a_mark) const {
	if (std::find(m_vector.begin(), m_vector.end(), a_mark) == m_vector.end()) {
		return false;
	}
	else
		return true;
}

// ��������� �������� ���������
const std::string& Dimension::get_name() const {
	return m_name;
}

// ��������� ������� ������� ���������
const std::vector<std::string>& Dimension::get_positions() const {
	return m_vector;
}