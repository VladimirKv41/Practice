#pragma once
#include <string>
#include <vector>

class Dimension;
class Fact;
class Measure;
class DataPoint;
class Selection;

// ���
class Cube{
public:

	friend Selection;

	Cube();

	// ���������� ���������
	bool add_Dimension(const std::string& a_dim_name);

	// ���������� �������
	bool add_Measure(const std::string& a_measure_name);

	// ���������� �����
	int8_t add_Fact(double a_value, const std::string& a_measure, const std::vector<std::string>& a_positions_list);

    // ������� ����
	void clean();
	
	~Cube();

private:

	// ������� ������� ����������
	template <class T>
	void clean_vector(std::vector<T*>& a_vector);

	// ������� ������/���������/������/����������� ����
	std::vector<Fact*> m_facts;
	std::vector<Dimension*> m_dims;
	std::vector<Measure*> m_measures;
	std::vector<DataPoint*> m_points;
	// ��������� �������
	Selection* m_selection;
};