#pragma once
#include <string>

// �������
class Measure {
public:

	Measure(const std::string &a_name);

	// ��������� �������� �������
	const std::string& get_name() const;

private:
	// �������� �������
	std::string m_name;
};