#include "Selection.h"
#include "DataPoint.h"
#include "Cube.h"
#include "Dimension.h"
#include "Fact.h"
#include "Measure.h"
#include <iostream>
#include <map>

enum make_result {
	CUBE_DELETED = -2,
	UNKNOWN_DIMENSION,
	FACT_NOT_FOUND,
	ADDED
};



Selection::Selection(Cube* a_cube): m_cube(a_cube), m_aggregation_dim(new Dimension("���������")) {
	m_cube->m_selection = this;
}

// �������� �������
// 1. �������� �� ����������, ������� ��������� ������ �� ������ ���������� ���������
// 2. ��������� ������ �� �����������, �� ������ ������� ������������ �������.
// 3. �������� �� ������������ �� �������, ���� ������� � ��������� � ������� ��������� � ����������,
// �� � ������� ����������� ��� �����������, ��������� � ��� �� ������.
// 4. ������� ��������, � ����������� �� ����������.
//                           �������� ���������          ������ ������� � ���������                             ������ ������
int8_t Selection::make(const std::string& a_dim_name, const std::vector<std::string>& a_positions_list, const std::vector<std::string>& a_measure_list) {
	// ��������, ���������� �� ���
	if (m_aggregation_dim == nullptr)
		return CUBE_DELETED;
	for (std::vector<Dimension*>::const_iterator it_dim = m_cube->m_dims.begin(); it_dim != m_cube->m_dims.end(); it_dim++) {
		// ��������, ��������� �� ��������� � ���������
		if ((*it_dim)->get_name() == a_dim_name) {
			std::vector<DataPoint*> dpoint_vector;
			// ���� ������� ��� ���������, �� ����� ������� ������������ �� ��� ��������� �����������
			if (m_selection_points.size()) {
				dpoint_vector = m_selection_points;
				m_selection_points.clear();
			}
			// ���� �� ���������, �� ������� ��� ����������� ���������� ���������
			else
				dpoint_vector = (*it_dim)->get_DataPoints();
			// �������� �� ������������ �� �������
			for (std::vector<DataPoint*>::const_iterator it_dpoint = dpoint_vector.begin(); it_dpoint != dpoint_vector.end(); it_dpoint++) {
				for (std::vector<std::string>::const_iterator it_list = a_positions_list.begin(); it_list != a_positions_list.end(); it_list++) {
					if ((*it_dpoint)->get_dim_position_name() == (*it_list)) {
						// ���� ������� �� �������, �� ����������� ��� �����������
						if (!a_measure_list.size() || std::find(a_measure_list.begin(), a_measure_list.end(), (*it_dpoint)->get_Fact()->get_Measure_name()) != a_measure_list.end()) {
							m_selection_points.insert(std::end(m_selection_points), std::begin((*it_dpoint)->get_Fact()->get_DataPoints()), std::end((*it_dpoint)->get_Fact()->get_DataPoints()));
							break;
						}
					}
				}
			}
			if (m_selection_points.size())
				return ADDED;
			else
				return FACT_NOT_FOUND;
		}
	}
	return UNKNOWN_DIMENSION;
}

// ����� ���������
//                            ��� ���������       �������� ���������                       ������ ������
bool Selection::aggregation(agg_type a_agg_type, const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list) {
	switch (a_agg_type) {
		case agg_type::COUNT:
			count(a_dimension_name, a_measure_list);
			return true;
		case agg_type::SUM:
			sum(a_dimension_name, a_measure_list);
			return true;
		case agg_type::AVERAGE:
			average(a_dimension_name, a_measure_list);
			return true;
		default:
			return false;
	}
}

// ����� �������
void Selection::print() const {
	uint32_t counter = 0;
	// ����� ����������� �� ������ ����
	for (std::vector<DataPoint*>::const_iterator it_dpoint = m_selection_points.begin(); it_dpoint != m_selection_points.end(); it_dpoint++) {
		std::cout << (*it_dpoint)->get_dim_position_name() << " | ";
		counter++;
		if (counter == m_cube->m_dims.size() ) {
			counter = 0;
			std::cout << (*it_dpoint)->get_Fact()->get_Measure_name() << " " << (*it_dpoint)->get_Fact()->get_value() << std::endl;
		}
	}
	counter = 0;
	// ����� ����������� �� ������ ����������
	for (std::vector<DataPoint*>::const_iterator it_dpoint = m_aggregation_points.begin(); it_dpoint != m_aggregation_points.end(); it_dpoint++) {
		std::cout << (*it_dpoint)->get_dim_position_name() << " | ";
		if (counter == m_cube->m_dims.size()-1) {
			counter = 0;
			std::cout << (*it_dpoint)->get_Fact()->get_Measure_name() << " " << (*it_dpoint)->get_Fact()->get_value() << std::endl;
			continue;
		}
		counter++;
	}
	std::cout << std::endl;
}

