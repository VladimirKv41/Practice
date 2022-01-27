#pragma once
#include <vector>
#include <string>

class DataPoint;
class Dimension;
class Cube;
class Fact;
class Measure;

enum class agg_type {
	COUNT,
	SUM,
	AVERAGE
};

// �������
class Selection {
public:

	Selection(Cube* a_cube);

	// �������� �������
	int8_t make(const std::string& a_dim_name, const std::vector<std::string>& a_positions_list, const std::vector<std::string>& a_measure_list = {});

	// ����� ���������
	bool aggregation(agg_type a_agg_type,const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list = {});

	// ����� �������
	void print() const;

	// ������� �������
	void clean();

	~Selection();

private:

	// ��������� - ������������
	void count(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);
	// ��������� - ����������
	void sum(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);
	// ��������� - ������� ��������
	void average(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list);

	// ����������� ����, �� ������� ������� �������
	std::vector<DataPoint*> m_selection_points;
	// �����������/�����/�������, ��������� �� ������ ���������
	std::vector<DataPoint*> m_aggregation_points;
	std::vector<Fact*> m_aggregation_facts;
	std::vector<Measure*> m_aggregation_measures;
	// ��������� ��� ���������
	Dimension* m_aggregation_dim;
	// ��������� ��� ��� �������� �������
	Cube* m_cube;
};