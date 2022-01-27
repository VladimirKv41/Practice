#pragma once
#include <string>
#include <vector>

class DataPoint;

// ���������
class Dimension {
public:

	Dimension(const std::string &a_name);

	// ���������� ��������� �����������
	void push_DataPoint(DataPoint* a_point);

	// ��������� ������� ��������� �����������
	const std::vector<DataPoint*>& get_DataPoints() const;

	// ��������� ������� ������� � ���������
	uint32_t get_mark(const std::string &a_mark);

	// ����� ������� � ���������
	bool search_mark(const std::string &a_mark) const;

	// ��������� �������� ���������
	const std::string& get_name() const;

	// ��������� ������� ������� ���������
	const std::vector<std::string>& get_positions() const;
	
private:
	// ������ ������� ���������
	std::vector<std::string> m_vector;
	// �������� ���������
	std::string m_name;
	// ������ ��������� �����������
	std::vector<DataPoint*> m_points;
};