// ������� �������
void Selection::clean() {
	if (m_aggregation_dim != nullptr) {
		delete m_aggregation_dim;
		m_aggregation_dim = nullptr;
		m_selection_points.resize(0);
		m_cube->clean_vector(m_aggregation_facts);
		m_cube->clean_vector(m_aggregation_measures);
		m_cube->clean_vector(m_aggregation_points);
	}
}

Selection::~Selection() {
	clean();
	// ��������� ����, ��� ������� ������ �� ����������
	m_cube->m_selection = nullptr;
}

// ��������� - ����������
// 1. �������� �� ��������, ������������ ������ ���������, ���� �� �������, �� �� ����.
// 2. �������� �������������� ����������(map): ���� - ������ �� �����, ��� ����� - ������ ������� � ���������; �������� - ����������.
// 3. �������� �� ������������ ������� � ���������� map-����������.
// 4. �������� �� ����������� map-���������� � �������� ����� ����������� � ������ � ���.
//                                    �������� ���������                        ������ ������
void Selection::count(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list) {
	for (std::vector<Measure*>::const_iterator it_measure = m_cube->m_measures.begin(); it_measure != m_cube->m_measures.end(); it_measure++) {
		// ��������, ������� �� ������ �������
		if (!a_measure_list.size() || std::find(a_measure_list.begin(), a_measure_list.end(), (*it_measure)->get_name()) != a_measure_list.end()) {
			uint8_t counter = 0;
			// ������ ������� �� 1 ������ ���������� ���������, �.�. � ������������� ��������� ����� ����������� ����� �����������
			std::vector<uint32_t> temp_vector(m_cube->m_dims.size() - 1);
			std::map<std::vector<uint32_t>, uint32_t> temp_map;
			// ���������� map-����������
			for (std::vector<DataPoint*>::iterator it_dpoint = m_selection_points.begin(); it_dpoint != m_selection_points.end(); it_dpoint++) {
				if ((*it_dpoint)->get_Fact()->get_Measure() == *it_measure) {
					// ���������� �����-�������
					if ((*it_dpoint)->get_Dimension()->get_name() != a_dimension_name) {
						temp_vector.at(counter) = (*it_dpoint)->get_dim_position_index();
						counter++;
					}
					// ������� ����������
					if (counter == m_cube->m_dims.size() - 1) {
						temp_map[temp_vector]++;
						counter = 0;
					}
				}
			}
			// ��������� ������� ������� ����������
			uint8_t meas_index = std::find_if(m_aggregation_measures.begin(), m_aggregation_measures.end(), [](const Measure* m) { return (m->get_name() == "����������"); }) - m_aggregation_measures.begin();
			if (meas_index == m_aggregation_measures.size()) {
				m_aggregation_measures.push_back(new Measure("����������"));
			}
			// C������� ������ � �����������
			for (std::map<std::vector<uint32_t>, uint32_t>::iterator it_map = temp_map.begin(); it_map != temp_map.end(); it_map++) {
				m_aggregation_facts.push_back(new Fact(it_map->second, m_aggregation_measures.at(meas_index)));
				counter = 0;
				for (std::vector<Dimension*>::const_iterator it_dim = m_cube->m_dims.begin(); it_dim != m_cube->m_dims.end(); it_dim++) {
					if ((*it_dim)->get_name() != a_dimension_name) {
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), *it_dim, it_map->first.at(counter)));
						counter++;
					}
					else {
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), m_aggregation_dim,
							m_aggregation_dim->get_mark("COUNT(" + m_cube->m_dims.at(it_dim - m_cube->m_dims.begin())->get_name() + ")")));
					}

				}
			}
		}
	}
};

