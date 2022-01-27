#pragma once
#include <string>

class Dimension;
class Fact;

// �����������
class DataPoint {
public:
	DataPoint(Fact* a_fact, Dimension* a_dim, uint32_t a_position);

	// ��������� ���������� ���������
	const Dimension* const get_Dimension() const;

	// ��������� ���������� �����
	const Fact* const get_Fact() const;

	// ��������� ������� � ��������� ���������
	const std::string& get_dim_position_name() const;

	// ��������� ������� ������� � ��������� ���������
	uint32_t get_dim_position_index() const;
	
private:
	// ��������� ����/���������
	Fact* m_fact;
	Dimension* m_dim;
	// ������ ������� � ��������� ���������
	uint32_t m_position_index;
};