// ��������� - ������������
// 1. �������� �� ��������, ������������ ������ ���������, ���� �� �������, �� �� ����.
// 2. �������� �������������� ����������(map): ���� - ������ �� �����, ��� ����� - ������ ������� � ���������; �������� - �����.
// 3. �������� �� ������������ ������� � ���������� map-����������.
// 4. �������� �� ����������� map-���������� � �������� ����� ����������� � ������ � ���.
//                                    �������� ���������                        ������ ������
void Selection::sum(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list) {
	for (std::vector<Measure*>::const_iterator it_measure = m_cube->m_measures.begin(); it_measure != m_cube->m_measures.end(); it_measure++) {
		// ��������, ������� �� ������ �������
		if (!a_measure_list.size() || std::find(a_measure_list.begin(), a_measure_list.end(), (*it_measure)->get_name()) != a_measure_list.end()) {
			uint32_t counter = 0;
			// ������ ������� �� 1 ������ ���������� ���������, �.�. � ������������� ��������� ����� ����������� ����� �����������
			std::vector<uint32_t> temp_vector(m_cube->m_dims.size() - 1);
			std::map<std::vector<uint32_t>, double> temp_map;
			// ���������� map-����������
			for (std::vector<DataPoint*>::iterator it_dpoint = m_selection_points.begin(); it_dpoint != m_selection_points.end(); it_dpoint++) {
				if ((*it_dpoint)->get_Fact()->get_Measure() == *it_measure) {
					// ���������� �����-�������
					if ((*it_dpoint)->get_Dimension()->get_name() != a_dimension_name) {
						temp_vector.at(counter) = (*it_dpoint)->get_dim_position_index();
						counter++;
					}
					// ������������
					if (counter == m_cube->m_dims.size() - 1) {
						temp_map[temp_vector] += (*it_dpoint)->get_Fact()->get_value();
						counter = 0;
					}
				}
			}
			// C������� ������ � �����������
			for (std::map<std::vector<uint32_t>, double>::iterator it_map = temp_map.begin(); it_map != temp_map.end(); it_map++) {
				m_aggregation_facts.push_back(new Fact(it_map->second, *it_measure));
				counter = 0;
				for (std::vector<Dimension*>::const_iterator it_dim = m_cube->m_dims.begin(); it_dim != m_cube->m_dims.end(); it_dim++) {
					if ((*it_dim)->get_name() != a_dimension_name) {
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), *it_dim, it_map->first.at(counter)));
						counter++;
					}
					else
					{
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), m_aggregation_dim,
							m_aggregation_dim->get_mark("SUM(" + m_cube->m_dims.at(it_dim - m_cube->m_dims.begin())->get_name() + ")")));
					}
				}
			}
		}
	}
};

// ��������� - ������� ��������
// 1. �������� �� ��������, ������������ ������ ���������, ���� �� �������, �� �� ����.
// 2. �������� �������������� ����������(map): ���� - ������ �� �����, ��� ����� - ������ ������� � ���������; �������� - ����, ���
// ������ ����� - �����, ������ - ����������.
// 3. �������� �� ������������ ������� � ���������� map-����������.
// 4. �������� �� ����������� map-���������� � �������� ����� ����������� � ������ � ���.
//                                    �������� ���������                        ������ ������
void Selection::average(const std::string& a_dimension_name, const std::vector<std::string>& a_measure_list) {
	for (std::vector<Measure*>::const_iterator it_measure = m_cube->m_measures.begin(); it_measure != m_cube->m_measures.end(); it_measure++) {
		// ��������, ������� �� ������ �������
		if (!a_measure_list.size() || std::find(a_measure_list.begin(), a_measure_list.end(), (*it_measure)->get_name()) != a_measure_list.end()) {
			uint32_t counter = 0;
			// ������ ������� �� 1 ������ ���������� ���������, �.�. � ������������� ��������� ����� ����������� ����� �����������
			std::vector<uint32_t> temp_vector(m_cube->m_dims.size() - 1);
			std::map<std::vector<uint32_t>, std::pair<double, uint32_t>> temp_map;
			// ���������� map-����������
			for (std::vector<DataPoint*>::iterator it_dpoint = m_selection_points.begin(); it_dpoint != m_selection_points.end(); it_dpoint++) {
				if ((*it_dpoint)->get_Fact()->get_Measure() == *it_measure) {
					// ���������� �����-�������
					if ((*it_dpoint)->get_Dimension()->get_name() != a_dimension_name) {
						temp_vector.at(counter) = (*it_dpoint)->get_dim_position_index();
						counter++;
					}
					// ������������ � ������� ����������
					if (counter == m_cube->m_dims.size() - 1) {
						temp_map[temp_vector].first += (*it_dpoint)->get_Fact()->get_value();
						temp_map[temp_vector].second++;
						counter = 0;
					}
				}
			}
			// C������� ������ � �����������
			for (std::map<std::vector<uint32_t>, std::pair<double, uint32_t>>::iterator it_map = temp_map.begin(); it_map != temp_map.end(); it_map++) {
				m_aggregation_facts.push_back(new Fact(it_map->second.first / it_map->second.second, *it_measure));
				counter = 0;
				for (std::vector<Dimension*>::const_iterator it_dim = m_cube->m_dims.begin(); it_dim != m_cube->m_dims.end(); it_dim++) {
					if ((*it_dim)->get_name() != a_dimension_name) {
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), *it_dim, it_map->first.at(counter)));
						counter++;
					}
					else {
						m_aggregation_points.push_back(new DataPoint(m_aggregation_facts.back(), m_aggregation_dim,
							m_aggregation_dim->get_mark("AVERAGE(" + m_cube->m_dims.at(it_dim - m_cube->m_dims.begin())->get_name() + ")")));
					}
				}
			}
		}

	}
};